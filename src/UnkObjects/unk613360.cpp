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

#include "unk613360.hpp"
#include "unk613330.hpp"
#include "../Game.hpp"
#include <string>

// mc2:0x00659B38
unk_613360::vtable_t unk_613360::vtable_values = {
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005ED480),
    &unk_613360::impl_04,
    MC2_PROC_MEMBER_PTR<void, unk_613360>(0x00613380),
    &unk_613360::impl_0C,
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005CA940),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00406990),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613770),
    &unk_613330::impl_1C,
    &unk_613330::impl_20,
    &unk_613330::impl_24,
    &unk_613330::impl_28
};

unk_613360::unk_613360() {
    vtable = &unk_613360::vtable_values;
    unk104 = 0;
}

//mc2:0x006136C0
void unk_613360::impl_04(char *destination, std::uint32_t unk2, char *unk3, char *extension) {
    if (vir_24(unk3) == false) {
        destination[0] = '\0';
        vir_28(destination, unk3, extension);
        return;
    }

    safe_strncpy(destination, (this->unk104 != 0) ? this->unk04 : glo_860120, 256);
    vir_28(destination, unk3, extension);
}

//mc2:0x00613470
void unk_613360::impl_0C() {
    this->unk104--;
}
