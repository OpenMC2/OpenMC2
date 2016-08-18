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

#include "unk613330.hpp"
#include "../Logging.hpp"

// mc2:0x00659B0C
static unk_613330::unk_613330_vTable unk_613330_vtable = {
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005ED480),
    MC2_PROC_MEMBER_PTR<void, unk_613330, char*, int32_t, char*, char*>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00619AB9),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005CA940),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00406990),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613770),
    &unk_613330::impl_1C,
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613800),
    &unk_613330::impl_24,
    MC2_PROC_MEMBER_PTR<void, unk_613330, char*, char*, char*>(0x00613520)
};

unk_613330::unk_613330() : vtable(&unk_613330_vtable) {
    glo_860220 = this;
}

// mc2: 0x00613780
void unk_613330::impl_1C(char *unk1, char *unk2, int32_t unk3, int32_t unk4) {
    char unk5[256];
    vir_04(unk5, 256, unk1, unk2);

    (MC2_PROC_PTR<void, char *, int32_t>(0x00617C40))(unk5, unk4);
}

// mc2: 0x006134F0
bool unk_613330::impl_24(char *unk1) {
    if (unk1 == nullptr)
        return true;

    if (*unk1 == '\\' || *unk1 == '/')
        return false;

    if (unk1[1] == ':')
        return false;

    return true;
}