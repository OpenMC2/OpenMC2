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

// originally malloc'd in carviewer.cpp
class unk_419D20 {
private:
    std::uint8_t pad00[0x2C];

public:
    unk_419D20() {
        MC2_CALL_MEMBER<0x00419D20, void>(this);
    }

    void sub_419980() {
        MC2_CALL_MEMBER<0x00419980, void>(this);
    }

    void sub_419CA0() {
        MC2_CALL_MEMBER<0x00419CA0, void>(this);
    }
};
static_assert(sizeof(unk_419D20) == 0x2C, "Wrong size for unk_419D20");

extern unk_419D20 *&glo_695760;
inline unk_419D20 *sub_419D80() {
    assert(glo_695760 == nullptr);
    return glo_695760 = new unk_419D20;
}
