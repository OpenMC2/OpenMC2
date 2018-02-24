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

class unk_404B90 {
private:
    struct {
        void *unk00;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> unk04;
    } *vtable;

public:
    unk_404B90() {
        MC2_CALL_MEMBER<0x00404B90, void>(this);
    }

    inline void vir04(std::uint32_t a) {
        this->vtable->unk04(this, a);
    }

};

extern unk_404B90 *&glo_6C3890;
