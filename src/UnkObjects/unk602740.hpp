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

class unk_602740 {
private:

public:
    unk_602740() {
        MC2_PROC_MEMBER<void>(0x00602740, this);
    }

    // mc2: 0x006025C0
    ~unk_602740() {
        MC2_PROC_MEMBER<void>(0x006025C0, this);
    }
};

#define glo_85D400 MC2_GLOBAL<unk_602740>(0x0085D400)
