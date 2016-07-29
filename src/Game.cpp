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

#include "Game.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstring>
#include <new>

#include "CommandLine.hpp"
#include "Logging.hpp"
#include "UnkObjects/unk402560.hpp"
#include "UnkObjects/unk600960.hpp"
#include "UnkObjects/unk613360.hpp"
#include "UnkObjects/unk6C2E88.hpp"
#include "UnkObjects/unk6C3250.hpp"
#include "UnkObjects/unk6C3890.hpp"

static void sub_53A890(const char *args) {
    sub_612C70(loc_6C3690);
    safe_strncpy(loc_6C3690, args, 0x200);
    sub_612F00();
    sub_612A80(loc_6C3690);
}

// mc2: 0x00401190
int sub_401190() {
    sub_53A890("mc.exe -path=. -archive=assets_p.dat");
    glo_85837C = 101;
    sub_5EDA50("Midnight Club II");
    sub_5ECBE0();
    glo_8602D4 = 1;
    glo_679778 = 0;
    sub_53A000();
    sub_53B9F0();
    glo_6C2C5C = 0;
    glo_6CE210 = 1;
    glo_6CE211 = 1;
    const char *gamePath = ".";
    sub_612EB0("path", 0, &gamePath);
    new (MC2_MALLOC(0x108)) unk_613360;
    sub_6134D0(gamePath);
    glo_6C3250.sub_53B6A0();
    sub_5ED7B0(glo_6C3250.get_unk44(), glo_6C3250.get_unk48(), glo_6C3250.get_unk4C(), 32, 0);
    sub_53A7B0(gamePath, 48, 0, 0, 0);
    glo_692E1C = glo_679810;
    std::memcpy(loc_692E20, glo_679810, 10 * sizeof(void *));
    loc_692E20[2] = loc_4010B0;
    glo_679810 = loc_692E20;
    sub_53A1B0();
    bool runforever = sub_612E10("runforever");
    if (sub_612E10("shiplist") && !sub_612E10("noresources") &&
        !sub_612E10("noraceresources") && !sub_612E10("archive")) {
        sub_613DD0("mc2_xbox.shiplist", MC2_MALLOC(0x30000), 0x30000);
    }
    sub_401170();

    do {
        sub_53A7E0("assets_p.dat");
        glo_85D3F8 = new (MC2_MALLOC(0x27C4)) unk_600960(global_hWnd);
        unk_402560 *esi = sub_402560();
        esi->sub_401860();
        sub_4028E0();
        sub_404BF0();

        std::uint32_t t;
        if (sub_612E10("nofe")) t = 6;
        else if (sub_612E10("carview")) t = 20;
        else if (sub_612E10("raceed")) t = 19;
        else if (sub_612E10("movie")) {
            const char *var4 = "angel.imf";
            sub_612EB0("movie", 0, &var4);
            glo_6C2E88.sub_53ACB0(var4);
            t = 15;
        } else if (sub_612E10("skipintro") || glo_6C2C64 != 0) t = 11;
        else {
            glo_6C2E88.sub_53ACB0("rockstar.pss");
            t = 15;
        }
        glo_6C3890->vir04(t);

        esi->sub_402120();
        sub_53A8F0();
        sub_402590();
        sub_4017E0();
        sub_53A870();

        if (runforever)
            mc2_log_C("\n\n-----------------------------------"
                "------------------------------------\n\n");
    } while (runforever);

    sub_53A7D0();
    sub_5ED220();
    return 0;
}

#define sub_6178E0 (MC2_PROC_PTR<int, LPEXCEPTION_POINTERS>(0x006178E0))

int sub_6181F0() {
    __try {
        return sub_401190();
    } __except (sub_6178E0(GetExceptionInformation())) {
        mc2_log_C("ExceptMain: Abnormal exit.");
        return 1;
    }
    return 0;
}
