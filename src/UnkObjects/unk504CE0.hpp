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
class unk_504CE0 {
private:
    std::uint8_t pad00[0x10274];

public:
    unk_504CE0() {
        MC2_CALL_MEMBER<0x00504CE0, void>(this);
    }

    void sub_503F30() {
        return MC2_CALL_MEMBER<0x00503F30, void>(this);
    }
};
static_assert(sizeof(unk_504CE0) == 0x10274, "Wrong size for unk_504CE0");

extern unk_504CE0 *(&glo_69C868);
