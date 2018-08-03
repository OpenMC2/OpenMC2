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

// originally malloc'd in raceeditor.cpp
class unk_412280 {
private:
    std::uint8_t pad00[0x4F0];

public:
    unk_412280() {
        MC2_CALL_MEMBER<0x00412280, void>(this);
    }

    void sub_4158F0() {
        return MC2_CALL_MEMBER<0x004158F0, void>(this);
    }

    void sub_4155D0() {
        return MC2_CALL_MEMBER<0x004155D0, void>(this);
    }
};
static_assert(sizeof(unk_412280) == 0x4F0, "Wrong size for unk_412280");

extern unk_412280 *(&glo_6956DC);
inline unk_412280 *sub_412550() {
    return glo_6956DC = new unk_412280;
}
