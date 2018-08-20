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

// originally malloc'd in ambienttraffic.cpp
class unk_4E8B70 {
private:
    std::uint8_t pad00[0x13C];

public:
    unk_4E8B70() {
        MC2_CALL_MEMBER<0x004E8B70, void>(this);
    }

    void sub_4E84D0() {
        return MC2_CALL_MEMBER<0x004E84D0, void>(this);
    }
};
static_assert(sizeof(unk_4E8B70) == 0x13C, "Wrong size for unk_4E8B70");

extern unk_4E8B70 *(&glo_69947C);
inline unk_4E8B70 *sub_4E9040() {
    return glo_69947C = new unk_4E8B70();
}
