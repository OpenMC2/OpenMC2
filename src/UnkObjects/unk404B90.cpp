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

#include "unk404B90.hpp"

#include "../Game.hpp"
#include "../Logging.hpp"

// mc2: 0x0062D968
const unk_404B90::vtable_t unk_404B90::vtable_values = {
    &unk_404B90::scalar_deleter,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x00403810),
    MC2_PROC_MEMBER_PTR<void, void>(0x004045E0),
    &mc2_thiscall::null<>,
    &unk_404B90::impl_set_state,
};

unk_404B90::unk_404B90() {
    vtable = &vtable_values;
    this->set_gamestate(GameState::Boot);
    unk44 = unk48 = static_cast<float>(glo_6754A4);
    sub_4014C0();
}

// mc2: 0x00404A90
void unk_404B90::impl_set_state(GameState arg0) {
    switch (arg0) {
    case GameState::Boot:
        this->sub_403840();
        break;
    case GameState::Game:
        this->sub_4047A0();
        break;
    case GameState::Replay:
        this->sub_4049E0();
        break;
    case GameState::Movie:
        this->sub_403860();
        break;
    case GameState::FrontEnd:
        this->sub_4038E0();
        break;
    case GameState::RaceEditor:
        this->state = GameState::RaceEditor;
        this->sub_403AE0();
        break;
    case GameState::CarViewer:
        this->sub_403B30();
        break;
    case GameState::Quit:
        this->sub_402AC0();
        break;
    default:
        mc2_log_fatal("mcGameState::EnterState - invalid State");
        break;
    }

    this->state = arg0;
    this->unk08 = 0;
    this->unk09 = 0;
    this->unk0A = 0;
}

MC2_DEF_GLOBAL(glo_6754A4, 0x006754A4);

MC2_DEF_GLOBAL(glo_6C3890, 0x006C3890);
MC2_DEF_GLOBAL(glo_6C3894, 0x006C3894);
