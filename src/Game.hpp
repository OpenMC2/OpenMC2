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

constexpr mc2_proc<0x004010B0, void> sub_4010B0;
constexpr mc2_proc<0x00401170, void> sub_401170;
constexpr mc2_proc<0x004017E0, void> sub_4017E0;
constexpr mc2_proc<0x00402590, void> sub_402590;
constexpr mc2_proc<0x004028E0, void> sub_4028E0;
constexpr mc2_proc<0x00404BF0, void> sub_404BF0;
constexpr mc2_proc<0x0053A1B0, void> sub_53A1B0;
constexpr mc2_proc<0x0053A7D0, void> sub_53A7D0;
constexpr mc2_proc<0x0053A8F0, void> sub_53A8F0;
constexpr mc2_proc<0x00577480, void, const char *> sub_577480;
constexpr mc2_proc<0x005ECB90, void> sub_5ECB90;
constexpr mc2_proc<0x005ED220, void> sub_5ED220;
constexpr mc2_proc<0x005ED240, void, const char *, std::uint32_t, std::uint32_t> sub_5ED240;
constexpr mc2_proc<0x005EDA50, void, const char *> sub_5EDA50;
constexpr mc2_proc<0x005F0BC0, void> sub_5F0BC0;
constexpr mc2_proc<0x005F12F0, bool> sub_5F12F0;
constexpr mc2_proc<0x005F9E20, void> sub_5F9E20;
constexpr mc2_proc<0x005F9E30, void> sub_5F9E30;
constexpr mc2_proc<0x005FD2D0, void> sub_5FD2D0;
constexpr mc2_proc<0x00612130, void> sub_612130;
constexpr mc2_proc<0x00612C70, void, char *> sub_612C70;
constexpr mc2_proc<0x00613DD0, void, const char *, void *, std::uint32_t> sub_613DD0;
constexpr mc2_proc<0x00617AA0, void> sub_617AA0;

constexpr mc2_pointer<0x006754AC, const char *> location_texture_dir_name;
constexpr mc2_pointer<0x00675518, const char *> location_mod_dir_name;
// This is just 1.0
constexpr mc2_pointer<0x0062D57C, const float> loc_1_P_0;

constexpr mc2_pointer<0x00674FAC, std::uint32_t> loc_674FAC;
constexpr mc2_pointer<0x00674FB0, std::uint32_t> loc_674FB0;
constexpr mc2_pointer<0x00674FB4, std::uint32_t> loc_674FB4;
constexpr mc2_pointer<0x00674FB8, std::uint32_t> loc_674FB8;
constexpr mc2_pointer<0x00675030, std::uint32_t> loc_675030;
constexpr mc2_pointer<0x006754A4, std::uint32_t> loc_6754A4;
constexpr mc2_pointer<0x006754A8, float> loc_6754A8;

constexpr mc2_pointer<0x00679810, unk_679810_funcTable *> loc_679810;
constexpr mc2_pointer<0x00679814, unk_679810_funcTable *> loc_679814;
constexpr mc2_pointer<0x00692E1C, unk_679810_funcTable *> loc_692E1C;

constexpr mc2_pointer<0x006C2C5C, std::uint32_t> location_LanguageID;
constexpr mc2_pointer<0x006CE210, std::uint8_t> loc_6CE210;
constexpr mc2_pointer<0x006CE211, std::uint8_t> loc_6CE211;

constexpr mc2_pointer<0x00692E20, unk_679810_funcTable> loc_692E20;
constexpr mc2_pointer<0x00679884, unk_679810_funcTable> loc_679884;
constexpr mc2_pointer<0x006C3690, char[0x200]> loc_6C3690;

constexpr mc2_pointer<0x00858364, HWND> location_hWnd;
constexpr mc2_pointer<0x00858371, bool> loc_858371;
constexpr mc2_pointer<0x00858373, bool> loc_858373;
constexpr mc2_pointer<0x00858374, bool> loc_858374;
constexpr mc2_pointer<0x00858375, bool> loc_858375;
constexpr mc2_pointer<0x00858376, bool> loc_858376;
constexpr mc2_pointer<0x00858377, bool> loc_858377;
constexpr mc2_pointer<0x0085837C, std::uint32_t> loc_85837C;
constexpr mc2_pointer<0x00858388, std::uint32_t> loc_858388;
constexpr mc2_pointer<0x0085838C, float> loc_85838C;
constexpr mc2_pointer<0x00858390, const char *> location_WindowText;
constexpr mc2_pointer<0x0085839C, std::uint32_t> loc_85839C;
constexpr mc2_pointer<0x008583B0, float> loc_8583B0;
constexpr mc2_pointer<0x0085AE8C, bool> loc_85AE8C;
constexpr mc2_pointer<0x0085AE98, std::uint32_t> loc_85AE98;
constexpr mc2_pointer<0x0085FBB0, std::uint32_t> loc_85FBB0;
constexpr mc2_pointer<0x0085FBC4, std::uint32_t> loc_85FBC4;
constexpr mc2_pointer<0x0085FBDC, float> loc_85FBDC;
constexpr mc2_pointer<0x0085FBE0, float> loc_85FBE0;
constexpr mc2_pointer<0x008602D4, bool> loc_8602D4;
constexpr mc2_pointer<0x00860AD8, mc2_proc_ptr<bool, char *, bool>> loc_860AD8;
constexpr mc2_pointer<0x0086D8A8, std::uint32_t> loc_86D8A8;

constexpr mc2_pointer<0x0066315C, std::uint32_t> loc_66315C;

constexpr mc2_pointer<0x006C2C58, std::uint32_t> location_SKUVersion;
constexpr mc2_pointer<0x006C2C60, std::uint32_t> loc_6C2C60;
constexpr mc2_pointer<0x006C2C64, std::uint8_t> loc_6C2C64;
constexpr mc2_pointer<0x006C2C66, bool> loc_unlock_races;
constexpr mc2_pointer<0x006C2C67, bool> loc_unlock_cities;
constexpr mc2_pointer<0x006C2C68, bool> loc_unlock_vehicles;
constexpr mc2_pointer<0x006C2C69, bool> loc_unlock_customization;
constexpr mc2_pointer<0x006C2C6A, bool> loc_unlock_abilities;
constexpr mc2_pointer<0x006C2C6B, bool> loc_unlock_difficulty; // unused?
constexpr mc2_pointer<0x00860120, char[256]> loc_860120;
constexpr mc2_pointer<0x006754C4, mc2_proc_ptr<void>> loc_6754C4;
constexpr mc2_pointer<0x00858328, mc2_proc_ptr<void>> loc_858328;
