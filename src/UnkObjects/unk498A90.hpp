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

#include "unk5E33D0.hpp"

// originally malloc'd in popupmgr.c
class unk_498A90_p : public unk_5E33D0_p {
private:
    std::uint8_t pad0C[0x6C];

public:
    unk_498A90_p(std::uint32_t arg0) {
        MC2_CALL_MEMBER<0x00498A90, void>(this, arg0);
    }

    void sub_498760() {
        return MC2_CALL_MEMBER<0x00498760, void>(this);
    }
};
static_assert(sizeof(unk_498A90_p) == 0x78, "Wrong size for unk_498A90_p");
static_assert(std::is_trivially_destructible<unk_498A90_p>::value, "unk_498A90_p is not trivially destructible");

using unk_498A90 = MC2_DestroyingWrapper<unk_498A90_p>;

extern unk_498A90 *(&glo_6984B4);
inline unk_498A90 *sub_498BC0(std::uint32_t arg0) {
    assert(glo_6984B4 == nullptr);
    return glo_6984B4 = new unk_498A90(arg0);
}
