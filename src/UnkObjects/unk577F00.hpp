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

// originally malloc'd in layercity.c
class unk_577F00 {
private:
    std::uint8_t pad00[0x08];

public:
    unk_577F00(std::uint32_t arg0) {
        MC2_CALL_MEMBER<0x00577F00, void>(this, arg0);
    }

    void sub_578000() {
        return MC2_CALL_MEMBER<0x00578000, void>(this);
    }
};
static_assert(sizeof(unk_577F00) == 0x08, "Wrong size for unk_577F00");

extern unk_577F00 *(&glo_6C5304);
