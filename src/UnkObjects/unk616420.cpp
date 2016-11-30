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

unk_616420::unk_616420(char *unk1, file_handle_struct *unk2) {
    this->unk9C = 0;
    vtable = MC2_POINTER<void *>(0x0062FF40);
    sub_615130(unk1, unk2);
}
    
void unk_616420::sub_615130(char *unk1, file_handle_struct *unk2) {
    this->unk04 = unk1;
    this->unk08 = 1;
    this->unk0C = unk2;
    this->unk10 = 32;
    this->unk14 = 0;
    this->unk18 = 0;
    this->unk98 = 0;
}