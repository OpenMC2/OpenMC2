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

#include "Addresses.hpp"
#include "FileHandler.hpp"

class Archive {
private:
    Archive * unk00;
    HANDLE unk04 = INVALID_HANDLE_VALUE;
    HANDLE unk08;
    void *unk0C = nullptr;
    void *unk10 = nullptr;
    std::uint32_t unk14 = 0;
    std::uint8_t pad18[4];
    FileHandler::FuncTable *unk1C = nullptr;

public:
    // mc2: 0x005FC660
    Archive();

    // mc2: 0x005FC690
    ~Archive();

    bool sub_5FD3A0(const char *file_name, FileHandler *file) {
        return MC2_PROC_MEMBER<bool>(0x005FD3A0, this, file_name, file);
    }

    bool sub_5FDBF0(const char *file_name, FileHandler::FuncTable *b, bool c);
    bool sub_5FDCE0(const char *file_name) {
        return this->sub_5FDBF0(file_name, nullptr, true);
    }
};

extern Archive *&glo_85D1C4;

void sub_5FDD20();
