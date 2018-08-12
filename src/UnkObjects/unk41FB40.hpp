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

// originally malloc'd in layerfrontend.c
class unk_41FB40 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };

private:
    const void *vtable;
    std::uint8_t pad04[0x54];

public:
    unk_41FB40() {
        MC2_CALL_MEMBER<0x0041FB40, void>(this);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_41FB40) {
        MC2_CALL_MEMBER<0x0041EA90, void>(this);
    }

    void sub_420B70() {
        MC2_CALL_MEMBER<0x00420B70, void>(this);
    }

    void sub_41A960() {
        MC2_CALL_MEMBER<0x0041A960, void>(this);
    }
};
static_assert(sizeof(unk_41FB40) == 0x58, "Wrong size for unk_41FB40");
