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

#include "unk401FD0.hpp"

// mc2: 0x0062D5F8
const unk_401FD0::vtable_t unk_401FD0::vtable_values = {
    &unk_401FD0::scalar_deleter,
    MC2_PROC_MEMBER_PTR<bool, void>(0x005E32B0),
    MC2_PROC_MEMBER_PTR<bool, void>(0x005E3320),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x00402070),
    &mc2_thiscall::null<>,
    &mc2_thiscall::null<>,
    &unk_401FD0::impl_vir18,
    &unk_401FD0::impl_vir1C,
};

unk_401FD0::unk_401FD0() {
    vtable = &vtable_values;
    this->sub_5E3380("default");
    this->vir08();
}
