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
#include "unk613330.hpp"

class unk_613360 : public unk_613330 {
public:
    struct unk_613360_vTable{
        void (__thiscall *vir_00)(unk_613330 *);
        void (__thiscall unk_613360::* vir_04)(char *destination, int32_t unk2, char *unk3, char *extension);
        void (__thiscall *vir_08)(unk_613360 *);
        void (__thiscall unk_613360::* vir_0C)();
        void (__thiscall *vir_10)(unk_613330 *);
        void (__thiscall *vir_14)(unk_613330 *);
        void (__thiscall *vir_18)(unk_613330 *);
        FileHandler *(__thiscall unk_613330::* vir_1C)(char *unk1, char *unk2, int32_t unk3, int32_t unk4);
        FileHandler *(__thiscall unk_613330::* vir_20)(char *unk1, char *unk2, int32_t unk3);
        bool (__thiscall unk_613330::* vir_24)(char *unk1);
        void (__thiscall unk_613330::* vir_28)(char *destination, char *unk2, char *extension);
    };
private:
    char unk04[0x100];
    std::uint32_t unk104;

public:
    unk_613360();

    void impl_04(char *destination, int32_t unk2, char *unk3, char *extension);
    void impl_0C();
};
