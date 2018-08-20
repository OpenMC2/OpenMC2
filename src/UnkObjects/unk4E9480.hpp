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

// originally malloc'd in trainmanager.cpp
class unk_4E9480 {
private:
    std::uint8_t pad00[0x24];

public:
    unk_4E9480() {
        MC2_CALL_MEMBER<0x004E9480, void>(this);
    }

    void sub_4E9260() {
        return MC2_CALL_MEMBER<0x004E9260, void>(this);
    }
};
static_assert(sizeof(unk_4E9480) == 0x24, "Wrong size for unk_4E9480");

extern unk_4E9480 *(&glo_699498);
