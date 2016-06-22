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

#include "CommandLine.hpp"

#include <algorithm>
#include <cstring>

#include "Addresses.hpp"

// mc2: 0x006131E0
void parse_commandline(std::int32_t argc, char **argv) {
    if (argc != 0 && argv != nullptr) global_exe_name = argv[0];
    else global_exe_name = "unknown";
    if (argc <= 1) return;

    bool c = false;
    for (std::int32_t i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) print_help();
        else if (argv[i][0] == '-' && (argv[i][1] < '0' || argv[i][1] > '9')) {
            c = true;
            for (cmdline_info &x : global_cmdline) {
                if (x.index == 0) {
                    std::uint32_t namelen = std::strlen(x.name);
                    if (sub_6299B6(argv[i] + 1, x.name, namelen) == 0) {
                        if (argv[i][namelen + 1] == '\0') {
                            if (i == argc - 1 || (argv[i + 1][0] == '-' &&
                                (argv[i + 1][1] < '0' || argv[i + 1][1] > '9')))
                                x.value = &glo_860119; // glo_860119 == "" ?
                            else x.value = argv[i + 1];
                        } else if (argv[i][namelen + 1] == '=') {
                            x.value = &argv[i][namelen + 2];
                        }
                    }
                }
            }
        } else if (!c) {
            for (cmdline_info &x : global_cmdline)
                if (x.index == i) x.value = argv[i];
        }
    }
}

// mc2: 0x00612FB0
void print_help() {
    if (!global_help_has_printed) {
        global_help_has_printed = true;

        std::int32_t best = 0;
        for (cmdline_info &x : global_cmdline)
            if (x.index > best) best = x.index;

        sub_log_info("%s ", global_exe_name);
        for (int i = 0; i < best; ++i)
            for (cmdline_info &x : global_cmdline)
                if (x.index == i + 1)
                    sub_log_info("%s ", x.name);
        sub_log_info("[options]\n");

        for (int i = 0; i < 2; ++i) {
            if (i == 1) sub_log_info("\n[options] are number of the following:\n");
            for (cmdline_info &x : global_cmdline) {
                if ((x.index == 0) != (i == 0)) {
                    if (i == 0) sub_log_info("%s: ", x.name);
                    else sub_log_info("-%s: ", x.name);

                    int rowlen = 10 - std::strlen(x.name) - (i == 0 ? 2 : 3);
                    sub_log_info("%.*s", std::max(rowlen, 0), "          ");
                    rowlen += 70;

                    char *c = x.desc;
                    if (*c != '\0') {
                        while (true) {
                            char *s = c++;
                            for (char *d = c; d - s < rowlen; ++d)
                                if (*d == ' ' || *(d - 1) == '-') c = d;
                                else if (*d == '\0') {
                                    sub_log_info("%s\n", s);
                                    goto nextarg;
                                }

                                sub_log_info("%.*s\n          ", c - s, s);
                                rowlen = 70;
                                if (*c == ' ') ++c;
                        }
                    }
                }
            nextarg:;
            }
        }
    }
}
