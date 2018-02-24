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
#include "CInit.hpp"
#include "CommandLine.hpp"
#include "Config.hpp"
#include "Game.hpp"
#include "Logging.hpp"
#include "Memory.hpp"
#include "UnkObjects/unk5769E0.hpp"

#include <exception>
#include <cstdlib>

static_assert(sizeof(std::uintptr_t) == 4, "Compilation Not x86");
static_assert(sizeof(char) == 1, "Strings are not expected size");
static_assert(sizeof(bool) == 1, "Bools are not expected size");


static DWORD &mc2_osplatform = MC2_GLOBAL<DWORD>(0x0086D7D4);
static DWORD &mc2_winmajor = MC2_GLOBAL<DWORD>(0x0086D7E0);

static MC2_PROC_PTR<std::uint32_t, std::uint32_t> mc2__heap_init(0x0061CFB1);
static MC2_PROC_PTR<std::int32_t> mc2__ioinit(0x0061CDEC);
static MC2_PROC_PTR<void> mc2___endstdio(0x0061BC18);
static MC2_PROC_PTR<void> mc2__reset_excflt(0x0061EEE5);


// mc2: 0x0061958A
void load_mc2_dll() { // WinMainCRTSetup()
    //__SEH_prolog

    // Setup key parts of _cexit
    std::atexit([]() { mc2__reset_excflt(); });
    std::atexit([]() { mc2___endstdio(); });

    mc2_osplatform = VER_PLATFORM_WIN32_NT; // OpenMC2 doesn't support anything else
    mc2_winmajor = 6; // OpenMC2 doesn't officially support XP
    // (plus, specifying too high a version here doesn't produce any errors)

    if (mc2__heap_init(0) == 0) std::terminate(); // fast_error_exit(_RT_HEAPINIT)
    if (mc2__ioinit() < 0) std::terminate(); // _amsg_exit(_RT_LOWIOINIT)

    int initret = mc2_cinit(); // <- Magic
    if (initret != 0) std::terminate(); // _amsg_exit(initret)

    // remove call to WinMain and exit
    //__SEH_epilog
}

// mc2: 0x00401010
int StartOpenMC2() {
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
    return StartOpenMC2();
}

#pragma warning (disable: 4996)
AUTO_HOOK_X86(0x0061A76D, &std::atexit);
AUTO_HOOK_X86(0x0061B7C1, &std::getenv);
#pragma warning (default: 4996)

MC2_DEF_PROC(sub_61A5DC, 0x0061A5DC);

MC2_DEF_GLOBAL(glo_67A760, 0x0067A760);
MC2_DEF_POINTER(loc_67A770, 0x0067A770);
MC2_DEF_GLOBAL(glo_682E18, 0x00682E18);
MC2_DEF_GLOBAL(glo_8602C8, 0x008602C8);
MC2_DEF_GLOBAL(glo_679778, 0x00679778);
