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

class unk_4020F0 {
protected:
    struct vtable_t {
        MC2_PROC_MEMBER_PTR<unk_4020F0 *, void, bool> vir_00;
    };

private:
    static vtable_t vtable_values;

    void *vtable;
    std::uint32_t unk04;
    std::uint8_t pad08[4];

public:
    unk_4020F0() : vtable(&vtable_values), unk04(0) { }

    unk_4020F0 *vir_00(bool unk0) {
        return static_cast<vtable_t *>(vtable)->vir_00(this, unk0);
    }

    void sub_401860();

    void sub_402120() {
        return MC2_CALL_MEMBER<0x00402120, void>(this);
    }
};

unk_4020F0 *sub_402560();

extern MC2_PROC_PTR<void> sub_405D50;
extern MC2_PROC_PTR<void> sub_4069B0;
extern MC2_PROC_PTR<void> sub_40E240;
extern MC2_PROC_PTR<void> sub_477EF0;
extern MC2_PROC_PTR<void> sub_479100;
extern MC2_PROC_PTR<void> sub_482C60;
extern MC2_PROC_PTR<void, std::uint32_t> sub_4CEB00;
extern MC2_PROC_PTR<void, bool> sub_52B6C0;
extern MC2_PROC_PTR<void> sub_53C6B0;
extern MC2_PROC_PTR<void> sub_53C9E0;
extern MC2_PROC_PTR<void> sub_53DE60;
extern MC2_PROC_PTR<void, bool> sub_5670D0;
extern MC2_PROC_PTR<void> sub_57E250;
extern MC2_PROC_PTR<void> sub_5D36D0;

extern bool &glo_662284;
extern const char *(&glo_662288);
extern std::uint32_t &glo_6745C0;
extern bool &glo_675024;
extern const char *(&glo_675028);
extern bool &glo_692E6C;
extern unk_4020F0 *(&glo_692E7C);

extern std::uint32_t &glo_8582A8;
extern const char *(&glo_8582C4);
