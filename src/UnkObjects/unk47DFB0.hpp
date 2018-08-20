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

// originally malloc'd in pausemenu.cpp
class unk_47DFB0 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };
    static const vtable_t vtable_values;

    struct unk54_t {
        std::uint8_t pad00[0x178];
        std::uint8_t unk178;
    };

protected:
    const void *vtable;
public:
    std::uint8_t pad04[0x50];
    unk54_t *unk54;
    std::uint8_t pad58[0x90];

public:
    unk_47DFB0() {
        MC2_CALL_MEMBER<0x0047DFB0, void>(this);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_47DFB0) {
        MC2_CALL_MEMBER<0x0047C950, void>(this);
    }
};
static_assert(sizeof(unk_47DFB0) == 0xE8, "Wrong size for unk_47DFB0");

extern unk_47DFB0 *(&glo_697B90);
inline unk_47DFB0 *sub_47E150() {
    return glo_697B90 = new unk_47DFB0;
}
