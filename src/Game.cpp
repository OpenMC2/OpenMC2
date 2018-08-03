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

#include <cstring>

#include "Archive.hpp"
#include "Config.hpp"
#include "CommandLine.hpp"
#include "Logging.hpp"
#include "Memory.hpp"
#include "Settings.hpp"

#include "UnkObjects/unk4020F0.hpp"
#include "UnkObjects/unk404B90.hpp"
#include "UnkObjects/unk53AF00.hpp"
#include "UnkObjects/unk5769E0.hpp"
#include "UnkObjects/unk577510.hpp"
#include "UnkObjects/unk5FAC30.hpp"
#include "UnkObjects/unk600960.hpp"
#include "UnkObjects/unk612850.hpp"
#include "UnkObjects/unk613360.hpp"

static void sub_612A80(char *args) {
    glo_8600F0 = 0;
    glo_8600EC = nullptr;
    char *esi = args;

    esi = std::strchr(args, ' ');
    if (esi == nullptr) {
        glo_8600F8.loc_611DC0();
        return;
    }

    *esi = '\0';
    glo_8600EC = new char*;
    *glo_8600EC = mc2_strdup(args);

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

        glo_8600F8.sub_612150(key, value);

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
    
    glo_8600F8.loc_611DC0();
    return;
}

void sub_612F00() {
    unk_612850::indexed_map_entry index_entry;

    for (bool valid = glo_8600F8.sub_611FE0(&index_entry); valid; valid = glo_8600F8.sub_612020(&index_entry)) {
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

    glo_8600F8.sub_612050();
}

static void sub_53A890(const char *args) {
    sub_612C70(glo_6C3690);
    safe_strncpy(glo_6C3690, args, sizeof(glo_6C3690));
    sub_612F00();
    sub_612A80(glo_6C3690);
}

// mc2: 0x005EDA50
void game_set_window_title(char *title) {
    HWND hWnd = global_hWnd;
    global_WindowText = title;
    if (hWnd != nullptr)
        SetWindowTextA(global_hWnd, title);
}

// mc2: 0x00539FE0 and 0x00539D90
void check_sku_version() {
    global_SKUVersion = 0; //SKU VERSION SLUS-20209

    char *skuVersion = nullptr;

    switch (global_SKUVersion) {
    case 0:
        skuVersion = "SLUS-20209";
        break;
    case 1:
    case 2:
        skuVersion = "SLES-51054";
        break;
    case 3:
        skuVersion = "SLPM-20209";
        break;
    default:
        // SKU unrecognised
        mc2_log_error("Unhandled sku");
        return;
    }

    mc2_log_info("mcConfig:AutoDetectSku - product code '%s'", skuVersion);
}

// mc2: 0x0053B9B0
// Likely related to assets_p: /tune/hud/ntsc/
void sub_53B9B0() {
    if (sub_612E10("pc_480")) glo_66315C = 7; // 480 x 720
    else if (sub_612E10("pc_720")) glo_66315C = 8; // 720 x 1280
    else glo_66315C = 0; // 480 x 640
}

void sub_53B9F0() {
    switch (glo_66315C) {
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

int get_language_id(const char *path) {
    for (int i = 0; i < 10; ++i) {
        const char *language = LanguageShortList[i];

        if (stricmp(path, language) == 0) {
            return i;
        }
    }
    return -1;
}

const char *get_language_string(int id) {
    return LanguageShortList[id];
}

constexpr const char *GameModes[5] = {
    "cruise", "arcade", "adventure", "frontend", "raceeditor",
};

bool sub_539DE0(const char *path) {
    for (int i = 0; i < 5; ++i) {
        const char *unk = GameModes[i];

        if (stricmp(path, unk) == 0) {
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
        int lang = get_language_id(path);
        if (lang == -1) {
            mc2_log_error("Invalid language");
            return;
        }

        mc2_log_info("Setting language to %s (%d)", LanguageShortList[lang], lang);
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

void sub_53A7B0(const char *a, std::uint32_t b, bool c, std::uint32_t d, std::uint32_t e) {
    sub_612C70(glo_6C3690);

    // sub_577390:
    sub_5ED240(a, d, e);
    if (c)
        sub_5ED7B0(640, 480, 32, 32, 0);
    if (!sub_5F12F0())
        mc2_log_fatal("Could not start graphics.  "
            "Please check that you're in 32bpp mode "
            "and you have a DX9-class video driver.");

    glo_6C52E4 = new unk_577510;
    glo_6C52E8 = new unk_5769E0;
    glo_6C52E4->sub_5775A0(glo_6C52E8, b << 20, 1, 1, sub_612E10("checkalloc"));
    glo_6C52E0 = global_primary_unk5769E0;
    global_primary_unk5769E0 = glo_6C52E8;
}

static bool sub_577480(const char *archive) {
    if (sub_612E10("archive")) {
        sub_5FDD20();
    } // no else?

    //loc_5EF2DO
    sub_5EE9F0();

    glo_858378 = sub_5ED990();
    glo_858378->sub_419DB0();

    glo_858394 = sub_5ED990();
    sub_5FAFE0(322, 2, 1024);

    return true;
}

void sub_53A7E0(const char *archive) {
    mc2_log_info("ARGS: %s", glo_6C3690);
    sub_612A80(glo_6C3690);

    if (sub_612E10("nosmallocator")) {
        mc2_log_info("Disabling smallocator");
        global_primary_unk5769E0->sub_575B10();
    }

    sub_577480(archive);
    global_texture_dir_name = "texture_x";
    global_mod_dir_name = "xmod";
    sub_5F9E20();

    if (sub_612E10("memorylog")) {
        // Code calls sub_5C3530(6), which is a nop
    }
}

void sub_53A870() {
    sub_5F9E30();
    sub_612C70(glo_6C3690);
    sub_612F00();

    // sub_5774A0:
    sub_5F0BC0();
    sub_5FD2D0();
    sub_612130();
    glo_6C52E4->sub_577610();
    sub_617AA0();
}

void sub_5ECBE0() {
    if (glo_6754C4 != sub_5ECB90) {
        mc2_log_info("Installed bink gfxLoadImage support");
        glo_858328 = glo_6754C4;
        glo_6754C4 = sub_5ECB90;
    }
}

// mc2: 0x005F5690
void set_pal_mode() {
    if (glo_pal_cmdline.value != nullptr) {
        glo_pal_mode = true;
    }
    
    if (!glo_pal_mode) {
        glo_6754A4 = 60;
        glo_6754A8 = 1.0f / 60.0f;
    } else {
        glo_6754A4 = 50;
        glo_6754A8 = 1.0f / 50.0f;
    }
}

void sub_5ED7B0(std::int32_t width, std::int32_t height, std::int32_t cdepth, std::int32_t zdepth, std::int32_t unk5) {
	if (sub_612E10("ref")) {
		glo_858373 = 1;
		glo_858374 = 1;
	}
	else if (sub_612E10("blade") || sub_612E10("bladed")) {
		glo_858376 = 1;
		glo_858374 = 1;
	}
	else if (sub_612E10("swage")) {
		glo_858375 = 1;
		glo_858374 = 1;
	}
	else if (sub_612E10("sw")) {
		glo_858374 = 1;
	}
	
	if (sub_612E10("sysmem")) {
		glo_858377 = 1;
	}

	if (sub_612E10("novblank")) {
		glo_675030 = 0;
	}

	if (sub_612E10("window")) {
		glo_windowed_mode = 1;
	}
	else if (sub_612E10("fs") || sub_612E10("fullscreen")) {
		glo_windowed_mode = 0;
	}

    // Use preset vars if available
    sub_612E30("width", 0, &width);
    sub_612E30("height", 0, &height);
    sub_612E30("cdepth", 0, &cdepth);
    sub_612E30("zdepth", 0, &zdepth);

    set_pal_mode();

    if (glo_858371 != 0) {
        width = GetSystemMetrics(SM_CXFULLSCREEN);
        height = GetSystemMetrics(SM_CYFULLSCREEN);
        glo_858388 = 0;
        glo_85839C = 0;
    }
    
    glo_858377 = glo_858374;
    glo_674FB4 = cdepth;
    glo_674FB8 = zdepth;
    glo_674FAC = width;
    glo_674FB0 = height;
    glo_85FBC4 = width;
    glo_85FBB0 = height;
    glo_8583B0 = static_cast<float>(width);
    glo_85838C = static_cast<float>(height);    
    glo_85FBDC = static_cast<float>(1.0 / width);
    glo_85FBE0 = static_cast<float>(1.0 / height);
}

// mc2: 0x00401190
int run_game() {
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
    new unk_613360;
    sub_6134D0(gamePath);
    //glo_Settings.load_settings();
    sub_5ED7B0(glo_Settings.get_screen_width(), glo_Settings.get_screen_height(), glo_Settings.get_screen_depth(), 32, 0);
    sub_53A7B0(gamePath, 48, 0, 0, 0); // main window creation
    glo_692E1C = glo_679810;
    glo_692E20 = *glo_679810;
    glo_692E20.read = sub_4010B0;
    glo_679810 = &glo_692E20;
    sub_53A1B0();
    bool runforever = sub_612E10("runforever");
    if (sub_612E10("shiplist") && !sub_612E10("noresources") &&
        !sub_612E10("noraceresources") && !sub_612E10("archive")) {
        sub_613DD0("mc2_xbox.shiplist", new std::uint8_t[0x30000], 0x30000);
    }
    sub_401170();

    do {
        sub_53A7E0("assets_p.dat");
        glo_85D3F8 = new unk_600960(global_hWnd);
        unk_4020F0 *game = sub_402560();
        game->sub_401860();
        sub_4028E0();
        sub_404BF0();

        if (sub_612E10("nofe")) glo_6C3890->vir04(6);
        else if (sub_612E10("carview")) glo_6C3890->vir04(20);
        else if (sub_612E10("raceed")) glo_6C3890->vir04(19);
        else if (sub_612E10("movie")) {
            const char *var4 = "angel.imf";
            sub_612EB0("movie", 0, &var4);
            glo_6C2E88.sub_53ACB0(var4);
            glo_6C3890->vir04(15);
        } else if (sub_612E10("skipintro") || glo_6C2C64 != 0) glo_6C3890->vir04(11);
        else {
            glo_6C2E88.sub_53ACB0("rockstar.pss");
            glo_6C3890->vir04(15);
        }

        game->game_loop();
        sub_53A8F0();
        sub_402590();
        sub_4017E0();
        sub_53A870();

        if (runforever)
            mc2_log_info("\n\n-----------------------------------"
                "------------------------------------\n\n");
    } while (runforever);

    sub_53A7D0();
    sub_5ED220();
    return 0;
}

/*
 * Attempts to print a stack trace using stack frames
 */
void sub_6177E0(std::int32_t depth, DWORD ebp, FILE *log, const char *) {
    char buffer[0x200];
    struct bp_frame {
        bp_frame *prev;
        DWORD caller;
    };
    bp_frame *frame = reinterpret_cast<bp_frame *>(ebp);

    for (; depth > 0; --depth) {
        __try {
            if (frame == nullptr) break;
            DWORD caller = frame->caller;
            frame = frame->prev;
            if (caller == 0) return;

            sub_617760(buffer, caller);

            if (log != nullptr) fprintf(log, "%s,", buffer);
            else mc2_log_info("%s", buffer);
        } __except (true) { break; }
    }

    if (depth > 0) {
        if (log != nullptr) fprintf(log, "<invalid address>");
        else mc2_log_info("<invalid address>");
    } else {
        if (log != nullptr) fprintf(log, "...");
        else mc2_log_info("...");
    }
}

static bool sub_6178E0(LPEXCEPTION_POINTERS except) {
    char buffer[0x200];
    PCONTEXT context = except->ContextRecord;
    sub_617760(buffer, context->Eip);

    mc2_log_info("\nEAX=%08X EBX=%08X ECX=%08X EDX=%08X\nESI=%08X EDI=%08X EBP=%08X ESP=%08X",
        context->Eax, context->Ebx, context->Ecx, context->Edx,
        context->Esi, context->Edi, context->Ebp, context->Esp
    );
    mc2_log_info("Exception %X at EIP=%s", except->ExceptionRecord->ExceptionCode, buffer);
    sub_6177E0(16, context->Ebp, nullptr, "\n");

    return true;
}

// mc2: 0x006181F0
int run_game_guarded() {
    __try {
        return run_game();
    } __except (sub_6178E0(GetExceptionInformation())) {
        mc2_log_info("ExceptMain: Abnormal exit.");
        return 1;
    }
    return 0;
}

MC2_DEF_PROC(sub_4010B0, 0x004010B0);
MC2_DEF_PROC(sub_401170, 0x00401170);
MC2_DEF_PROC(sub_4014C0, 0x004014C0);
MC2_DEF_PROC(sub_4017E0, 0x004017E0);
MC2_DEF_PROC(sub_402590, 0x00402590);
MC2_DEF_PROC(sub_4028E0, 0x004028E0);
MC2_DEF_PROC(sub_53A1B0, 0x0053A1B0);
MC2_DEF_PROC(sub_53A7D0, 0x0053A7D0);
MC2_DEF_PROC(sub_53A8F0, 0x0053A8F0);
MC2_DEF_PROC(sub_5ECB90, 0x005ECB90);
MC2_DEF_PROC(sub_5ED240, 0x005ED240);
MC2_DEF_PROC(sub_5EDA50, 0x005EDA50);
MC2_DEF_PROC(sub_5EE9F0, 0x005EE9F0);
MC2_DEF_PROC(sub_5F0BC0, 0x005F0BC0);
MC2_DEF_PROC(sub_5F12F0, 0x005F12F0);
MC2_DEF_PROC(sub_5F9E20, 0x005F9E20);
MC2_DEF_PROC(sub_5F9E30, 0x005F9E30);
MC2_DEF_PROC(sub_5FAFE0, 0x005FAFE0);
MC2_DEF_PROC(sub_5FD2D0, 0x005FD2D0);
MC2_DEF_PROC(sub_612130, 0x00612130);
MC2_DEF_PROC(sub_612C70, 0x00612C70);
MC2_DEF_PROC(sub_613DD0, 0x00613DD0);
MC2_DEF_PROC(sub_617760, 0x00617760);

MC2_DEF_GLOBAL(global_texture_dir_name, 0x006754AC);
MC2_DEF_GLOBAL(global_mod_dir_name, 0x00675518);

MC2_DEF_GLOBAL(glo_674FAC, 0x00674FAC);
MC2_DEF_GLOBAL(glo_674FB0, 0x00674FB0);
MC2_DEF_GLOBAL(glo_674FB4, 0x00674FB4);
MC2_DEF_GLOBAL(glo_674FB8, 0x00674FB8);
MC2_DEF_GLOBAL(glo_675030, 0x00675030);
MC2_DEF_GLOBAL(glo_6754A8, 0x006754A8);

MC2_DEF_GLOBAL(global_LanguageID, 0x006C2C5C); // glo_6C2C5C
MC2_DEF_GLOBAL(glo_6CE210, 0x006CE210);
MC2_DEF_GLOBAL(glo_6CE211, 0x006CE211);

MC2_DEF_GLOBAL(glo_6C3690, 0x006C3690);

MC2_DEF_GLOBAL(global_hWnd, 0x00858364);
MC2_DEF_GLOBAL(glo_858371, 0x00858371);
MC2_DEF_GLOBAL(glo_858373, 0x00858373);
MC2_DEF_GLOBAL(glo_858374, 0x00858374);
MC2_DEF_GLOBAL(glo_858375, 0x00858375);
MC2_DEF_GLOBAL(glo_858376, 0x00858376);
MC2_DEF_GLOBAL(glo_858377, 0x00858377);
MC2_DEF_GLOBAL(glo_85837C, 0x0085837C);
MC2_DEF_GLOBAL(glo_858388, 0x00858388);
MC2_DEF_GLOBAL(glo_85838C, 0x0085838C);
MC2_DEF_GLOBAL(glo_85839C, 0x0085839C);
MC2_DEF_GLOBAL(glo_8583B0, 0x008583B0);
MC2_DEF_GLOBAL(glo_pal_mode, 0x0085AE8C);
MC2_DEF_GLOBAL(glo_85D1C0, 0x0085D1C0);
MC2_DEF_GLOBAL(glo_85FBB0, 0x0085FBB0);
MC2_DEF_GLOBAL(glo_85FBC4, 0x0085FBC4);
MC2_DEF_GLOBAL(glo_85FBDC, 0x0085FBDC);
MC2_DEF_GLOBAL(glo_85FBE0, 0x0085FBE0);
MC2_DEF_GLOBAL(glo_8602D4, 0x008602D4);
MC2_DEF_GLOBAL(glo_860AD8, 0x00860AD8);
MC2_DEF_GLOBAL(glo_86D8A8, 0x0086D8A8);
MC2_DEF_GLOBAL(global_WindowText, 0x00858390);
MC2_DEF_GLOBAL(global_SKUVersion, 0x006C2C58);
MC2_DEF_GLOBAL(glo_66315C, 0x0066315C);

MC2_DEF_GLOBAL(glo_6C2C60, 0x006C2C60);
MC2_DEF_GLOBAL(glo_6C2C64, 0x006C2C64);
MC2_DEF_GLOBAL(glo_unlock_races, 0x006C2C66);
MC2_DEF_GLOBAL(glo_unlock_cities, 0x006C2C67);
MC2_DEF_GLOBAL(glo_unlock_vehicles, 0x006C2C68);
MC2_DEF_GLOBAL(glo_unlock_customization, 0x006C2C69);
MC2_DEF_GLOBAL(glo_unlock_abilities, 0x006C2C6A);
MC2_DEF_GLOBAL(glo_unlock_difficulty, 0x006C2C6B);
MC2_DEF_POINTER(glo_860120, 0x00860120);
MC2_DEF_GLOBAL(glo_6754C4, 0x006754C4);
MC2_DEF_GLOBAL(glo_858328, 0x00858328);
