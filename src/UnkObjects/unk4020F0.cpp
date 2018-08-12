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

#include "unk4020F0.hpp"
#include "unk402800.hpp"
#include "unk404B90.hpp"
#include "unk405630.hpp"
#include "unk405C90.hpp"
#include "unk406950.hpp"
#include "unk4094A0.hpp"
#include "unk412280.hpp"
#include "unk419D20.hpp"
#include "unk41FB40.hpp"
#include "unk421350.hpp"
#include "unk477E80.hpp"
#include "unk4788D0.hpp"
#include "unk482C30.hpp"
#include "unk4CE870.hpp"
#include "unk52AA80.hpp"
#include "unk53C670.hpp"
#include "unk53C9E0.hpp"
#include "unk57DC70.hpp"
#include "unk5FAC30.hpp"
#include "unk611C60.hpp"
#include "unk612850.hpp"
#include "unk6144B0.hpp"
#include "unk6633B0.hpp"

#include "../Config.hpp"
#include "../Logging.hpp"

#include <timeapi.h>

constexpr DWORD disclaimer_time = 5000;

// mc2: 0x0062D530
const unk_4020F0::vtable_t unk_4020F0::vtable_values = {
    &unk_4020F0::scalar_deleter,
};

static void call_glo_6CE2E4_vir10() {
    glo_6CE2E4->vir10();
}

void unk_4020F0::sub_401860() {
    glo_675024 = false;
    sub_53DE60();
    sub_53C6B0();
    sub_405D50();

    if (sub_612E10("nooverframe")) glo_662284 = false;
    if (sub_612E10("drawnothing")) glo_692E6C = true;
    sub_52B6C0(!sub_612E10("noaudio"));
    unk_614400 var10(&call_glo_6CE2E4_vir10);
    glo_860618.sub_6144D0(&var10);
    sub_4069B0();
    glo_6C50F0.unk02 = false;
    glo_6C50F0.sub_6126E0(0xD3);
    sub_4CEB00(0x13);
    sub_5670D0(nullptr);
    this->unk04 = false;

    sub_53C9E0();
    sub_479100();
    sub_477EF0();
    sub_482C60();

    sub_40E240();
    glo_8582A8 = 0;
    glo_6745C0 = 0;
    glo_8582C4 = "popup";
    sub_57E250();
    glo_675028 = glo_662288;
}

static void sub_506CF0() {
    glo_6A04BC = 0;
    glo_6A04B4 = 0;
}

// mc2: 0x00402120
void unk_4020F0::game_loop() {
    mc2_log_info("mcGame:Execute - kDebugLevel %d", 0); // macro kDebugLevel?
    unk_611C60 timer;
    bool stop = false;

    do {
        glo_6C3890->vir08();
        timer.fetch_time();
        glo_692EB4->sub_4064E0();

        switch (glo_6C3890->get_gamestate()) {
        case GameState::Boot:
            mc2_log_info("Welcome to the boot state.");
            glo_6C3890->vir04(17);
            break;

        case GameState::Game:
        case GameState::Replay:
            sub_5ECFD0();
            this->sub_401960();
            this->sub_401CB0();
            sub_5ED000();

            if  (glo_858384 & 2) {
                Sleep(30); // near-30 fps cap?
                if (glo_858384 & 2) sub_506CF0();
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
                glo_692EB0->sub_405360();
                if (glo_6C3890->get_unk0A() != 0) {
                    this->sub_401960();
                    this->sub_401CB0();
                    glo_692EB0->sub_405360();
                }
            } else {
                sub_5ED050(0);
                this->sub_4019C0();
                glo_692EB0->sub_405360();
                if (glo_6C3890->get_unk0A() != 0) {
                    this->sub_401960();
                    this->sub_401CB0();
                    glo_692EB0->sub_405360();
                }
                sub_5ED0C0();
            }
            break;

        case GameState::Movie:
            glo_6957BC->sub_420EA0();
            if (glo_6957BC != nullptr && glo_6957BC->unk1C == 0) {
                sub_5ED9C0();
                sub_5EF3F0();
                sub_5EF420(3, 0xFF000000, 1.0f, 0);
                if (glo_6957BC != nullptr) glo_6957BC->sub_421050();
                sub_5F0F00();
            } else {
                glo_6C3890->vir04(0x10);
            }
            break;

        case GameState::FrontEnd:
        {
            if (glo_6622B0 && !startup_config.fast_disclaimer) {
                std::uint32_t esi = timeGetTime() - glo_692E90;
                if (esi < disclaimer_time) Sleep(disclaimer_time - esi);
            }
            glo_6622B0 = false;

            unk_41FB40 *esi = glo_692E88->get6().unk14;
            sub_5ECFD0();
            sub_613FC0();
            if (glo_8582DC == 4) {
                glo_6C38B4->vir58();
            }
            esi->sub_420B70();
            sub_5ED000();
            if (glo_858384 & 2) {
                Sleep(30);
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
            } else {
                sub_5ED050(0);
                esi->sub_41A960();
                sub_5ED0C0();
            }
            break;
        }

        case GameState::RaceEditor:
            sub_5ECFD0();
            sub_613FC0();
            glo_6956DC->sub_4158F0();
            sub_5ED000();
            if (glo_858384 & 2) {
                Sleep(30);
                glo_6CE2E4->set_unk51_1();
                glo_6CE2E4->vir10();
            } else {
                sub_5ED050(0);
                sub_5F23A0(glo_858378);
                sub_5EF420(3, glo_674F9C, 1.0f, 0);
                glo_6956DC->sub_4155D0();
                sub_5ED0C0();
            }
            break;

        case GameState::CarViewer:
            sub_613FC0();
            sub_5ED4A0(1);
            glo_695760->sub_419980();
            glo_695760->sub_419CA0();
            sub_5ED000();
            sub_5ED0C0();
            Sleep(10);
            break;

        case GameState::Quit:
            stop = true;
            sub_5ED4A0(1);
            sub_5ED000();
            sub_5ED0C0();
            sub_5ED4A0(0);
            sub_5ED000();
            sub_5ED0C0();
            break;

        default:
            mc2_log_fatal("Invalid State");
            break;
        }

        if (glo_6C3890->get_gamestate() == GameState::Replay) {
            while (timer.get_delta_seconds() < 0.33) {
                if ((glo_6797CC - timer.get_delta_seconds()) / glo_6797CC <= 0.25f) break;
                Sleep(1);
            }
        }

    } while (!stop && !sub_5ED220());
}

MC2_DEF_PROC(sub_4069B0, 0x004069B0);
MC2_DEF_PROC(sub_40E240, 0x0040E240);
MC2_DEF_PROC(sub_5670D0, 0x005670D0);
MC2_DEF_PROC(sub_5D36D0, 0x005D36D0);
MC2_DEF_PROC(sub_5ECFD0, 0x005ECFD0);
MC2_DEF_PROC(sub_5ED000, 0x005ED000);
MC2_DEF_PROC(sub_5ED050, 0x005ED050);
MC2_DEF_PROC(sub_5ED0C0, 0x005ED0C0);
MC2_DEF_PROC(sub_5ED220, 0x005ED220);
MC2_DEF_PROC(sub_5ED4A0, 0x005ED4A0);
MC2_DEF_PROC(sub_5ED9C0, 0x005ED9C0);
MC2_DEF_PROC(sub_5EF3F0, 0x005EF3F0);
MC2_DEF_PROC(sub_5EF420, 0x005EF420);
MC2_DEF_PROC(sub_5F0F00, 0x005F0F00);
MC2_DEF_PROC(sub_613FC0, 0x00613FC0);

MC2_DEF_GLOBAL(glo_662284, 0x00662284);
MC2_DEF_GLOBAL(glo_662288, 0x00662288);
MC2_DEF_GLOBAL(glo_6622B0, 0x006622B0);
MC2_DEF_GLOBAL(glo_6745C0, 0x006745C0);
MC2_DEF_GLOBAL(glo_674F9C, 0x00674F9C);
MC2_DEF_GLOBAL(glo_675024, 0x00675024);
MC2_DEF_GLOBAL(glo_675028, 0x00675028);
MC2_DEF_GLOBAL(glo_6797CC, 0x006797CC);
MC2_DEF_GLOBAL(glo_692E6C, 0x00692E6C);
MC2_DEF_GLOBAL(glo_692E7C, 0x00692E7C);
MC2_DEF_GLOBAL(glo_692E90, 0x00692E90);
MC2_DEF_GLOBAL(glo_6A04B4, 0x006A04B4);
MC2_DEF_GLOBAL(glo_6A04BC, 0x006A04BC);

MC2_DEF_GLOBAL(glo_8582A8, 0x008582A8);
MC2_DEF_GLOBAL(glo_8582C4, 0x008582C4);
MC2_DEF_GLOBAL(glo_8582DC, 0x008582DC);
MC2_DEF_GLOBAL(glo_858384, 0x00858384);
