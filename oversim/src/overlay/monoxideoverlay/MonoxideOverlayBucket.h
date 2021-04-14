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

#ifndef __MONOXIDE_OVERLAY_BUCKET_H
#define __MONOXIDE_OVERLAY_BUCKET_H

#include "../monoxideoverlay/MonoxideOverlayNodeHandle.h"

/**
 * @file MonoxideOverlayBucket.h
 * @author Sebastian Mies, Ingmar Baumgart, Bernhard Heep
 */

class MonoxideOverlayBucket : public BaseKeySortedVector< MonoxideOverlayBucketEntry > {
public:
    MonoxideOverlayBucket(uint16_t maxSize=0,
                   const Comparator<OverlayKey>* comparator = NULL);

    ~MonoxideOverlayBucket();

    inline void setLastUsage(simtime_t time) {
        this->lastUsage = time;
    }

    inline simtime_t getLastUsage() const {
        return this->lastUsage;
    }

    std::list<MonoxideOverlayBucketEntry> replacementCache;

private:
    simtime_t lastUsage;
};

#endif

