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

#define sub_5772E0 (MC2_PROC_PTR<void *, size_t, const char *, std::uint32_t>(0x005772E0))
#define sub_612E10 (MC2_PROC_PTR<bool, char *>(0x00612E10))
#define sub_612E30 (MC2_PROC_PTR<bool, char *, std::uint32_t, void *>(0x00612E30))
#define sub_612F00 (MC2_PROC_PTR<void>(0x00612F00))
#define sub_614A10 (MC2_PROC_PTR<char *, const char *, const char *, std::uint32_t>(0x00614A10))

#define MC2_MALLOC(size) (sub_5772E0(size, "OpenMC2:" __FILE__, __LINE__))
#define MC2_STRDUP(s) (sub_614A10(s, "OpenMC2:" __FILE__, __LINE__))

// Global Variables

#define glo_67A760 (MC2_GLOBAL<void *>(0x0067A760))
#define loc_67A770 (MC2_POINTER<void>(0x0067A770))
#define glo_682E18 (MC2_GLOBAL<bool>(0x00682E18))
