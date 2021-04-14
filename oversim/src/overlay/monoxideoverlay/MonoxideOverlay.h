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
 * @file MonoxideOverlay.h
 * @author Sebastian Mies, Ingmar Baumgart, Bernhard Heep
 */

#ifndef __MONOXIDE_OVERLAY_H_
#define __MONOXIDE_OVERLAY_H_

#include <deque>

#include "../monoxideoverlay/MonoxideOverlayBucket.h"
#include "../monoxideoverlay/MonoxideOverlayNodeHandle.h"
#include "common/OverSimDefs.h"

#include "common/CommonMessages_m.h"
#include "common/BaseOverlay.h"
#include "common/GlobalStatistics.h"
#include "common/NeighborCache.h"



/**
 * MonoxideOverlay overlay module
 *
 * @author Sebastian Mies, Ingmar Baumgart, Bernhard Heep
 *
 * This class implements the MonoxideOverlay protocol described in
 * P. Maymounkov and D. Mazi��res, "MonoxideOverlay: A Peer-to-Peer Information System
 * Based on the XOR Metric", Lecture Notes in Computer Science,
 * Peer-to-Peer Systems: First International Workshop (IPTPS 2002).
 * Revised Papers, 2002, 2429/2002, 53-65
 *
 * The recursive routing mode (R/MonoxideOverlay) is described in
 * B. Heep, "R/MonoxideOverlay: Recursive and Topology-aware Overlay Routing",
 * Proceedings of the Australasian Telecommunication Networks and
 * Applications Conference 2010 (ATNAC 2010), Auckland, New Zealand, 2010
 *
 * The security extensions (S/MonoxideOverlay) are described in
 * I. Baumgart and S. Mies, "S/MonoxideOverlay: A Practicable Approach Towards
 * Secure Key-Based Routing", Proceedings of the 13th International
 * Conference on Parallel and Distributed Systems (ICPADS '07),
 * Hsinchu, Taiwan, 2007
 */
class MonoxideOverlay : public BaseOverlay, public ProxListener
{
protected://fields: kademlia parameters

    uint32_t k; /*< number of redundant graphs */
    uint32_t b; /*< number of bits to consider */
    uint32_t s; /*< number of siblings         */

    uint32_t maxStaleCount; /*< number of timouts until node is removed from
                            routingtable */

    bool exhaustiveRefresh; /*< if true, use exhaustive-iterative lookups to refresh buckets */
    bool pingNewSiblings;
    bool secureMaintenance; /**< if true, ping not authenticated nodes before adding them to a bucket */
    bool newMaintenance;

    bool enableReplacementCache; /*< enables the replacement cache to store nodes if a bucket is full */
    bool replacementCachePing; /*< ping the least recently used node in a full bucket, when a node is added to the replacement cache */
    uint replacementCandidates; /*< maximum number of candidates in the replacement cache for each bucket */
    int siblingRefreshNodes; /*< number of redundant nodes for exhaustive sibling table refresh lookups (0 = numRedundantNodes) */
    int bucketRefreshNodes; /*< number of redundant nodes for exhaustive bucket refresh lookups (0 = numRedundantNodes) */

    // R/MonoxideOverlay
    bool activePing;
    bool proximityRouting;
    bool proximityNeighborSelection;
    bool altRecMode;

    simtime_t minSiblingTableRefreshInterval;
    simtime_t minBucketRefreshInterval;
    simtime_t siblingPingInterval;

    cMessage* bucketRefreshTimer;
    cMessage* siblingPingTimer;

public:
    int myKey = 0;

    MonoxideOverlay();

    ~MonoxideOverlay();

    void initializeOverlay(int stage);

    void finishOverlay();

    void joinOverlay();

    bool isSiblingFor(const NodeHandle& node,const OverlayKey& key,
                      int numSiblings, bool* err );

    int getMaxNumSiblings();

    int getMaxNumRedundantNodes();

    void handleTimerEvent(cMessage* msg);

    bool handleRpcCall(BaseCallMessage* msg);

    void handleUDPMessage(BaseOverlayMessage* msg);

    virtual void proxCallback(const TransportAddress& node, int rpcId,
                              cObject *contextPointer, Prox prox);

protected:
    NodeVector* findNode(const OverlayKey& key,
                         int numRedundantNodes,
                         int numSiblings,
                         BaseOverlayMessage* msg);

    void handleRpcResponse(BaseResponseMessage* msg,
                           cObject* context,
                           int rpcId, simtime_t rtt);

    void handleRpcTimeout(BaseCallMessage* msg, const TransportAddress& dest,
                          cObject* context, int rpcId,
                          const OverlayKey& destKey);

    /**
     * handle a expired bucket refresh timer
     */
    void handleBucketRefreshTimerExpired();

    OverlayKey distance(const OverlayKey& x,
                        const OverlayKey& y,
                        bool useAlternative = false) const;

    /**
     * updates information shown in GUI
     */
    void updateTooltip();

    virtual void lookupFinished(bool isValid);

    virtual void handleNodeGracefulLeaveNotification();

    friend class MonoxideOverlayLookupListener;

#ifdef PAIL
    AbstractProxKeyComparator* getProxKeyComparator(const OverlayKey& relativeKey,
                                                    uint8_t bitsPerDigit,
                                                    const AdjustableProxComparator* apc) {
        return new MonoxideOverlayPRComparator(relativeKey, bitsPerDigit);
    };
#endif
private:
    uint32_t bucketRefreshCount; /*< statistics: total number of bucket refreshes */
    uint32_t siblingTableRefreshCount; /*< statistics: total number of sibling table refreshes */
    uint32_t nodesReplaced;

    KeyDistanceComparator<KeyXorMetric>* comparator;

    MonoxideOverlayBucket*  siblingTable;
    std::vector<MonoxideOverlayBucket*> routingTable;
    int numBuckets;

    void routingInit();

    void routingDeinit();

    /**
     * Returns the index of the bucket the key would reside
     * with respect to MonoxideOverlay parameters
     *
     * @param key The key of the node
     * @param firstOnLayer If true bucket with smallest index on same layer
     *                     is returned
     * @return int The index of the bucket
     */
    int routingBucketIndex(const OverlayKey& key, bool firstOnLayer = false);

    /**
     * Returns a Bucket or <code>NULL</code> if the bucket has not
     * yet allocated. If ensure is true, the bucket allocation is
     * ensured.
     *
     * @param key The key of the node
     * @param ensure If true, the bucket allocation is ensured
     *
     * @return Bucket* The Bucket
     */
    MonoxideOverlayBucket* routingBucket(const OverlayKey& key, bool ensure);

    /**
     * Adds a node to the routing table
     *
     * @param handle handle to add
     * @param isAlive true, if it is known that the node is alive
     * @param rtt measured round-trip-time to node
     * @param maintenanceLookup true, if this node was learned from a maintenance lookup
     * @return true, if the node was known or has been added
     */
    bool routingAdd(const NodeHandle& handle, bool isAlive,
                    simtime_t rtt = SIMTIME_MAX, bool maintenanceLookup = false);

    /**
     * Removes a node after a number of timeouts or immediately
     * if immediately is true (behaves like routingRemove).
     *
     * @param key Node's key to remove
     * @param immediately If true, the node is removed immediately
     * @return true, if the node has been removed
     */
    bool routingTimeout(const OverlayKey& key, bool immediately = false);

    void refillSiblingTable();

    void sendSiblingFindNodeCall(const TransportAddress& dest);

    void setBucketUsage(const OverlayKey& key);

    bool recursiveRoutingHook(const TransportAddress& dest,
                              BaseRouteMessage* msg);

    bool handleFailedNode(const TransportAddress& failed);

    virtual void setOwnNodeID() override;
};

#endif
