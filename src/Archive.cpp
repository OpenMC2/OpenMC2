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

#include "Archive.hpp"
#include "Game.hpp"
#include "Logging.hpp"

#include "UnkObjects/unk612850.hpp"

// mc2: 0x005FC660
Archive::Archive() {
    unk00 = glo_85D1C4;
    glo_85D1C4 = this;
}

void sub_5FDD20() {
    if (sub_612E10("logopen")) {
        glo_85D1C0 = true;
    }

    const char *file_name;
    for (std::uint32_t i = 0; sub_612EB0("archive", i, &file_name); ++i) {
        Archive *x = new Archive;
        if (x->sub_5FDCE0(file_name)) {
            sub_6134D0("");
        } else {
            mc2_log_error("Failed to load archive '%s'", file_name);
            delete x;
        }
    }
}

Archive *&glo_85D1C4 = MC2_GLOBAL<Archive *>(0x0085D1C4);
