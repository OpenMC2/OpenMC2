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
#include "unk613330.hpp"

class unk_613360_p : public unk_613330_p {
private:
    static const vtable_t vtable_values;

private:
    char unk04[0x100];
    std::uint32_t unk104 = 0;

public:
    unk_613360_p() { vtable = &vtable_values; }

    void impl_04(char *destination, std::uint32_t unk2, const char *unk3, const char *extension);
    void impl_0C();
};
static_assert(sizeof(unk_613360_p) == 0x108, "Bad Size: unk_613360_p");
static_assert(std::is_trivially_destructible<unk_613360_p>::value, "unk_613360_p is not trivially destructible");

using unk_613360 = MC2_DestroyingWrapper<unk_613360_p>;
