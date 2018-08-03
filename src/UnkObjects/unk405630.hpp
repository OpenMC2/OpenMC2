/**********************************************************************
* OpenMC2 - An Open Source Re-Implementation of Midnight Club 2
* Copyright (C) 2016  LRFLEW
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#pragma once

#include "../Addresses.hpp"

// originally malloc'd in replaymgr.c
class unk_405630 {
protected:
    std::uint8_t pad00[0x3C];

public:
    unk_405630() {
        MC2_CALL_MEMBER<0x00405630, void>(this);
    }

    void sub_405360() {
        MC2_CALL_MEMBER<0x00405360, void>(this);
    }
};
static_assert(sizeof(unk_405630) == 0x3C, "Wrong size for unk_405630");

extern unk_405630 *(&glo_692EB0);
inline unk_405630 *sub_405690() {
    return glo_692EB0 = new unk_405630;
}
