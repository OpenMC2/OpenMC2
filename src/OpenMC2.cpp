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

static_assert(sizeof(std::uintptr_t) == 4, "Compilation Not x86");
static_assert(sizeof(char) == 1, "Strings are not expected size");
static_assert(sizeof(bool) == 1, "Bools are not expected size");


#define mc2_osplatform MC2_GLOBAL<DWORD>(0x0086D7D4)
#define mc2_winmajor MC2_GLOBAL<DWORD>(0x0086D7E0)
#define mc2_winminor MC2_GLOBAL<DWORD>(0x0086D7E4)
#define mc2_osver MC2_GLOBAL<DWORD>(0x0086D7D8)
#define mc2_winver MC2_GLOBAL<DWORD>(0x0086D7DC)
#define mc2_acmdln MC2_GLOBAL<LPSTR>(0x0086EDC4)
#define mc2_aenvptr MC2_GLOBAL<LPSTR>(0x0086D818)

#define mc2__heap_init MC2_PROC_PTR<std::uint32_t, std::uint32_t>(0x0061CFB1)
#define mc2__RTC_Initialize MC2_PROC_PTR<void>(0x0061C7F1)
#define mc2__ioinit MC2_PROC_PTR<std::int32_t>(0x0061CDEC)
#define mc2___ctrGenEnvironmentStringsA MC2_PROC_PTR<LPSTR>(0x0061CCCA)
#define mc2_setargv MC2_PROC_PTR<std::int32_t>(0x006192D5)
#define mc2__setenvp MC2_PROC_PTR<std::int32_t>(0x0061CC03)
#define mc2_cinit MC2_PROC_PTR<std::uint32_t>(0x006193FE)
#define mc2__wincmdln MC2_PROC_PTR<LPSTR>(0x0061CB9A)
#define mc2__cexit MC2_PROC_PTR<void>(0x00619547)


// mc2: 0x0061958A
void load_mc2_dll() { // WinMainCRTSetup()
    //__SEH_prolog
#pragma warning (disable: 4996)
    OSVERSIONINFOA win_ver;
    win_ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&win_ver);
#pragma warning (default: 4996)

    mc2_osplatform = win_ver.dwPlatformId;
    mc2_winmajor = win_ver.dwMajorVersion;
    mc2_winminor = win_ver.dwMinorVersion;
    mc2_osver = win_ver.dwBuildNumber & 0x7FFF;
    if (win_ver.dwPlatformId != VER_PLATFORM_WIN32_NT) mc2_osver |= 0x8000;
    mc2_winver = (win_ver.dwMajorVersion << 8) + win_ver.dwMinorVersion;

    /*
     * Original had code to check here for a "CLR header" in the
     * exe, but the code that uses the result has been removed.
     * (It related to how to exit the program)
     */

    if (mc2__heap_init(0) == 0) std::terminate(); // fast_error_exit(_RT_HEAPINIT)
    mc2__RTC_Initialize();
    if (mc2__ioinit() < 0) std::terminate(); // _amsg_exit(_RT_LOWIOINIT)

    mc2_acmdln = GetCommandLineA();
    mc2_aenvptr = mc2___ctrGenEnvironmentStringsA();
    if (mc2_setargv() < 0) std::terminate(); // _amsg_exit(_RT_SPACEARG)
    if (mc2__setenvp() < 0) std::terminate(); // _amsg_exit(_RT_SPACEENV)

    std::uint32_t initret = mc2_cinit(); // <- Magic
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
    int result = StartOpenMC2();
    mc2__cexit();
    return result;
}
