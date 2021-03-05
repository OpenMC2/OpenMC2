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

#include "unk53A920.hpp"

// mc2: 0x0064D2AC
const unk_53A920_p::vtable_t unk_53A920_p::vtable_values = {
    &unk_53A920_p::scalar_deleter,
    &mc2_thiscall::null<std::uint32_t>,
    &mc2_thiscall::null<>,
    &mc2_thiscall::null<>,
    &unk_53A920_p::impl_set_state,
};
