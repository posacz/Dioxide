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
 * @file PubSubMMOG.h
 * @author Stephan Krause
 */

#ifndef __PUBSUBMMOG_H_
#define __PUBSUBMMOG_H_

#include "common/OverSimDefs.h"
#include "common/NodeHandle.h"
#include "common/BaseOverlay.h"
#include "overlay/pubsubmmog/PubSubSubspace.h"
#include "overlay/pubsubmmog/PubSubMessage_m.h"

class PubSubMMOG : public BaseOverlay
{
    public:
        // OMNeT++
        virtual ~PubSubMMOG();
        virtual void initializeOverlay(int stage) override;
        virtual void finishOverlay() override;
        virtual void handleUDPMessage(BaseOverlayMessage* msg) override;
        virtual void handleTimerEvent(cMessage* msg) override;
        virtual void handleAppMessage(cMessage* msg) override;
        virtual void receiveSignal(cComponent *source, simsignal_t category, cObject *obj, cObject *details) override;
        virtual bool handleRpcCall(BaseCallMessage* msg) override;
        virtual void handleRpcResponse(BaseResponseMessage *msg,
                                       cObject* context,
                                       int rpcId, simtime_t rtt) override;
        virtual void handleRpcTimeout(BaseCallMessage *msg,
                                      const TransportAddress & dest,
                                      cObject* context,
                                      int rpcId, const OverlayKey &destKey) override;

    protected:

        void setBootstrapedIcon();
        void handleMove( GameAPIPositionMessage* posMsg );
        void handleMoveMessage( PubSubMoveMessage* moveMsg );
        void handleMoveListMessage( PubSubMoveListMessage* moveMsg );
        void handleJoinResponse( PubSubJoinResponse* joinResp );
        void handleSubscriptionCall( PubSubSubscriptionCall* subCall );
        void handleSubscriptionResponse( PubSubSubscriptionResponse* subResp );
        void handleResponsibleNodeResponse( PubSubResponsibleNodeResponse* subResp );
        void handleTakeOver( PubSubTakeOverSubspaceCall* toCall );
        void handleHelpResponse( PubSubHelpResponse* helpResp );
        void handleBackupCall( PubSubBackupCall* backupCall );
        void handleBackupResponse( PubSubBackupResponse* backupResp );
        void handleIntermediateCall( PubSubIntermediateCall* intermediateCall );
        void handleIntermediateResponse( PubSubIntermediateResponse* intermediateResp );
        void handleAdoptChildCall( PubSubAdoptChildCall* adoptCall );
        void handleAdoptChildResponse( PubSubAdoptChildResponse* adoptResp );
        void handlePingCall( PubSubPingCall* hearbeatCall );
        void handlePingResponse( PubSubPingResponse* pingResp );

        void takeOverNewSubspace( PubSubSubspaceId subspaceId );
        void takeOverSubspace( PubSubSubspaceResponsible& subspaceId, bool isNew );
        void sendHearbeatToChildren();
        void sendPingToChildren();
        void handleParentTimeout( PubSubTimer* timer );
        void handleBackupCallTimeout( PubSubBackupCall* backupCall, const TransportAddress& oldNode );
        void handlePingCallTimeout( PubSubPingCall* pingCall, const TransportAddress& oldNode );
        void handleSubscriptionCallTimeout( PubSubSubscriptionCall* subscriptionCall, const TransportAddress& oldNode );
        void handleUnsubscriptionMessage( PubSubUnsubscriptionMessage* unsMsg );
        void handleNodeLeftMessage( PubSubNodeLeftMessage* leftMsg );
        void handleReplacementMessage( PubSubReplacementMessage* replaceMsg );
        void handleReleaseIntermediate( PubSubReleaseIntermediateMessage* releaseMsg );
        void handleIntermediateBackup( PubSubBackupIntermediateMessage* backupMsg );
        void handleSubscriptionBackup( PubSubBackupSubscriptionMessage* backupMsg );
        void handleUnsubscribeBackup( PubSubBackupUnsubscribeMessage* backupMsg );

        void unsubscribeChild( const NodeHandle& node, PubSubSubspaceResponsible& subspace );
        void sendMessageToChildren( PubSubSubspaceResponsible& subspace,
                                        BaseOverlayMessage* toIntermediates,
                                        BaseOverlayMessage* toBackup,
                                        BaseOverlayMessage* toPlayers );

        void publishEvents();
        void startTimer( PubSubTimer* timer );

        std::list<PubSubSubspace> subscribedSubspaces;
        std::map<PubSubSubspaceId, PubSubSubspaceResponsible> responsibleSubspaces;
        std::map<PubSubSubspaceId, PubSubSubspaceResponsible> backupSubspaces;
        std::map<PubSubSubspaceId, PubSubSubspaceIntermediate> intermediateSubspaces;

        int subspaceSize;
        double AOIWidth;

        int numSubspaces;
        simtime_t parentTimeout;
        int maxChildren;

        bool allowOldMoveMessages;

        unsigned int currentRegionX, currentRegionY;
        double movementRate;
        double maxMoveDelay;
        PubSubTimer* heartbeatTimer;
        PubSubTimer* childPingTimer;
        PubSubTimer* eventDeliveryTimer;
        cMessage* joinTimer;
        TransportAddress lobbyServer;

        // statistics
        int numEventsWrongTimeslot;
        int numEventsCorrectTimeslot;
        int numPubSubSignalingMessages;
        int pubSubSignalingMessagesSize;
        int numMoveMessages;
        int moveMessagesSize;
        int numMoveListMessages;
        int moveListMessagesSize;
        int respMoveListMessagesSize;
        int lostMovementLists;
        int receivedMovementLists;
};

#endif
