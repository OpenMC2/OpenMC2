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

#include <cstdarg>

#include "Addresses.hpp"

enum LogLevels {
    LOG_LEVEL_PRINT = 0,
    LOG_LEVEL_B,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL_ERROR
};

// sub_6184A0
void __cdecl mc2_log_level_v(LogLevels level, const char *format, va_list ap);

// sub_618610
void mc2_log_print(const char *format, ...);

// sub_618630
void mc2_log_B(const char *format, ...);

// sub_618650
void mc2_log_info(const char *format, ...);

// sub_618670
void mc2_log_warning(const char *format, ...);

// sub_618690
void mc2_log_error(const char *format, ...);

// sub_6186B0
void mc2_log_fatal(const char *format, ...);

extern bool &global_mbox_fatal; // glo_679844
extern std::uint8_t &global_log_level_flags; // glo_679848

extern std::int32_t &global_clog_begin; // glo_86CC38
extern std::int32_t &global_clog_end; // glo_86CC3C
extern bool &global_mbox_error; // glo_86D288
extern bool &glo_86D298;

extern char *loc_86CC40;
