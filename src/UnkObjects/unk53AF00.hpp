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

// names from mc2: 0x00663300
enum class RaceType : std::uint32_t {
    roam,
    find_hook,
    hookman_cruise,
    follow,
    cp_unordered,
    cp_unordered_time_local,
    cp_unordered_time_global,
    cp_ordered,
    cp_ordered_time_local,
    cp_ordered_time_global,
    capture_the_flag,
    bomb_tag,
    lose_the_cops,
    destroy,
};

class unk_53AF00 {
public:
    std::uint8_t pad00[0x18];
    RaceType unk18;
    std::uint8_t pad1C[0x1D];
    bool unk39;
    std::uint8_t pad3A[0x1E];
    char unk58[0x100];
    std::uint8_t pad158[0x1E0];
    std::uint32_t unk338;
    std::uint8_t pad33C[0x84];
    bool unk3C0;
    bool unk3C1;
    std::uint8_t pad3C2[0x02];

public:
    unk_53AF00() {
        MC2_CALL_MEMBER<0x0053AF00, void>(this);
    }

    void sub_53ACB0(const char *a) {
        MC2_CALL_MEMBER<0x0053ACB0, void>(this, a);
    }
};
static_assert(sizeof(unk_53AF00) == 0x3C4, "Wrong size for unk_53AF00");

extern unk_53AF00 &glo_6C32C8;
extern unk_53AF00 &glo_6C2E88;
