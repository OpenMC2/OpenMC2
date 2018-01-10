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

#include "Logging.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <string>

#include "FileHandler.hpp"

constexpr char *levelLabels[] = {
    "",
    "",
    "",
    "Warning: ",
    "Error: ",
    "Fatal Error: ",
};

constexpr char *levelEscLabels[] = {
    "",
    "",
    "",
    "\x1B[33mWarning: ",
    "\x1B[31mError: ",
    "\x1B[31mFatal Error: ",
};

constexpr char *levelEscClear[] = {
    "",
    "\x1B[0m\n",
    "\x1B[0m\n",
    "\x1B[0m\n",
    "\x1B[0m\n",
    "\x1B[0m\n",
};

// I'm not exactly sure what the purpose of these are, but they're in the code.

inline void ind_86D284(char *text) {
    static constexpr mc2_pointer<0x0086D284, mc2_proc_ptr<void, char *>> glo_86D284;
    if (*glo_86D284 != nullptr) {
        *mc2_pointer<0x0086D280, std::uint8_t>() = 1;
        (*glo_86D284)(text);
    }
}

// mc2: 0x00618470
inline void ind_86D290() {
    static constexpr mc2_pointer<0x0086D290, mc2_proc_ptr<void>> glo_86D290;
    if (*glo_86D290 != nullptr) (*glo_86D290)();
}

// mc2: 0x00618480
inline void ind_86D294() {
    static constexpr mc2_pointer<0x0086D294, mc2_proc_ptr<void>> glo_86D294;
    if (*glo_86D294 != nullptr) (*glo_86D294)();
}


// mc2: 0x00618270
static void clog_add(char *text) {
    *location_clog_end = ++(*location_clog_end) % 20;
    if (*location_clog_end == *location_clog_begin)
        *location_clog_begin = ++(*location_clog_begin) % 20;

    safe_strncpy((*loc_86CC40)[*location_clog_end], text, 80);
}

// mc2: 0x006182C0
static void print_ansi_esc(char *text) {
    bool escaped = false;
    unsigned int color;
    for (const char *c = text; *c != '\0'; ++c) {
        if (*c == '\x1B' && *(c + 1) == '[') {
            escaped = true;
            color = 0;
            ++c;
        } else if (escaped) {
            if (*c == 'm') {
                fflush(stdout);
                if (color == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                else if (color == 38) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                else if (color > 30 && color < 38) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                    ((color - 30) & 1 ? FOREGROUND_RED : 0) |
                    ((color - 30) & 2 ? FOREGROUND_GREEN : 0) |
                    ((color - 30) & 4 ? FOREGROUND_BLUE : 0) |
                    FOREGROUND_INTENSITY);
                escaped = false;
            } else if (*c >= '0' && *c <= '9') {
                color = (color * 10) + (*c - '0');
            }
        } else putc(*c, stdout);
    }
}


// mc2: 0x006184A0
void __cdecl mc2_log_level_v(LogLevels level, const char *format, va_list ap) {
    char text[0x1000];
    std::vsnprintf(text, 0x1000, format, ap);

    if ((*location_mbox_error && level == LOG_LEVEL_ERROR) ||
        (*location_mbox_fatal && level == LOG_LEVEL_FATAL_ERROR)) {
        ind_86D290();
        MessageBoxA(nullptr, text, levelLabels[level], MB_ICONERROR);
        if (level == LOG_LEVEL_ERROR) ind_86D294();
    }

    const char *suffix;
    if (level == LOG_LEVEL_PRINT) suffix = "";
    else suffix = "\n";

    char output[0x1000];
    std::snprintf(output, 0x1000, "%s%s%s", levelLabels[level], text, suffix);
    OutputDebugStringA(output);

    std::snprintf(output, 0x1000, "%s%s%s", levelEscLabels[level], text, levelEscClear[level]);
    clog_add(text);
    print_ansi_esc(output); // indirctly through off_67984C

    if (*loc_86D28C != nullptr) {
        sub_618050(*loc_86D28C, "%s%s%s", levelEscLabels[level], text, levelEscClear[level]);
        (*loc_86D28C)->sub_617AF0();
    }

    if (level == LOG_LEVEL_FATAL_ERROR) ind_86D284(text);

    *loc_86D298 = true;
}

// All references to sub_6184A0 are indirectly called
// via off_679880 in the original assembly

// mc2: 0x00618610
void mc2_log_print(const char *format, ...) {
    if (*location_log_level_flags & 0x02) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_PRINT, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618630
void mc2_log_B(const char *format, ...) {
    if (*location_log_level_flags & 0x02) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_B, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618650
void mc2_log_C(const char *format, ...) {
    if (*location_log_level_flags & 0x02) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_C, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618670
void mc2_log_warning(const char *format, ...) {
    if (*location_log_level_flags & 0x04) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_WARNING, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618690
void mc2_log_error(const char *format, ...) {
    if (*location_log_level_flags & 0x08) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_ERROR, format, ap);
        va_end(ap);
    }
}

// mc2: 0x006186B0 Based on
void mc2_log_fatal(const char *format, ...) {
    if (format != NULL) {
        va_list ap;
        va_start(ap, format);
        mc2_log_level_v(LOG_LEVEL_FATAL_ERROR, format, ap);
        va_end(ap);
    }

    std::terminate();
}

AUTO_HOOK_FNPTR_ADDR(0x00679880, mc2_log_level_v);
