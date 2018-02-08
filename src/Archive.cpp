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
#include "Memory.hpp"

#include "UnkObjects/unk612850.hpp"

// mc2: 0x005FC660
Archive::Archive() {
    unk00 = glo_85D1C4;
    glo_85D1C4 = this;
}

// mc2: 0x005FC690
Archive::~Archive() {
    mc2_aligned_free(unk0C);
    mc2_aligned_free(unk10);

    if (unk04 != INVALID_HANDLE_VALUE && unk1C != nullptr) {
        unk1C->close_file(unk04);
        CloseHandle(unk08);
    }

    glo_85D1C4 = unk00;
}

bool Archive::sub_5FDBF0(const char *file_name, FileHandler::FuncTable *b, bool c) {
    if (glo_85D1C8 == nullptr && c) {
        glo_85D1C8 = glo_679810;
        glo_679810 = &glo_6781C0;
    }
    
    unk1C = (b != nullptr) ? b : glo_85D1C8;
    FileHandler *file = sub_617CD0(file_name, unk1C, true);
    if (file == nullptr || !this->sub_5FD3A0(file_name, file)) return false;

    file->sub_617FB0();
    unk04 = unk1C->sub_00(file_name, true);
    unk08 = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
    return true;
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
