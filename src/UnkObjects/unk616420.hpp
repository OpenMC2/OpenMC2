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
protected:
    struct vtable_t {
        MC2_PROC_MEMBER_PTR<void, void> vir_00;
        MC2_PROC_MEMBER_PTR<void, void> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<void, void> vir_18;
        MC2_PROC_MEMBER_PTR<void, void> vir_1C;
        MC2_PROC_MEMBER_PTR<void, void> vir_20;
        MC2_PROC_MEMBER_PTR<void, void> vir_24;
        MC2_PROC_MEMBER_PTR<void, void> vir_28;
        MC2_PROC_MEMBER_PTR<void, void> vir_2C;
        MC2_PROC_MEMBER_PTR<void, void> vir_30;
        MC2_PROC_MEMBER_PTR<void, void> vir_34;
        MC2_PROC_MEMBER_PTR<void, void> vir_38;
        MC2_PROC_MEMBER_PTR<void, void> vir_3C;
        MC2_PROC_MEMBER_PTR<void, void> vir_40;
        MC2_PROC_MEMBER_PTR<void, void> vir_44;
        MC2_PROC_MEMBER_PTR<void, void> vir_48;
        MC2_PROC_MEMBER_PTR<void, void> vir_4C;
        MC2_PROC_MEMBER_PTR<void, void> vir_50;
        MC2_PROC_MEMBER_PTR<void, void> vir_54;
        MC2_PROC_MEMBER_PTR<void, void> vir_58;
        MC2_PROC_MEMBER_PTR<void, void> vir_5C;
        MC2_PROC_MEMBER_PTR<void, void> vir_60;
        MC2_PROC_MEMBER_PTR<void, void> vir_64;
        MC2_PROC_MEMBER_PTR<void, void> vir_68;
        MC2_PROC_MEMBER_PTR<void, void> vir_6C;
        MC2_PROC_MEMBER_PTR<void, void> vir_70;
        MC2_PROC_MEMBER_PTR<void, void> vir_74;
        MC2_PROC_MEMBER_PTR<void, void> vir_78;
        MC2_PROC_MEMBER_PTR<void, void> vir_7C;
        MC2_PROC_MEMBER_PTR<void, void> vir_80;
        MC2_PROC_MEMBER_PTR<void, void> vir_84;
        MC2_PROC_MEMBER_PTR<void, void> vir_88;
        MC2_PROC_MEMBER_PTR<void, void> vir_8C;
        MC2_PROC_MEMBER_PTR<void, void> vir_90;
        MC2_PROC_MEMBER_PTR<bool, void, const char *, std::uint32_t> vir_94;
        MC2_PROC_MEMBER_PTR<void, void> vir_98;
        MC2_PROC_MEMBER_PTR<void, void> vir_9C;
        MC2_PROC_MEMBER_PTR<void, void> vir_100;
    };
private:
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
        return MC2_CALL_MEMBER<0x006154D0, bool>(this, unk1, unk2);
    }

    std::int32_t sub_47C920(char *unk1, std::uint32_t unk2) {
        return MC2_CALL_MEMBER<0x0047C920, std::int32_t>(this, unk1, unk2);
    }

    std::int32_t read_integer() {
        return MC2_CALL_MEMBER<0x00615790, std::int32_t>(this);
    }
};

static_assert(sizeof(unk_616420) == 0xA0, "Bad Size: unk_616420");

void sub_615740(unk_616420 *unk1, char *format, ...);
