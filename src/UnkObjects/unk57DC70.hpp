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

// originally malloc'd in ragdollmgr.c
class unk_57DC70 {
private:
    std::uint32_t unk00 = 0;
    std::uint32_t unk04 = 0;
    std::uint32_t unk08 = 0;
    std::uint32_t unk0C = 0;
    std::uint32_t unk10 = 0;
    std::uint32_t unk14 = 0;

public:
    // constructor handled by default initialization
};
static_assert(sizeof(unk_57DC70) == 0x18, "Wrong size for unk_57DC70");

extern unk_57DC70 *(&glo_6C8EB0);
inline unk_57DC70 *sub_57E250() {
    assert(glo_6C8EB0 == nullptr);
    return glo_6C8EB0 = new unk_57DC70();
}
