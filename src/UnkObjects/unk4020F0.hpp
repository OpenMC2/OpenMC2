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

#include "unk401FD0.hpp"

class unk_4020F0 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
public:
    unk_401FD0 *unk04 = nullptr;
    std::uint8_t pad08[4];

public:
    unk_4020F0() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_4020F0) {
        MC2_CALL_MEMBER<0x00401820, void>(this);
    }

    void sub_401960() {
        MC2_CALL_MEMBER<0x00401960, void>(this);
    }

    void sub_401CB0() {
        MC2_CALL_MEMBER<0x00401CB0, void>(this);
    }

    void sub_4019C0() {
        MC2_CALL_MEMBER<0x004019C0, void>(this);
    }

    void sub_401E50(std::uint32_t arg0) {
        MC2_CALL_MEMBER<0x00401E50, void>(this, arg0);
    }

    void sub_401860();
    // mc2: 0x00402120
    void game_loop();
};

extern MC2_PROC_PTR<void> sub_4069B0;
extern MC2_PROC_PTR<void> sub_40E240;
extern MC2_PROC_PTR<void, const char *> sub_5670D0;
extern MC2_PROC_PTR<void> sub_5D36D0;
extern MC2_PROC_PTR<void> sub_5ECFD0;
extern MC2_PROC_PTR<void> sub_5ED000;
extern MC2_PROC_PTR<void, std::uint32_t> sub_5ED050;
extern MC2_PROC_PTR<void> sub_5ED0C0;
extern MC2_PROC_PTR<bool> sub_5ED220;
extern MC2_PROC_PTR<void, std::uint32_t> sub_5ED4A0;
extern MC2_PROC_PTR<void> sub_5ED9C0;
extern MC2_PROC_PTR<void> sub_5EF3F0;
extern MC2_PROC_PTR<void, std::uint32_t, std::uint32_t, float, std::uint32_t> sub_5EF420;
extern MC2_PROC_PTR<void> sub_5F0F00;
extern MC2_PROC_PTR<void> sub_613FC0;

extern bool &glo_662284;
extern const char *(&glo_662288);
extern bool &glo_6622B0;
extern std::uint32_t &glo_6745C0;
extern std::uint32_t &glo_674F9C;
extern bool &glo_675024;
extern const char *(&glo_675028);
extern float &glo_6797CC;
extern bool &glo_692E6C;
extern DWORD &glo_692E90;
extern std::uint8_t &glo_6A04B4;
extern std::uint32_t &glo_6A04BC;

extern unk_4020F0 *(&glo_692E7C);
inline unk_4020F0 *sub_402560() {
    return glo_692E7C = new unk_4020F0;
}

extern std::uint32_t &glo_8582A8;
extern const char *(&glo_8582C4);
extern std::uint32_t &glo_8582DC;
extern std::uint8_t &glo_858384;
