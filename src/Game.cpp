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

#include "Config.hpp"
#include "CommandLine.hpp"
#include "Logging.hpp"
#include "Memory.hpp"
#include "Settings.hpp"
#include "UnkObjects/unk402560.hpp"
#include "UnkObjects/unk5769E0.hpp"
#include "UnkObjects/unk577510.hpp"
#include "UnkObjects/unk600960.hpp"
#include "UnkObjects/unk613360.hpp"
#include "UnkObjects/unk6C2E88.hpp"
#include "UnkObjects/unk6C3890.hpp"
#include "UnkObjects/unk8600F8.hpp"

static void sub_612A80(char *args) {
    *loc_8600F0 = 0;
    *loc_8600EC = nullptr;
    char *esi = args;

    esi = std::strchr(args, ' ');
    if (esi == nullptr) {
        loc_8600F8->loc_611DC0();
        return;
    }

    *esi = '\0';
    *loc_8600EC = new char*;
    **loc_8600EC = mc2_strdup(args);

    *esi = ' ';
    esi++;

    if (*esi == '\0') {
        loc_8600F8->loc_611DC0();
        return;
    }

    for (char *cur = esi; *cur != '\0'; ++cur) {
        if (*cur != '-')
            continue;

        (*loc_8600F0)++;

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
        unk_612150 *value = loc_8600F8->sub_6124A0(key);

        if (value != nullptr) {
            cur = value_str;
            continue;
        }

        value = new unk_612150;

        nextSeperator = value_str;
        if (*nextSeperator != '\0') {
            while (*nextSeperator != '\0' && *nextSeperator != '-') {
                value->count++;
                if (*nextSeperator == 0)
                    break;

                bool has_space = false;
                for (; true; ++nextSeperator) {
                    if (*nextSeperator == '=')
                        break;

                    if (*nextSeperator == ' ')
                        has_space = true;
                    else if (has_space)
                        break;

                    if (*nextSeperator == '\0')
                        break;

                }
            }
        }
        
        cur = nextSeperator - 1;

        loc_8600F8->sub_612150(key, value);

        value->args = new char*[value->count];

        if (value->count == 0)
            continue;

        std::uint32_t values_index = 0;
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
            
            value->args[values_index++] = mc2_strdup(cur_value_str);

        } while (values_index < value->count);
    }
    
    loc_8600F8->loc_611DC0();
    return;
}

void sub_612F00() {
    unk_8600F8::indexed_map_entry index_entry;

    for (bool valid = loc_8600F8->sub_611FE0(&index_entry); valid; valid = loc_8600F8->sub_612020(&index_entry)) {
        unk_612150 *value = index_entry.value;
        if (value != nullptr) {
            if (value->count != 0) {
                for (std::uint32_t i = 0; i < value->count; ++i) {
                    delete [] value->args[i];
                }
                value->count = 0;
            }

            delete [] value->args;
            delete value;
        }
    }

    loc_8600F8->sub_612050();
}

static void sub_53A890(const char *args) {
    sub_612C70(*loc_6C3690);
    safe_strncpy(*loc_6C3690, args, sizeof(*loc_6C3690));
    sub_612F00();
    sub_612A80(*loc_6C3690);
}

// mc2: 0x005EDA50
void game_set_window_title(const char *title) {
    HWND hWnd = *location_hWnd;
    *location_WindowText = title;
    if (hWnd != nullptr)
        SetWindowTextA(*location_hWnd, title);
}

// mc2: 0x00539FE0 and 0x00539D90
void check_sku_version() {
    *location_SKUVersion = 0; //SKU VERSION SLUS-20209

    char *skuVersion = nullptr;

    switch (*location_SKUVersion) {
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
    if (sub_612E10("pc_480")) *loc_66315C = 7; // 480 x 720
    else if (sub_612E10("pc_720")) *loc_66315C = 8; // 720 x 1280
    else *loc_66315C = 0; // 480 x 640
}

void sub_53B9F0() {
    switch (*loc_66315C) {
    case 7:
        sub_5ED7B0(720, 480, 32, 32, 0);
        break;
    case 8:
        sub_5ED7B0(1280, 720, 32, 32, 0);
        break;
    default:
        sub_5ED7B0(640, 480, 32, 32, 0);
        break;
    }
}

constexpr const char *LanguageShortList[10] = {
    "en", "es", "fr", "de", "it",
    "pt", "jp", "ch", "ko", "no",
};

int sub_5E1B50(const char *path) {
    for (int i = 0; i < 10; ++i) {
        const char *language = LanguageShortList[i];

        if (stricmp(path, language) == 0) {
            return i;
        }
    }
    return -1;
}

const char *sub_5E1B40(int id) {
    return LanguageShortList[id];
}

constexpr const char *GameModes[5] = {
    "cruise", "arcade", "adventure", "frontend", "raceeditor",
};

bool sub_539DE0(const char *path) {
    for (int i = 0; i < 5; ++i) {
        const char *unk = GameModes[i];

        if (stricmp(path, unk) == 0) {
            *loc_6C2C60 = i;
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
        *loc_unlock_races = true;
        *loc_unlock_cities = true;
        *loc_unlock_vehicles = true;
        *loc_unlock_customization = true;
        *loc_unlock_abilities = true;
        *loc_unlock_difficulty = true;
    }
    else {
        if (sub_612E10("unlockraces")) {
            *loc_unlock_races = true;
        }
        if (sub_612E10("unlockcities")) {
            *loc_unlock_cities = true;
        }
        if (sub_612E10("unlockvehicles")) {
            *loc_unlock_vehicles = true;
        }
        if (sub_612E10("unlockcustomization")) {
            *loc_unlock_customization = true;
        }
        if (sub_612E10("unlockabilities")) {
            *loc_unlock_abilities = true;
        }
        if (sub_612E10("unlockinsanity")) {
            *loc_unlock_difficulty = true;
        }
        if (sub_612E10("unlockdifficulty")) {
            *loc_unlock_difficulty = true;
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
        *location_LanguageID = lang;
    }

    if (sub_612E10("fromconfigurator")) {
        *loc_6C2C64 = 1;
    }

    const char *unk;
    if (sub_612EB0("mode", 0, &unk)) {
        sub_539DE0(unk);
    }
}

void sub_6134D0(const char *var8) {
    char *destination = *loc_860120;
    safe_strncpy(destination, var8, sizeof(*loc_860120));

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
    unk_612150 *value = loc_8600F8->sub_6124A0(key);

    if (value == nullptr || value_index >= value->count)
        return false;

    *value_arg = value->args[value_index];
    return true;
}

void sub_53A7B0(const char *a, std::uint32_t b, bool c, std::uint32_t d, std::uint32_t e) {
    sub_612C70(*loc_6C3690);

    // sub_577390:
    sub_5ED240(a, d, e);
    if (c)
        sub_5ED7B0(640, 480, 32, 32, 0);
    if (!sub_5F12F0())
        mc2_log_fatal("Could not start graphics.  "
            "Please check that you're in 32bpp mode "
            "and you have a DX9-class video driver.");

    *loc_6C52E4 = new unk_577510;
    *loc_6C52E8 = new unk_5769E0;
    (*loc_6C52E4)->sub_5775A0(*loc_6C52E8, b << 20, 1, 1, sub_612E10("checkalloc"));
    *loc_6C52E0 = *location_primary_unk5769E0;
    *location_primary_unk5769E0 = *loc_6C52E8;
}

void sub_53A7E0(const char *archive) {
    mc2_log_C("ARGS: %s", *loc_6C3690);
    sub_612A80(*loc_6C3690);

    if (sub_612E10("nosmallocator")) {
        mc2_log_C("Disabling smallocator");
        (*location_primary_unk5769E0)->sub_575B10();
    }

    sub_577480(archive);
    *location_texture_dir_name = "texture_x";
    *location_mod_dir_name = "xmod";
    sub_5F9E20();

    if (sub_612E10("memorylog")) {
        // Code calls sub_5C3530(6), which is a nop
    }
}

void sub_53A870() {
    sub_5F9E30();
    sub_612C70(*loc_6C3690);
    sub_612F00();

    // sub_5774A0:
    sub_5F0BC0();
    sub_5FD2D0();
    sub_612130();
    (*loc_6C52E4)->sub_577610();
    sub_617AA0();
}

void sub_5ECBE0() {
    if (*loc_6754C4 != &sub_5ECB90) {
        mc2_log_C("Installed bink gfxLoadImage support");
        *loc_858328 = *loc_6754C4;
        *loc_6754C4 = &sub_5ECB90;
    }
}

void sub_5F5690() {
    if (*loc_85AE98 != 0) {
        *loc_85AE8C = true;
    }
    else if (!*loc_85AE8C) {
        *loc_6754A4 = 60;
        *loc_6754A8 = 1.0f/60.0f;
        return;
    }
    *loc_6754A4 = 50;
    *loc_6754A8 = 1.0f/50.0f;
}

void sub_5ED7B0(std::int32_t width, std::int32_t height, std::int32_t cdepth, std::int32_t zdepth, std::int32_t unk5) {
	if (sub_612E10("ref")) {
		*loc_858373 = true;
		*loc_858374 = true;
	}
	else if (sub_612E10("blade") || sub_612E10("bladed")) {
        *loc_858376 = 1;
		*loc_858374 = true;
	}
	else if (sub_612E10("swage")) {
		*loc_858375 = 1;
		*loc_858374 = true;
	}
	else if (sub_612E10("sw")) {
        *loc_858374 = true;
	}
	
	if (sub_612E10("sysmem")) {
		*loc_858377 = 1;
	}

	if (sub_612E10("novblank") || true) {
		*loc_675030 = 0;
	}

	if (sub_612E10("window")) {
		*loc_windowed_mode = true;
	}
	else if (sub_612E10("fs") || sub_612E10("fullscreen")) {
		*loc_windowed_mode = false;
	}

    // Use preset vars if available
    sub_612E30("width", 0, &width);
    sub_612E30("height", 0, &height);
    sub_612E30("cdepth", 0, &cdepth);
    sub_612E30("zdepth", 0, &zdepth);

    sub_5F5690();

    if (*loc_858371) {
        width = GetSystemMetrics(SM_CXFULLSCREEN);
        height = GetSystemMetrics(SM_CYFULLSCREEN);
        *loc_858388 = 0;
        *loc_85839C = 0;
    }
    
    *loc_858377 = *loc_858374;
    *loc_674FB4 = cdepth;
    *loc_674FB8 = zdepth;
    *loc_674FAC = width;
    *loc_674FB0 = height;
    *loc_85FBC4 = width;
    *loc_85FBB0 = height;
    *loc_8583B0 = static_cast<float>(width);
    *loc_85838C = static_cast<float>(height);
    *loc_85FBDC = static_cast<float>(1.0 / width);
    *loc_85FBE0 = static_cast<float>(1.0 / height);
}

// mc2: 0x00401190
int sub_401190() {
    sub_53A890("mc.exe -path=. -archive=assets_p.dat");
    *loc_85837C = 101;
    game_set_window_title("Midnight Club II");
    sub_5ECBE0();
    *loc_8602D4 = true;
    *loc_679778 = false;
    sub_53A000();
    sub_53B9F0();
    *location_LanguageID = 0;
    *loc_6CE210 = 1;
    *loc_6CE211 = 1;
    const char *gamePath = ".";
    sub_612EB0("path", 0, &gamePath);
    new unk_613360;
    sub_6134D0(gamePath);
    loc_Settings->load_settings();
    sub_5ED7B0(loc_Settings->get_screen_width(), loc_Settings->get_screen_height(), loc_Settings->get_screen_depth(), 32, 0);
    sub_53A7B0(gamePath, 48, 0, 0, 0); // main window creation
    *loc_692E1C = *loc_679810;
    *loc_692E20 = **loc_679810;
    loc_692E20->sub_08 = &sub_4010B0;
    *loc_679810 = loc_692E20;
    sub_53A1B0();
    bool runforever = sub_612E10("runforever");
    if (sub_612E10("shiplist") && !sub_612E10("noresources") &&
        !sub_612E10("noraceresources") && !sub_612E10("archive")) {
        sub_613DD0("mc2_xbox.shiplist", new std::uint8_t[0x30000], 0x30000);
    }
    sub_401170();

    do {
        sub_53A7E0("assets_p.dat");
        *loc_85D3F8 = new unk_600960(*location_hWnd);
        unk_402560 *esi = sub_402560();
        esi->sub_401860();
        sub_4028E0();
        sub_404BF0();

        if (sub_612E10("nofe")) (*loc_6C3890)->vir04(6);
        else if (sub_612E10("carview")) (*loc_6C3890)->vir04(20);
        else if (sub_612E10("raceed")) (*loc_6C3890)->vir04(19);
        else if (sub_612E10("movie")) {
            const char *var4 = "angel.imf";
            sub_612EB0("movie", 0, &var4);
            loc_6C2E88->sub_53ACB0(var4);
            (*loc_6C3890)->vir04(15);
        } else if (sub_612E10("skipintro") || *loc_6C2C64 != 0) (*loc_6C3890)->vir04(11);
        else {
            loc_6C2E88->sub_53ACB0("rockstar.pss");
            (*loc_6C3890)->vir04(15);
        }

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

constexpr mc2_proc<0x006178E0, int, LPEXCEPTION_POINTERS> sub_6178E0;

int sub_6181F0() {
    __try {
        return sub_401190();
    } __except (sub_6178E0(GetExceptionInformation())) {
        mc2_log_C("ExceptMain: Abnormal exit.");
        return 1;
    }
    return 0;
}
