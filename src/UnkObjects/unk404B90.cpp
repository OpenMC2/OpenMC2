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
    &unk_404B90::impl_vir04,
    &unk_404B90::impl_vir08,
    &mc2_thiscall::null<>,
    &unk_404B90::impl_set_state,
};

unk_404B90::unk_404B90() {
    vtable = &vtable_values;
    this->set_gamestate(GameState::Boot);
    unk44 = unk48 = static_cast<float>(glo_6754A4);
    sub_4014C0();
}

// mc2: 0x00403810
void unk_404B90::impl_vir04(std::uint32_t arg0) {
    if (this->unk3C == 10) return;
    if (++this->unk34 == 10) this->unk34 = 0;
    this->unk0C[this->unk34] = arg0;
    ++this->unk3C;
}

void unk_404B90::impl_vir08() {
    while (this->unk3C != 0) {
        --this->unk3C;
        if (++this->unk38 == 10) this->unk38 = 0;

        switch (this->unk0C[this->unk38]) {
        case 0:
            mc2_log_fatal("Unimplemented request -- None");
            break;
        case 1: // Pause?
            if (this->state == GameState::Game ||
                this->state == GameState::Replay) {
                this->sub_4030C0();
            }
            break;
        case 2: // Unpause?
            this->sub_4031B0();
            break;
        case 3: // Local-Pause?
            if (this->state == GameState::Game ||
                this->state == GameState::Replay) {
                this->sub_4031E0();
            }
            break;
        case 4: // Local-Unpuase?
            this->sub_4032B0();
            break;
        case 5:
            this->sub_4032E0();
            break;
        case 6:
        case 7:
            this->sub_4032F0();
            break;
        case 8:
            this->sub_403300();
            break;
        case 9:
            this->sub_403350();
            break;
        case 10:
            this->sub_403410();
            break;
        case 11:
            this->sub_4034A0();
            break;
        case 12:
            this->sub_4034F0();
            break;
        case 13: // Start Replay?
            this->set_gamestate(GameState::Replay);
            break;
        case 14: // Delayed Pause?
            this->vir04(1);
            break;
        case 15:
            this->sub_403640();
            break;
        case 16:
            this->sub_4043C0();
            break;
        case 17: // Back to FrontEnd?
            this->set_gamestate(GameState::FrontEnd);
            break;
        case 18:
            this->sub_403710();
            break;
        case 19: // Start Race Editor?
            this->set_gamestate(GameState::RaceEditor);
            break;
        case 20:
            this->set_gamestate(GameState::CarViewer);
            break;
        case 21:
            this->sub_403780();
            break;
        case 22: // Quit?
            this->set_gamestate(GameState::Quit);
            break;
        default:
            mc2_log_fatal("Unrecognized request");
            break;
        }
    }
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
