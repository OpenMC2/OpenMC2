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

#include <array>

struct unk_679810_funcTable{
    HANDLE (*sub_00)(char *path, bool unk2);
    HANDLE (*sub_04)(char *path);
    mc2_proc_ptr<void> sub_08;
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
    std::uint32_t unk_0C;
    std::int32_t unk_10;
    std::uint32_t unk_14;
    std::int32_t buffer_size; // 0x18

    void sub_617FB0();

    inline void sub_617AF0() {
        return mc2_call_proc_thiscall<0x00617AF0, void>(this);
    }

    inline std::int32_t sub_617E40(const char *a, size_t b) {
        return mc2_call_proc_thiscall<0x00617E40, std::int32_t>(this, a, b);
    }

    inline void sub_617F40(char a) {
        return mc2_call_proc_thiscall<0x00617F40, void>(this, a);
    }
};

static_assert(sizeof(FileHandler) == 0x1C, "BAD SIZE");

void sub_618050(FileHandler *a, const char *format, ...);
FileHandler *register_file_handle(char * path, HANDLE file, unk_679810_funcTable * fileFuncs);

constexpr mc2_pointer<0x00860AE0, std::array<FileHandler, 12>> loc_FileHandles;
constexpr mc2_pointer<0x00860C30, std::array<char[0x1000], 12>> loc_FileHandle_TextBuffer;
constexpr mc2_pointer<0x0086D28C, FileHandler *> loc_86D28C;
constexpr mc2_pointer<0x00679818, std::int32_t> loc_679818;
