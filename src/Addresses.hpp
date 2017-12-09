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

#pragma once

#include <cstdint>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#define safe_strncpy(dest, src, len) ((void) strncpy_s(dest, len, src, len - 1))

// Helper Functions

extern "C" __declspec(dllimport) void mc2_import_start();

inline std::intptr_t MC2_OFFSET() {
    return reinterpret_cast<std::intptr_t>(&mc2_import_start) - 0x00401000;
}

template<class T>
inline T &MC2_GLOBAL(const std::uintptr_t address) {
    return *reinterpret_cast<T *>(MC2_OFFSET() + address);
}

template<class T>
inline T *MC2_POINTER(const std::uintptr_t address) {
    return reinterpret_cast<T *>(MC2_OFFSET() + address);
}

template<class T, class... Types>
inline T MC2_PROC(const std::uintptr_t address, Types... args) {
    return reinterpret_cast<T(__cdecl *)(Types...)>(MC2_OFFSET() + address)(args...);
}

template<class T, class X, class... Types>
inline T MC2_PROC_MEMBER(const std::uintptr_t address, X *const self, Types... args) {
    return reinterpret_cast<T(__thiscall *)(X *, Types...)>(MC2_OFFSET() + address)(self, args...);
}

template<class T, class... Types>
inline T (&__cdecl MC2_PROC_PTR(const std::uintptr_t address))(Types...) {
    return *reinterpret_cast<T(__cdecl *)(Types...)>(MC2_OFFSET() + address);
}

template<class T, class... Types>
inline T (&__cdecl MC2_PROC_PTR_VA(const std::uintptr_t address))(Types..., ...) {
    return *reinterpret_cast<T(__cdecl *)(Types..., ...)>(MC2_OFFSET() + address);
}


template<class T, class... Types>
inline void Hook_x86(T(&in)(Types...), T(&out)(Types...)) {
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

template<class T, class... Types>
struct Auto_Hook_x86_Obj {
    Auto_Hook_x86_Obj(T(&in)(Types...), T(&out)(Types...)) { Hook_x86(in, out); }
};

template<class T, class... Types>
Auto_Hook_x86_Obj<T, Types...> Auto_Hook_x86_Func(T(&in)(Types...), T(&out)(Types...)) {
    return Auto_Hook_x86_Obj<T, Types...>(in, out);
}

template<class T, class... Types>
Auto_Hook_x86_Obj<T, Types...> Auto_Hook_x86_Func(std::uint32_t in, T(&out)(Types...)) {
    return Auto_Hook_x86_Obj<T, Types...>(MC2_PROC_PTR<T, Types...>(in), out);
}

#define AUTO_HOOK_X86(in, out) static const auto _hookobj_##in (Auto_Hook_x86_Func(in, out))


template<class T, class... Types>
inline void Hook_Fnptr(T(*&in)(Types...), T(&out)(Types...)) {
    in = &out;
}

template<class T, class... Types>
struct Auto_Hook_Fnptr_Obj {
    Auto_Hook_Fnptr_Obj(T(*&in)(Types...), T(&out)(Types...)) { Hook_Fnptr(in, out); }
};

template<class T, class... Types>
Auto_Hook_Fnptr_Obj<T, Types...> Auto_Hook_Fnptr_Func(T(*&in)(Types...), T(&out)(Types...)) {
    return Auto_Hook_Fnptr_Obj<T, Types...>(in, out);
}

template<class T, class... Types>
Auto_Hook_Fnptr_Obj<T, Types...> Auto_Hook_Fnptr_Func(std::uint32_t in, T(&out)(Types...)) {
    return Auto_Hook_Fnptr_Obj<T, Types...>(MC2_GLOBAL<T(*)(Types...)>(in), out);
}

#define AUTO_HOOK_FNPTR(in, out) static const auto _hookobj_##in (Auto_Hook_Fnptr_Func(in, out))


// Functions

#define sub_61A5DC (MC2_PROC_PTR<uint32_t, char *>(0x0061A5DC))

// Global Variables

#define glo_67A760 (MC2_GLOBAL<void *>(0x0067A760))
#define loc_67A770 (MC2_POINTER<void>(0x0067A770))
#define glo_682E18 (MC2_GLOBAL<bool>(0x00682E18))
#define glo_8602C8 (MC2_GLOBAL<uint32_t>(0x008602C8))
#define glo_679778 (MC2_GLOBAL<std::uint8_t>(0x00679778))

// MC2 Pre-Main Stuff
#define mc2_crt_start_main (MC2_PROC_PTR<void>(0x0061958A))
#define mc2_crt_call_main (MC2_PROC_PTR<void>(0x0061970D))
#define mc2_crt_end_main (MC2_PROC_PTR<void>(0x00619754))
