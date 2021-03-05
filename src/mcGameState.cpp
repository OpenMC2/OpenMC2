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

#include "mcGameState.hpp"

#include "Game.hpp"
#include "Logging.hpp"
#include "mcGame.hpp"
#include "mcLayerMgr.hpp"

#include "UnkObjects/unk405630.hpp"
#include "UnkObjects/unk406950.hpp"
#include "UnkObjects/unk467180.hpp"
#include "UnkObjects/unk47C830.hpp"
#include "UnkObjects/unk482C30.hpp"
#include "UnkObjects/unk52AA80.hpp"
#include "UnkObjects/unk53AF00.hpp"
#include "UnkObjects/unk5E14C0.hpp"
#include "UnkObjects/unk603B10.hpp"
#include "UnkObjects/unk612850.hpp"

// mc2: 0x0062D968
const mcGameState_p::vtable_t mcGameState_p::vtable_values = {
    &mcGameState_p::scalar_deleter,
    &mcGameState_p::impl_vir04,
    &mcGameState_p::impl_vir08,
    &mc2_thiscall::null<>,
    &mcGameState_p::impl_EnterState,
};

mcGameState_p::mcGameState_p() {
    vtable = &vtable_values;
    this->EnterState(GameState::Boot);
    unk44 = unk48 = static_cast<float>(glo_6754A4);
    sub_4014C0();
}

// mc2: 0x00403810
void mcGameState_p::impl_vir04(std::uint32_t arg0) {
    if (this->unk3C == 10) return;
    if (++this->unk34 == 10) this->unk34 = 0;
    this->unk0C[this->unk34] = arg0;
    ++this->unk3C;
}

void mcGameState_p::impl_vir08() {
    while (this->unk3C != 0) {
        --this->unk3C;
        if (++this->unk38 == 10) this->unk38 = 0;

        switch (this->unk0C[this->unk38]) {
        case 0:
            mc2_log_quit("Unimplemented request -- None");
            break;
        case 1: // Pause?
            if (this->state == GameState::Game ||
                this->state == GameState::Replay) {
                this->DoPauseSimulation();
            }
            break;
        case 2: // Unpause?
            this->DoResumeSimulation();
            break;
        case 3: // Local-Pause?
            if (this->state == GameState::Game ||
                this->state == GameState::Replay) {
                this->DoPauseLocally();
            }
            break;
        case 4: // Local-Unpuase?
            this->DoResume();
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
            this->EnterState(GameState::Replay);
            break;
        case 14: // Delayed Pause?
            this->vir04(1);
            break;
        case 15:
            this->sub_403640();
            break;
        case 16:
            this->DoEndMovie();
            break;
        case 17: // Back to FrontEnd?
            this->EnterState(GameState::FrontEnd);
            break;
        case 18:
            this->sub_403710();
            break;
        case 19: // Start Race Editor?
            this->EnterState(GameState::RaceEditor);
            break;
        case 20:
            this->EnterState(GameState::CarViewer);
            break;
        case 21:
            this->sub_403780();
            break;
        case 22: // Quit?
            this->EnterState(GameState::Quit);
            break;
        default:
            mc2_log_quit("Unrecognized request");
            break;
        }
    }
}

// mc2: 0x00404A90
void mcGameState_p::impl_EnterState(GameState arg0) {
    switch (arg0) {
    case GameState::Boot:
        sub_613AC0(":BOOT");
        this->sub_402EB0();
        this->state = GameState::Boot;
        break;
    case GameState::Game:
        this->EnterStateGame();
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
        mc2_log_quit("mcGameState::EnterState - invalid State");
        break;
    }

    this->state = arg0;
    this->unk08 = 0;
    this->unk09 = 0;
    this->unk0A = 0;
}

// mc2: 0x004047A0
void mcGameState_p::EnterStateGame() {
    this->sub_403B80(1);
    this->state = GameState::Game;
    glo_6C38B4->sub_535DC0(3);
    if (glo_692EB0 != nullptr) glo_692EB0->sub_405420();
    glo_692E7C->sub_401E50(0);
    if (!glo_6C32C8.unk39) {
        glo_692E79 = true;
        if (glo_6C2E88.unk58[0] != '\0') glo_692E7C->unk04->sub_5E3380(glo_6C2E88.unk58);
        glo_692E7C->unk04->vir08();
        glo_692E78 = true;
    }
    if (sub_612E10("quitonload")) glo_6C3890->vir04(22);
    glo_6C38B4->sub_535DC0(5);

    if (!glo_692E55) goto end;
    if (glo_692E60) goto end;
    sub_4016A0(1);
    if (glo_697B88->unk04->unk554 == nullptr) goto end;
    if (glo_6C2C60 != 2) goto end;
    if (glo_6C3890->state == GameState::Replay) goto end;

    std::uint32_t esi;
    if (stricmp(glo_697B88->unk04->unk554, "Tutorial") == 0) esi = 1;
    else if (stricmp(glo_697B88->unk04->unk554, "coprace") == 0) esi = 2;
    else goto end;

    glo_8582C8.sub_5E1A80();
    glo_692E88->get4().post_loading_screen(esi);
    if (sub_467650(24) || sub_402A90(1) != 0) esi = 0x800;
    else esi = 0;
    mc2_log_display("Waiting for you to press start in EnterStateGame-gamestate.c, %d", esi);
    glo_69585C->sub_467090(0, 1);
    if (!glo_6C32C8.unk3C0 && !glo_6C32C8.unk3C1) {
        while (!(esi & 0x800)) {
            sub_6040E0();
            sub_6039E0();
            if (sub_467650(24) || sub_402A90(1) != 0) esi = 0x800;
            Sleep(33);
            glo_6CE2E4->vir10();
        }
    }
    glo_8582C4 = "popup";
    glo_8582C8.sub_5E1500("mcstrings", global_LanguageID, 2, 0);

    end:
    sub_539D40();
    glo_6C38A4->vir04(2);
    if (glo_697B88 != nullptr) glo_697B88->unk04->vir10();
}

MC2_DEF_PROC(sub_4016A0, 0x004016A0);
MC2_DEF_PROC(sub_402A90, 0x00402A90);
MC2_DEF_PROC(sub_467650, 0x00467650);
MC2_DEF_PROC(sub_539D40, 0x00539D40);
MC2_DEF_PROC(sub_6039E0, 0x006039E0);
MC2_DEF_PROC(sub_613AC0, 0x00613AC0);

MC2_DEF_GLOBAL(glo_6754A4, 0x006754A4);
MC2_DEF_GLOBAL(glo_692E55, 0x00692E55);
MC2_DEF_GLOBAL(glo_692E60, 0x00692E60);
MC2_DEF_GLOBAL(glo_692E78, 0x00692E78);
MC2_DEF_GLOBAL(glo_692E79, 0x00692E79);

MC2_DEF_GLOBAL(glo_6C3890, 0x006C3890);
MC2_DEF_GLOBAL(glo_6C3894, 0x006C3894);
