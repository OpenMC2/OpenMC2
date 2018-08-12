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

// originally malloc'd in racemgr.c
class unk_47C830 {
public:
    class unk_04_t {
    protected:
        struct vtable_t {
            std::uint8_t pad00[0x10];
            MC2_PROC_MEMBER_PTR<void, void> vir_10;
        };

        const void *vtable;
    public:
        std::uint8_t pad04[0x550];
        const char *unk554;

        void vir10() {
            return static_cast<const vtable_t *>(this->vtable)->vir_10(this);
        }
    };

protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };

protected:
    const void *vtable;
public:
    unk_04_t *unk04;
    std::uint8_t pad08[0x08];

public:
    unk_47C830() {
        MC2_CALL_MEMBER<0x0047C830, void>(this);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_47C830) {
        MC2_CALL_MEMBER<0x0047bf50, void>(this);
    }
};
static_assert(sizeof(unk_47C830) == 0x10, "Wrong size for unk_47C830");

extern unk_47C830 *(&glo_697B88);
inline unk_47C830 *sub_47C8C0() {
    return glo_697B88 = new unk_47C830();
}
