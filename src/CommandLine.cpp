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

#include <cstring>

#include "Addresses.hpp"
#include "UnkStructures.hpp"

// mc2: 0x006131E0
void parse_commandline(std::int32_t argc, char **argv) {
    if (argc != 0 && argv != nullptr) glo_860114 = argv[0];
    else glo_860114 = "unknown";
    if (argc <= 1) return;

    bool c = false;
    for (std::int32_t i=1; i < argc; ++i) {
        if (strcmp(argv[i], "-help") == 0) print_help();
        else if (argv[i][0] == '-' && (argv[i][1] < '0' || argv[i][1] > '9')) {
            c = true;
            for (str_860110 *x = glo_860110; x != nullptr; x = x->unk10) {
                if (x->unk0C == 0) {
                    std::uint32_t x00len = std::strlen(x->unk00);
                    if (sub_6299B6(argv[i] + 1, x->unk00, x00len) == 0) {
                        if (argv[i][x00len + 1] == '\0') {
                            if (i == argc - 1 || (argv[i + 1][0] == '-' &&
                                (argv[i + 1][1] < '0' || argv[i + 1][1] > '9')))
                                x->unk08 = &glo_860119;
                            else x->unk08 = argv[i + 1];
                        } else if (argv[i][x00len + 1] == '=') {
                            x->unk08 = &argv[i][x00len + 2];
                        }
                    }
                }
            }
        } else if (!c) {
            for (str_860110 *x = glo_860110; x != nullptr; x = x->unk10)
                if (x->unk0C == i) x->unk08 = argv[i];
        }
    }
}
