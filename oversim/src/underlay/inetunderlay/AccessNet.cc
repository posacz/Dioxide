//
// Copyright (C) 2006 Institut fuer Telematik, Universitaet Karlsruhe (TH)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//

/**
 * @file AccessNet.cc
 * @author Markus Mauch
 */

#include <vector>
#include <iostream>

#include "common/OverSimDefs.h"

#include "inet/networklayer/ipv4/IIPv4RoutingTable.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/ipv6/IPv6RoutingTable.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"
#include "inet/networklayer/ipv6/IPv6InterfaceData.h"

#include "underlay/inetunderlay/AccessNet.h"

Define_Module(AccessNet);

std::ostream& operator<<(std::ostream& os, NodeInfo& n)
{
    os << n.ipvxAddress;
    return os;
}

void AccessNet::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL) {
        useIPv6 = par("useIPv6Addresses").boolValue();
    }
    else if (stage == INITSTAGE_NETWORK_LAYER) {
        router.module = getParentModule();
        router.interfaceTable = L3AddressResolver().interfaceTableOf(getParentModule());
    }
    else if (stage == INITSTAGE_NETWORK_LAYER_3) {
        if (useIPv6){
            router.routingTable6 = L3AddressResolver().routingTable6Of(getParentModule());
            router.ipvxAddress = getAssignedPrefix(router.interfaceTable);
        } else {
            router.routingTable = L3AddressResolver().routingTableOf(getParentModule());
            router.ipvxAddress = L3AddressResolver().addressOf(getParentModule());
            router.ipvxAddress = L3AddressResolver().addressOf(getParentModule(), L3AddressResolver::ADDR_IPv4);
        }
        channelTypesTx = cStringTokenizer(par("channelTypes"), " ").asVector();
        channelTypesRx = cStringTokenizer(par("channelTypesRx"), " ").asVector();

        if (channelTypesRx.size() != channelTypesTx.size()) {
            channelTypesRx = channelTypesTx;
        }

        int chanIndex = intuniform(0, channelTypesTx.size()-1);

        selectChannel(channelTypesRx[chanIndex], channelTypesTx[chanIndex]);

        // statistics
        lifetimeVector.setName("Terminal Lifetime");

        WATCH_VECTOR(overlayTerminal);

        lastIP = 0;

        updateDisplayString();
    }
}

void AccessNet::handleMessage(cMessage* msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}

L3Address AccessNet::addOverlayNode(cModule* node, bool migrate)
{
    Enter_Method("addOverlayNode()");

    TerminalInfo terminal;
    terminal.module = node;
    terminal.interfaceTable = L3AddressResolver().interfaceTableOf(node);
    terminal.remoteInterfaceTable = router.interfaceTable;
    if (useIPv6) {
        terminal.routingTable6 = L3AddressResolver().routingTable6Of(node);
    }
    else {
        terminal.routingTable = L3AddressResolver().routingTableOf(node);
    }
    terminal.PPPInterface = node->getSubmodule("ppp", 0);
    terminal.createdAt = simTime();

    // find unassigned ip address:
    // check list of returned IPs
    // TODO: check overlays for side effects of reused IP addresses
//    if (returnedIPs.size() != 0) {
//      terminal.IPv4Address = returnedIPs.back();
//      returnedIPs.pop_back();
//    }
//    else {
    if (useIPv6) {
        IPv6Words candidate(router.ipvxAddress);
        // we dont need to check for duplicates because of the giant address space and reuse of old IPs
        candidate.d1 += ++lastIP;
        terminal.ipvxAddress = L3Address(IPv6Address(candidate.d0, candidate.d1, candidate.d2, candidate.d3));
    } else {
        uint32_t routerAddr = router.ipvxAddress.toIPv4().getInt();

        // Start at last given address, check if next address is valid and free.
        bool ip_test = false;
        for (uint32_t ipOffset = lastIP + 1; ipOffset != lastIP; ipOffset++) {
            if ( ipOffset == 0x10000) {
                // Netmask = 255.255.0.0, so roll over if offset = 2**16
                ipOffset = 0;
                continue;
            }

            uint32_t ip = routerAddr + ipOffset;

            // Check if IP is valid:
            //   Reject x.y.z.0 or x.y.z.255 or x.y.255.z
            if ( ((ip & 0xff) == 0) || ((ip & 0xff) == 0xff)
                    || ((ip & 0xff00) == 0xff00) ) {
                continue;
            }

            // Check if IP is free
            ip_test = true;
            for (uint32_t i = 0; i < overlayTerminal.size(); i++) {
                if (overlayTerminal[i].ipvxAddress == L3Address(IPv4Address(ip))) {
                    ip_test = false;
                    break;
                }
            }

            // found valid IP
            if (ip_test) {
                terminal.ipvxAddress = L3Address(IPv4Address(ip));
                lastIP = ipOffset;
                break;
            }
        }
        if (!ip_test)
            throw cRuntimeError ("Error creating node: No available IP in access net!");
    }
//    }

    // update ip display string
    if (hasGUI()) {
        const char* ip_disp = const_cast<char*>
        (terminal.ipvxAddress.str().c_str());
        terminal.module->getDisplayString().insertTag("t", 0);
        terminal.module->getDisplayString().setTagArg("t", 0, ip_disp);
        terminal.module->getDisplayString().setTagArg("t", 1, "l");
    }


    //
    // Create new remote ppp interface module for this terminal
    //

    // create ppp interface module

    int k = 1;
    while ( router.module->findSubmodule("ppp", k) != -1 )
        k++;

    cModuleType* pppInterfaceModuleType = cModuleType::get("inet.linklayer.ppp.PPPInterface");
    terminal.remotePPPInterface = pppInterfaceModuleType->
    create("ppp", router.module, 0, k);


    //
    // Connect all gates
    //

    // connect terminal to access router and vice versa
    cGate* routerInGate = firstUnusedGate(router.module, "pppg", cGate::INPUT);
    cGate* routerOutGate = firstUnusedGate(router.module, "pppg", cGate::OUTPUT);

    cChannelType* channelTypeRx = cChannelType::find( channelTypeRxStr.c_str() );
    cChannelType* channelTypeTx = cChannelType::find( channelTypeTxStr.c_str() );
    if (!channelTypeRx || !channelTypeTx) 
        throw cRuntimeError("Could not find Channel or ChannelRx Type. Most likely "
            "parameter channelTypes does not match the channels defined "
            "in channels.ned");

    terminal.module->gate("pppg$o", 0)->connectTo(routerInGate,
                channelTypeRx->create(channelTypeRxStr.c_str()));
    routerOutGate->connectTo(terminal.module->gate("pppg$i", 0),
                 channelTypeTx->create(channelTypeTxStr.c_str()));

    // connect ppp interface module to router module and vice versa
    routerInGate->connectTo(terminal.remotePPPInterface->gate("phys$i"));
    terminal.remotePPPInterface->gate("phys$o")->connectTo(routerOutGate);

    // connect ppp interface module to network layer module and vice versa
    cModule* netwModule = router.module->getSubmodule("networkLayer");

    cGate* netwInGate = firstUnusedGate(netwModule, "ifIn");
    cGate* netwOutGate = firstUnusedGate(netwModule, "ifOut");

    netwOutGate->connectTo(terminal.remotePPPInterface->gate("upperLayerIn"));
    terminal.remotePPPInterface->gate("upperLayerOut")->connectTo(netwInGate);

    // connect network layer module to ip and arp modules
    cModule* ipModule;
    if (useIPv6) {
        ipModule = router.module->getSubmodule("networkLayer")->getSubmodule("ipv6");
    }
    else {
        ipModule = router.module->getSubmodule("networkLayer")->getSubmodule("ip");
    }

    cGate* ipIn = firstUnusedGate(ipModule, "queueIn");
    cGate* ipOut = firstUnusedGate(ipModule, "queueOut");
    netwInGate->connectTo(ipIn);
    ipOut->connectTo(netwOutGate);    //comment out for speed-hack

    //
    // Start ppp interface modules
    //
    terminal.remotePPPInterface->finalizeParameters();
    terminal.remotePPPInterface->setDisplayString("i=block/ifcard");
    terminal.remotePPPInterface->buildInside();
    terminal.remotePPPInterface->scheduleStart(simTime());
    terminal.remotePPPInterface->callInitialize();

    if (!migrate) {
        // we are already in stage 4 and need to call initialize
    // for all previous stages manually
        for (int i=0; i < MAX_STAGE_UNDERLAY + 1; i++) {
            terminal.module->callInitialize(i);
        }
    }

    terminal.remoteInterfaceEntry = router.interfaceTable->getInterface(
            router.interfaceTable->getNumInterfaces() - 1);
    terminal.interfaceEntry = terminal.interfaceTable->getInterfaceByName("ppp0");


    //
    // Fill in interface table and routing table.
    //

    if (useIPv6) {
        //
        // Fill in interface table.

        // router
        IPv6InterfaceData* interfaceData = new IPv6InterfaceData;
        interfaceData->setAdvSendAdvertisements(true); // router
        interfaceData->assignAddress(IPv6Address::formLinkLocalAddress(terminal.remoteInterfaceEntry->getInterfaceToken()), false, 0, 0);
        terminal.remoteInterfaceEntry->setIPv6Data(interfaceData);
        terminal.remoteInterfaceEntry->setMACAddress(MACAddress::generateAutoAddress());

        // terminal
        terminal.interfaceEntry->ipv6Data()->setAdvSendAdvertisements(false); // host
        terminal.interfaceEntry->ipv6Data()->assignAddress(terminal.ipvxAddress.toIPv6(), false, 0, 0);
        terminal.interfaceEntry->ipv6Data()->assignAddress(IPv6Address::formLinkLocalAddress(terminal.interfaceEntry->getInterfaceToken()), false, 0, 0);
        terminal.interfaceEntry->setMACAddress(MACAddress::generateAutoAddress());

        //
        // Fill in routing table.
        //

        // router
        router.routingTable6->addStaticRoute(terminal.ipvxAddress.toIPv6(),64, terminal.remoteInterfaceEntry->getInterfaceId(), terminal.interfaceEntry->ipv6Data()->getLinkLocalAddress());

        // terminal
        terminal.routingTable6->addDefaultRoute(terminal.remoteInterfaceEntry->ipv6Data()->getLinkLocalAddress(), terminal.interfaceEntry->getInterfaceId(), 0);

    } else {

        //
        // Fill in interface table.
        //

        // router
        IPv4InterfaceData* interfaceData = new IPv4InterfaceData;
        interfaceData->setIPAddress(router.ipvxAddress.toIPv4());
        interfaceData->setNetmask(IPv4Address::ALLONES_ADDRESS);
        terminal.remoteInterfaceEntry->setIPv4Data(interfaceData);

        // terminal
        terminal.interfaceEntry->ipv4Data()->setIPAddress(terminal.ipvxAddress.toIPv4());
        terminal.interfaceEntry->ipv4Data()->setNetmask(IPv4Address::ALLONES_ADDRESS);

        //
        // Fill in routing table.
        //

        // router
        IPv4Route* re = new IPv4Route();
        re->setDestination(terminal.ipvxAddress.toIPv4());
        re->setNetmask(IPv4Address(IPv4Address::ALLONES_ADDRESS));
        re->setInterface(terminal.remoteInterfaceEntry);
        re->setSourceType(IPv4Route::MANUAL);
        router.routingTable->addRoute(re);
        terminal.remoteRoutingEntry = re;

        // terminal
        IPv4Route* te = new IPv4Route();
        te->setDestination(IPv4Address::UNSPECIFIED_ADDRESS);
        te->setNetmask(IPv4Address::UNSPECIFIED_ADDRESS);
        te->setGateway(router.ipvxAddress.toIPv4());
        te->setInterface(terminal.interfaceEntry);
        te->setSourceType(IPv4Route::MANUAL);
        terminal.routingTable->addRoute(te);
        terminal.routingEntry = te;

    }


    // append module to overlay terminal vector
    overlayTerminal.push_back(terminal);
    //int ID = terminal.module->getId();

    updateDisplayString();

    return terminal.ipvxAddress;
}

int AccessNet::getRandomNodeId()
{
    Enter_Method("getRandomNodeId()");

    return overlayTerminal[intuniform(0, overlayTerminal.size() - 1)].module->getId();
}

cModule* AccessNet::removeOverlayNode(int ID)
{
    Enter_Method("removeOverlayNode()");

    cModule* node = NULL;
    TerminalInfo terminal;
    int index;

    for(unsigned int i=0; i<overlayTerminal.size(); i++) {
        if(overlayTerminal[i].module->getId() == ID) {
            terminal = overlayTerminal[i];
            node = terminal.module;
            index = i;
        }
    }

    if(node == NULL) return NULL;

    cModule* ppp = terminal.remotePPPInterface;

    // disconnect terminal
    node->gate("pppg$o", 0)->disconnect();
    node->gate("pppg$i", 0)->getPreviousGate()->disconnect();

    // disconnect ip and arp modules
    ppp->gate("upperLayerIn")->getPathStartGate()->disconnect();
    ppp->gate("upperLayerOut")->getNextGate()->disconnect();

    // remove associated ppp interface module
    ppp->callFinish();
    ppp->deleteModule();

    // remove associated interface table entry
    router.interfaceTable->deleteInterface(terminal.remoteInterfaceEntry);

    // remove routing entries //TODO: IPv6
    if (!useIPv6) {
        terminal.routingTable->deleteRoute(terminal.routingEntry);
        router.routingTable->deleteRoute(terminal.remoteRoutingEntry);
    } else {
#if 0
        for (int i = 0; i < terminal.routingTable6->getNumRoutes(); i++) {
            IPv6Route* route = terminal.routingTable6->getRoute(i);
            if (route->getDestPrefix() == terminal.remoteInterfaceEntry->
                    ipv6Data()->getLinkLocalAddress()) {
                terminal.routingTable6->purgeDestCacheEntriesToNeighbour(terminal.remoteInterfaceEntry->ipv6Data()->getLinkLocalAddress(), route->getInterface()->getInterfaceId());
                terminal.routingTable6->removeRoute(route);
            }
        }
#endif

        for (int i = 0; i < router.routingTable6->getNumRoutes(); i++) {
            IPv6Route* route = router.routingTable6->getRoute(i);
            if (route->getDestPrefix() == terminal.ipvxAddress.toIPv6()) {
                router.routingTable6->purgeDestCacheEntriesToNeighbour(terminal.interfaceEntry->ipv6Data()->getLinkLocalAddress(), route->getInterface()->getInterfaceId());
                router.routingTable6->removeRoute(route);
                break;
            }
        }
    }

    // statistics
    lifetimeVector.record(simTime() - overlayTerminal[index].createdAt);

    // remove terminal from overlay terminal vector
    overlayTerminal.erase(overlayTerminal.begin() + index);

    updateDisplayString();

    return node;
}

cModule* AccessNet::getOverlayNode(int ID)
{
    Enter_Method("getOverlayNode()");

    cModule* node = NULL;

    for(unsigned int i=0; i<overlayTerminal.size(); i++) {
        if(overlayTerminal[i].module->getId() == ID)
            node = overlayTerminal[i].module;
    }
    return node;
}

void AccessNet::updateDisplayString()
{
    if (hasGUI()) {
        char buf[80];
        if ( overlayTerminal.size() == 1 ) {
            sprintf(buf, "1 terminal connected");
        } else {
            sprintf(buf, "%zi terminals connected", overlayTerminal.size());
        }
        getDisplayString().setTagArg("t", 0, buf);
        getDisplayString().setTagArg("t", 2, "blue");
    }
}

cGate* firstUnusedGate(cModule* owner, const char* name, cGate::Type type)
{
    int index;
    for (index = 0; index < owner->gateSize(name); index++) {
        cGate *gate = type == cGate::NONE ? owner->gate(name, index) : owner->gateHalf(name, type, index);
        if (!gate->isConnectedOutside()) {
            return gate;
        }
    }

    owner->setGateSize(name, index + 2);
    return type == cGate::NONE ? owner->gate(name, index + 1) : owner->gateHalf(name, type, index + 1);
}

L3Address AccessNet::getAssignedPrefix(IInterfaceTable* ift)
{
    //FIXME: support multiple prefixes
    for (int i = 0; i< ift->getNumInterfaces(); i++) {
        if (!ift->getInterface(i)->isLoopback()) {
            if (ift->getInterface(i)->ipv6Data()->getNumAdvPrefixes() == 1)
                return ift->getInterface(i)->ipv6Data()->getAdvPrefix(0).prefix;
            else
                throw cRuntimeError("Prefix is not unique.");
        }
    }
    return L3Address();
}
