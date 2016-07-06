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

#include <cstdint>

#include "../Addresses.hpp"

class unk_6C3250 {
private:
    std::uint8_t pad00[0x44];
    std::uint32_t unk44;
    std::uint32_t unk48;
    std::uint32_t unk4C;

public:
    inline void sub_53B6A0() {
        MC2_PROC_MEMBER<void>(0x0053B6A0, this);
    }

    inline std::uint32_t unk_6C3250::get_unk44() const { return this->unk44; } // mc2: 0x004DBA90
    inline std::uint32_t unk_6C3250::get_unk48() const { return this->unk48; } // mc2: 0x0055E930
    inline std::uint32_t unk_6C3250::get_unk4C() const { return this->unk4C; } // mc2: 0x0053B320
};

#define glo_6C3250 (MC2_GLOBAL<unk_6C3250>(0x006C3250))
