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

#include "unk5769E0.hpp"
#include "unk612850.hpp"

#include <cstring>

// mc2: 0x00651408
const unk_5769E0::vtable_t unk_5769E0::vtable_values = {
    &unk_5769E0::scalar_deleter,
    MC2_PROC_MEMBER_PTR<void, void>(0x00575ED0),
};

unk_5769E0::unk_5769E0() {
    vtable = &vtable_values;
    next = global_last_unk5769E0;
    global_last_unk5769E0 = this;

    // A lot of function-pointers?
    glo_679784 = sub_5764A0;
    glo_679788 = sub_576530;
    glo_67978C = sub_5769C0;
    glo_679790 = sub_5769D0;
}

// mc2: 0x00575B70
void unk_5769E0::destructor() {
    vtable = &vtable_values;
    unk_5769E0 **x = &global_last_unk5769E0;
    while (*x != this) x = &(*x)->next;
    *x = next;
    unk08 = nullptr;
}

// mc2: 0x00575BA0
void unk_5769E0::sub_575BA0(void *a, std::uint32_t b, std::uint8_t c, std::uint8_t d) {
    unk08 = a;
    unk14 = 0;
    unkE8 = 0;
    unkF0 = 0;
    unkF8 = 0;
    unk100 = 0;
    unk108 = 0;
    unk110 = 0;

    if (sub_612E10("allocid") != 0) {
        glo_6C5254 = true;
        sub_612E30("allocid", 0, &glo_6C524C);
    }

    unk0C = b;
    unk10 = 0;
    unk20 = c;
    unk21 = 1;
    unk22 = d;
    unk23 = 0;
    unkE4 = 0;

    if (c != 0) std::memset(unk24, 0, 0x80);
    std::memset(unkA4, 0, 0x40);
}

MC2_DEF_PROC(sub_5764A0, 0x005764A0);
MC2_DEF_PROC(sub_576530, 0x00576530);
MC2_DEF_PROC(sub_5769C0, 0x005769C0);
MC2_DEF_PROC(sub_5769D0, 0x005769D0);

MC2_DEF_GLOBAL(glo_679784, 0x00679784);
MC2_DEF_GLOBAL(glo_679788, 0x00679788);
MC2_DEF_GLOBAL(glo_67978C, 0x0067978C);
MC2_DEF_GLOBAL(glo_679790, 0x00679790);

MC2_DEF_GLOBAL(global_last_unk5769E0, 0x006C5240); // glo_6C5240
MC2_DEF_GLOBAL(glo_6C5254, 0x006C5254);
MC2_DEF_GLOBAL(global_primary_unk5769E0, 0x006C5258); // glo_6C5258

MC2_DEF_GLOBAL(glo_6C524C, 0x006C524C);
MC2_DEF_GLOBAL(glo_6C52E0, 0x006C52E0);
MC2_DEF_GLOBAL(glo_6C52E8, 0x006C52E8);

