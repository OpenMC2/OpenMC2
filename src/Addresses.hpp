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

#include "CommandLine.hpp"
#include "Logging.hpp"
#include "UnkObjects/unk86D28C.hpp"

#define safe_strncpy(dest, src, len) ((void) strncpy_s(dest, len, src, len - 1))

// Helper Functions

template<class T>
inline T &MC2_GLOBAL(const std::uintptr_t address) {
    return *reinterpret_cast<T *>(address);
}

template<class T>
inline T *MC2_POINTER(const std::uintptr_t address) {
    return reinterpret_cast<T *>(address);
}

template<class T, class... Types>
inline T MC2_PROC(const std::uintptr_t address, Types... args) {
    return reinterpret_cast<T(__cdecl *)(Types...)>(address)(args...);
}

template<class T, class X, class... Types>
inline T MC2_PROC_MEMBER(const std::uintptr_t address, X *const self, Types... args) {
    return reinterpret_cast<T(__thiscall *)(X *, Types...)>(address)(self, args...);
}

template<class T, class... Types>
inline T (*MC2_PROC_PTR(const std::uintptr_t address))(Types...) {
    return reinterpret_cast<T(__cdecl *)(Types...)>(address);
}

template<class T, class... Types>
inline T (*MC2_PROC_PTR_VA(const std::uintptr_t address))(Types..., ...) {
    return reinterpret_cast<T(__cdecl *)(Types..., ...)>(address);
}

// Functions

#define sub_575B70 (MC2_PROC_PTR<void>(0x00575B70))
#define sub_612910 (MC2_PROC_PTR<void, std::int32_t, char **>(0x00612910))
#define sub_612E10 (MC2_PROC_PTR<std::uint8_t, char *>(0x00612E10))
#define sub_612E30 (MC2_PROC_PTR<void, char *, std::uint32_t, std::uint32_t *>(0x00612E30))
#define sub_612F00 (MC2_PROC_PTR<void>(0x00612F00))
#define sub_6181F0 (MC2_PROC_PTR<std::uint32_t>(0x006181F0))
#define sub_61BAC1 (MC2_PROC_PTR<void, void *>(0x0061BAC1))
#define sub_6299B6 (MC2_PROC_PTR<std::uint32_t, char *, char *, std::uint32_t>(0x006299B6))

// Global Variables

#define glo_679844 (MC2_GLOBAL<std::uint8_t>(0x00679844))
#define glo_679848 (MC2_GLOBAL<std::uint8_t>(0x00679848))
#define glo_67A760 (MC2_GLOBAL<std::uint32_t *>(0x0067A760))
#define glo_67A770 (MC2_GLOBAL<std::uint32_t>(0x0067A770))
#define glo_682E18 (MC2_GLOBAL<std::uint32_t>(0x00682E18))
#define glo_6C5240 (MC2_GLOBAL<unk_5769E0 *>(0x006C5240))
#define glo_6C524C (MC2_GLOBAL<std::uint32_t>(0x006C524C))
#define glo_6C5254 (MC2_GLOBAL<std::uint8_t>(0x006C5254))
#define glo_6C5258 (MC2_GLOBAL<unk_5769E0 *>(0x006C5258))

#define global_cmdline (MC2_GLOBAL<cmdline_info *>(0x00860110)) // glo_860110
#define global_exe_name (MC2_GLOBAL<char *>(0x00860114)) // glo_860114
#define global_help_has_printed (MC2_GLOBAL<std::uint8_t>(0x00860118)) // glo_860118
#define glo_860119 (MC2_GLOBAL<char>(0x00860119))
#define glo_86CC38 (MC2_GLOBAL<std::int32_t>(0x0086CC38))
#define glo_86CC3C (MC2_GLOBAL<std::int32_t>(0x0086CC3C))
#define glo_86D288 (MC2_GLOBAL<std::uint8_t>(0x0086D288))
#define glo_86D28C (MC2_GLOBAL<unk_86D28C *>(0x0086D28C))
#define glo_86D298 (MC2_GLOBAL<std::uint8_t>(0x0086D298))
#define global_argc (MC2_GLOBAL<std::int32_t>(0x0086D7E8)) // glo_86D7E8
#define global_argv (MC2_GLOBAL<char **>(0x0086D7EC)) // glo_86D7EC

#define loc_86CC40 (MC2_POINTER<char>(0x0086CC40))
