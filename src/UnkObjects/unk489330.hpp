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

// originally malloc'd in raceeditor.cpp
class unk_489330 {
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<void, void> vir_18;
        MC2_PROC_MEMBER_PTR<void, void> vir_1C;
        // ...
    };

    const void *vtable;
public:
    std::uint8_t pad04[0x550];
    const char *unk554;
    std::uint8_t pad558[0xB90];

public:
    unk_489330(std::uint32_t arg1) {
        MC2_CALL_MEMBER<0x00489330, void>(this, arg1);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_489330) {
        MC2_CALL_MEMBER<0x00489540, void>(this);
    }

    void sub_485530() {
        return MC2_CALL_MEMBER<0x00485530, void>(this);
    }

    void vir10() {
        return static_cast<const vtable_t *>(this->vtable)->vir_10(this);
    }
    void vir14() {
        return static_cast<const vtable_t *>(this->vtable)->vir_14(this);
    }
    void vir18() {
        return static_cast<const vtable_t *>(this->vtable)->vir_18(this);
    }
};
static_assert(sizeof(unk_489330) == 0x10E8, "Wrong size for unk_489330");
