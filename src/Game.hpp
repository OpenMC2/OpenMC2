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

#include "Addresses.hpp"

int sub_401190();

int sub_6181F0();

#define sub_401170 (MC2_PROC_PTR<void>(0x00401170))
#define sub_4017E0 (MC2_PROC_PTR<void>(0x004017E0))
#define sub_402590 (MC2_PROC_PTR<void>(0x00402590))
#define sub_4028E0 (MC2_PROC_PTR<void>(0x004028E0))
#define sub_404BF0 (MC2_PROC_PTR<void>(0x00404BF0))
#define sub_53A1B0 (MC2_PROC_PTR<void>(0x0053A1B0))
#define sub_53A7B0 (MC2_PROC_PTR<void, const char *, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t>(0x0053A7B0))
#define sub_53A7D0 (MC2_PROC_PTR<void>(0x0053A7D0))
#define sub_53A7E0 (MC2_PROC_PTR<void, const char *>(0x0053A7E0))
#define sub_53A870 (MC2_PROC_PTR<void>(0x0053A870))
#define sub_53A8F0 (MC2_PROC_PTR<void>(0x0053A8F0))
#define sub_53B9F0 (MC2_PROC_PTR<void>(0x0053B9F0))
#define sub_5ECBE0 (MC2_PROC_PTR<void>(0x005ECBE0))
#define sub_5ED220 (MC2_PROC_PTR<void>(0x005ED220))
#define sub_5ED7B0 (MC2_PROC_PTR<void, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t>(0x005ED7B0))
#define sub_5EDA50 (MC2_PROC_PTR<void, const char *>(0x005EDA50))
#define sub_612C70 (MC2_PROC_PTR<void, char *>(0x00612C70))
#define sub_612EB0 (MC2_PROC_PTR<bool, const char *, std::int32_t, const char **>(0x00612EB0))
#define sub_613DD0 (MC2_PROC_PTR<void, const char *, void *, std::uint32_t>(0x00613DD0))
#define sub_627145 (MC2_PROC_PTR<bool, const char *, const char *>(0x00627145))

#define loc_4010B0 (MC2_POINTER<void>(0x004010B0))

#define glo_679778 (MC2_GLOBAL<std::uint8_t>(0x00679778))
#define glo_679810 (MC2_GLOBAL<void **>(0x00679810))
#define glo_692E1C (MC2_GLOBAL<void *>(0x00692E1C))
#define global_LanguageID (MC2_GLOBAL<std::uint32_t>(0x006C2C5C))
#define glo_6C2C64 (MC2_GLOBAL<std::uint8_t>(0x006C2C64))
#define glo_6CE210 (MC2_GLOBAL<std::uint8_t>(0x006CE210))
#define glo_6CE211 (MC2_GLOBAL<std::uint8_t>(0x006CE211))

#define loc_692E20 (MC2_POINTER<void *>(0x00692E20))
#define loc_6C3690 (MC2_POINTER<char>(0x006C3690)) // size: 0x200

#define global_hWnd (MC2_GLOBAL<HWND>(0x00858364))
#define glo_85837C (MC2_GLOBAL<std::uint32_t>(0x0085837C))
#define glo_8602D4 (MC2_GLOBAL<std::uint8_t>(0x008602D4))
#define glo_86D8A8 (MC2_GLOBAL<std::uint32_t>(0x0086D8A8))
#define global_WindowText (MC2_GLOBAL<char *>(0x00858390))
#define global_SKUVersion (MC2_GLOBAL<std::uint32_t>(0x006C2C58))
#define glo_66315C (MC2_GLOBAL<std::uint32_t>(0x0066315C))

#define glo_6C2C60 (MC2_GLOBAL<std::uint32_t>(0x006C2C60))
#define glo_6C2C64 (MC2_GLOBAL<std::uint8_t>(0x006C2C64))
#define glo_unlock_races (MC2_GLOBAL<std::uint8_t>(0x006C2C66))
#define glo_unlock_cities (MC2_GLOBAL<std::uint8_t>(0x006C2C67))
#define glo_unlock_vehicles (MC2_GLOBAL<std::uint8_t>(0x006C2C68))
#define glo_unlock_customization (MC2_GLOBAL<std::uint8_t>(0x006C2C69))
#define glo_unlock_abilities (MC2_GLOBAL<std::uint8_t>(0x006C2C6A))
#define glo_unlock_difficulty (MC2_GLOBAL<std::uint8_t>(0x006C2C6B))
#define glo_860120 (MC2_POINTER<char>(0x00860120))
