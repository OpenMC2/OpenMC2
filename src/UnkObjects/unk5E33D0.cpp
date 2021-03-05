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

#include "unk5E33D0.hpp"

#include "../Memory.hpp"

// mc2: 0x00656574
const unk_5E33D0_p::vtable_t unk_5E33D0_p::vtable_values = {
    &unk_5E33D0_p::scalar_deleter,
    MC2_PROC_MEMBER_PTR<bool, void>(0x005E32B0),
    MC2_PROC_MEMBER_PTR<bool, void>(0x005E3320),
    &mc2_thiscall::null<std::uint32_t>,
    &mc2_thiscall::null<>,
    &mc2_thiscall::null<>,
    &unk_5E33D0_p::impl_vir18,
    &unk_5E33D0_p::impl_vir1C,
};

void unk_5E33D0_p::destructor() {
    delete[] this->unk04;
    this->unk04 = nullptr;
}

void unk_5E33D0_p::sub_5E3380(const char *arg0) {
    delete[] unk04;
    unk04 = mc2_strdup(arg0);
}
