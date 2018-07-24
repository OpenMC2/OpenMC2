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

// originally malloc'd in racestate.cpp
class unk_482C30 {
private:
    std::uint8_t pad00[0x34];

public:
    unk_482C30() {
        MC2_CALL_MEMBER<0x00482C30, void>(this);
    }
};
static_assert(sizeof(unk_482C30) == 0x34, "Wrong size for unk_482C30");

extern unk_482C30 *(&glo_6C38A4);
extern unk_482C30 *(&glo_6C38A8);
inline unk_482C30 *sub_482C60() {
    return glo_6C38A4 = glo_6C38A8 = new unk_482C30();
}
