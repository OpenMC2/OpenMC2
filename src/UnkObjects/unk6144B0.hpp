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

class unk_6144B0 {
private:
    void *unk00;
    std::uint16_t unk04;
    std::uint16_t unk06;

public:
    constexpr unk_6144B0(void *unk00, std::uint16_t unk06) :
    unk00(unk00), unk04(0), unk06(unk06) { }
};

extern unk_6144B0 &glo_860300;
extern unk_6144B0 &glo_860618;

extern void *loc_860308;
extern void *loc_860508;
