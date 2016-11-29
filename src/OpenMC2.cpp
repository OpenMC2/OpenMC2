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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <cstdint>

static_assert(sizeof(std::uintptr_t) == 4, "Compilation Not x86");
static_assert(sizeof(char) == 1, "Strings are not expected size");
static_assert(sizeof(bool) == 1, "Bools are not expected size");

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

// The template here adds compile-type checks to make sure
// that hooked methods are hooked with compatible functions.
template<class T, class... Types>
static void Hook_x86(T (*__cdecl in)(Types...), T (*__cdecl out)(Types...)) {
#pragma pack(push, 1)
    struct x86_jump {
        const std::uint8_t cmd = 0xE9;
        std::uintptr_t addr;
    };
#pragma pack(pop)
    static_assert(sizeof(x86_jump) == 5, "pragma pack failed");

    x86_jump cmd;
    cmd.addr = reinterpret_cast<std::uintptr_t>(out) - reinterpret_cast<std::uintptr_t>(in) - 5;
    WriteProcessMemory(GetCurrentProcess(), in, &cmd, 5, nullptr);
}

void OpenMC2_Hooks() {
    MC2_GLOBAL<void (*)(LogLevels, const char *, va_list)>(0x00679880) = &mc2_log_level_v;

    Hook_x86(&hook_5772E0, &mc2_malloc_info);
    Hook_x86(&hook_577320, &mc2_free);

    Hook_x86(&hook_5772A0, &mc2_malloc);
    Hook_x86(&hook_577350, &mc2_free);

    Hook_x86(&hook_613EA0, &mc2_aligned_malloc);
    Hook_x86(&hook_613EF0, &mc2_aligned_free);

    Hook_x86(&hook_614A10, &mc2_strdup_info);
}

// mc2: 0x00401010
extern "C" __declspec(dllexport) int __stdcall StartOpenMC2(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "\n\n\tOpenMC2 Is On Its Way :D\n\n" << std::endl;
    OpenMC2_Hooks();

    // Init MC2_MALLOC
    if ((glo_682E18 & 1) == 0) {
        glo_682E18 |= 1;
        glo_67A760 = loc_67A770;
    }

    load_config();

    unk_5769E0 a;
    a.sub_575BA0(glo_67A760, 0x18680, 1, 0);
    global_primary_unk5769E0 = &a;
    parse_commandline(global_argc, global_argv);
    sub_612910(global_argc, global_argv);

    int b = sub_6181F0();

    sub_612F00();

    return b;
}
