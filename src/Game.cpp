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

#include "Game.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstring>
#include <new>

#include "CommandLine.hpp"
#include "Logging.hpp"
#include "UnkObjects/unk402560.hpp"
#include "UnkObjects/unk600960.hpp"
#include "UnkObjects/unk613360.hpp"
#include "UnkObjects/unk6C2E88.hpp"
#include "UnkObjects/unk6C3250.hpp"
#include "UnkObjects/unk6C3890.hpp"
#include "UnkObjects/unk8600F8.hpp"
#include "config.hpp"

static void sub_612A80(char *args) {
    glo_8600F0 = 0;
    glo_8600EC = nullptr;
    char *esi = args;
    if (*esi != '\0') {
        esi = std::strchr(args, ' ');
        if (esi == nullptr) {
            glo_8600F8.loc_611DC0();
            return;
        }
    }

    if (*esi == '\0') {
        glo_8600F8.loc_611DC0();
        return;
    }

    *esi = '\0';
    glo_8600EC = (char**)MC2_MALLOC(4);

    uint32_t length = strlen(args);
    *glo_8600EC = MC2_STRDUP(args);

    *esi = ' ';
    esi++;

    if (*esi == '\0') {
        glo_8600F8.loc_611DC0();
        return;
    }

    for (char *cur = esi; *cur != '\0'; ++cur) {
        if (*cur != '-')
            continue;

        glo_8600F0++;

        char *nextSeperator = cur;
        while (*nextSeperator != '\0') {
            if (*nextSeperator == ' ')
                break;
            if (*nextSeperator == '=')
                break;
            nextSeperator++;
        }
        char *key = cur + 1;
        char *value_str = cur;
        if (*nextSeperator != '\0') {
            *nextSeperator = '\0';
            value_str = nextSeperator + 1;
        }
        unk_612150 *value = glo_8600F8.sub_6124A0(key);

        if (value != nullptr) {
            cur = value_str;
            continue;
        }

        value = new(MC2_MALLOC(sizeof(unk_612150))) unk_612150;

        if (value != nullptr) {
            value->count = 0;
            value->args = nullptr;
        }
        if (value == nullptr) {
            // The original code forces an access violation instead
            mc2_log_fatal("MC2 MALLOC Failed");
        }

        nextSeperator = value_str;
        if (*nextSeperator != '\0') {
            while (*nextSeperator != '-') {
                value->count++;
                if (*nextSeperator == 0)
                    break;

                do {
                    if (*nextSeperator == '=')
                        break;

                    if (*nextSeperator == ' ')
                        break;

                } while (*++nextSeperator != '\0');

                if (*nextSeperator == '\0')
                    break;

                do {
                    if (*nextSeperator == '=')
                        continue;

                    if (*nextSeperator != ' ')
                        break;

                } while (*++nextSeperator != '\0');

                if (*nextSeperator == '\0')
                    break;
            }
        }
        
        cur = nextSeperator - 1;

        glo_8600F8.sub_612150(key, value);

        value->args = (char**)MC2_MALLOC(value->count * 4);

        if (value->count == 0)
            continue;

        uint32_t values_index = 0;
        do {
            char *cur_value_str = value_str;
            if (*value_str != '\0') {

                do {
                    if (*value_str == ' ')
                        break;
                } while (*value_str++ != '\0');

                if (*value_str != '\0') {
                    *value_str++ = '\0';
                }
            }
            
            value->args[values_index++] = MC2_STRDUP(cur_value_str);

        } while (values_index < value->count);
    }
    
    glo_8600F8.loc_611DC0();
    return;
}

void sub_612F00() {
    index_hash_map_entry index_entry;
    if (glo_8600F8.sub_611FE0(&index_entry) == false) {
        glo_8600F8.sub_612050();
        return;
    }

    do {
        unk_612150 *value = index_entry.value;
        if (value != nullptr) {
            if (value->count != 0) {
                for (uint32_t i = 0; i < value->count; ++i) {
                    MC2_FREE(value->args[i]);
                }
                value->count = 0;
            }

            MC2_FREE(value->args);
            MC2_FREE(value);
        }
    } while (glo_8600F8.sub_612020(&index_entry));
    glo_8600F8.sub_612050();
}

static void sub_53A890(const char *args) {
    sub_612C70(loc_6C3690);
    safe_strncpy(loc_6C3690, args, 0x200);
    sub_612F00();
    sub_612A80(loc_6C3690);
}

// mc2: 0x005EDA50
void game_set_window_title(char *title) {
    HWND hWnd = global_hWnd;
    global_WindowText = title;
    if (hWnd != NULL)
        SetWindowTextA(global_hWnd, title);
}

// mc2: 0x00539FE0 and 0x00539D90
void check_sku_version() {
    global_SKUVersion = 0; //SKU VERSION SLUS-20209

    char *skuVersion = NULL;

    switch (global_SKUVersion) {
    case 0:
        skuVersion = "SLUS-20209";
        break;
    case 1:
        skuVersion = "SLES-51054";
        break;
    case 2:
        skuVersion = "SLPM-20209";
        break;
    default:
        // SKU unrecognised
        mc2_log_error("Unhandled sku");
        return;
    }

    mc2_log_C("mcConfig:AutoDetectSku - product code '%s'", skuVersion);
}

// mc2: 0x0053B9B0
// Likely related to assets_p: /tune/hud/ntsc/
void sub_53B9B0() {
    if (sub_612E10("pc_480")) glo_66315C = 7; // 480 x 720
    else if (sub_612E10("pc_720")) glo_66315C = 8; // 720 x 1280
    else glo_66315C = 0; // 480 x 640
}

void sub_53B9F0() {
    int resolution[3][2] = {
        {640, 480},
        {720, 480},
        {1280,720}
    };

    int index = 0;
    switch (glo_66315C) {
    case 7:
        index = 1;
        break;
    case 8:
        index = 2;
        break;
    }

    sub_5ED7B0(resolution[index][0], resolution[index][1], 32, 32, 0);
}

constexpr const char *LanguageShortList[10] = {
    "en", "es", "fr", "de", "it",
    "pt", "jp", "ch", "ko", "no",
};

int sub_5E1B50(const char *path) {
    for (int i = 0; i < 10; ++i) {
        const char *language = LanguageShortList[i];

        if (sub_627145(path, language)) {
            return i;
        }
    }
    return -1;
}

constexpr const char *GameModes[5] = {
    "cruise", "arcade", "adventure", "frontend", "raceeditor",
};

bool sub_539DE0(const char *path) {
    for (int i = 0; i < 5; ++i) {
        const char *unk = GameModes[i];

        if (sub_627145(path, unk)) {
            glo_6C2C60 = i;
            return true;
        }
    }
    mc2_log_fatal("mcConfig::SetMode() failed");
    return false;
}

void sub_53A000() {
    check_sku_version();
    sub_53B9B0();

    if (sub_612E10("unlockall")) {
        glo_unlock_races = 1;
        glo_unlock_cities = 1;
        glo_unlock_vehicles = 1;
        glo_unlock_customization = 1;
        glo_unlock_abilities = 1;
        glo_unlock_difficulty = 1;
    }
    else {
        if (sub_612E10("unlockraces")) {
            glo_unlock_races = 1;
        }
        if (sub_612E10("unlockcities")) {
            glo_unlock_cities = 1;
        }
        if (sub_612E10("unlockvehicles")) {
            glo_unlock_vehicles = 1;
        }
        if (sub_612E10("unlockcustomization")) {
            glo_unlock_customization = 1;
        }
        if (sub_612E10("unlockabilities")) {
            glo_unlock_abilities = 1;
        }
        if (sub_612E10("unlockinsanity")) {
            glo_unlock_difficulty = 1;
        }
        if (sub_612E10("unlockdifficulty")) {
            glo_unlock_difficulty = 1;
        }
    }
    if (sub_612E10("lang")) {
        const char *path;
        sub_612EB0("lang", 0, &path);
        int lang = sub_5E1B50(path);
        if (lang == -1) {
            mc2_log_error("Invalid language");
            return;
        }

        mc2_log_C("Setting language to %s (%d)", LanguageShortList[lang], lang);
        global_LanguageID = lang;
    }

    if (sub_612E10("fromconfigurator")) {
        glo_6C2C64 = 1;
    }

    const char *unk;
    if (sub_612EB0("mode", 0, &unk)) {
        sub_539DE0(unk);
    }
}

void sub_6134D0(const char *var8) {
    char *destination = glo_860120;
    safe_strncpy(destination, var8, 256);

    if (*destination == '\0')
        return;

    char *str = destination;
    while (*str++ != '\0') {
        if (*str == '/') {
            *str = '\\';
        }
    }

    int length = strlen(destination);

    if (length == 0)
        return;

    if (destination[length - 1] != '\\') {
        destination[length] = '\\';
        destination[length + 1] = '\0';
    }
}

bool sub_612EB0(const char * key, std::uint32_t value_index, const char ** value_arg) {
    unk_612150 *value = glo_8600F8.sub_6124A0(key);

    if (value == nullptr)
        return false;

    if (value_index >= value->count)
        return false;

    *value_arg = value->args[value_index];
    return true;
}

void sub_5ECBE0() {
    if (glo_6754C4 != sub_5ECB90) {
        mc2_log_C("Installed bink gfxLoadImage support");
        glo_858328 = glo_6754C4;
        glo_6754C4 = sub_5ECB90;
    }
}

// mc2: 0x00401190
int sub_401190() {
    sub_53A890("mc.exe -path=. -archive=assets_p.dat");
    glo_85837C = 101;
    game_set_window_title("Midnight Club II");
    sub_5ECBE0();
    glo_8602D4 = 1;
    glo_679778 = 0;
    sub_53A000();
    sub_53B9F0();
    global_LanguageID = 0;
    glo_6CE210 = 1;
    glo_6CE211 = 1;
    const char *gamePath = ".";
    sub_612EB0("path", 0, &gamePath);
    new (MC2_MALLOC(0x108)) unk_613360;
    sub_6134D0(gamePath);
    glo_6C3250.sub_53B6A0();
    sub_5ED7B0(glo_6C3250.get_unk44(), glo_6C3250.get_unk48(), glo_6C3250.get_unk4C(), 32, 0);
    sub_53A7B0(gamePath, 48, 0, 0, 0); // main window creation
    glo_692E1C = glo_679810;
    std::memcpy(loc_692E20, glo_679810, 10 * sizeof(void *));
    loc_692E20[2] = loc_4010B0;
    glo_679810 = loc_692E20;
    sub_53A1B0();
    bool runforever = sub_612E10("runforever");
    if (sub_612E10("shiplist") && !sub_612E10("noresources") &&
        !sub_612E10("noraceresources") && !sub_612E10("archive")) {
        sub_613DD0("mc2_xbox.shiplist", MC2_MALLOC(0x30000), 0x30000);
    }
    sub_401170();

    do {
        sub_53A7E0("assets_p.dat");
        glo_85D3F8 = new (MC2_MALLOC(0x27C4)) unk_600960(global_hWnd);
        unk_402560 *esi = sub_402560();
        esi->sub_401860();
        sub_4028E0();
        sub_404BF0();

        std::uint32_t t;
        if (sub_612E10("nofe")) t = 6;
        else if (sub_612E10("carview")) t = 20;
        else if (sub_612E10("raceed")) t = 19;
        else if (sub_612E10("movie")) {
            const char *var4 = "angel.imf";
            sub_612EB0("movie", 0, &var4);
            glo_6C2E88.sub_53ACB0(var4);
            t = 15;
        } else if (sub_612E10("skipintro") || glo_6C2C64 != 0) t = 11;
        else {
            glo_6C2E88.sub_53ACB0("rockstar.pss");
            t = 15;
        }
        glo_6C3890->vir04(t);

        esi->sub_402120();
        sub_53A8F0();
        sub_402590();
        sub_4017E0();
        sub_53A870();

        if (runforever)
            mc2_log_C("\n\n-----------------------------------"
                "------------------------------------\n\n");
    } while (runforever);

    sub_53A7D0();
    sub_5ED220();
    return 0;
}

#define sub_6178E0 (MC2_PROC_PTR<int, LPEXCEPTION_POINTERS>(0x006178E0))

int sub_6181F0() {
    __try {
        return sub_401190();
    } __except (sub_6178E0(GetExceptionInformation())) {
        mc2_log_C("ExceptMain: Abnormal exit.");
        return 1;
    }
    return 0;
}
