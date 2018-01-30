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

struct unk_612150 {
    std::uint32_t count = 0;
    char **args = nullptr;
};

class unk_612850 {
public:
    struct hash_map_entry {
        char *name;
        unk_612150 *value;
        hash_map_entry *next;
        
        hash_map_entry() = default;
        inline hash_map_entry(char *name, unk_612150 *value, hash_map_entry *next) :
            name(name), value(value), next(next) { }
    };

    struct indexed_map_entry {
        uint32_t index;
        char *name;
        unk_612150 *value;
    };

private:
    std::uint8_t pad00[0x2];
    std::uint8_t unk02;
    std::uint8_t unk03;
    std::uint8_t pad04[0x4];
    std::int32_t max_entries;  // 0x08
    std::int32_t num_entries;  // 0x0C
    hash_map_entry **entries;  // 0x10
    unk_612850 *unk14;

public:
    unk_612850(std::uint32_t a = 101, std::uint32_t b = 0, std::uint32_t c = 32,
        std::uint32_t d = 1, std::uint32_t e = 0) {
        MC2_PROC_MEMBER<void>(0x00612850, this, a, b, c, d, e);
    }

    // mc2: 0x006126B0
    ~unk_612850() {
        MC2_PROC_MEMBER<void>(0x006126B0, this);
    }

    void loc_611DC0();
    
    inline hash_map_entry *sub_611DF0(const char *a, unk_612150 *b, hash_map_entry *unk_loc) {
        return MC2_PROC_MEMBER<hash_map_entry*>(0x00611DF0, this, a, b, unk_loc);
    }

    bool sub_612150(const char *a, unk_612150 *b);
    // mc2: 0x00611E70
    uint32_t get_entry_index(const char *a);
    unk_612150* sub_6124A0(const char *a);

    inline void sub_6125A0(uint32_t new_max_entries) {
        MC2_PROC_MEMBER<void>(0x006125A0, this, new_max_entries);
    }

    bool sub_611FE0(indexed_map_entry *eax);

    inline void sub_612050() {
        MC2_PROC_MEMBER<void>(0x00612050, this);
    }

    bool sub_612020(indexed_map_entry *eax);

    hash_map_entry *unk_612850::sub_611F60(int32_t unk);
};

bool sub_612E10(const char *key);
bool sub_612E30(const char *key, std::uint32_t index, int32_t * decimal_value);

extern unk_612850 &glo_69685C;
extern unk_612850 &glo_697E24;
extern unk_612850 &glo_6C50F0;
extern unk_612850 &glo_6C5224;
extern unk_612850 &glo_6CE228;
extern unk_612850 &glo_857850;
extern unk_612850 &glo_857868;
extern unk_612850 &glo_858288;
extern unk_612850 &glo_8582AC;
extern unk_612850 &glo_8586B8;
extern unk_612850 &glo_85ADDC;
extern unk_612850 &glo_85AE60;
extern unk_612850 &glo_8600F8;

extern unk_612850 *&glo_8600E8;
