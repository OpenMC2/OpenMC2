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

#include "Addresses.hpp"

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
    void (*glo_86D284)(char *) = MC2_GLOBAL<void (*)(char *)>(0x0086D284);
    if (glo_86D284 != nullptr) {
        MC2_GLOBAL<std::uint8_t>(0x0086D280) = 1;
        glo_86D284(text);
    }
}

// mc2: 0x00618470
inline void ind_86D290() {
    void (*glo_86D290)() = MC2_GLOBAL<void (*)()>(0x0086D290);
    if (glo_86D290 != nullptr) glo_86D290();
}

// mc2: 0x00618480
inline void ind_86D294() {
    void (*glo_86D294)() = MC2_GLOBAL<void (*)()>(0x0086D294);
    if (glo_86D294 != nullptr) glo_86D294();
}

// mc2: 0x006182C0
static void sub_6182C0(char *text) {
    sub_618270(text);
    bool escaped = false;
    unsigned int color;
    for (const char *c = text; *c != '\0'; ++c) {
        if (*c == '\x1B' && *(c + 1) == '[') {
            escaped = true;
            color = 0;
            ++c;
        } else if (escaped) {
            if (*c == 'm') {
                sub_61BAC1(loc_6799C0);
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
        } else {
            sub_61BA40(*c, loc_6799C0);
        }
    }
}

// mc2: 0x006184A0
void __cdecl sub_6184A0(LogLevels level, const char *format, va_list ap) {
    char text[0x1000];
    std::vsnprintf(text, 0x1000, format, ap);

    if ((glo_86D288 != 0 && level == LOG_LEVEL_ERROR) ||
        (glo_679844 != 0 && level == LOG_LEVEL_FATAL_ERROR)) {
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
    sub_6182C0(output); // indirctly through off_67984C

    if (glo_86D28C != nullptr) {
        sub_618050(output, "%s%s%s", levelEscLabels[level], text, levelEscClear[level]);
        MC2_PROC_MEMBER<void>(0x00617AF0, output);
    }

    if (level == LOG_LEVEL_FATAL_ERROR) ind_86D284(text);

    glo_86D298 = 1;
}

// All references to sub_6184A0 are indirectly called
// via off_679880 in the original assembly

// mc2: 0x00618610
void mc2_log_print(const char *format, ...) {
    if (glo_679848 & 0x02) {
        va_list ap;
        va_start(ap, format);
        sub_6184A0(LOG_LEVEL_PRINT, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618630
void mc2_log_B(const char *format, ...) {
    if (glo_679848 & 0x02) {
        va_list ap;
        va_start(ap, format);
        sub_6184A0(LOG_LEVEL_B, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618650
void mc2_log_C(const char *format, ...) {
    if (glo_679848 & 0x02) {
        va_list ap;
        va_start(ap, format);
        sub_6184A0(LOG_LEVEL_C, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618670
void mc2_log_warning(const char *format, ...) {
    if (glo_679848 & 0x04) {
        va_list ap;
        va_start(ap, format);
        sub_6184A0(LOG_LEVEL_WARNING, format, ap);
        va_end(ap);
    }
}

// mc2: 0x00618690
void mc2_log_error(const char *format, ...) {
    if (glo_679848 & 0x08) {
        va_list ap;
        va_start(ap, format);
        sub_6184A0(LOG_LEVEL_ERROR, format, ap);
        va_end(ap);
    }
}
