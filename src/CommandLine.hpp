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

#include <cstdint>
#include <iterator>

#include "Addresses.hpp"

class cmdline_info {
public:
    const char *name; // 0x00
    const char *desc; // 0x04
    const char *value; // 0x08
    std::int32_t index; // 0x0C
    cmdline_info *next; // 0x10

    // mc2: 0x00612F80
    cmdline_info(std::int32_t index, const char *name, const char *desc);

    // C++ Magic
    class iterator : public std::iterator<std::forward_iterator_tag, cmdline_info> {
    public:
        inline iterator(cmdline_info *c) : info(c) { }
        inline iterator() : info(nullptr) { }
        inline cmdline_info &operator*() const { return *info; }
        inline cmdline_info *operator->() const { return info; }
        inline bool operator==(const iterator &o) const { return info == o.info; }
        inline bool operator!=(const iterator &o) const { return info != o.info; }
        inline iterator &operator++() { info = info->next; return *this; }
        inline iterator operator++(int i) { iterator tmp(*this); info = info->next; return tmp; }

    private:
        cmdline_info *info;
    };

    inline iterator begin() { return iterator(this); }
    inline iterator end() { return iterator(); }
};

inline cmdline_info::iterator begin(cmdline_info c) { return c.begin(); }
inline cmdline_info::iterator end(cmdline_info c) { return c.end(); }
inline cmdline_info::iterator begin(cmdline_info *c) { return c->begin(); }
inline cmdline_info::iterator end(cmdline_info *c) { return c->end(); }

// sub_6131E0
void parse_commandline(std::int32_t argc, char **argv);

// sub_612FB0
void print_help();

void sub_612910(std::int32_t argc, char **argv);

#define glo_pal_cmdline (MC2_GLOBAL<cmdline_info>(0x0085AE90)) // glo_85AE90

#define global_cmdline (MC2_GLOBAL<cmdline_info *>(0x00860110)) // glo_860110
#define global_exe_name (MC2_GLOBAL<char *>(0x00860114)) // glo_860114
#define global_help_has_printed (MC2_GLOBAL<bool>(0x00860118)) // glo_860118
#define global_argc (MC2_GLOBAL<std::int32_t>(0x0086D7E8)) // glo_86D7E8
#define global_argv (MC2_GLOBAL<char **>(0x0086D7EC)) // glo_86D7EC

#define glo_8600EC (MC2_GLOBAL<char **>(0x008600EC))
#define glo_8600F0 (MC2_GLOBAL<std::int32_t>(0x008600F0))
