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

// mc2:0x00659B38
static unk_613360::unk_613360_vTable unk_613360_vtable = {
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005ED480),
    MC2_PROC_MEMBER_PTR<void, unk_613360>(0x006136C0),
    MC2_PROC_MEMBER_PTR<void, unk_613360>(0x00613380),
    MC2_PROC_MEMBER_PTR<void, unk_613360>(0x00613470),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x005CA940),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00406990),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613770),
    &unk_613330::impl_1C,
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613800),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x006134F0),
    MC2_PROC_MEMBER_PTR<void, unk_613330>(0x00613520)
};

unk_613360::unk_613360(){
    vtable = &unk_613360_vtable;
    unk104 = 0;
}