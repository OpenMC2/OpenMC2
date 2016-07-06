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

#include "unk86D28C.hpp"

#include <algorithm>
#include <cstdarg>
#include <cstdio>

// mc2: 0x00618050
void sub_618050(unk_86D28C *a, const char *format, ...) {
    char buffer[0x400];
    va_list ap;
    va_start(ap, format);
    size_t len = std::vsnprintf(buffer, 0x400, format, ap);
    a->sub_617E40(buffer, std::max(len, (size_t) 0));
    va_end(ap);
}
