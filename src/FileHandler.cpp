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
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include "Game.hpp"
#include "FileHandler.hpp"
#include "Logging.hpp"

void FileHandler::sub_617FB0(){
    if (this->unk_14 == 0 &&
        this->unk_10 != 0) {
        sub_617AF0();
    }

    this->file_funcs->close_file(this->handle);
    this->handle = INVALID_HANDLE_VALUE;
    this->file_funcs = nullptr;
}

FileHandler *sub_617CD0(const char *file_name, FileHandler::FuncTable *funcs, bool c) {
    HANDLE x = funcs->open_file(file_name, c);

    if (x != INVALID_HANDLE_VALUE) {
        if (glo_860AD8 == nullptr || !glo_860AD8(file_name, c)) {
            return register_file_handle(file_name, x, funcs);
        }
        funcs->close_file(x);
    }

    return nullptr;
}

// mc2: 0x00618050
void sub_618050(FileHandler *a, const char *format, ...) {
    char buffer[0x400];
    va_list ap;
    va_start(ap, format);
    int len = std::vsnprintf(buffer, 0x400, format, ap);
    a->sub_617E40(buffer, std::min(std::max(len, 0), 0x3FF));
    va_end(ap);
}

// mc2: 0x00617BB0
FileHandler *register_file_handle(const char * path, HANDLE file, FileHandler::FuncTable * fileFuncs) {
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(glo_FileHandles.size()); ++i){
        FileHandler &freeHandle = glo_FileHandles[i];
        if (freeHandle.file_funcs == nullptr) {
            freeHandle.unk_0C = 0;
            freeHandle.unk_10 = 0;
            freeHandle.unk_14 = 0;
            freeHandle.handle = file;
            freeHandle.buffer_size = 0x1000;
            freeHandle.text_buffer = glo_FileHandle_TextBuffer[i];
            freeHandle.file_funcs = fileFuncs;
            glo_679818 = std::max(glo_679818, i);
            return &freeHandle;
        }
    }

    sub_617AA0();
    mc2_log_error("Out of file handles.");
    return nullptr;
}

void(__cdecl &sub_617AA0)() = MC2_PROC_PTR<void>(0x00617AA0);

std::array<FileHandler, 12> &glo_FileHandles = MC2_GLOBAL<std::array<FileHandler, 12>>(0x00860AE0);
std::array<char[0x1000], 12> &glo_FileHandle_TextBuffer = MC2_GLOBAL<std::array<char[0x1000], 12>>(0x00860C30);
FileHandler *&glo_86D28C = MC2_GLOBAL<FileHandler *>(0x0086D28C);
std::int32_t &glo_679818 = MC2_GLOBAL<std::int32_t>(0x00679818);

FileHandler::FuncTable *&glo_679810 = MC2_GLOBAL<FileHandler::FuncTable *>(0x00679810);
FileHandler::FuncTable *&glo_679814 = MC2_GLOBAL<FileHandler::FuncTable *>(0x00679814);
FileHandler::FuncTable *&glo_692E1C = MC2_GLOBAL<FileHandler::FuncTable *>(0x00692E1C);
FileHandler::FuncTable *&glo_85D1C8 = MC2_GLOBAL<FileHandler::FuncTable *>(0x0085D1C8);

FileHandler::FuncTable &glo_6781C0 = MC2_GLOBAL<FileHandler::FuncTable>(0x006781C0);
FileHandler::FuncTable &glo_679884 = MC2_GLOBAL<FileHandler::FuncTable>(0x00679884);
FileHandler::FuncTable &glo_692E20 = MC2_GLOBAL<FileHandler::FuncTable>(0x00692E20);

