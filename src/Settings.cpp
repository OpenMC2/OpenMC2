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

#include "Settings.hpp"
#include "UnkObjects/unk613330.hpp"
#include "UnkObjects/unk616420.hpp"
#include "Game.hpp"

Settings::Settings() {
    this->requires_saving = false;
    this->unk71 = false;
    set_defualts();
}

void Settings::set_defualts() {
    this->unk00 = 0;
    set_audio_driver("Miles Fast 2D Positional Audio");
    set_screen_width(640);
    set_screen_height(480);
    set_screen_depth(32);
    set_draw_distance(1);
    set_environment_mapping(1);
    set_reflections(1);
    set_shadows(1);
    set_fullscreen_effects(1);
    this->language_id = 0;
}

bool Settings::load_settings_file() {
    unk_679810_funcTable *fileFuncs = glo_679810;

    glo_679810 = loc_679884;

    file_handle_struct* file = glo_860220->vir_1C("userdata\\options.cfg", "", 0, 1);
    if (file == nullptr) {
        file = glo_860220->vir_1C("userdata\\default.cfg", "", 0, 1);
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
            set_audio_driver(buffer);
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

    set_require_saving(false);

    MC2_PROC_MEMBER<void, file_handle_struct>(0x00617FB0, file);

    return true;
}

bool Settings::save_to_settings_file() {
    unk_679810_funcTable *fileFuncs = glo_679810;

    glo_679810 = loc_679884;

    file_handle_struct* file = glo_860220->vir_20("userdata\\options.cfg", "", 0, 1);
    if (file == nullptr) {
        return false;
    }

    unk_616420 option("options", file);

    option.sub_615740("Audio Driver: %s\n", this->get_audio_driver());
    option.sub_615740("ScreenWidth: %d\n", reinterpret_cast<const void *>(this->get_screen_width()));
    option.sub_615740("ScreenHeight: %d\n", reinterpret_cast<const void *>(this->get_screen_height()));
    option.sub_615740("ScreenDepth: %d\n", reinterpret_cast<const void *>(this->get_screen_depth()));
    option.sub_615740("DrawDistance: %d\n", reinterpret_cast<const void *>(this->get_draw_distance()));
    option.sub_615740("EnvironmentMapping: %d\n", reinterpret_cast<const void *>(this->get_environment_mapping()));
    option.sub_615740("Reflections: %d\n", reinterpret_cast<const void *>(this->get_reflections()));
    option.sub_615740("Shadows: %d\n", reinterpret_cast<const void *>(this->get_shadows()));
    option.sub_615740("FullscreenEffects: %d\n", reinterpret_cast<const void *>(this->get_fullscreen_effects()));
    const char *language = sub_5E1B40(this->language_id);
    if (language != nullptr) {
        option.sub_615740("Language: %s\n", reinterpret_cast<const void *>(language));
    }
    // In the original this was a var arg input but it is simpler to split it up
    option.sub_615740("InputDevice: %d ", reinterpret_cast<const void *>(this->get_input_device_1()));
    option.sub_615740("%d\n", reinterpret_cast<const void *>(this->get_input_device_2()));

    set_require_saving(false);
    
    MC2_PROC_MEMBER<void, file_handle_struct>(0x00617FB0, file);

    return true;
}
