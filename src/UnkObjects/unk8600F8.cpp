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

#include "unk8600F8.hpp"

#include <cstring>

#include "../Addresses.hpp"

// Remove from Linked List?
void unk_8600F8::loc_611DC0() {
    unk_8600F8 **x;
    for (x = &glo_8600E8; *x != nullptr && *x != this; x = &(*x)->unk14);
    *x = this->unk14;
    this->unk14 = nullptr;
}

void unk_8600F8::sub_612150(const char *a, unk_612150 *b) {
    MC2_PROC_MEMBER<void>(0x00612150, this, a, b);
}

std::int32_t unk_8600F8::sub_6124A0(char *a) {
    return MC2_PROC_MEMBER<std::int32_t>(0x006124A0, this, a);
}
