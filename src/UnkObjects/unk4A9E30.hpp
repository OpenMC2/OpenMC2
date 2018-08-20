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

// originally malloc'd in manager.cpp
class unk_4A9E30 {
private:
    std::uint32_t unk00 = 0;
    std::uint8_t pad04[0x04];
    std::uint32_t unk08 = 0;
    std::uint32_t unk0C = 0;

public:
    void sub_4A9F30() {
        return MC2_CALL_MEMBER<0x004A9F30, void>(this);
    }
};
static_assert(sizeof(unk_4A9E30) == 0x10, "Wrong size for unk_4A9E30");

extern unk_4A9E30 *(&glo_698624);
inline unk_4A9E30 *sub_498BC0() {
    return glo_698624 = new unk_4A9E30();
}
