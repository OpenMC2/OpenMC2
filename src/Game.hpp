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

extern void(__cdecl &sub_4010B0)();
extern void(__cdecl &sub_401170)();
extern void(__cdecl &sub_4017E0)();
extern void(__cdecl &sub_402590)();
extern void(__cdecl &sub_4028E0)();
extern void(__cdecl &sub_404BF0)();
extern void(__cdecl &sub_53A1B0)();
extern void(__cdecl &sub_53A7D0)();
extern void(__cdecl &sub_53A8F0)();
extern void(__cdecl &sub_577480)(const char *);
extern void(__cdecl &sub_5ECB90)();
extern void(__cdecl &sub_5ED220)();
extern void(__cdecl &sub_5ED240)(const char *, std::uint32_t, std::uint32_t);
extern void(__cdecl &sub_5EDA50)(const char *);
extern void(__cdecl &sub_5F0BC0)();
extern bool(__cdecl &sub_5F12F0)();
extern void(__cdecl &sub_5F9E20)();
extern void(__cdecl &sub_5F9E30)();
extern void(__cdecl &sub_5FD2D0)();
extern void(__cdecl &sub_612130)();
extern void(__cdecl &sub_612C70)(char *);
extern void(__cdecl &sub_613DD0)(const char *, void *, std::uint32_t);

extern const char *&global_texture_dir_name;
extern const char *&global_mod_dir_name;

extern std::uint32_t &glo_674FAC;
extern std::uint32_t &glo_674FB0;
extern std::uint32_t &glo_674FB4;
extern std::uint32_t &glo_674FB8;
extern std::uint32_t &glo_675030;
extern std::uint32_t &glo_6754A4;
extern float &glo_6754A8;

extern unk_679810_funcTable *&glo_679810;
extern unk_679810_funcTable *&glo_679814;
extern unk_679810_funcTable *&glo_692E1C;
extern std::uint32_t &global_LanguageID; // glo_6C2C5C
extern std::uint8_t &glo_6CE210;
extern std::uint8_t &glo_6CE211;

extern unk_679810_funcTable &glo_692E20;
extern unk_679810_funcTable &glo_679884;
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
extern std::uint32_t &glo_85FBB0;
extern std::uint32_t &glo_85FBC4;
extern float &glo_85FBDC;
extern float &glo_85FBE0;
extern std::uint8_t &glo_8602D4;
extern bool(__cdecl *&glo_860AD8)(char *, bool);
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
extern void(__cdecl *&glo_6754C4)();
extern void(__cdecl *&glo_858328)();
