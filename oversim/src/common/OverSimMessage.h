//
// Copyright (C) 2008 Institut fuer Telematik, Universitaet Karlsruhe (TH)
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

#include "common/OverSimMessage_m.h"

class OverSimMessage : public OverSimMessage_Base
{
public:
    OverSimMessage(const char *name=NULL, int kind=0) : OverSimMessage_Base(name,kind) {}
    OverSimMessage(const OverSimMessage& other) : OverSimMessage_Base(other.getName()) {operator=(other);}
    OverSimMessage& operator=(const OverSimMessage& other) {OverSimMessage_Base::operator=(other); return *this;}
    virtual OverSimMessage *dup() const {return new OverSimMessage(*this);}

    virtual void parsimPack(cCommBuffer *b) const;
    virtual void parsimUnpack(cCommBuffer *b);
};
