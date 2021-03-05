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

// originally malloc'd in movieplayer.cpp
class unk_421350 {
public:
    std::uint8_t pad00[0x1C];
    std::uint8_t unk1C;
    std::uint8_t pad1D[0x13];

public:
    unk_421350() {
        MC2_CALL_MEMBER<0x00421350, void>(this);
    }

    void sub_420EA0() {
        MC2_CALL_MEMBER<0x00420EA0, void>(this);
    }

    void sub_421050() {
        MC2_CALL_MEMBER<0x00421050, void>(this);
    }
};
static_assert(sizeof(unk_421350) == 0x30, "Wrong size for unk_421350");

extern unk_421350 *(&glo_6957BC);
inline unk_421350 *sub_421490() {
    assert(glo_6957BC == nullptr);
    return glo_6957BC = new unk_421350;
}
