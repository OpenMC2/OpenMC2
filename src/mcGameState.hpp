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

#include "Addresses.hpp"

#include "UnkObjects/unk53A920.hpp"

// originally malloc'd in gamestate.c
class mcGameState_p : public unk_53A920_p {
protected:
    static const vtable_t vtable_values;

    std::uint32_t unk0C[10];
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
    mcGameState_p();

    MC2_SCALAR_DELETING_DESTRUCTOR(mcGameState_p) {
        MC2_CALL_MEMBER<0x004037F0, void>(this);
    }

protected:
    void impl_vir04(std::uint32_t arg0);
    void impl_vir08();
    void impl_EnterState(GameState arg0);

private:
    void sub_402EB0() {
        return MC2_CALL_MEMBER<0x00402EB0, void>(this);
    }
    // mc2: 0x004047A0
    // Might be for another class, mcNetManager?
    void EnterStateGame();
    void sub_403B80(std::uint32_t arg0) {
        return MC2_CALL_MEMBER<0x00403B80, void>(this, arg0);
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

    void DoPauseSimulation() {
        return MC2_CALL_MEMBER<0x004030C0, void>(this);
    }
    void DoResumeSimulation() {
        return MC2_CALL_MEMBER<0x004031B0, void>(this);
    }
    void DoPauseLocally() {
        return MC2_CALL_MEMBER<0x004031E0, void>(this);
    }
    void DoResume() {
        return MC2_CALL_MEMBER<0x004032B0, void>(this);
    }
    void sub_4032E0() {
        return MC2_CALL_MEMBER<0x004032E0, void>(this);
    }
    void sub_4032F0() {
        return MC2_CALL_MEMBER<0x004032F0, void>(this);
    }
    void sub_403300() {
        return MC2_CALL_MEMBER<0x00403300, void>(this);
    }
    void sub_403350() {
        return MC2_CALL_MEMBER<0x00403350, void>(this);
    }
    void sub_403410() {
        return MC2_CALL_MEMBER<0x00403410, void>(this);
    }
    void sub_4034A0() {
        return MC2_CALL_MEMBER<0x004034A0, void>(this);
    }
    void sub_4034F0() {
        return MC2_CALL_MEMBER<0x004034F0, void>(this);
    }
    void sub_403640() {
        return MC2_CALL_MEMBER<0x00403640, void>(this);
    }
    void DoEndMovie() {
        return MC2_CALL_MEMBER<0x004043C0, void>(this);
    }
    void sub_403710() {
        return MC2_CALL_MEMBER<0x00403710, void>(this);
    }
    void sub_403780() {
        return MC2_CALL_MEMBER<0x00403780, void>(this);
    }
};
static_assert(sizeof(mcGameState_p) == 0x60, "Bad Size: mcGameState_p");
static_assert(std::is_trivially_destructible<mcGameState_p>::value, "mcGameState_p is not trivially destructible");

using mcGameState = MC2_DestroyingWrapper<mcGameState_p>;

extern MC2_PROC_PTR<void, std::uint32_t> sub_4016A0;
extern MC2_PROC_PTR<std::uint32_t, std::uint32_t> sub_402A90;
extern MC2_PROC_PTR<bool, std::uint32_t> sub_467650;
extern MC2_PROC_PTR<void> sub_539D40;
extern MC2_PROC_PTR<void> sub_6039E0;
extern MC2_PROC_PTR<void, const char *> sub_613AC0;

extern std::uint32_t &glo_6754A4;
extern bool &glo_692E55;
extern bool &glo_692E60;
extern bool &glo_692E78;
extern bool &glo_692E79;

extern mcGameState *&glo_6C3890;
extern mcGameState *&glo_6C3894;
inline void sub_404BF0() {
    assert(glo_6C3890 == nullptr && glo_6C3894 == nullptr);
    glo_6C3890 = glo_6C3894 = new mcGameState;
}
