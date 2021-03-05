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

class unk_5E33D0_p {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<bool, void> vir_04;
        MC2_PROC_MEMBER_PTR<bool, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<const char *, void> vir_18;
        MC2_PROC_MEMBER_PTR<const char *, void> vir_1C;
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    char *unk04 = nullptr;
    std::uint32_t unk08 = 0;

public:
    unk_5E33D0_p() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_5E33D0_p);

    void sub_5E3380(const char *arg0);

    bool vir08() {
        return static_cast<const vtable_t *>(this->vtable)->vir_08(this);
    }

protected:
    const char *impl_vir18() { return "tune"; }
    const char *impl_vir1C() { return "parFileIO"; }
};
static_assert(sizeof(unk_5E33D0_p) == 0x0C, "Wrong size for unk_5E33D0_p");
static_assert(std::is_trivially_destructible<unk_5E33D0_p>::value, "unk_5E33D0_p is not trivially destructible");

using unk_5E33D0 = MC2_DestroyingWrapper<unk_5E33D0_p>;
