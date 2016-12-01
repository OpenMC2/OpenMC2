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

#include "../Addresses.hpp"
#include "../Game.hpp"

class unk_6C3250 {
private:
    std::uint8_t pad00[0x44];
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
    bool unk70;

public:
    void sub_49C460(bool unk1) {
        this->unk70 = unk1;
    }

    bool sub_53B6A0();
    void sub_53B520(char *unk1) {
        MC2_PROC_MEMBER<void, unk_6C3250, char *>(0x0053B520, this, unk1);
    }

    // mc2: 0x0053B550
    void set_screen_width(uint32_t new_width) {
        if (this->screen_width == new_width)
            return;

        this->screen_width = new_width;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B570
    void set_screen_height(uint32_t new_height) {
        if (this->screen_height == new_height)
            return;

        this->screen_height = new_height;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B590
    void set_screen_depth(uint32_t new_depth) {
        if (this->screen_depth == new_depth)
            return;

        this->screen_depth = new_depth;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B5B0
    void set_draw_distance(uint32_t new_distance) {
        if (this->draw_distance == new_distance)
            return;

        this->draw_distance = new_distance;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B600
    void set_environment_mapping(uint32_t new_mapping) {
        if (this->environment_mapping == new_mapping)
            return;

        this->environment_mapping = new_mapping;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B620
    void set_reflections(uint32_t new_reflections) {
        if (this->reflections == new_reflections)
            return;

        this->reflections = new_reflections;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B640
    void set_shadows(uint32_t new_shadows) {
        if (this->shadows == new_shadows)
            return;

        this->shadows = new_shadows;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B660
    void set_fullscreen_effects(uint32_t new_effects) {
        if (this->fullscreen_effects == new_effects)
            return;

        this->fullscreen_effects = new_effects;
        sub_49C460(true);
    }

    // mc2: 0x0053B680
    void set_language_id(int32_t id) {
        this->language_id = id;
        global_LanguageID = id;
        sub_49C460(true);
    }
    
    // mc2: 0x0053B5D0
    void set_input_device(int32_t device_1, int32_t device_2) {
        if (this->input_device_1 == device_1 && this->input_device_2 == device_2)
            return;

        this->input_device_1 = device_1;
        this->input_device_2 = device_2;
        sub_49C460(true);
    }

    inline std::uint32_t unk_6C3250::get_screen_width() const { return this->screen_width; } // mc2: 0x004DBA90
    inline std::uint32_t unk_6C3250::get_screen_height() const { return this->screen_height; } // mc2: 0x0055E930
    inline std::uint32_t unk_6C3250::get_screen_depth() const { return this->screen_depth; } // mc2: 0x0053B320
};

#define glo_6C3250 (MC2_GLOBAL<unk_6C3250>(0x006C3250))
