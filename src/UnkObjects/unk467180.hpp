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

// originally malloc'd in playermgr.c
class unk_467180 {
private:
    std::uint8_t pad00[0x6C];

public:
    unk_467180() {
        MC2_CALL_MEMBER<0x00467180, void>(this);
    }

    void sub_467090(std::uint32_t arg0, std::uint32_t arg1) {
        MC2_CALL_MEMBER<0x00467090, void>(this, arg0, arg1);
    }

    void sub_4673B0() {
        return MC2_CALL_MEMBER<0x004673B0, void>(this);
    }
};
static_assert(sizeof(unk_467180) == 0x6C, "Wrong size for unk_467180");

extern unk_467180 *(&glo_69585C);
inline unk_467180 *sub_467480() {
    return glo_69585C = new unk_467180;
}
