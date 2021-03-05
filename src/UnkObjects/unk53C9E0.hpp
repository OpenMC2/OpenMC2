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

// originally malloc'd in mcresource.cpp
class unk_53C9E0 {
private:
    // possibly empty class given size of 1
    std::uint8_t pad00[1];

public:
    // no constructor function
};
static_assert(sizeof(unk_53C9E0) == 1, "Wrong size for unk_53C9E0");

extern unk_53C9E0 *(&glo_6C389C);
inline unk_53C9E0 *sub_53C9E0() {
    assert(glo_6C389C == nullptr);
    return glo_6C389C = new unk_53C9E0();
}
