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

// Functions

#define sub_575B70 (MC2_PROC_PTR<void>(0x00575B70))
#define sub_612910 (MC2_PROC_PTR<void, std::uint32_t, std::uint32_t>(0x00612910))
#define sub_612E10 (MC2_PROC_PTR<std::uint8_t, char *>(0x00612E10))
#define sub_612E30 (MC2_PROC_PTR<void, char *, std::uint32_t, std::uint32_t *>(0x00612E30))
#define sub_612F00 (MC2_PROC_PTR<void>(0x00612F00))
#define sub_6131E0 (MC2_PROC_PTR<void, std::uint32_t, std::uint32_t>(0x006131E0))
#define sub_6181F0 (MC2_PROC_PTR<std::uint32_t>(0x006181F0))

// Global Variables

#define glo_67A760 (MC2_GLOBAL<std::uint32_t *>(0x0067A760))
#define glo_67A770 (MC2_GLOBAL<std::uint32_t>(0x0067A770))
#define glo_682E18 (MC2_GLOBAL<std::uint32_t>(0x00682E18))
#define glo_6C5240 (MC2_GLOBAL<unk_5769E0 *>(0x006C5240))
#define glo_6C524C (MC2_GLOBAL<std::uint32_t>(0x006C524C))
#define glo_6C5254 (MC2_GLOBAL<std::uint8_t>(0x006C5254))
#define glo_6C5258 (MC2_GLOBAL<unk_5769E0 *>(0x006C5258))

#define glo_86D7E8 (MC2_GLOBAL<std::uint32_t>(0x0086D7E8))
#define glo_86D7EC (MC2_GLOBAL<std::uint32_t>(0x0086D7EC))
