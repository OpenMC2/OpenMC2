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

// originally malloc'd in c:\\soft_x\\mc2\\src\\mcgame\\game.h
class unk_401FD0_p : public unk_5E33D0_p {
protected:
    static const vtable_t vtable_values;

protected:
    std::uint8_t unk0C = 0;
    std::uint8_t pad0D[0x3];
    std::uint32_t unk10 = 0;
    float unk14 = 0.25f;
    float unk18 = 0.5f;
    float unk1C = 0.25f;
    float unk20 = 0.6f;
    float unk24 = 1.3f;
    std::uint32_t unk28 = 0;
    float unk2C = 1.0f;

public:
    unk_401FD0_p();

protected:
    const char *impl_vir18() { return "tune/city"; }
    const char *impl_vir1C() { return  "loadTransition"; }
};
static_assert(sizeof(unk_401FD0_p) == 0x30, "Wrong size for unk_401FD0_p");
static_assert(std::is_trivially_destructible<unk_401FD0_p>::value, "unk_401FD0_p is not trivially destructible");

using unk_401FD0 = MC2_DestroyingWrapper<unk_401FD0_p>;
