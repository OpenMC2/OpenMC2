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

#include <cstdint>

class unk_5769E0_p;
using unk_5769E0 = MC2_DestroyingWrapper<unk_5769E0_p>;

// Related to original malloc implementation
class unk_5769E0_p {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void> vir_04;
    };

private:
    static const vtable_t vtable_values;

private:
    const void *vtable;
    unk_5769E0 *next;
    void *unk08 = nullptr;
    std::uint32_t unk0C = 0;
    std::uint32_t unk10;
    std::uint32_t unk14;
    std::uint32_t unk18 = 0;
    std::uint32_t unk1C = 0;
    std::uint8_t unk20;
    std::uint8_t unk21;
    std::uint8_t unk22;
    std::uint8_t unk23;
    std::uint8_t unk24[0x80];
    std::uint8_t unkA4[0x40];
    std::uint32_t unkE4;
    std::uint32_t unkE8 = 0;
    std::uint16_t unkEC = 0x0008;
    std::uint16_t unkEE = 0x0F00;
    std::uint32_t unkF0 = 0;
    std::uint16_t unkF4 = 0x000C;
    std::uint16_t unkF6 = 0x1680;
    std::uint32_t unkF8 = 0;
    std::uint16_t unkFC = 0x0010;
    std::uint16_t unkFE = 0x1E00;
    std::uint32_t unk100 = 0;
    std::uint16_t unk104 = 0x0020;
    std::uint16_t unk106 = 0x3C00;
    std::uint32_t unk108 = 0;
    std::uint16_t unk10C = 0x0030;
    std::uint16_t unk10E = 0x5A00;
    std::uint32_t unk110 = 0;
    std::uint16_t unk114 = 0x0040;
    std::uint16_t unk116 = 0x7800;

public:
    unk_5769E0_p();
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_5769E0_p);

    void sub_575BA0(void *a, std::uint32_t b, std::uint8_t c, std::uint8_t d);

    void sub_575B10() {
        MC2_CALL_MEMBER<0x00575B10, void>(this);
    }

    void sub_576210() {
        MC2_CALL_MEMBER<0x00576210, void>(this);
    }
};
static_assert(std::is_trivially_destructible<unk_5769E0_p>::value, "unk_5769E0_p is not trivially destructible");

extern MC2_PROC_PTR<void, std::uint32_t> sub_5764A0;
extern MC2_PROC_PTR<void, std::uint32_t> sub_576530;
extern MC2_PROC_PTR<void> sub_5769C0;
extern MC2_PROC_PTR<void> sub_5769D0;

extern MC2_PROC_PTR<void, std::uint32_t> &glo_679784;
extern MC2_PROC_PTR<void, std::uint32_t> &glo_679788;
extern MC2_PROC_PTR<void> &glo_67978C;
extern MC2_PROC_PTR<void> &glo_679790;

extern unk_5769E0 *&global_last_unk5769E0; // glo_6C5240
extern bool &glo_6C5254;
extern unk_5769E0 *&global_primary_unk5769E0; // glo_6C5258

extern int32_t &glo_6C524C;
extern unk_5769E0 *&glo_6C52E0;
extern unk_5769E0 *&glo_6C52E8;

