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

// originally malloc'd in layermgr.c
class unk_402800 {
public:
    // need to figure out these structures more
    class sub_unk04_t {
    public:
        void sub_420B70() {
            MC2_CALL_MEMBER<0x00420B70, void>(this);
        }

        void sub_41A960() {
            MC2_CALL_MEMBER<0x0041A960, void>(this);
        }
    };

    class unk04_t {
    public:
        std::uint8_t pad00[0x14];
        sub_unk04_t *unk14;
    };

private:
    std::uint8_t pad00[0x4];
    unk04_t *unk04[7];
    std::uint8_t pad20[0x10C];

public:
    unk_402800() {
        MC2_CALL_MEMBER<0x00402800, void>(this);
    }

    unk04_t *sub_4025C0(std::uint32_t index) {
        return unk04[index];
    }
};
static_assert(sizeof(unk_402800) == 0x12C, "Wrong size for unk_421350");

extern unk_402800 *(&glo_692E88);
inline unk_402800 *sub_4028E0() {
    return glo_692E88 = new unk_402800;
}
#pragma once
