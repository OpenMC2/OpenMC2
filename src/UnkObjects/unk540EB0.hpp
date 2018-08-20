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

// originally malloc'd in layerambients.c
class unk_540EB0 {
private:
    std::uint8_t pad00[0xEC];

public:
    unk_540EB0() {
        MC2_CALL_MEMBER<0x00540EB0, void>(this);
    }

    void sub_541280() {
        return MC2_CALL_MEMBER<0x00541280, void>(this);
    }
};
static_assert(sizeof(unk_540EB0) == 0xEC, "Wrong size for unk_540EB0");

extern unk_540EB0 *(&glo_6C38B8);
