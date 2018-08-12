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

#include "unk4094A0.hpp"

// originally malloc'd in layermgr.c
class unk_402800 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    const std::array<unk_4094A0 *, 9> ptrs; // 0x04
    // unions to prevent automatic destructor calls
    union { unk_40AE70 unk28; };
    union { unk_40AB30 unk5C; };
    union { unk_40A940 unk78; };
    union { unk_40A4A0 unk94; };
    union { unk_409ED0 unkB8; };
    union { unk_409DF0 unkD4; };
    union { unk_409A70 unkE8; };
    union { unk_409CF0 unk104; };
    union { unk_409C50 unk118; };

public:
    unk_402800();
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_402800);

    // Reference version of mc2: 0x004025C0
    unk_4094A0 &get(std::size_t index) {
        assert(index < 9);
        assert(ptrs_verify());
        return *ptrs[index];
    }

    // Individual getters for each index of mc2: 0x004025C0.
    // Returns the sub-type of the element, which removes
    // the need for the caller to cast the result, providing
    // better type safety. Use when the index is a constant.
    unk_40AE70 &get0() { assert(ptrs_verify()); return unk28; }
    unk_40AB30 &get1() { assert(ptrs_verify()); return unk5C; }
    unk_40A940 &get2() { assert(ptrs_verify()); return unk78; }
    unk_40A4A0 &get3() { assert(ptrs_verify()); return unk94; }
    unk_409ED0 &get4() { assert(ptrs_verify()); return unkB8; }
    unk_409DF0 &get5() { assert(ptrs_verify()); return unkD4; }
    unk_409A70 &get6() { assert(ptrs_verify()); return unkE8; }
    unk_409CF0 &get7() { assert(ptrs_verify()); return unk104; }
    unk_409C50 &get8() { assert(ptrs_verify()); return unk118; }

    void sub_402970() {
        MC2_CALL_MEMBER<0x00402970, void>(this);
    }

public:
    // mc2: 0x004025C0 (don't directly use; for hooking)
    unk_4094A0 * sub_4025C0(std::uint32_t index) {
        return &this->get(index);
    }

private:
    std::array<unk_4094A0 *, 9> ptrs_init();
    bool ptrs_verify();
};
static_assert(sizeof(unk_402800) == 0x12C, "Wrong size for unk_421350");

extern std::int32_t &glo_6622B8;
extern std::int32_t &glo_6622BC;

extern unk_402800 *(&glo_692E88);
inline unk_402800 *sub_4028E0() {
    return glo_692E88 = new unk_402800;
}
