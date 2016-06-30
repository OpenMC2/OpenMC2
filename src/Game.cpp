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

#include "Game.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Logging.hpp"

#define sub_6178E0 (MC2_PROC_PTR<int, LPEXCEPTION_POINTERS>(0x006178E0))

int sub_6181F0() {
    __try {
        return sub_401190();
    } __except (sub_6178E0(GetExceptionInformation())) {
        mc2_log_C("ExceptMain: Abnormal exit.");
        return 1;
    }
    return 0;
}
