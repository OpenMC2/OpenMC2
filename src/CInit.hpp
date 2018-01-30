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

int mc2_cinit();

constexpr float sqrt_12_constant = 7.136496544f; // 2.0f * sqrt(12.732395f)
constexpr float sqrt_9_8_constant = 259.2296143f; // sqrt(9.8f / 0.00525f) * 6.0f

// All set to sqrt_12_constant
extern float &glo_692E80;
extern float &glo_692EAC;
extern float &glo_692EBC;
extern float &glo_692EC4;
extern float &glo_692EC8;
extern float &glo_696764;
extern float &glo_6967B0;
extern float &glo_696850;
extern float &glo_697B8C;
extern float &glo_697C18;
extern float &glo_698490;
extern float &glo_698620;
extern float &glo_69910C;
extern float &glo_6993A0;
extern float &glo_69948C;
extern float &glo_699690;
extern float &glo_69B5F8;
extern float &glo_69B78C;
extern float &glo_69C7A8;
extern float &glo_69C7AC;
extern float &glo_69C7B0;
extern float &glo_69C7B4;
extern float &glo_69C7BC;
extern float &glo_69C7C0;
extern float &glo_69C7C4;
extern float &glo_69C7C8;
extern float &glo_69C7CC;
extern float &glo_69C7D8;
extern float &glo_69C7E0;
extern float &glo_6C2600;
extern float &glo_6C521C;

extern float &glo_699860; // = 200.0f
extern float &glo_69B698; // = (44.704f / -26.8224f) * -0.5f
extern float &glo_69988C; // = 5.0f
extern float &glo_699864; // = 2.0f
extern float &glo_69B658; // = 0.2f
extern float &glo_699868; // = 0.22352f
extern float &glo_69B69C; // = 44.704f
extern float &glo_69B660; // = 1.34112f
extern float &glo_699888; // = -1.78816f
extern float &glo_69B664; // = -26.8224f
extern float &glo_69B65C; // = -1.78816f * 3.0f
extern float &glo_69985C; // = -26.8224f
extern float &glo_69B748; // = 5.0f / 6.0f
extern float &glo_6C39A4; // = 50.0f
extern float &glo_6C39A0; // = 90.0f
extern float &glo_6C520C; // = 1609.344f / 60.0f
extern float &glo_6C5220; // = 1.0f / 50.0f
extern float &glo_6C9034; // = (float) fabs((double) -9.8f)
extern float &glo_6C9030; // = 0.035f * 0.15f
extern float &glo_6C902C; // = sqrt_9_8_constant
extern float &glo_6CE510; // = 1.0f / 330.0f
