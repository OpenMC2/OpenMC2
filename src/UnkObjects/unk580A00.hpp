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

// originally malloc'd in layercity.c
class unk_580A00_p {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_14;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_18;
    };

protected:
    const void *vtable;
public:
    std::uint8_t pad04[0x2C];

public:
    unk_580A00_p() {
        MC2_CALL_MEMBER<0x00406950, void>(this);
    }

    MC2_SCALAR_DELETING_DESTRUCTOR(unk_580A00_p) {
        MC2_CALL_MEMBER<0x00585010, void>(this);
    }

    bool sub_584FB0() {
        return MC2_CALL_MEMBER<0x00584FB0, bool>(this);
    }
};
static_assert(sizeof(unk_580A00_p) == 0x30, "Wrong size for unk_580A00_p");
static_assert(std::is_trivially_destructible<unk_580A00_p>::value, "unk_580A00_p is not trivially destructible");

using unk_580A00 = MC2_DestroyingWrapper<unk_580A00_p>;

extern unk_580A00 *(&glo_6C8EEC);
