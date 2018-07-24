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

// originally malloc'd in progressmanager.c
class unk_53C670 {
private:
    std::uint8_t pad00[0x70];

public:
    unk_53C670() {
        MC2_CALL_MEMBER<0x0053C670, void>(this);
    }
};
static_assert(sizeof(unk_53C670) == 0x70, "Wrong size for unk_53C670");

extern unk_53C670 *(&glo_6C3898);
inline unk_53C670 *sub_53C6B0() {
    return glo_6C3898 = new unk_53C670;
}
