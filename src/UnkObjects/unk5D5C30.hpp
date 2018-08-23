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

#include "unk52AA80.hpp"

class unk_5D5C30 {
private:
    const void *vtable;
    std::uint8_t pad04[0x34];

public:
    unk_5D5C30() {
        MC2_CALL_MEMBER<0x005D5C30, void>(this);
    }
    // mc2: 0x005D5BD0
    unk_5D5C30(const char *arg0) {
        MC2_CALL_MEMBER<0x005D5BD0, void>(this, arg0);
    }

    void sub_5D5800(unk_52AA80 *arg0) {
        MC2_CALL_MEMBER<0x005D5800, void>(this, arg0);
    }
};
static_assert(sizeof(unk_5D5C30) == 0x38, "Wrong size for unk_5D5C30");
