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

#include "unk6C3250.hpp"
#include "unk613330.hpp"
#include "unk616420.hpp"
#include "../Game.hpp"

bool unk_6C3250::sub_53B6A0() {
    unk_679810_funcTable *fileFuncs = glo_679810;

    glo_679810 = loc_679884;

    file_handle_struct* file = glo_860220->impl_1C("userdata\\options.cfg", "", 0, 1);
    if (file == nullptr) {
        file = glo_860220->impl_1C("userdata\\default.cfg", "", 0, 1);
    }

    glo_679810 = fileFuncs;
    if (file == nullptr) {
        return false;
    }

    unk_616420 option("options", file);
    char buffer[256];
    if (option.sub_6154D0("AudioDriver:", 1)) {
        if (option.sub_47C920(buffer, 0xFF) >= 0) {
            buffer[255] = '\0';
            sub_53B520(buffer);
        }
    }
    //53b75E
    return MC2_PROC_MEMBER<bool>(0x0053B6A0, this);
}
