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
#include "../Game.hpp"

class unk_616420 {
protected:
    void *vtable;
    char *unk04;
    uint32_t unk08;
    file_handle_struct *unk0C;
    uint32_t unk10;
    uint32_t unk14;
    uint8_t unk18;
    uint8_t unk19[0x7F];
    uint32_t unk98;
    uint32_t unk9C;

public:
    unk_616420(char *unk1, file_handle_struct *unk2);

    void sub_615130(char *unk1, file_handle_struct *unk2);

    bool sub_6154D0(char *unk1, uint32_t unk2) {
        return MC2_PROC_MEMBER<bool, unk_616420, char *, uint32_t>(0x006154D0, this, unk1, unk2);
    }

    int32_t sub_47C920(char *unk1, uint32_t unk2) {
        return MC2_PROC_MEMBER<int32_t, unk_616420, char *, uint32_t>(0x0047C920, this, unk1, unk2);
    }
};