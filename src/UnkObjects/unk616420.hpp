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
#include "../FileHandler.hpp"

class unk_616420 {
private:
    struct vtable_t {
        mc2_proc_thiscall_ptr<void, unk_616420> vir_00;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_04;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_08;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_0C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_10;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_14;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_18;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_1C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_20;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_24;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_28;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_2C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_30;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_34;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_38;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_3C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_40;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_44;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_48;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_4C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_50;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_54;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_58;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_5C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_60;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_64;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_68;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_6C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_70;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_74;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_78;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_7C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_80;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_84;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_88;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_8C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_90;
        mc2_proc_thiscall_ptr<bool, unk_616420, const char *, std::uint32_t> vir_94;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_98;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_9C;
        mc2_proc_thiscall_ptr<void, unk_616420> vir_100;
    };
    static vtable_t vtable_values;

protected:
    void *vtable;
    char *unk04;
    std::uint32_t unk08;
    FileHandler *unk0C;
    std::uint32_t unk10;
    std::uint32_t unk14;
    std::uint8_t unk18;
    std::uint8_t unk19[0x7F];
    std::uint32_t unk98;
    std::uint32_t unk9C;

public:
    unk_616420(char *unk1, FileHandler *unk2);

    void sub_615130(char *unk1, FileHandler *unk2);

    bool vir_94(char *unk1, std::uint32_t unk2) {
        return static_cast<vtable_t*>(vtable)->vir_94(this, unk1, unk2);
    }

    // Use vir_94() to call
    // mc2: 0x00615B70
    bool impl_94(const char *unk1, std::uint32_t unk2);

    bool sub_6154D0(char *unk1, std::uint32_t unk2) {
        return mc2_call_proc_thiscall<0x006154D0, bool>(this, unk1, unk2);
    }

    std::int32_t sub_47C920(char *unk1, std::uint32_t unk2) {
        return mc2_call_proc_thiscall<0x0047C920, std::int32_t>(this, unk1, unk2);
    }

    std::int32_t read_integer() {
        return mc2_call_proc_thiscall<0x00615790, std::int32_t>(this);
    }
};

static_assert(sizeof(unk_616420) == 0xA0, "Bad Size: unk_616420");

void sub_615740(unk_616420 *unk1, char *format, ...);
