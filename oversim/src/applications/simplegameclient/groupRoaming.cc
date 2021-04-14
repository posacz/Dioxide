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
* @file groupRoaming.cc
* @author Helge Backhaus
*/

#include "applications/simplegameclient/groupRoaming.h"

groupRoaming::groupRoaming(double areaDimension, double speed, NeighborMap *Neighbors, GlobalCoordinator* coordinator, CollisionList* CollisionRect, int groupSize)
             :MovementGenerator(areaDimension, speed, Neighbors, coordinator, CollisionRect)
{
    groupNr = coordinator->getPeerCount() / groupSize;

    if((coordinator->getPeerCount() % groupSize) == 0) {
        target.x = RNGCONTEXT uniform(0.0, areaDimension);
        target.y = RNGCONTEXT uniform(0.0, areaDimension);
        coordinator->increasePositionSize();
        coordinator->setPosition(groupNr, target);
    }
    else {
        target = coordinator->getPosition(groupNr);
    }

    coordinator->increasePeerCount();
}


void groupRoaming::move()
{
    if(coordinator->getPosition(groupNr) != target) {
        target = coordinator->getPosition(groupNr);
    }

    flock();
    position += direction * speed;
    if(testBounds()) {
        position += direction * speed * 2;
        testBounds();
    }

    if(target.distanceSqr(position) < speed * speed) {
        target.x = RNGCONTEXT uniform(0.0, areaDimension);
        target.y = RNGCONTEXT uniform(0.0, areaDimension);
        coordinator->setPosition(groupNr, target);
    }
}
