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

class unk_603B10 {
private:
    std::uint8_t pad00[0x4];
    std::uint32_t unk04 = 1;
    std::uint8_t unk08 = 0;
    std::uint8_t pad09[0x0F];
    std::uint32_t unk18 = 0;

public:
    void sub_603B70() {
        return MC2_CALL_MEMBER<0x00603B70, void>(this);
    }
};
static_assert(sizeof(unk_603B10) == 0x1C, "Wrong size for unk_603B10");

extern std::array<unk_603B10, 4> &glo_85FAA0;

inline void sub_6040E0() {
    for (unk_603B10 &x : glo_85FAA0) x.sub_603B70();
}
