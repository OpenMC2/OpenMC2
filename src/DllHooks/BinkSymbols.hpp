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

#include "../Addresses.hpp"

#include <array>

constexpr size_t BinkCount = 9;
extern std::array<void *, BinkCount> &BinkPointers;

constexpr std::array<const char *, BinkCount> BinkNames = {
    "_BinkNextFrame@4",
    "_BinkCopyToBuffer@28",
    "_BinkOpenMiles@4",
    "_BinkSetSoundSystem@8",
    "_BinkSetVolume@12",
    "_BinkClose@4",
    "_BinkWait@4",
    "_BinkOpen@8",
    "_BinkDoFrame@4",
};
