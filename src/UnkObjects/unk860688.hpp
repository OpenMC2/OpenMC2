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

#include "../Addresses.hpp"

#include <array>

// Appears to be related to file proccessing
class unk_860688 {
private:
    std::array<char, 4> signature;
    void (__cdecl *callback)(void *); // argument is pointer to some type
    std::uint8_t pad08[4]{ };
    unk_860688 *next;

public:
    unk_860688(std::array<char, 4> signature, void(__cdecl *callback)(void *));
};

#define glo_860688 MC2_GLOBAL<unk_860688 *>(0x00860688)
