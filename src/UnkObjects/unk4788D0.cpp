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

#include "unk4788D0.hpp"

// mc2: 0x0063E330
const unk_4788D0_p::vtable_t unk_4788D0_p::vtable_values = {
    &unk_4788D0_p::scalar_deleter,
};

// mc2: 0x00478910
void unk_4788D0_p::destructor() {
    vtable = &vtable_values;
    ::operator delete(unk08);
}

MC2_DEF_GLOBAL(glo_6968B0, 0x006968B0);
