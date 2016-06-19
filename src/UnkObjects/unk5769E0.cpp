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
#include "../Addresses.hpp"

#include <cstring>

// mc2: 0x005769E0
unk_5769E0::unk_5769E0() {
    unk00 = MC2_POINTER<void>(0x00651408); // virtual function pointers?

    unk08 = nullptr;
    unk0C = 0;
    unk18 = 0;
    unk1C = 0;
    unkE8 = 0;
    unkEC = 0x0008;
    unkEE = 0x0F00;
    unkF0 = 0;
    unkF4 = 0x000C;
    unkF6 = 0x1680;
    unkF8 = 0;
    unkFC = 0x0010;
    unkFE = 0x1E00;
    unk100 = 0;
    unk104 = 0x0020;
    unk106 = 0x3C00;
    unk108 = 0;
    unk10C = 0x0030;
    unk10E = 0x5A00;
    unk110 = 0;
    unk114 = 0x0040;
    unk116 = 0x7800;

    unk04 = glo_6C5240;
    glo_6C5240 = this;

    // A lot of function-pointers?
    if (MC2_GLOBAL<void *>(0x00679784) != MC2_POINTER<void>(0x005764A0))
        MC2_GLOBAL<void *>(0x00679784) = MC2_POINTER<void>(0x005764A0);
    if (MC2_GLOBAL<void *>(0x00679788) != MC2_POINTER<void>(0x00576530))
        MC2_GLOBAL<void *>(0x00679788) = MC2_POINTER<void>(0x00576530);
    if (MC2_GLOBAL<void *>(0x0067978C) != MC2_POINTER<void>(0x005769C0))
        MC2_GLOBAL<void *>(0x0067978C) = MC2_POINTER<void>(0x005769C0);
    if (MC2_GLOBAL<void *>(0x00679790) != MC2_POINTER<void>(0x005769D0))
        MC2_GLOBAL<void *>(0x00679790) = MC2_POINTER<void>(0x005769D0);
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
        glo_6C5254 = 1;
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
