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

#include "unk616420.hpp"
#include <cstdarg>
#include <cstdio>

// mc2:0x0062FF40
 unk_616420::vtable_t unk_616420::vtable_values = {
     &mc2_proc_thiscall<0x004BCFD0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615220, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615780, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615780, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615790, void, unk_616420>{},
     &mc2_proc_thiscall<0x006157F0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006158D0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006158A0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006158D0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615870, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615850, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615910, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615920, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615940, void, unk_616420>{},
     &mc2_proc_thiscall<0x006159E0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006159C0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006159A0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615980, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615960, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615A00, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615A20, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615AC0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615AA0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615A80, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615A60, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615A40, void, unk_616420>{},
     &mc2_proc_thiscall<0x006162F0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00616360, void, unk_616420>{},
     &mc2_proc_thiscall<0x006163D0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615AE0, void, unk_616420>{},
     &mc2_proc_thiscall<0x0040E770, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615D40, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615CE0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615C80, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615C30, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615BF0, void, unk_616420>{},
     &mc2_proc_thiscall<0x006156F0, void, unk_616420>{},
     &unk_616420::impl_94,
     &mc2_proc_thiscall<0x00615DA0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615BF0, void, unk_616420>{},
     &mc2_proc_thiscall<0x00615BF0, void, unk_616420>{},
};

unk_616420::unk_616420(char *unk1, FileHandler *unk2) {
    this->unk9C = 0;
    vtable = &vtable_values;
    sub_615130(unk1, unk2);
}
    
void unk_616420::sub_615130(char *unk1, FileHandler *unk2) {
    this->unk04 = unk1;
    this->unk08 = 1;
    this->unk0C = unk2;
    this->unk10 = 32;
    this->unk14 = 0;
    this->unk18 = 0;
    this->unk98 = 0;
}

void sub_615740(unk_616420 *unk1, char *format, ...) {
    char buffer[512];
    va_list args;
    va_start(args, format);
    std::vsnprintf(buffer, 512, format, args);
    unk1->vir_94(buffer, 0);
    va_end(args);
}

//mc2: 0x00615B70
bool unk_616420::impl_94(const char *unk1, std::uint32_t unk2) {
    const char *message = unk1[0] == '\0' ? R"("")" : unk1;

    int len = strlen(message);
    std::int32_t bytes_written = this->unk0C->sub_617E40(message, len) + unk2;
    int total_length = len + unk2;

    for (; unk2 != 0; --unk2) {
        if (this->unk0C->unk_14 == 0 &&
            this->unk0C->unk_10 < this->unk0C->buffer_size) {
            this->unk0C->text_buffer[this->unk0C->unk_10++] = '\t';
        } else {
            this->unk0C->sub_617F40('\t');
        }
    }
    return bytes_written == total_length;
}
