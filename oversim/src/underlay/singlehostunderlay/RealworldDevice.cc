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
 * @file RealworldDevice.cc
 * @author Stephan Krause
 */

#include "underlay/singlehostunderlay/RealworldDevice.h"


void RealworldDevice::initialize(int stage)
{

    RealworldConnector::initialize(stage);

    // register our interface entry in IRoutingTable
    if (stage == INITSTAGE_LINK_LAYER) {
        interfaceEntry = registerInterface();
    }

}

InterfaceEntry *RealworldDevice::registerInterface()
{
    InterfaceEntry *e = new InterfaceEntry(this);

    // port: index of gate where our "upperLayerIn" is connected (in IP)
    int outputPort = /*getParentModule()->*/gate("upperLayerIn")->getPreviousGate()->getIndex();
    e->setNodeOutputGateId(outputPort);

    // generate a link-layer address to be used as interface token for IPv6
    InterfaceToken token(0, (*getSimulation()).getUniqueNumber(), 64);
    e->setInterfaceToken(token);

    // MTU: typical values are 576 (Internet de facto), 1500 (Ethernet-friendly),
    // 4000 (on some point-to-point links), 4470 (Cisco routers default, FDDI compatible)
    e->setMtu(mtu);

    // capabilities
    e->setMulticast(true);
    e->setPointToPoint(true);

    // add
    IInterfaceTable *ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
    ift->addInterface(e);

    return e;
}


