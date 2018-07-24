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

#include "unk4020F0.hpp"
#include "unk405C90.hpp"
#include "unk477E80.hpp"
#include "unk4788D0.hpp"
#include "unk482C30.hpp"
#include "unk4CE870.hpp"
#include "unk52AA80.hpp"
#include "unk53C670.hpp"
#include "unk53C9E0.hpp"
#include "unk57DC70.hpp"
#include "unk612850.hpp"
#include "unk6144B0.hpp"
#include "unk6633B0.hpp"

// mc2: 0x0062D530
unk_4020F0::vtable_t unk_4020F0::vtable_values = {
    MC2_PROC_MEMBER_PTR<unk_4020F0 *, void, bool>(0x00402100),
};

void unk_4020F0::sub_401860() {
    glo_675024 = false;
    sub_53DE60();
    sub_53C6B0();
    sub_405D50();

    if (sub_612E10("nooverframe")) glo_662284 = false;
    if (sub_612E10("drawnothing")) glo_692E6C = true;
    sub_52B6C0(!sub_612E10("noaudio"));
    unk_614400 var10(sub_5D36D0);
    glo_860618.sub_6144D0(&var10);
    sub_4069B0();
    glo_6C50F0.unk02 = false;
    glo_6C50F0.sub_6126E0(0xD3);
    sub_4CEB00(0x13);
    sub_5670D0(nullptr);
    this->unk04 = false;

    sub_53C9E0();
    sub_479100();
    sub_477EF0();
    sub_482C60();

    sub_40E240();
    glo_8582A8 = 0;
    glo_6745C0 = 0;
    glo_8582C4 = "popup";
    sub_57E250();
    glo_675028 = glo_662288;
}

MC2_DEF_PROC(sub_4069B0, 0x004069B0);
MC2_DEF_PROC(sub_40E240, 0x0040E240);
MC2_DEF_PROC(sub_5670D0, 0x005670D0);
MC2_DEF_PROC(sub_5D36D0, 0x005D36D0);

MC2_DEF_GLOBAL(glo_662284, 0x00662284);
MC2_DEF_GLOBAL(glo_662288, 0x00662288);
MC2_DEF_GLOBAL(glo_6745C0, 0x006745C0);
MC2_DEF_GLOBAL(glo_675024, 0x00675024);
MC2_DEF_GLOBAL(glo_675028, 0x00675028);
MC2_DEF_GLOBAL(glo_692E6C, 0x00692E6C);
MC2_DEF_GLOBAL(glo_692E7C, 0x00692E7C);

MC2_DEF_GLOBAL(glo_8582A8, 0x008582A8);
MC2_DEF_GLOBAL(glo_8582C4, 0x008582C4);
