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

class unk_5769E0 {
private:
    void *unk00;
    unk_5769E0 *unk04;
    void *unk08;
    std::uint32_t unk0C;
    std::uint32_t unk10;
    std::uint32_t unk14;
    std::uint32_t unk18;
    std::uint32_t unk1C;
    std::uint8_t unk20;
    std::uint8_t unk21;
    std::uint8_t unk22;
    std::uint8_t unk23;
    std::uint8_t unk24[0x80];
    std::uint8_t unkA4[0x40];
    std::uint32_t unkE4;
    std::uint32_t unkE8;
    std::uint16_t unkEC;
    std::uint16_t unkEE;
    std::uint32_t unkF0;
    std::uint16_t unkF4;
    std::uint16_t unkF6;
    std::uint32_t unkF8;
    std::uint16_t unkFC;
    std::uint16_t unkFE;
    std::uint32_t unk100;
    std::uint16_t unk104;
    std::uint16_t unk106;
    std::uint32_t unk108;
    std::uint16_t unk10C;
    std::uint16_t unk10E;
    std::uint32_t unk110;
    std::uint16_t unk114;
    std::uint16_t unk116;

public:
    unk_5769E0();

    // mc2: 0x00575B70
    inline ~unk_5769E0() {
        MC2_PROC_MEMBER<void>(0x00575B70, this);
    }

    void sub_575BA0(void *a, std::uint32_t b, std::uint8_t c, std::uint8_t d);

    inline void sub_575B10() {
        MC2_PROC_MEMBER<void>(0x00575B10, this);
    }
};

extern unk_5769E0 *&global_last_unk5769E0; // glo_6C5240
extern bool &glo_6C5254;
extern unk_5769E0 *&global_primary_unk5769E0; // glo_6C5258

extern int32_t &glo_6C524C;
extern unk_5769E0 *&glo_6C52E0;
extern unk_5769E0 *&glo_6C52E8;

