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
#include "FileHandler.hpp"

int sub_401190();

int sub_5E1B50(const char *path);
const char *sub_5E1B40(int id);

int sub_6181F0();

void sub_612F00();
bool sub_612EB0(const char *key, std::uint32_t value_index, const char **value_arg);

void sub_5ED7B0(int32_t width, int32_t height, int32_t cdepth, int32_t zdepth, int32_t unk5);

#define sub_401170 (MC2_PROC_PTR<void>(0x00401170))
#define sub_4017E0 (MC2_PROC_PTR<void>(0x004017E0))
#define sub_402590 (MC2_PROC_PTR<void>(0x00402590))
#define sub_4028E0 (MC2_PROC_PTR<void>(0x004028E0))
#define sub_404BF0 (MC2_PROC_PTR<void>(0x00404BF0))
#define sub_53A1B0 (MC2_PROC_PTR<void>(0x0053A1B0))
#define sub_53A7D0 (MC2_PROC_PTR<void>(0x0053A7D0))
#define sub_53A8F0 (MC2_PROC_PTR<void>(0x0053A8F0))
#define sub_577480 (MC2_PROC_PTR<void, const char *>(0x00577480))
#define sub_5ECB90 (MC2_PROC_PTR<void>(0x005ECB90))
#define sub_5ED220 (MC2_PROC_PTR<void>(0x005ED220))
#define sub_5ED240 (MC2_PROC_PTR<void, const char *, std::uint32_t, std::uint32_t>(0x005ED240))
#define sub_5EDA50 (MC2_PROC_PTR<void, const char *>(0x005EDA50))
#define sub_5F0BC0 (MC2_PROC_PTR<void>(0x005F0BC0))
#define sub_5F12F0 (MC2_PROC_PTR<bool>(0x005F12F0))
#define sub_5F9E20 (MC2_PROC_PTR<void>(0x005F9E20))
#define sub_5F9E30 (MC2_PROC_PTR<void>(0x005F9E30))
#define sub_5FD2D0 (MC2_PROC_PTR<void>(0x005FD2D0))
#define sub_612130 (MC2_PROC_PTR<void>(0x00612130))
#define sub_612C70 (MC2_PROC_PTR<void, char *>(0x00612C70))
#define sub_613DD0 (MC2_PROC_PTR<void, const char *, void *, std::uint32_t>(0x00613DD0))

#define loc_4010B0 (MC2_PROC_PTR<void>(0x004010B0))

#define global_texture_dir_name (MC2_GLOBAL<const char *>(0x006754AC))
#define global_mod_dir_name (MC2_GLOBAL<const char *>(0x00675518))
// This is just 1.0
#define glo_1_P_0 (MC2_GLOBAL<float>(0x0062D57C))

#define glo_674FAC (MC2_GLOBAL<std::uint32_t>(0x00674FAC))
#define glo_674FB0 (MC2_GLOBAL<std::uint32_t>(0x00674FB0))
#define glo_674FB4 (MC2_GLOBAL<std::uint32_t>(0x00674FB4))
#define glo_674FB8 (MC2_GLOBAL<std::uint32_t>(0x00674FB8))
#define glo_675030 (MC2_GLOBAL<std::uint32_t>)(0x00675030)
#define glo_6754A4 (MC2_GLOBAL<std::uint32_t>(0x006754A4))
#define glo_6754A8 (MC2_GLOBAL<float>(0x006754A8))

#define glo_679810 (MC2_GLOBAL<unk_679810_funcTable *>(0x00679810))
#define glo_679814 (MC2_GLOBAL<unk_679810_funcTable *>(0x00679814))
#define glo_692E1C (MC2_GLOBAL<unk_679810_funcTable *>(0x00692E1C))
#define global_LanguageID (MC2_GLOBAL<std::uint32_t>(0x006C2C5C))
#define glo_6C2C64 (MC2_GLOBAL<std::uint8_t>(0x006C2C64))
#define glo_6CE210 (MC2_GLOBAL<std::uint8_t>(0x006CE210))
#define glo_6CE211 (MC2_GLOBAL<std::uint8_t>(0x006CE211))

#define loc_692E20 (MC2_POINTER<unk_679810_funcTable>(0x00692E20))
#define loc_679884 (MC2_POINTER<unk_679810_funcTable>(0x00679884))
#define loc_6C3690 (MC2_POINTER<char>(0x006C3690)) // size: 0x200

#define global_hWnd (MC2_GLOBAL<HWND>(0x00858364))
#define glo_858371 (MC2_GLOBAL<std::uint8_t>(0x00858371))
#define glo_858373 (MC2_GLOBAL<std::uint8_t>)(0x00858373)
#define glo_858374 (MC2_GLOBAL<std::uint8_t>)(0x00858374)
#define glo_858375 (MC2_GLOBAL<std::uint8_t>)(0x00858375)
#define glo_858376 (MC2_GLOBAL<std::uint8_t>)(0x00858376)
#define glo_858377 (MC2_GLOBAL<std::uint8_t>)(0x00858377)
#define glo_85837C (MC2_GLOBAL<std::uint32_t>(0x0085837C))
#define glo_858388 (MC2_GLOBAL<std::uint32_t>(0x00858388))
#define glo_85838C (MC2_GLOBAL<float>(0x0085838C))
#define glo_85839C (MC2_GLOBAL<std::uint32_t>(0x0085839C))
#define glo_8583B0 (MC2_GLOBAL<float>(0x008583B0))
#define glo_pal_mode (MC2_GLOBAL<bool>(0x0085AE8C))
#define glo_85FBB0 (MC2_GLOBAL<std::uint32_t>(0x0085FBB0))
#define glo_85FBC4 (MC2_GLOBAL<std::uint32_t>(0x0085FBC4))
#define glo_85FBDC (MC2_GLOBAL<float>(0x0085FBDC))
#define glo_85FBE0 (MC2_GLOBAL<float>(0x0085FBE0))
#define glo_8602D4 (MC2_GLOBAL<std::uint8_t>(0x008602D4))
#define glo_860AD8 (MC2_GLOBAL<bool(*)(char *path, bool unk2)>(0x00860AD8))
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
#define glo_6754C4 (MC2_GLOBAL< void(__cdecl *)() >(0x006754C4))
#define glo_858328 (MC2_GLOBAL< void(__cdecl *)() >(0x00858328))
