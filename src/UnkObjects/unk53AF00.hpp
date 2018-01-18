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

class unk_53AF00 {
private:
    std::uint8_t pad00[0x3C4];

public:
    unk_53AF00() {
        MC2_PROC_MEMBER<void>(0x0053AF00, this);
    }

    void sub_53ACB0(const char *a) {
        MC2_PROC_MEMBER<void>(0x0053ACB0, this, a);
    }
};

#define glo_6C32C8 MC2_GLOBAL<unk_53AF00>(0x006C32C8)
#define glo_6C2E88 MC2_GLOBAL<unk_53AF00>(0x006C2E88)
