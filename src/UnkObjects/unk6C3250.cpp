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

    if (option.sub_6154D0("ScreenWidth:", 1)) {
        set_screen_width(option.read_integer());
    }

    if (option.sub_6154D0("ScreenHeight:", 1)) {
        set_screen_height(option.read_integer());
    }

    if (option.sub_6154D0("ScreenDepth:", 1)) {
        set_screen_depth(option.read_integer());
    }

    if (option.sub_6154D0("DrawDistance:", 1)) {
        set_draw_distance(option.read_integer());
    }

    if (option.sub_6154D0("EnvironmentMapping:", 1)) {
        set_environment_mapping(option.read_integer());
    }

    if (option.sub_6154D0("Reflections:", 1)) {
        set_reflections(option.read_integer());
    }

    if (option.sub_6154D0("Shadows:", 1)) {
        set_shadows(option.read_integer());
    }

    if (option.sub_6154D0("FullScreenEffects:", 1)) {
        set_fullscreen_effects(option.read_integer());
    }

    if (option.sub_6154D0("Language:", 1)) {
        if (option.sub_47C920(buffer, 0xFF) >= 0) {
            buffer[255] = '\0';
            int languageId = sub_5E1B50(buffer);
            if (languageId != -1) {
                set_language_id(languageId);
            }
        }
    }

    if (option.sub_6154D0("InputDevice:", 1)) {
        int32_t device_1 = option.read_integer();
        int32_t device_2 = option.read_integer();
        set_input_device(device_1, device_2);
    }

    sub_49C460(false);

    MC2_PROC_MEMBER<void, file_handle_struct>(0x00617FB0, file);

    return true;
    //53b7CD
    //return MC2_PROC_MEMBER<bool>(0x0053B6A0, this);
}
