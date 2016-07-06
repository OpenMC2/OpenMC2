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

#include <cstdint>

#include "../Addresses.hpp"

class unk_6C3890 {
private:
    struct {
        void *unk00;
        void (__thiscall *unk04)(unk_6C3890 *, std::uint32_t);
    } *vtable;

public:
    inline void vir04(std::uint32_t a) {
        this->vtable->unk04(this, a);
    }

};

#define glo_6C3890 (MC2_GLOBAL<unk_6C3890 *>(0x006C3890))
