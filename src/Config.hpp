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

#include <string>

void load_config();

extern std::string config_assets_name;

struct net_config_t {
    std::string main;
    std::string master;
    std::string natneg1;
    std::string natneg2;
};
extern net_config_t net_config;

extern bool &glo_windowed_mode;

extern const char *&glo_6738A0;
extern const char *&glo_6738A4;
extern const char *&glo_6C4C74;
extern char (&glo_6C4EA0)[64];
