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
#include "Config.hpp"
#include "Game.hpp"
#include "Logging.hpp"
#include "Memory.hpp"

#include "UnkObjects/unk612850.hpp"

#include <cassert>
#include <cctype>
#include <algorithm>
#include <array>

constexpr std::array<std::uint8_t, 4> DAVE_Magic{ { 'D', 'A', 'V', 'E' } };
constexpr std::array<std::uint8_t, 4> Dave_Magic{ { 'D', 'a', 'v', 'e' } };

constexpr std::array<std::uint8_t, 4> PK12_Magic{ { 'P', 'K',  1 ,  2  } };
constexpr std::array<std::uint8_t, 4> PK34_Magic{ { 'P', 'K',  3 ,  4  } };
constexpr std::array<std::uint8_t, 4> PK56_Magic{ { 'P', 'K',  5 ,  6  } };

constexpr std::uint32_t Dave_Align = 0x800;
constexpr std::uint16_t ZIP_Uncompressed = 0;
constexpr std::uint16_t ZIP_DEFLATE = 8;

// ZIP File Headers
#pragma pack(push, 1)
struct ZIP_Local {
    std::array<std::uint8_t, 4> magic;
    std::uint16_t versionMin;
    std::uint16_t genFlags;
    std::uint16_t compression;
    std::uint16_t modTime, modDate;
    std::uint32_t crc;
    std::uint32_t compressSize, uncompressSize;
    std::uint16_t nameLen, extraLen;
};

struct ZIP_Central {
    std::array<std::uint8_t, 4> magic;
    std::uint16_t version, versionMin;
    std::uint16_t genFlags;
    std::uint16_t compression;
    std::uint16_t modTime, modDate;
    std::uint32_t crc;
    std::uint32_t compressSize, uncompressSize;
    std::uint16_t nameLen, extraLen, commentLen;
    std::uint16_t disk;
    std::uint16_t intAttr;
    std::uint32_t extAttr;
    std::uint32_t fileOffset;
};

struct ZIP_End {
    std::array<std::uint8_t, 4> magic;
    std::uint16_t fileDisk;
    std::uint16_t cdirDisk;
    std::uint16_t cdirCount;
    std::uint16_t totalCount;
    std::uint32_t cdirSize;
    std::uint32_t cdirOffset;
    std::uint16_t commentLen;
};
#pragma pack(pop)
static_assert(sizeof(ZIP_Local) == 30, "Bad Size: ZIP_Local");
static_assert(sizeof(ZIP_Central) == 46, "Bad Size: ZIP_Central");
static_assert(sizeof(ZIP_End) == 22, "Bad Size: ZIP_End");

// mc2: 0x005FC660
Archive::Archive() {
    prevArchive = glo_85D1C4;
    glo_85D1C4 = this;
}

// mc2: 0x005FC690
Archive::~Archive() {
    mc2_aligned_free(nameBuffer);
    mc2_aligned_free(metaBuffer);

    if (unk04 != INVALID_HANDLE_VALUE && this->fileFuncs != nullptr) {
        this->fileFuncs->close_file(unk04);
        CloseHandle(unk08);
    }

    glo_85D1C4 = prevArchive;
}

// mc2: 0x005FC830 (a = eax, b = edx)
static bool compare_paths(const char *a, const char *b) {
    for (; ; ++a, ++b) {
        char x = *a == '\\' ? '/' : std::tolower(*a);
        char y = *a == '\\' ? '/' : std::tolower(*b);
        if (x < y) return true;
        if (y < x) return false;
        if (x == '\0') return false;
    }
}

bool Archive::sub_5FD3A0(const char *file_name, FileHandler *file) {
    std::array<std::uint8_t, 4> magic;
    file->read(magic);

    if (magic == DAVE_Magic || magic == Dave_Magic) {
        mc2_log_info("'%s' is optimized archive.", file_name);

        bool var364 = magic == Dave_Magic;
        if (var364) {
            glo_85CD28 = true;
            glo_85CD30 = true;
        }

        std::uint32_t metaLen, nameLen;
        file->read(numFiles);
        file->read(metaLen);
        file->read(nameLen);
        metaBuffer = reinterpret_cast<meta_t *>(mc2_aligned_malloc(metaLen, 128));
        nameBuffer = reinterpret_cast<std::uint8_t *>(mc2_aligned_malloc(nameLen, 128));

        file->seek(1 * Dave_Align);
        file->read(metaBuffer, metaLen & ~0x3);
        sub_5FCFD0(metaBuffer, metaLen);
        file->read(nameBuffer, nameLen);
        for (std::uint32_t i = 0; i < numFiles; ++i) {
            metaBuffer[i].nameRaw = nameBuffer + metaBuffer[i].nameOffset;
        }

        mc2_log_info("%s: %d files in central directory (%d bytes + %d string heap = %d total).",
            file_name, numFiles, metaLen, nameLen, metaLen + nameLen);

        if (!var364) {
            nameBuffer = sub_5FCBF0(metaBuffer, numFiles, nameBuffer, 0);
        }
    } else { // Try ZIP file
        ZIP_End eocd;
        file->seek(file->size() - sizeof(ZIP_End));
        file->read(eocd);
        if (eocd.magic != PK56_Magic) {
            mc2_log_warning("%s: Central directory signature not found (zipfile comments not supported).", file_name);
            file->sub_617FB0();
            return false;
        } else if (eocd.fileDisk != eocd.cdirDisk || eocd.cdirCount != eocd.totalCount) {
            mc2_log_warning("%s: Multi-part zipfiles not supported.", file_name);
            file->sub_617FB0();
            return false;
        }

        numFiles = eocd.cdirCount;
        metaBuffer = reinterpret_cast<meta_t *>(mc2_aligned_malloc(numFiles * sizeof(meta_t), 128));
        std::uint32_t nameSize = eocd.cdirSize - (numFiles * (64 - 1));
        nameBuffer = reinterpret_cast<std::uint8_t *>(mc2_aligned_malloc(nameSize, 128));

        file->seek(eocd.cdirOffset);
        std::uint32_t nameBuffLen = 0;
        for (std::uint32_t i = 0; i < numFiles; ++i) {
            ZIP_Central central;
            file->read(central);

            if (central.magic != PK12_Magic) {
                mc2_log_warning("%s: Central Directory Entry has incorrect magic.", file_name);
                file->sub_617FB0();
                return false;
            }
            if (central.compression != ZIP_Uncompressed && central.compression != ZIP_DEFLATE) {
                mc2_log_warning("%s: Compression method besides store or deflate encountered.", file_name);
                file->sub_617FB0();
                return false;
            }

            metaBuffer[i].nameRaw = nameBuffer + nameBuffLen;
            metaBuffer[i].dataOffset = central.fileOffset;
            metaBuffer[i].decompressLen = central.uncompressSize;
            metaBuffer[i].compressLen = central.compressSize;

            file->read_array(nameBuffer + nameBuffLen, central.nameLen);
            nameBuffLen += central.nameLen;
            nameBuffer[nameBuffLen++] = '\0';
            file->skip(central.extraLen + central.commentLen);
        }

        for (std::uint32_t i = 0; i < numFiles; ++i) {
            ZIP_Local local;
            file->seek(metaBuffer[i].dataOffset);
            file->read(local);

            if (local.magic != PK34_Magic) {
                mc2_log_warning("%s: Local File Header has incorrect magic.", file_name);
                file->sub_617FB0();
                return false;
            }

            metaBuffer[i].dataOffset += sizeof(local) + local.nameLen + local.extraLen;
        }

        mc2_log_info("%s: %d files in central directory (%d bytes + %d(%d) string heap).",
            file_name, numFiles, numFiles * sizeof(meta_t), nameBuffLen, nameSize);
        std::sort(metaBuffer, metaBuffer + numFiles, [](const meta_t &a, const meta_t &b) {
            return compare_paths(a.name, b.name);
        });
        nameBuffer = sub_5FCBF0(metaBuffer, numFiles, nameBuffer, 0);
    }

    unk18 = 0;
    return true;
}

bool Archive::sub_5FDBF0(const char *file_name, FileHandler::FuncTable *b, bool c) {
    if (glo_85D1C8 == nullptr && c) {
        glo_85D1C8 = glo_679810;
        glo_679810 = &glo_6781C0;
    }
    this->fileFuncs = (b != nullptr) ? b : glo_85D1C8;

    FileHandler *file = sub_617CD0(file_name, this->fileFuncs, true);
    if (file == nullptr || !this->sub_5FD3A0(file_name, file)) return false;
    file->sub_617FB0();

    unk04 = this->fileFuncs->open_file(file_name, true);
    unk08 = CreateFileA(file_name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
    return true;
}

void sub_5FDD20() {
    if (sub_612E10("logopen")) {
        glo_85D1C0 = true;
    }

    Archive *x = new Archive;
    if (x->sub_5FDCE0(config_assets_name.c_str())) {
        sub_6134D0("");
    } else {
        mc2_log_error("Failed to load archive '%s'", config_assets_name.c_str());
        delete x;
    }
}

MC2_DEF_PROC(sub_5FCBF0, 0x005FCBF0);
MC2_DEF_PROC(sub_5FCFD0, 0x005FCFD0);

MC2_DEF_GLOBAL(glo_85CD28, 0x0085CD28);
MC2_DEF_GLOBAL(glo_85CD30, 0x0085CD30);
MC2_DEF_GLOBAL(glo_85D1C4, 0x0085D1C4);

AUTO_HOOK_MEMBER_X86(0x005FD3A0, &Archive::sub_5FD3A0);
