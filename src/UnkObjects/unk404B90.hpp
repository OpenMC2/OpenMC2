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
#include "unk53A920.hpp"

// originally malloc'd in gamestate.c
class unk_404B90 : public unk_53A920 {
protected:
    static const vtable_t vtable_values;

    std::uint8_t pad0C[0x28];
    std::uint32_t unk34 = 0;
    std::uint32_t unk38 = 0;
    std::uint32_t unk3C = 0;
    std::uint32_t unk40 = 0;
    float unk44;
    float unk48 = 1.0f;
    float unk4C;
    std::uint8_t pad50[0x4];
    std::uint32_t unk54 = 1;
    std::uint32_t unk58 = 0;
    std::uint32_t unk5C = 1;

public:
    unk_404B90();

    MC2_SCALAR_DELETING_DESTRUCTOR(unk_404B90) {
        MC2_CALL_MEMBER<0x004037F0, void>(this);
    }

protected:
    void impl_set_state(GameState arg1);

private:
    void sub_403840() {
        return MC2_CALL_MEMBER<0x00403840, void>(this);
    }
    void sub_4047A0() {
        return MC2_CALL_MEMBER<0x004047A0, void>(this);
    }
    void sub_4049E0() {
        return MC2_CALL_MEMBER<0x004049E0, void>(this);
    }
    void sub_403860() {
        return MC2_CALL_MEMBER<0x00403860, void>(this);
    }
    void sub_4038E0() {
        return MC2_CALL_MEMBER<0x004038E0, void>(this);
    }
    void sub_403AE0() {
        return MC2_CALL_MEMBER<0x00403AE0, void>(this);
    }
    void sub_403B30() {
        return MC2_CALL_MEMBER<0x00403B30, void>(this);
    }
    void sub_402AC0() {
        return MC2_CALL_MEMBER<0x00402AC0, void>(this);
    }
};
static_assert(sizeof(unk_404B90) == 0x60, "Bad Size: unk_404B90");

extern std::uint32_t &glo_6754A4;

extern unk_404B90 *&glo_6C3890;
extern unk_404B90 *&glo_6C3894;
inline void sub_404BF0() {
    glo_6C3890 = glo_6C3894 = new unk_404B90;
}
