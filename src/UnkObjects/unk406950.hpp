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

// originally malloc'd in netmanager.c
class unk_406950_p {
protected:
    // giant vtable size 0x1F4 (125 functions)
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        std::uint8_t pad04[0x54];
        MC2_PROC_MEMBER_PTR<void, void> vir_58;
        std::uint8_t pad5C[0x198];
    };
    static_assert(sizeof(vtable_t) == 0x1F4, "Wrong vtable size for unk_406950_p");

protected:
    const void *vtable;
public:
    std::uint8_t pad04[0x04];
    std::int32_t unk08;
    std::uint8_t pad0C[0x68];
    std::uint32_t unk74;
    std::uint8_t pad78[0x288];

public:
    unk_406950_p(std::uint32_t arg1, std::uint32_t arg2) {
        MC2_CALL_MEMBER<0x00406950, void>(this, arg1, arg2);
    }

    MC2_SCALAR_DELETING_DESTRUCTOR(unk_406950_p) {
        MC2_CALL_MEMBER<0x004069A0, void>(this);
    }

    void vir58() {
        return static_cast<const vtable_t *>(this->vtable)->vir_58(this);
    }

    void sub_535DC0(std::uint32_t arg0) {
        MC2_CALL_MEMBER<0x00535DC0, void>(this, arg0);
    }
};
static_assert(sizeof(unk_406950_p) == 0x300, "Wrong size for unk_406950_p");
static_assert(std::is_trivially_destructible<unk_406950_p>::value, "unk_406950_p is not trivially destructible");

using unk_406950 = MC2_DestroyingWrapper<unk_406950_p>;

extern unk_406950 *(&glo_6C2BB4);
extern unk_406950 *(&glo_6C38B4);
