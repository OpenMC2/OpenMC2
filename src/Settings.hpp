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

#include <cstdint>

#include "Addresses.hpp"
#include "Game.hpp"

class Settings {
private:
    std::uint32_t unk00;
    char audio_driver[0x40];
    std::uint32_t screen_width; //0x44
    std::uint32_t screen_height; //0x48
    std::uint32_t screen_depth; //0x4C
    std::uint32_t draw_distance; //0x50
    std::uint32_t environment_mapping; //0x54
    std::uint32_t reflections; //0x58
    std::uint32_t shadows; //0x5C
    std::uint32_t fullscreen_effects; //0x60
    std::int32_t input_device_1; //0x64
    std::int32_t input_device_2; //0x68
    std::int32_t language_id; // 0x6C
    bool requires_saving; // 0x70
    bool unk71;

public:
    // mc2: 0x0053B990
    Settings();

    // mc2: 0x0053B930
    void set_defualts();

    void set_require_saving(bool unk1) {
        this->requires_saving = unk1;
    }

    // mc2: 0x0053B6A0
    bool load_settings_file();

    // mc2: 0x0053B510
    bool save_settings_file() {
        if (this->requires_saving == false)
            return false;
        return save_to_settings_file();
    }

    // mc2: 0x0053B370
    bool save_to_settings_file() {
        return MC2_PROC_MEMBER<bool, Settings>(0x0053B370, this);
    }

    // mc2: 0x0053B520
    void set_audio_driver(char *driver) {
        safe_strncpy(this->audio_driver, driver, sizeof(this->audio_driver));
        this->audio_driver[sizeof(this->audio_driver) - 1] = '\0';
        unk71 = true;
        set_require_saving(true);
    }

    // mc2: 0x0053B550
    void set_screen_width(uint32_t new_width) {
        if (this->screen_width == new_width)
            return;

        this->screen_width = new_width;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B570
    void set_screen_height(uint32_t new_height) {
        if (this->screen_height == new_height)
            return;

        this->screen_height = new_height;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B590
    void set_screen_depth(uint32_t new_depth) {
        if (this->screen_depth == new_depth)
            return;

        this->screen_depth = new_depth;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B5B0
    void set_draw_distance(uint32_t new_distance) {
        if (this->draw_distance == new_distance)
            return;

        this->draw_distance = new_distance;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B600
    void set_environment_mapping(uint32_t new_mapping) {
        if (this->environment_mapping == new_mapping)
            return;

        this->environment_mapping = new_mapping;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B620
    void set_reflections(uint32_t new_reflections) {
        if (this->reflections == new_reflections)
            return;

        this->reflections = new_reflections;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B640
    void set_shadows(uint32_t new_shadows) {
        if (this->shadows == new_shadows)
            return;

        this->shadows = new_shadows;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B660
    void set_fullscreen_effects(uint32_t new_effects) {
        if (this->fullscreen_effects == new_effects)
            return;

        this->fullscreen_effects = new_effects;
        set_require_saving(true);
    }

    // mc2: 0x0053B680
    void set_language_id(int32_t id) {
        this->language_id = id;
        global_LanguageID = id;
        set_require_saving(true);
    }
    
    // mc2: 0x0053B5D0
    void set_input_device(int32_t device_1, int32_t device_2) {
        if (this->input_device_1 == device_1 && this->input_device_2 == device_2)
            return;

        this->input_device_1 = device_1;
        this->input_device_2 = device_2;
        set_require_saving(true);
    }

    std::uint32_t get_screen_width() const { return this->screen_width; } // mc2: 0x004DBA90
    std::uint32_t get_screen_height() const { return this->screen_height; } // mc2: 0x0055E930
    std::uint32_t get_screen_depth() const { return this->screen_depth; } // mc2: 0x0053B320
    const char *get_audio_driver() const { return this->audio_driver; } // mc2:0x0053B310
    std::uint32_t get_input_device_1() const { return this->input_device_1; } // mc2:0x0053B330
    std::uint32_t get_input_device_2() const { return this->input_device_2; } // mc2:0x0053B340
    std::uint32_t get_reflections() const { return this->reflections; } // mc2:0x0053B350
    std::uint32_t get_fullscreen_effects() const { return this->fullscreen_effects; } // mc2:0x0053B360
    std::uint32_t get_environment_mapping() const { return this->environment_mapping; } // mc2:0x005AEBA0
    std::uint32_t get_shadows() const { return this->shadows; } // mc2:0x0055E920
};

#define glo_Settings (MC2_GLOBAL<Settings>(0x006C3250))
