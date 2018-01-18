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

class unk_579410 {
private:
    std::uint8_t pad00[0xA8];

public:
    unk_579410() {
        MC2_PROC_MEMBER<void>(0x00579410, this);
    }

    // mc2: 0x005E3280
    ~unk_579410() {
        MC2_PROC_MEMBER<void>(0x005E3280, this);
    }
};

#define glo_699890 MC2_GLOBAL<unk_579410>(0x00699890)
#define glo_69B6A0 MC2_GLOBAL<unk_579410>(0x0069B6A0)
