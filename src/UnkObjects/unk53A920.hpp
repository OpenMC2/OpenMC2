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

enum class GameState : std::int32_t {
    Undefined,
    Boot,
    Game,
    Replay,
    Movie,
    FrontEnd,
    RaceEditor,
    CarViewer,
    Quit,
};

class unk_53A920 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void, GameState> set_state;
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    GameState state = GameState::Undefined;
    std::uint8_t unk08 = 0;
    std::uint8_t unk09 = 0;
    std::uint8_t unk0A = 0;
    std::uint8_t unk0B = 0;

public:
    unk_53A920() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_53A920) { /* only resets vtable */ }

    void vir04(std::uint32_t a) {
        static_cast<const vtable_t *>(this->vtable)->vir_04(this, a);
    }
    void vir08() {
        static_cast<const vtable_t *>(this->vtable)->vir_08(this);
    }
    void vir0C() {
        static_cast<const vtable_t *>(this->vtable)->vir_0C(this);
    }

    GameState get_gamestate() { return this->state; }
    void set_gamestate(GameState a) {
        static_cast<const vtable_t *>(this->vtable)->set_state(this, a);
    }
    std::uint8_t get_unk0A() { return this->unk0A; }

protected:
    void impl_set_state(GameState state) { this->state = state; }
};
static_assert(sizeof(unk_53A920) == 0x0C, "Bad Size: unk_53A920");
