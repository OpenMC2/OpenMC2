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

class unk_5D6A30 {
private:
    void *vtable;
    unk_5D6A30 *unk04;
    unk_5D6A30 *unk08;

public:
    unk_5D6A30() {
        MC2_PROC_MEMBER<void>(0x005D6A30, this);
    }

    // mc2: 0x005D6AF0
    ~unk_5D6A30() {
        MC2_PROC_MEMBER<void>(0x005D6AF0, this);
    }
};

#define glo_6CE520 MC2_GLOBAL<unk_5D6A30>(0x006CE520)
#define glo_6CE52C MC2_GLOBAL<unk_5D6A30>(0x006CE52C)
#define glo_6CE538 MC2_GLOBAL<unk_5D6A30>(0x006CE538)
#define glo_6CE544 MC2_GLOBAL<unk_5D6A30>(0x006CE544)
#define glo_6CE550 MC2_GLOBAL<unk_5D6A30>(0x006CE550)
#define glo_6CE55C MC2_GLOBAL<unk_5D6A30>(0x006CE55C)
#define glo_6CE568 MC2_GLOBAL<unk_5D6A30>(0x006CE568)
