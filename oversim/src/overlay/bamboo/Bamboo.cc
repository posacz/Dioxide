//
// Copyright (C) 2012 Institute of Telematics, Karlsruhe Institute of Technology (KIT)
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
 * @file Bamboo.cc
 * @author Gerhard Petruschat, Bernhard heep
 */

#include <cassert>

#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/ipv4/IPv4InterfaceData.h"
#include "common/RpcMacros.h"
#include "inet/common/InitStages.h"
#include "common/GlobalStatistics.h"
#include "common/LookupListener.h"
#include "common/AbstractLookup.h"

#include "overlay/bamboo/Bamboo.h"


Define_Module(Bamboo);

Bamboo::~Bamboo()
{
    // destroy self timer messages
    cancelAndDelete(localTuningTimer);
    cancelAndDelete(leafsetMaintenanceTimer);
    cancelAndDelete(globalTuningTimer);
}


void Bamboo::initializeOverlay(int stage)
{
    if ( stage != MIN_STAGE_OVERLAY )
        return;

    // Bamboo provides KBR services
    kbr = true;

    rowToAsk = 0;

    baseInit();

    localTuningInterval = par("localTuningInterval");
    leafsetMaintenanceInterval = par("leafsetMaintenanceInterval");
    globalTuningInterval = par("globalTuningInterval");

    localTuningTimer = new cMessage("repairTaskTimer");
    leafsetMaintenanceTimer = new cMessage("leafsetMaintenanceTimer");
    globalTuningTimer = new cMessage("globalTuningTimer");
}


void Bamboo::joinOverlay()
{
    changeState(INIT);

    if (bootstrapNode.isUnspecified()) {
        // no existing pastry network -> first node of a new one
        changeState(READY);
    } else {
        // join existing pastry network
        changeState(JOIN);
    }
}


void Bamboo::changeState(int toState)
{
    baseChangeState(toState);

    switch (toState) {
    case INIT:
        break;

    case DISCOVERY:
        break;

    case JOIN: {
        EV << "[Bamboo::changeState()]\n"
           << "    sending join message via " << bootstrapNode
           << " to " << thisNode.getKey()
           << endl;

        RequestLeafSetCall* call = new RequestLeafSetCall("JOIN Call");
        call->setTimestamp(simTime());
        call->setStatType(MAINTENANCE_STAT);

        call->setBitLength(PASTRYREQUESTLEAFSETCALL_L(call));
        call->encapsulate(createStateMessage(PASTRY_STATE_LEAFSET));
        RECORD_STATS(leafsetReqSent++;
                     leafsetReqBytesSent += call->getByteLength());

        sendRouteRpcCall(OVERLAY_COMP, bootstrapNode, thisNode.getKey(), call);
    }

    break;

    case READY:
        cancelEvent(leafsetMaintenanceTimer);
        scheduleAt(simTime(), leafsetMaintenanceTimer);

        // schedule routing table maintenance task
        cancelEvent(localTuningTimer);
        scheduleAt(simTime() + localTuningInterval, localTuningTimer);

        cancelEvent(globalTuningTimer);
        scheduleAt(simTime() + globalTuningInterval, globalTuningTimer);

        break;
    }
}


void Bamboo::handleTimerEvent(cMessage* msg)
{
    if (msg == localTuningTimer) {
        EV << "[Bamboo::handleTimerEvent() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    starting local tuning "
           << "(aka neighbor's neighbors / routing table maintenance)"
           << endl;
        doLocalTuning();
        scheduleAt(simTime() + localTuningInterval, localTuningTimer);
    } else if (msg == leafsetMaintenanceTimer) {
        EV << "[Bamboo::handleTimerEvent() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    starting leafset maintenance"
           << endl;
        doLeafsetMaintenance();
        scheduleAt(simTime() + leafsetMaintenanceInterval,
                   leafsetMaintenanceTimer);
    } else if (msg == globalTuningTimer) {
        EV << "[Bamboo::handleTimerEvent() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    starting global tuning"
           << endl;
        doGlobalTuning();
        scheduleAt(simTime() + globalTuningInterval, globalTuningTimer);
    }
}


void Bamboo::handleRpcResponse(BaseResponseMessage* msg,
                               cObject* context, int rpcId,
                               simtime_t rtt)
{
    BasePastry::handleRpcResponse(msg, context, rpcId, rtt);

    RPC_SWITCH_START( msg )
    RPC_ON_RESPONSE( RequestLeafSet ) {
        EV << "[Bamboo::handleRpcResponse() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    Received a RequestLeafSet RPC Response (PUSH): id="
           << rpcId << "\n"
           << "    msg=" << *_RequestLeafSetResponse << " rtt=" << rtt
           << endl;
        handleRequestLeafSetResponse(_RequestLeafSetResponse);
        break;
    }
    RPC_SWITCH_END( )
}


void Bamboo::handleRequestLeafSetResponse(RequestLeafSetResponse* response)
{
    EV << "[Bamboo::handleRequestLeafSetResponse() @ " << thisNode.getIp()
       << " (" << thisNode.getKey().toString(16) << ")]"
       << endl;

    if (state == JOIN) {
        PastryStateMessage* stateMsg =
             check_and_cast<PastryStateMessage*>(response->decapsulate());

        stateMsg->setLeafSetArraySize(stateMsg->getLeafSetArraySize() + 1);
        stateMsg->setLeafSet(stateMsg->getLeafSetArraySize() - 1,
                             stateMsg->getSender());

        handleStateMessage(stateMsg);
    }
}


void Bamboo::doLeafsetMaintenance(void)
{
    const TransportAddress& ask = leafSet->getRandomNode();
    if (!ask.isUnspecified()) {
        EV << "[Bamboo::doLeafsetMaintenance()]\n"
           << "    leafset maintenance: pulling leafset from "
           << ask << endl;

        RequestLeafSetCall* call = new RequestLeafSetCall("LeafSet PULL");
        call->setTimestamp(simTime());
        call->setStatType(MAINTENANCE_STAT);

        call->setBitLength(PASTRYREQUESTLEAFSETCALL_L(call));
        call->encapsulate(createStateMessage(PASTRY_STATE_LEAFSET));
        RECORD_STATS(leafsetReqSent++;
                     leafsetReqBytesSent += call->getByteLength());

        sendUdpRpcCall(ask, call);
    }
}


int Bamboo::getNextRowToMaintain()
{
    int digit = 0;
    int lastRow = routingTable->getLastRow();

    int* choices = new int[lastRow + 1];
    int sum = 0;

    for (int i = 0; i < lastRow; ++i) {
        sum += (choices[i] = lastRow - i);
    }

    int rval = intuniform(0, sum);

    while (true) {
        rval -= choices [digit];
        if (rval <= 0)
            break;
        ++digit;
    }
    delete[] choices;

    return digit;
}


void Bamboo::doLocalTuning()
{
    rowToAsk = getNextRowToMaintain();

    const TransportAddress& ask4row = routingTable->getRandomNode(rowToAsk);

    if ((!ask4row.isUnspecified()) && (ask4row != thisNode)) {
        EV << "[Bamboo::doLocalTuning() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    Sending  Message to Node in Row" << rowToAsk
           << endl;

        RequestRoutingRowCall* call =
            new RequestRoutingRowCall("REQUEST ROUTINGROW Call (Local Tuning)");
        call->setStatType(MAINTENANCE_STAT);
        call->setRow(rowToAsk + 1);
        call->setBitLength(PASTRYREQUESTROUTINGROWCALL_L(call));
        RECORD_STATS(routingTableRowReqSent++;
                     routingTableRowReqBytesSent += call->getByteLength());

        sendUdpRpcCall(ask4row, call);
    }
}


void Bamboo::doGlobalTuning(void)
{
    int digit = getNextRowToMaintain();

    // would be a better alternative
    //OverlayKey OverlayKey::randomSuffix(uint pos) const;

    uint32_t maxDigitIndex = OverlayKey::getLength() - bitsPerDigit;
    uint32_t maxKeyIndex = OverlayKey::getLength() - 1;
    OverlayKey newKey = OverlayKey::random();
    while (newKey.getBitRange(maxDigitIndex - digit * bitsPerDigit, bitsPerDigit) ==
           thisNode.getKey().getBitRange(maxDigitIndex - digit * bitsPerDigit, bitsPerDigit)) {
        newKey = OverlayKey::random();
    }

    assert(digit * bitsPerDigit < OverlayKey::getLength());
    for (uint16_t i = 0; i < digit * bitsPerDigit; ++i) {
        newKey[maxKeyIndex - i] = thisNode.getKey().getBit(maxKeyIndex - i);
    }

    createLookup()->lookup(newKey, 1, 0, 0, new BambooLookupListener(this));
}


bool Bamboo::handleFailedNode(const TransportAddress& failed)
{
    if (state != READY) return false;

    if (failed.isUnspecified()) {
        throw cRuntimeError("Bamboo::handleFailedNode(): failed is unspecified!");
    }

    const TransportAddress& lsAsk = leafSet->failedNode(failed);
    routingTable->failedNode(failed);
    neighborhoodSet->failedNode(failed);

    if (lsAsk.isUnspecified() && (! leafSet->isValid())) {
        EV << "[Bamboo::handleFailedNode()]\n"
           << "    lost connection to the network, trying to re-join."
           << endl;
        join();
        return false;
    }

    return true;
}


void Bamboo::checkProxCache(void)
{
    // no cached STATE message?
    if (stateCache.msg) {
        simtime_t now = simTime();
        if (stateCache.prox) {
            // some entries not yet determined?
            if ((find(stateCache.prox->pr_rt.begin(), stateCache.prox->pr_rt.end(),
                      PASTRY_PROX_PENDING) != stateCache.prox->pr_rt.end()) ||
                (find(stateCache.prox->pr_ls.begin(), stateCache.prox->pr_ls.end(),
                      PASTRY_PROX_PENDING) != stateCache.prox->pr_ls.end()) ||
                (find(stateCache.prox->pr_ns.begin(), stateCache.prox->pr_ns.end(),
                      PASTRY_PROX_PENDING) != stateCache.prox->pr_ns.end())) {
                return;
            }
        }
        // merge info in own state tables
        // except leafset (was already handled in handleStateMessage)
        if (neighborhoodSet->mergeState(stateCache.msg, stateCache.prox)) {
            lastStateChange = now;
        }

        if (routingTable->mergeState(stateCache.msg, stateCache.prox)) {
            lastStateChange = now;
            EV << "[Bamboo::checkProxCache()]\n"
                    << "    Merged nodes into routing table."
                    << endl;
        }
    }

    delete stateCache.msg;
    stateCache.msg = NULL;
    delete stateCache.prox;
    stateCache.prox = NULL;

    if (state == JOIN) {
        changeState(READY);
    }

    updateTooltip();

    // process next queued message:
    if (! stateCacheQueue.empty()) {
        stateCache = stateCacheQueue.front();
	      stateCacheQueue.pop();
        if (proximityNeighborSelection) {
            pingNodes();
        } else {
            checkProxCache();
        }
    }
}


void Bamboo::handleStateMessage(PastryStateMessage* msg)
{
    if (debugOutput) {
        EV << "[Bamboo::handleStateMessage() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    new STATE message to process "
           << static_cast<void*>(msg) << " in state "
           << ((state == READY)?"READY":((state == JOIN)?"JOIN":"INIT"))
           << endl;
    }

    if (state == INIT) {
        EV << "[Bamboo::handleStateMessage() @ " << thisNode.getIp()
           << " (" << thisNode.getKey().toString(16) << ")]\n"
           << "    can't handle state messages until at least reaching JOIN state."
           << endl;
        delete msg;
        return;
    }

    PastryStateMsgHandle handle(msg);

    if (state == JOIN) {
        determineAliveTable(msg);
        leafSet->mergeState(msg, &aliveTable);
        // merged state into leafset right now
        lastStateChange = simTime();
        newLeafs();
        updateTooltip();

        // no state message is processed right now, start immediately:
        stateCache = handle;
        if (proximityNeighborSelection) {
            pingNodes();
        } else {
            checkProxCache();
        }

        return;
    }

    // determine aliveTable to prevent leafSet from merging nodes that are
    // known to be dead:
    determineAliveTable(msg);
    if (leafSet->mergeState(msg, &aliveTable)) {
        // merged state into leafset right now
        lastStateChange = simTime();
        newLeafs();
        updateTooltip();
    }
    // in READY state, only ping nodes to get proximity metric:
    if (!stateCache.msg) {
        // no state message is processed right now, start immediately:
        stateCache = handle;
        if (proximityNeighborSelection) {
            pingNodes();
        } else {
            checkProxCache();
        }
    } else {
        // enqueue message for later processing:
        stateCacheQueue.push(handle);
        if (stateCacheQueue.size() > 15) {
            delete stateCacheQueue.front().msg;
            stateCacheQueue.pop();
            EV << "[Bamboo::handleStateMessage() @ " << thisNode.getIp()
               << " (" << thisNode.getKey().toString(16) << ")]\n"
               << "    stateCacheQueue full -> pop()" << endl;
        }
        if (proximityNeighborSelection) {
            prePing(msg);
        } else {
            checkProxCache();
        }
    }
}


void Bamboo::lookupFinished(AbstractLookup *lookup)
{
    EV << "[Bamboo::lookupFinished() @ " << thisNode.getIp()
       << " (" << thisNode.getKey().toString(16) << ")]\n"
       << endl;

    if (lookup->isValid()) {
        EV  << "    Lookup successful" << endl;
        const NodeVector& result = lookup->getResult();
        if (result[0] != thisNode) {
            if (proximityNeighborSelection) {
                // Global Tuning PING
                Prox prox = neighborCache->getProx(result[0],
                                                   NEIGHBORCACHE_DEFAULT,
                                                   PING_SINGLE_NODE,
                                                   this, NULL);
                if (prox != Prox::PROX_UNKNOWN && prox != Prox::PROX_WAITING) {
                    routingTable->mergeNode(result[0], prox.proximity);
                }
            } else {
                routingTable->mergeNode(result[0], -1.0);
                checkProxCache();
            }
        }
    } else {
        EV << "    Lookup failed" << endl;
    }
}
