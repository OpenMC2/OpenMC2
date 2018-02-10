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

// size: 0x1C
class FileHandler {
public:
    struct FuncTable {
        HANDLE(*open_file)(const char *path, bool unk2);
        HANDLE(*sub_04)(const char *path);
        void(*sub_08)();
        void(*sub_0C)();
        void(*sub_10)();
        void(*close_file)(HANDLE file); // 0x14
        void(*sub_18)();
        void(*sub_1C)();
        void(*sub_20)();
        bool(*sub_24)();
        void(*sub_28)();
    };

    FuncTable *file_funcs; // 0x00
    HANDLE handle; // 0x04
    char *text_buffer; //0x08
    std::uint32_t unk_0C;
    std::int32_t unk_10;
    std::uint32_t unk_14;
    std::int32_t buffer_size; // 0x18

    void sub_617FB0();

    void sub_617AF0() {
        MC2_PROC_MEMBER<void>(0x00617AF0, this);
    }

    std::int32_t sub_617E40(const char *a, size_t b) {
        return MC2_PROC_MEMBER<std::int32_t>(0x00617E40, this, a, b);
    }

    void sub_617F40(char a) {
        MC2_PROC_MEMBER<void>(0x00617F40, this, a);
    }

    // mc2: 0x00617D20
    std::uint32_t read(void *data, std::uint32_t size) {
        return MC2_PROC_MEMBER<std::uint32_t>(0x00617D20, this, data, size);
    }
    template<class T>
    std::uint32_t read(T &value) {
        return read(&value, static_cast<std::uint32_t>(sizeof(T)));
    }
    template<class T>
    std::uint32_t read_array(T *array, size_t count) {
        return read(array, static_cast<std::uint32_t>(count * sizeof(T)));
    }

    // mc2: 0x00617F60
    void seek(std::uint32_t offset) {
        return MC2_PROC_MEMBER<void>(0x00617F60, this, offset);
    }

    // mc2: 0x00617FF0
    std::uint32_t size() {
        return MC2_PROC_MEMBER<std::uint32_t>(0x00617FF0, this);
    }
};

FileHandler *sub_617CD0(const char *, FileHandler::FuncTable *, bool);
void sub_618050(FileHandler *a, const char *format, ...);

// mc2: 0x00617BB0
FileHandler *register_file_handle(const char * path, HANDLE file, FileHandler::FuncTable * fileFuncs);

extern void(__cdecl &sub_617AA0)();

extern std::array<FileHandler, 12> &glo_FileHandles;
extern std::array<char[0x1000], 12> &glo_FileHandle_TextBuffer;
extern FileHandler *&glo_86D28C;
extern std::int32_t &glo_679818;

extern FileHandler::FuncTable *&glo_679810;
extern FileHandler::FuncTable *&glo_679814;
extern FileHandler::FuncTable *&glo_692E1C;
extern FileHandler::FuncTable *&glo_85D1C8;

extern FileHandler::FuncTable &glo_6781C0;
extern FileHandler::FuncTable &glo_679884;
extern FileHandler::FuncTable &glo_692E20;
