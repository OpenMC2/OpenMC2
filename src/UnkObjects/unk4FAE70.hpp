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

// originally malloc'd in layercity.c and raceeditor.cpp
class unk_4FAE70 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };

protected:
    const void *vtable;
    std::uint8_t pad04[0x6C];

public:
    unk_4FAE70() {
        MC2_CALL_MEMBER<0x004FAE70, void>(this);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_4FAE70) {
        MC2_CALL_MEMBER<0x004FAF30, void>(this);
    }

    void sub_4FBAA0() {
        MC2_CALL_MEMBER<0x004FBAA0, void>(this);
    }
};
static_assert(sizeof(unk_4FAE70) == 0x70, "Wrong size for unk_4FAE70");

extern unk_4FAE70 *(&glo_69C7D0);
