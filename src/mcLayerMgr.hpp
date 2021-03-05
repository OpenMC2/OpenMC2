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

#include "Addresses.hpp"

#include "UnkObjects/unk4094A0.hpp"

// originally malloc'd in layermgr.c
class mcLayerMgr_p {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    const std::array<unk_4094A0 *, 9> ptrs; // 0x04
    unk_40AE70_p unk28;
    unk_40AB30_p unk5C;
    unk_40A940_p unk78;
    unk_40A4A0_p unk94;
    unk_409ED0_p unkB8;
    unk_409DF0_p unkD4;
    unk_409A70_p unkE8;
    unk_409CF0_p unk104;
    unk_409C50_p unk118;

public:
    // mc2: 0x00402800
    mcLayerMgr_p();
    MC2_SCALAR_DELETING_DESTRUCTOR(mcLayerMgr_p);

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
    unk_40AE70 &get0() { assert(ptrs_verify()); return class_cast<unk_40AE70>(unk28); }
    unk_40AB30 &get1() { assert(ptrs_verify()); return class_cast<unk_40AB30>(unk5C); }
    unk_40A940 &get2() { assert(ptrs_verify()); return class_cast<unk_40A940>(unk78); }
    unk_40A4A0 &get3() { assert(ptrs_verify()); return class_cast<unk_40A4A0>(unk94); }
    unk_409ED0 &get4() { assert(ptrs_verify()); return class_cast<unk_409ED0>(unkB8); }
    unk_409DF0 &get5() { assert(ptrs_verify()); return class_cast<unk_409DF0>(unkD4); }
    unk_409A70 &get6() { assert(ptrs_verify()); return class_cast<unk_409A70>(unkE8); }
    unk_409CF0 &get7() { assert(ptrs_verify()); return class_cast<unk_409CF0>(unk104); }
    unk_409C50 &get8() { assert(ptrs_verify()); return class_cast<unk_409C50>(unk118); }

    void sub_402970() {
        MC2_CALL_MEMBER<0x00402970, void>(this);
    }

public:
    // mc2: 0x004025C0 (don't directly use; for hooking)
    unk_4094A0 *sub_4025C0(std::uint32_t index) {
        return &this->get(index);
    }

private:
    std::array<unk_4094A0 *, 9> ptrs_init();
    bool ptrs_verify();
};
static_assert(sizeof(mcLayerMgr_p) == 0x12C, "Wrong size for mcLayerMgr_p");
static_assert(std::is_trivially_destructible<mcLayerMgr_p>::value, "mcLayerMgr_p is not trivially destructible");

using mcLayerMgr = MC2_DestroyingWrapper<mcLayerMgr_p>;

extern std::int32_t &glo_6622B8;
extern std::int32_t &glo_6622BC;

extern mcLayerMgr *(&glo_692E88);
inline mcLayerMgr *sub_4028E0() {
    assert(glo_692E88 == nullptr);
    return glo_692E88 = new mcLayerMgr;
}
