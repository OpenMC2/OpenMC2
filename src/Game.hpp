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

int get_language_id(const char *path);
const char *get_language_string(int id);

void sub_6134D0(const char *var8);

void sub_6177E0(std::int32_t max, DWORD ebp, FILE *log, const char *endline);
int sub_6181F0();

void sub_612F00();

void sub_5ED7B0(int32_t width, int32_t height, int32_t cdepth, int32_t zdepth, int32_t unk5);

extern MC2_PROC_PTR<std::int32_t, HANDLE, void *, std::int32_t> sub_4010B0;
extern MC2_PROC_PTR<void> sub_401170;
extern MC2_PROC_PTR<void> sub_4017E0;
extern MC2_PROC_PTR<void> sub_402590;
extern MC2_PROC_PTR<void> sub_4028E0;
extern MC2_PROC_PTR<void> sub_404BF0;
extern MC2_PROC_PTR<void> sub_53A1B0;
extern MC2_PROC_PTR<void> sub_53A7D0;
extern MC2_PROC_PTR<void> sub_53A8F0;
extern MC2_PROC_PTR<void> sub_5ECB90;
extern MC2_PROC_PTR<void> sub_5ED220;
extern MC2_PROC_PTR<void, const char *, std::uint32_t, std::uint32_t> sub_5ED240;
extern MC2_PROC_PTR<void, const char *> sub_5EDA50;
extern MC2_PROC_PTR<void> sub_5EE9F0;
extern MC2_PROC_PTR<void> sub_5F0BC0;
extern MC2_PROC_PTR<bool> sub_5F12F0;
extern MC2_PROC_PTR<void> sub_5F9E20;
extern MC2_PROC_PTR<void> sub_5F9E30;
extern MC2_PROC_PTR<void, std::uint32_t, std::uint32_t, std::uint32_t> sub_5FAFE0;
extern MC2_PROC_PTR<void> sub_5FD2D0;
extern MC2_PROC_PTR<void> sub_612130;
extern MC2_PROC_PTR<void, char *> sub_612C70;
extern MC2_PROC_PTR<void, const char *, void *, std::uint32_t> sub_613DD0;
extern MC2_PROC_PTR<void, char *, DWORD> sub_617760;

extern const char *&global_texture_dir_name;
extern const char *&global_mod_dir_name;

extern std::uint32_t &glo_674FAC;
extern std::uint32_t &glo_674FB0;
extern std::uint32_t &glo_674FB4;
extern std::uint32_t &glo_674FB8;
extern std::uint32_t &glo_675030;
extern std::uint32_t &glo_6754A4;
extern float &glo_6754A8;

extern std::uint32_t &global_LanguageID; // glo_6C2C5C
extern std::uint8_t &glo_6CE210;
extern std::uint8_t &glo_6CE211;

extern char(&glo_6C3690)[0x200];

extern HWND &global_hWnd;
extern std::uint8_t &glo_858371;
extern std::uint8_t &glo_858373;
extern std::uint8_t &glo_858374;
extern std::uint8_t &glo_858375;
extern std::uint8_t &glo_858376;
extern std::uint8_t &glo_858377;
extern std::uint32_t &glo_85837C;
extern std::uint32_t &glo_858388;
extern float &glo_85838C;
extern std::uint32_t &glo_85839C;
extern float &glo_8583B0;
extern bool &glo_pal_mode;
extern bool &glo_85D1C0;
extern std::uint32_t &glo_85FBB0;
extern std::uint32_t &glo_85FBC4;
extern float &glo_85FBDC;
extern float &glo_85FBE0;
extern std::uint8_t &glo_8602D4;
extern MC2_PROC_PTR<bool, const char *, bool> &glo_860AD8;
extern std::uint32_t &glo_86D8A8;
extern char * &global_WindowText;
extern std::uint32_t &global_SKUVersion;
extern std::uint32_t &glo_66315C;

extern std::uint32_t &glo_6C2C60;
extern std::uint8_t &glo_6C2C64;
extern std::uint8_t &glo_unlock_races;
extern std::uint8_t &glo_unlock_cities;
extern std::uint8_t &glo_unlock_vehicles;
extern std::uint8_t &glo_unlock_customization;
extern std::uint8_t &glo_unlock_abilities;
extern std::uint8_t &glo_unlock_difficulty;
extern char *glo_860120;
extern MC2_PROC_PTR<void> &glo_6754C4;
extern MC2_PROC_PTR<void> &glo_858328;
