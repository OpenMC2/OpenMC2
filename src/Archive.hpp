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
public:
    struct meta_t {
        union {
            std::uintptr_t nameOffset;
            const char *name;
            const std::uint8_t *nameRaw; // will help with decoding base64 names
        };
            
        std::uint32_t dataOffset, decompressLen, compressLen;
    };

private:
    Archive *prevArchive;
    HANDLE unk04 = INVALID_HANDLE_VALUE;
    HANDLE unk08;
    std::uint8_t *nameBuffer = nullptr; // 0x0C
    meta_t *metaBuffer = nullptr; // 0x10
    std::uint32_t numFiles = 0; // 0x14
    std::uint32_t unk18;
    FileHandler::FuncTable *fileFuncs = nullptr;

public:
    // mc2: 0x005FC660
    Archive();

    // mc2: 0x005FC690
    ~Archive();

    bool sub_5FD3A0(const char *file_name, FileHandler *file);

    bool sub_5FDBF0(const char *file_name, FileHandler::FuncTable *b, bool c);
    bool sub_5FDCE0(const char *file_name) {
        return this->sub_5FDBF0(file_name, nullptr, true);
    }
};

void sub_5FDD20();

extern MC2_PROC_PTR<std::uint8_t *, Archive::meta_t *, std::uint32_t, std::uint8_t *, std::uint32_t> sub_5FCBF0;

extern std::uint32_t (&glo_85CD10)[4];
extern bool &glo_85CD28;
extern bool &glo_85CD30;
extern Archive *&glo_85D1C4;
