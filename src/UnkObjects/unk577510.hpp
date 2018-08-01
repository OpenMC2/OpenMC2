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
#include "unk5769E0.hpp"

class unk_577510 {
public:
    std::uint32_t unk00 = 0;
    std::uint32_t unk04 = 0;
    std::uint32_t unk08 = 0;
    std::uint32_t unk0C = 0;
    std::uint32_t unk10;

    void sub_5775A0(unk_5769E0 *a, std::uint32_t b, std::uint32_t c, std::uint32_t d, bool e) {
        return MC2_CALL_MEMBER<0x005775A0, void>(this, a, b, c, d, e);
    }

    void sub_577610() {
        return MC2_CALL_MEMBER<0x00577610, void>(this);
    }
};

extern unk_577510 *&glo_6C52E4;
