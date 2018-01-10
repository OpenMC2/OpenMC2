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

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdint>

#include "../Addresses.hpp"

class unk_600960 {
private:
    std::uint8_t pad00[0x27C4];

public:
    unk_600960(HWND hWnd) {
        mc2_call_proc_thiscall<0x00600960, void>(this, hWnd);
    }

};

constexpr mc2_pointer<0x0085D3F8, unk_600960 *> loc_85D3F8;
