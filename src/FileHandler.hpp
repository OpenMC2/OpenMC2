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
#include <Windows.h>

struct unk_679810_funcTable{
    HANDLE (*sub_00)(char *path, bool unk2);
    void (*sub_04)();
    void (*sub_08)();
    void (*sub_0C)();
    void (*sub_10)();
    void (*close_file)(HANDLE file); // 0x14
    void (*sub_18)();
    void (*sub_1C)();
    void (*sub_20)();
    bool (*sub_24)();
    void (*sub_28)();
};

// size: 0x1C
class FileHandler {
public:  
    unk_679810_funcTable *file_funcs; // 0x00
    HANDLE handle; // 0x04
    char *text_buffer; //0x08
    uint32_t unk_0C;
    uint32_t unk_10;
    uint32_t unk_14;
    uint32_t buffer_size; // 0x18

    void sub_617FB0();

    inline void sub_617AF0() {
        MC2_PROC_MEMBER<void>(0x00617AF0, this);
    }

    inline void sub_617E40(char *a, size_t b) {
        MC2_PROC_MEMBER<void>(0x00617E40, this, a, b);
    }
};

void sub_618050(FileHandler *a, const char *format, ...);
FileHandler *register_file_handle(char * path, HANDLE file, unk_679810_funcTable * fileFuncs);

#define glo_FileHandles (MC2_POINTER<FileHandler>(0x00860AE0))
//Array end
#define glo_FileHandles_end (MC2_POINTER<FileHandler>(0x00860C30))
#define glo_FileHandle_TextBuffer (MC2_POINTER<char [0x1000]>(0x00860C30))
#define glo_86D28C (MC2_GLOBAL<FileHandler *>(0x0086D28C))
#define glo_679818 (MC2_GLOBAL<int32_t>(0x00679818))
