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

static void sub_53A890(const char *args) {
    sub_612C70(loc_6C3690);
    safe_strncpy(loc_6C3690, args, 0x200);
    sub_612F00();
    sub_612A80(loc_6C3690);
}

// mc2: 0x005EDA50
void game_set_window_title(char* title) {
    HWND hWnd = global_hWnd;
    global_WindowText = title;
    if (hWnd != NULL)
        SetWindowTextA(global_hWnd, title);
}

// mc2: 0x00539FE0 and 0x00539D90
void check_sku_version() {
    global_SKUVersion = 0; //SKU VERSION SLUS-20209

    char* skuVersion = NULL;

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

    mc2_log_C(skuVersion);
}

void sub_53B9B0() {
    int esi = 0;
    if (sub_612E10("pc_480")) {
        esi = 7;
    }
    else if (sub_612E10("pc_720")) {
        esi = 8;
    }
    glo_66315C = esi;
}

//bool sub_627145(char* path, char* path2) {
//	//if (glo_86D8A8 == 0) {
//	//	//627CD0
//	//	return false;
//	//}
//
//
//}

int sub_5E1B50(const char* path) {
    for (int i = 0; i < 10; ++i) {
        char* language = global_LanguageList[i];

        if (sub_627145(path, language)) {
            return i;
        }
    }
    return -1;
}

bool sub_539DE0(const char* path) {
    for (int i = 0; i < 10; ++i) {
        char* unk = glo_663160[i];

        if (sub_627145(path, unk)) {
            glo_6C2C60 = i;
            return true;
        }
    }
    mc2_log_level_v(LOG_LEVEL_FATAL_ERROR, "mcConfig::SetMode() failed", NULL);
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
        const char* path;
        sub_612EB0("lang", 0, &path);
        int lang = sub_5E1B50(path);
        if (lang == -1) {
            mc2_log_error("Invalid language");
            return;
        }

        mc2_log_C("Setting language to %s (%d)", global_LanguageList[lang], lang);
        global_LanguageID = lang;
    }

    if (sub_612E10("fromconfigurator")) {
        glo_6C2C64 = 1;
    }

    const char* unk;
    if (sub_612EB0("mode", 0, &unk)) {
        sub_539DE0(unk);
    }
}

void sub_6134D0(const char* var8) {
    char* destination = glo_860120;
    memset(destination, 0, 256);
    safe_strncpy(destination, var8, 255);

    if (*destination == '\0')
        return;

    char* str = destination;
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
        destination[length] = '\0';
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
    glo_windowed_mode = 1; // Added to force window mode whilst developing
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
        }
        else if (sub_612E10("skipintro") || glo_6C2C64 != 0) t = 11;
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
