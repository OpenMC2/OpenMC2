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

// originally malloc'd in forcefield.cpp
class unk_477E80 {
private:
    std::uint8_t pad00[0xC08];

public:
    unk_477E80() {
        MC2_CALL_MEMBER<0x00477E80, void>(this);
    }

    void sub_477A50() {
        return MC2_CALL_MEMBER<0x00477A50, void>(this);
    }
};
static_assert(sizeof(unk_477E80) == 0xC08, "Wrong size for unk_477E80");

extern unk_477E80 *(&glo_6968AC);
inline unk_477E80 *sub_477EF0() {
    assert(glo_6968AC == nullptr);
    return glo_6968AC = new unk_477E80();
}
