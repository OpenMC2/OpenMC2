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

void FileHandler::sub_617FB0() {
    if (this->buffer_read == 0 &&
        this->buffer_offset != 0) {
        flush();
    }

    this->file_funcs->close_file(this->handle);
    this->handle = INVALID_HANDLE_VALUE;
    this->file_funcs = nullptr;
}

// mc2: 0x00617AF0
std::int32_t FileHandler::flush() {
    std::int32_t result = 0;
    if (buffer_read == 0) {
        if (buffer_offset != 0 && file_funcs->write != nullptr)
            result = file_funcs->write(handle, buffer, buffer_offset);
    } else if (buffer_read == buffer_offset && file_funcs->seek != nullptr) {
        result = file_funcs->seek(handle, seek_pos + buffer_offset, SeekStart);
    }

    seek_pos += buffer_offset;
    buffer_read = 0;
    buffer_offset = 0;
    if (file_funcs->sub_20 != nullptr) result = file_funcs->sub_20(handle);

    return result;
}

// mc2: 0x00617E40
std::int32_t FileHandler::write(const void *data, std::int32_t size) {
    if (buffer_read > 0 && this->flush() < 0) return -1;
    if (size < buffer_size) {
        const std::int32_t buffer_available = buffer_size - buffer_offset;
        if (size >= buffer_available) {
            std::memcpy(buffer + buffer_offset, data, buffer_available);
            data = reinterpret_cast<const std::uint8_t *>(data) + buffer_available;
            size -= buffer_available;
            buffer_offset = buffer_size;
            if (this->flush() < 0) return -1;
        }

        std::memcpy(buffer + buffer_offset, data, size);
        buffer_offset += size;
        return size;
    } else {
        if (this->flush() < 0) return -1;
        std::int32_t written = file_funcs->write(handle, data, size);
        if (written < 0) return -1;
        buffer_offset += written;
        return written;
    }
}

// mc2: 0x00617D20
std::int32_t FileHandler::read(void *data, std::int32_t size) {
    if (buffer_read == 0 && buffer_offset != 0 && this->flush() < 0) return -1;
    
    std::int32_t buffer_used = 0;
    const std::int32_t buffer_available = buffer_read - buffer_offset;
    if (size > buffer_available) {
        if (buffer_available > 0) {
            std::memcpy(data, buffer + buffer_offset, buffer_available);
            data = reinterpret_cast<std::uint8_t *>(data) + buffer_available;
            size -= buffer_available;
            buffer_used = buffer_available;
        }

        seek_pos += buffer_read;
        buffer_read = 0;
        buffer_offset = 0;

        if (size >= buffer_size) {
            // skip buffering if read would consume an entire buffer
            std::int32_t read = this->file_funcs->read(handle, data, size);
            if (read < 0) return -1;
            seek_pos += read;
            return read + buffer_used;
        }

        std::int32_t read = this->file_funcs->read(handle, buffer, buffer_size);
        if (read < 0) return -1;
        buffer_read = read;
        size = std::min(size, read);
    }

    std::memcpy(data, buffer + buffer_offset, size);
    buffer_offset += size;
    return buffer_used + size;
}

// mc2: 0x00617F60
std::int32_t FileHandler::seek(std::int32_t offset) {
    if (offset >= seek_pos && offset < seek_pos + buffer_read) {
        buffer_offset = offset - seek_pos;
        return offset;
    } else if (file_funcs->seek != nullptr) {
        if (this->flush() < 0) return -1;
        seek_pos = offset;
        return file_funcs->seek(handle, offset, SeekStart);
    } else {
        seek_pos = offset;
        return offset;
    }
}

std::int32_t FileHandler::skip(std::int32_t count) {
    if (count < buffer_read - buffer_offset) {
        buffer_offset += count;
        return seek_pos + buffer_offset;
    } else if (file_funcs->seek != nullptr) {
        if (this->flush() < 0) return -1;
        seek_pos += count;
        return file_funcs->seek(handle, seek_pos, SeekStart);
    } else {
        seek_pos += count;
        return seek_pos;
    }
}

// mc2: 0x00617FF0
std::int32_t FileHandler::size() {
    if (file_funcs->get_size != nullptr) {
        return file_funcs->get_size(handle);
    } else {
        if (this->flush() < 0) return -1;
        std::int32_t curpos = file_funcs->seek(handle, 0, SeekCurrent);
        std::int32_t size = file_funcs->seek(handle, 0, SeekEnd);
        file_funcs->seek(handle, curpos, SeekStart);
        return size;
    }
}

FileHandler *sub_617CA0(char *path) {
    HANDLE file = glo_679814->sub_04(path);

    if (file == INVALID_HANDLE_VALUE)
        return nullptr;

    return register_file_handle(path, file, glo_679814);
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

void sub_618050(FileHandler *a, const char *format, ...) {
    char buffer[0x400];
    va_list ap;
    va_start(ap, format);
    int len = std::vsnprintf(buffer, 0x400, format, ap);
    a->write(buffer, std::min(std::max(len, 0), 0x3FF));
    va_end(ap);
}

// mc2: 0x00617BB0
FileHandler *register_file_handle(const char * path, HANDLE file, FileHandler::FuncTable * fileFuncs) {
    for (std::int32_t i = 0; i < static_cast<std::int32_t>(glo_FileHandles.size()); ++i){
        FileHandler &freeHandle = glo_FileHandles[i];
        if (freeHandle.file_funcs == nullptr) {
            freeHandle.seek_pos = 0;
            freeHandle.buffer_offset = 0;
            freeHandle.buffer_read = 0;
            freeHandle.handle = file;
            freeHandle.buffer_size = 0x1000;
            freeHandle.buffer = glo_FileHandle_TextBuffer[i];
            freeHandle.file_funcs = fileFuncs;
            glo_679818 = std::max(glo_679818, i);
            return &freeHandle;
        }
    }

    sub_617AA0();
    mc2_log_error("Out of file handles.");
    return nullptr;
}

MC2_DEF_PROC(sub_617AA0, 0x00617AA0);

MC2_DEF_GLOBAL(glo_FileHandles, 0x00860AE0);
MC2_DEF_GLOBAL(glo_FileHandle_TextBuffer, 0x00860C30);
MC2_DEF_GLOBAL(glo_86D28C, 0x0086D28C);
MC2_DEF_GLOBAL(glo_679818, 0x00679818);

MC2_DEF_GLOBAL(glo_679810, 0x00679810);
MC2_DEF_GLOBAL(glo_679814, 0x00679814);
MC2_DEF_GLOBAL(glo_692E1C, 0x00692E1C);
MC2_DEF_GLOBAL(glo_85D1C8, 0x0085D1C8);

MC2_DEF_GLOBAL(glo_6781C0, 0x006781C0);
MC2_DEF_GLOBAL(glo_679884, 0x00679884);
MC2_DEF_GLOBAL(glo_692E20, 0x00692E20);

