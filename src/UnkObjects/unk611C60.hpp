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

extern MC2_PROC_PTR<std::uint32_t> get_lower_rdtsc; // 0x00611C30

extern float &glo_8600DC;

class unk_611C60 {
private:
    std::uint32_t unk00;

public:
    unk_611C60() {
        MC2_CALL_MEMBER<0x00611C60, void>(this);
    }

    void fetch_time() { unk00 = get_lower_rdtsc(); }

    std::uint32_t get_delta() const { return get_lower_rdtsc() - unk00; }
    float get_delta_seconds() const { return get_delta() * glo_8600DC; }
};

extern unk_611C60 &glo_692E68;
extern unk_611C60 &glo_6993A4;
extern unk_611C60 &glo_858358;
extern unk_611C60 &glo_85835C;
extern unk_611C60 &glo_858354;
extern unk_611C60 &glo_8602FC;
