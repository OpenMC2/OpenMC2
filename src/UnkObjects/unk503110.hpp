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

// originally malloc'd in mcSwPtx.cpp
class unk_503110 {
private:
    std::uint8_t unk00 = 1;
    std::uint8_t pad01[0x403];
    std::uint32_t unk404 = 0;

public:
    void sub_5031F0() {
        return MC2_CALL_MEMBER<0x005031F0, void>(this);
    }
};
static_assert(sizeof(unk_503110) == 0x408, "Wrong size for unk_503110");

extern unk_503110 *(&glo_69C858);
inline unk_503110 *sub_503120() {
    assert(glo_69C858 == nullptr);
    return glo_69C858 = new unk_503110;
}
