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

// originally malloc'd in mcaudiomgr.c
class unk_52AA80 {
private:
    std::uint8_t pad00[0x98];

public:
    unk_52AA80(bool arg1) {
        MC2_CALL_MEMBER<0x0052AA80, void>(this, arg1);
    }
};
static_assert(sizeof(unk_52AA80) == 0x98, "Wrong size for unk_52AA80");

extern unk_52AA80 *(&glo_6CE2E4);
inline unk_52AA80 *sub_52B6C0(bool arg1) {
    return glo_6CE2E4 = new unk_52AA80(arg1);
}
