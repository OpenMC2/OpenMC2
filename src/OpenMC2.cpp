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
#include "UnkObjects/unk5769E0.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <cstdint>

static_assert(sizeof(std::uintptr_t) == 4, "Compilation Not x86");
static_assert(sizeof(char) == 1, "Strings are not expected size");

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

extern "C" {
    __declspec(dllexport) int __stdcall StartOpenMC2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
}

// mc2: 0x00401010
__declspec(dllexport) int __stdcall StartOpenMC2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "\n\n\tOpenMC2 Is On Its Way :D\n\n" << std::endl;

    if ((glo_682E18 & 1) == 0) {
        glo_682E18 |= 1;
        glo_67A760 = &glo_67A770;
    }

    unk_5769E0 a;
    a.sub_575BA0(glo_67A760, 0x18680, 1, 0);
    glo_6C5258 = &a;
    parse_commandline(global_argc, global_argv);
    sub_612910(global_argc, global_argv);

    std::uint32_t b = sub_6181F0();

    sub_612F00();

    return b;
}
