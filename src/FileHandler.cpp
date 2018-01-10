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
FileHandler *register_file_handle(char * path, HANDLE file, unk_679810_funcTable * fileFuncs) {
    for (size_t i = 0; i < (*loc_FileHandles).size(); ++i){
        FileHandler &freeHandle = (*loc_FileHandles)[i];
        if (freeHandle.file_funcs == nullptr) {
            freeHandle.unk_0C = 0;
            freeHandle.unk_10 = 0;
            freeHandle.unk_14 = 0;
            freeHandle.handle = file;
            freeHandle.buffer_size = 0x1000;
            freeHandle.text_buffer = (*loc_FileHandle_TextBuffer)[i];
            freeHandle.file_funcs = fileFuncs;
            *loc_679818 = std::max(*loc_679818, (std::int32_t) i);
            return &freeHandle;
        }
    }

    sub_617AA0();
    mc2_log_error("Out of file handles.");
    return nullptr;
}
