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

#include "Addresses.hpp"
#include "CommandLine.hpp"
#include "Config.hpp"
#include "Game.hpp"
#include "Logging.hpp"
#include "Memory.hpp"
#include "UnkObjects/unk5769E0.hpp"

#include <iostream>
#include <cstdint>

#include <boost/dll.hpp>

static_assert(sizeof(std::uintptr_t) == 4, "Compilation Not x86");
static_assert(sizeof(char) == 1, "Strings are not expected size");
static_assert(sizeof(bool) == 1, "Bools are not expected size");


void load_mc2_dll() {
    Hook_x86(mc2_crt_call_main, mc2_crt_end_main);
    mc2_crt_start_main();
}

// mc2: 0x00401010
int StartOpenMC2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Init MC2_MALLOC
    if ((glo_682E18 & 1) == 0) {
        glo_682E18 |= 1;
        glo_67A760 = loc_67A770;
    }

    load_config();

    unk_5769E0 a;
    a.sub_575BA0(glo_67A760, 0x18680, 1, 0);
    global_primary_unk5769E0 = &a;
    parse_commandline(__argc, __argv);
    sub_612910(__argc, __argv);

    int b = sub_6181F0();

    sub_612F00();

    return b;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    load_mc2_dll();

    return StartOpenMC2(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
