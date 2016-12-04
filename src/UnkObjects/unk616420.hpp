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
public:
    struct unk_616420_vTable {
        void(__thiscall *vir_00)(unk_616420 *);
        void(__thiscall *vir_04)(unk_616420 *);
        void(__thiscall *vir_08)(unk_616420 *);
        void(__thiscall *vir_0C)(unk_616420 *);
        void(__thiscall *vir_10)(unk_616420 *);
        void(__thiscall *vir_14)(unk_616420 *);
        void(__thiscall *vir_18)(unk_616420 *);
        void(__thiscall *vir_1C)(unk_616420 *);
        void(__thiscall *vir_20)(unk_616420 *);
        void(__thiscall *vir_24)(unk_616420 *);
        void(__thiscall *vir_28)(unk_616420 *);
        void(__thiscall *vir_2C)(unk_616420 *);
        void(__thiscall *vir_30)(unk_616420 *);
        void(__thiscall *vir_34)(unk_616420 *);
        void(__thiscall *vir_38)(unk_616420 *);
        void(__thiscall *vir_3C)(unk_616420 *);
        void(__thiscall *vir_40)(unk_616420 *);
        void(__thiscall *vir_44)(unk_616420 *);
        void(__thiscall *vir_48)(unk_616420 *);
        void(__thiscall *vir_4C)(unk_616420 *);
        void(__thiscall *vir_50)(unk_616420 *);
        void(__thiscall *vir_54)(unk_616420 *);
        void(__thiscall *vir_58)(unk_616420 *);
        void(__thiscall *vir_5C)(unk_616420 *);
        void(__thiscall *vir_60)(unk_616420 *);
        void(__thiscall *vir_64)(unk_616420 *);
        void(__thiscall *vir_68)(unk_616420 *);
        void(__thiscall *vir_6C)(unk_616420 *);
        void(__thiscall *vir_70)(unk_616420 *);
        void(__thiscall *vir_74)(unk_616420 *);
        void(__thiscall *vir_78)(unk_616420 *);
        void(__thiscall *vir_7C)(unk_616420 *);
        void(__thiscall *vir_80)(unk_616420 *);
        void(__thiscall *vir_84)(unk_616420 *);
        void(__thiscall *vir_88)(unk_616420 *);
        void(__thiscall *vir_8C)(unk_616420 *);
        void(__thiscall *vir_90)(unk_616420 *);
        void(__thiscall *vir_94)(unk_616420 *, char *, uint32_t);
        void(__thiscall *vir_98)(unk_616420 *);
        void(__thiscall *vir_9C)(unk_616420 *);
        void(__thiscall *vir_100)(unk_616420 *);
    };
protected:
    void *vtable;
    char *unk04;
    uint32_t unk08;
    FileHandler *unk0C;
    uint32_t unk10;
    uint32_t unk14;
    uint8_t unk18;
    uint8_t unk19[0x7F];
    uint32_t unk98;
    uint32_t unk9C;

public:
    unk_616420(char *unk1, FileHandler *unk2);

    void sub_615130(char *unk1, FileHandler *unk2);

    void vir_94(char *unk1, uint32_t unk2) {
        static_cast<unk_616420_vTable*>(vtable)->vir_94(this, unk1, unk2);
    }

    bool sub_6154D0(char *unk1, uint32_t unk2) {
        return MC2_PROC_MEMBER<bool, unk_616420, char *, uint32_t>(0x006154D0, this, unk1, unk2);
    }

    int32_t sub_47C920(char *unk1, uint32_t unk2) {
        return MC2_PROC_MEMBER<int32_t, unk_616420, char *, uint32_t>(0x0047C920, this, unk1, unk2);
    }

    int32_t read_integer() {
        return MC2_PROC_MEMBER<int32_t, unk_616420>(0x00615790, this);
    }
};

void sub_615740(unk_616420 *_this, char *format, ...);
