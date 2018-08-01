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

// originally malloc'd in bangermgr.cpp
class unk_4788D0 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
    };
private:
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    std::uint32_t unk04 = 0;
    void *unk08 = nullptr;
    std::uint16_t unk0C = 0;
    std::uint16_t unk0E = 0;
    std::uint32_t unk10 = 0;
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;
    std::uint32_t unk1C = 0;
    std::uint32_t unk20 = 0;
    std::uint32_t unk24 = 0;
    std::uint32_t unk28 = 0;
    std::uint32_t unk2C = 0;
    std::uint32_t unk30 = 0;
    std::uint8_t pad34[0x8];

public:
    unk_4788D0() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_4788D0);

};
static_assert(sizeof(unk_4788D0) == 0x3C, "Wrong size for unk_4788D0");

extern unk_4788D0 *(&glo_6968B0);
inline unk_4788D0 *sub_479100() {
    return glo_6968B0 = new unk_4788D0();
}
