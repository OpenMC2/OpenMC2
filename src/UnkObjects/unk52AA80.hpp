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

// originally malloc'd in mcaudiomgr.c
// child to a class unk_5D39A0?
class unk_52AA80 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
    };

protected:
    const void *vtable;
    std::uint8_t pad04[0x4D];
    std::uint8_t unk51;
    std::uint8_t pad52[0x46];

public:
    unk_52AA80(bool arg1) {
        MC2_CALL_MEMBER<0x0052AA80, void>(this, arg1);
    }

    MC2_SCALAR_DELETING_DESTRUCTOR(unk_52AA80) {
        MC2_CALL_MEMBER<0x0052ADD0, void>(this);
    }

    void vir10() {
        static_cast<const vtable_t *>(this->vtable)->vir_10(this);
    }

    void set_unk51_1() { unk51 = 1; }
};
static_assert(sizeof(unk_52AA80) == 0x98, "Wrong size for unk_52AA80");

extern unk_52AA80 *(&glo_6CE2E4);
inline unk_52AA80 *sub_52B6C0(bool arg1) {
    return glo_6CE2E4 = new unk_52AA80(arg1);
}
