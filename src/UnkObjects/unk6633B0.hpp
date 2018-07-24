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

#include <array>

class unk_6633B0 {
public:
    const char *unk00;
    const char *unk04;
    std::uint8_t pad08[0x1270];
};
static_assert(sizeof(unk_6633B0) == 0x1278, "Wrong size for unk_6633B0");

extern MC2_PROC_PTR<void, const char *, bool> sub_53DD30;

extern std::array<unk_6633B0, 14> &glo_6633B0;
inline void sub_53DE60() {
    for (unk_6633B0 &x : glo_6633B0) sub_53DD30(x.unk04, false);
}
