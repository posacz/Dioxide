//
// Copyright (C) 2009 Institut fuer Telematik, Universitaet Karlsruhe (TH)
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

#ifndef __MONOXIDE_NODE_HANDLE_H
#define __MONOXIDE_NODE_HANDLE_H

#include "common/NodeHandle.h"
#include "common/NodeVector.h"
#include "../kademlia/KademliaNodeHandle.h"

/**
 * @file MonoxideOverlayNodeHandle.h
 * @author Sebastian Mies, Ingmar Baumgart, Bernhard Heep
 */
class MonoxideOverlayBucketEntry : public ProxNodeHandle
{
public:
    /**
     * Constructs an unspecified NodeHandle
     */
    MonoxideOverlayBucketEntry()
    : ProxNodeHandle()
    {
        staleCount = 0;
        pingSent = false;
    }

    MonoxideOverlayBucketEntry(const NodeHandle& handle, simtime_t prox = SIMTIME_MAX)
    : ProxNodeHandle(handle)
    {
        staleCount = 0;
        this->prox.proximity = SIMTIME_DBL(prox);
        this->prox.accuracy = 1.0;
        pingSent = false;
    }

    // TODO
    inline simtime_t getRtt() const { return getProx(); } //deprecated
    inline void setRtt(simtime_t rtt) { this->prox.proximity = SIMTIME_DBL(rtt);  this->prox.accuracy = 1; } //deprecated

    inline uint8_t getStaleCount() const { return staleCount; }

    inline void setStaleCount(uint8_t staleCount) { this->staleCount = staleCount; }

    inline void resetStaleCount() { this->setStaleCount(0); }

    inline void incStaleCount() { this->staleCount++; }

    inline void setLastSeen(simtime_t lastSeen) { this->lastSeen = lastSeen; }

    inline simtime_t getLastSeen() { return this->lastSeen; }

    inline void setPingSent(bool pingSent) { this->pingSent = pingSent; }

    inline bool getPingSent() const { return pingSent; };

private:

    uint8_t staleCount;
    simtime_t lastSeen;
    bool pingSent; /*< true, if there is a pending pong for this node */

    friend std::ostream& operator<<(std::ostream& os,
                                    const MonoxideOverlayBucketEntry& n)
    {
        os << (NodeHandle)n << " " << n.prox.proximity;
        return os;
    };
};

/**
 * Class for extracting the relevant OverlayKey from a type used as template
 * parameter T_key for NodeVector<T, T_key> - Version for MonoxideOverlayBucketEntry.
 *
 * @author Sebastian Mies
 * @author Felix M. Palmen
 */
template <> struct KeyExtractor<MonoxideOverlayBucketEntry>
{
    static const OverlayKey& key(const MonoxideOverlayBucketEntry& entry)
    {
        return entry.getKey();
    };
};

template <> struct ProxExtractor<MonoxideOverlayBucketEntry>
{
    static Prox prox(const MonoxideOverlayBucketEntry& entry)
    {
        return entry.getProx();
    };
};

#endif
