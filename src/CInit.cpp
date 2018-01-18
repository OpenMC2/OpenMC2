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

#include "Addresses.hpp"
#include "CommandLine.hpp"
#include "FileHandler.hpp"
#include "Settings.hpp"

#include "UnkObjects/unk4701A0.hpp"
#include "UnkObjects/unk47BEA0.hpp"
#include "UnkObjects/unk515240.hpp"
#include "UnkObjects/unk53AF00.hpp"
#include "UnkObjects/unk53E8D0.hpp"
#include "UnkObjects/unk5406A0.hpp"
#include "UnkObjects/unk546DA0.hpp"
#include "UnkObjects/unk579410.hpp"
#include "UnkObjects/unk59D370.hpp"
#include "UnkObjects/unk5D6A30.hpp"
#include "UnkObjects/unk5E14C0.hpp"
#include "UnkObjects/unk5EDA70.hpp"
#include "UnkObjects/unk5FB2E0.hpp"
#include "UnkObjects/unk602740.hpp"
#include "UnkObjects/unk611C60.hpp"
#include "UnkObjects/unk612850.hpp"
#include "UnkObjects/unk614370.hpp"
#include "UnkObjects/unk6144B0.hpp"
#include "UnkObjects/unk860688.hpp"

#include <cmath>
#include <cstdlib>
#include <new>

#define mc2___security_init_cookie MC2_PROC_PTR<void>(0x00625D30)

#define mc2__cfltcvt_tab MC2_GLOBAL<void(__cdecl *)(double *, char *, int, int, int)>(0x00679D18)
#define mc2__cropzeros_tab MC2_GLOBAL<void(__cdecl *)(char *)>(0x00679D1C)
#define mc2__fassign_tab MC2_GLOBAL<void(__cdecl *)(int, char *, char *)>(0x00679D20)
#define mc2__forcdecpt_tab MC2_GLOBAL<void(__cdecl *)(char *)>(0x00679D24)
#define mc2__positive_tab MC2_GLOBAL<int(__cdecl *)(double *)>(0x00679D28)
#define mc2__cldcvt_tab MC2_GLOBAL<void(__cdecl *)(double *, char *, int, int, int)>(0x00679D20)

#define mc2__fptrap MC2_PROC_PTR<void>(0x00624670)
#define mc2__cfltcvt MC2_PROC_PTR<void, double *, char *, int, int, int>(0x0061C725)
#define mc2__cropzeros MC2_PROC_PTR<void, char *>(0x0061C3EB)
#define mc2__fassign MC2_PROC_PTR<void, int, char *, char *>(0x0061C450)
#define mc2__forcdecpt MC2_PROC_PTR<void, char *>(0x0061C393)
#define mc2__positive MC2_PROC_PTR<int, double *>(0x0061C436)

#define glo_86D7C4 MC2_GLOBAL<std::int32_t>(0x0086D7C4)

void mc2__FPinit_proc() {
    // __cfltcvt_init
    mc2__cfltcvt_tab = &mc2__cfltcvt;
    mc2__cropzeros_tab = &mc2__cropzeros;
    mc2__fassign_tab = &mc2__fassign;
    mc2__forcdecpt_tab = &mc2__forcdecpt;
    mc2__positive_tab = &mc2__positive;
    mc2__cldcvt_tab = &mc2__cfltcvt;

    // __ms_p5_mp_test_fdiv
    /*
    * Original had a check for a 1994 CPU defect called the Pentium FDIV Bug.
    * Since no SSE compatible CPUs have the flaw, don't check for it when
    * /arch is set to SSE or higher.
    */
#if defined (_WIN32) && (!defined(_M_IX86_FP) || _M_IX86_FP == 0)
    glo_86D7C4 = IsProcessorFeaturePresent(PF_FLOATING_POINT_PRECISION_ERRATA);
#else
    glo_86D7C4 = 0;
#endif

    // __setdefaultprecision
    /*
    * Original set the x87 mode to 53-bit precision. This is invalid for SSE,
    * and the default is already 53-bit precision for x87, so it's removed.
    */
}

static int test_sse2() {
    // Original had a runtime check for SSE2. However, we're
    // compiling with static SSE2 support, so just use that value.
#if (defined(_M_IX86_FP) && _M_IX86_FP >= 2) || defined(__SSE2__)
    MC2_GLOBAL<std::uint32_t>(0x0086DA50) = 1;
    MC2_GLOBAL<std::uint32_t>(0x0086DA4C) = 1;
#else
    MC2_GLOBAL<std::uint32_t>(0x0086DA50) = 0;
    MC2_GLOBAL<std::uint32_t>(0x0086DA4C) = 0;
#endif
    return 0;
}

constexpr float sqrt_12_constant = 7.136496544f; // 2.0f * sqrt(12.732395f)
constexpr float sqrt_9_8_constant = 259.2296143f; // sqrt(9.8f / 0.00525f) * 6.0f

/*
* MC2 had a lot of float variables initialized to constant
* values on launch, so I set them all here for simplicity.
*/
static void init_float_constants() {
    MC2_GLOBAL<float>(0x00692E80) = sqrt_12_constant; // sub_629D10
    MC2_GLOBAL<float>(0x00692EAC) = sqrt_12_constant; // sub_629D30
    MC2_GLOBAL<float>(0x00692EBC) = sqrt_12_constant; // sub_629D50
    MC2_GLOBAL<float>(0x00692EC4) = sqrt_12_constant; // sub_629D70
    MC2_GLOBAL<float>(0x00692EC8) = sqrt_12_constant; // sub_629D90
    MC2_GLOBAL<float>(0x00696764) = sqrt_12_constant; // sub_629DF0
    MC2_GLOBAL<float>(0x006967B0) = sqrt_12_constant; // sub_629E10
    MC2_GLOBAL<float>(0x00696850) = sqrt_12_constant; // sub_629E40
    MC2_GLOBAL<float>(0x00697B8C) = sqrt_12_constant; // sub_629EA0
    MC2_GLOBAL<float>(0x00697C18) = sqrt_12_constant; // sub_629EC0
    MC2_GLOBAL<float>(0x00698490) = sqrt_12_constant; // sub_629F90
    MC2_GLOBAL<float>(0x00698620) = sqrt_12_constant; // sub_629FB0
    MC2_GLOBAL<float>(0x0069910C) = sqrt_12_constant; // sub_62A050
    MC2_GLOBAL<float>(0x006993A0) = sqrt_12_constant; // sub_62A070
    MC2_GLOBAL<float>(0x0069948C) = sqrt_12_constant; // sub_62A0D0
    MC2_GLOBAL<float>(0x00699690) = sqrt_12_constant; // sub_62A0F0
    MC2_GLOBAL<float>(0x0069B5F8) = sqrt_12_constant; // sub_62A110
    MC2_GLOBAL<float>(0x00699860) = 200.0f; // sub_62A130
    MC2_GLOBAL<float>(0x0069B698) = 5.0f / 6.0f; /* (44.704f / -26.8224f) * -0.5f */ // sub_62A140
    MC2_GLOBAL<float>(0x0069988C) = 5.0f; // sub_62A1A0
    MC2_GLOBAL<float>(0x00699864) = 2.0f; // sub_62A1B0
    MC2_GLOBAL<float>(0x0069B658) = 0.2f; // sub_62A1C0
    MC2_GLOBAL<float>(0x00699868) = 0.22352f; // sub_62A1D0
    MC2_GLOBAL<float>(0x0069B69C) = 44.704f; // sub_62A1E0
    MC2_GLOBAL<float>(0x0069B660) = 1.34112f; // sub_62A1F0
    MC2_GLOBAL<float>(0x00699888) = -1.78816f; // sub_62A200
    MC2_GLOBAL<float>(0x0069B664) = -26.8224f; // sub_62A210
    MC2_GLOBAL<float>(0x0069B65C) = -5.36448f; /* -1.78816f * 3.0f */ // sub_62A220
    MC2_GLOBAL<float>(0x0069985C) = -26.8224f; // sub_62A240
    MC2_GLOBAL<float>(0x0069B748) = 5.0f / 6.0f; // sub_62A250
    MC2_GLOBAL<float>(0x0069B78C) = sqrt_12_constant; // sub_62A260
    MC2_GLOBAL<float>(0x0069C7A8) = sqrt_12_constant; // sub_62A280
    MC2_GLOBAL<float>(0x0069C7AC) = sqrt_12_constant; // sub_62A2A0
    MC2_GLOBAL<float>(0x0069C7B0) = sqrt_12_constant; // sub_62A2C0
    MC2_GLOBAL<float>(0x0069C7B4) = sqrt_12_constant; // sub_62A2E0
    MC2_GLOBAL<float>(0x0069C7BC) = sqrt_12_constant; // sub_62A300
    MC2_GLOBAL<float>(0x0069C7C0) = sqrt_12_constant; // sub_62A320
    MC2_GLOBAL<float>(0x0069C7C4) = sqrt_12_constant; // sub_62A340
    MC2_GLOBAL<float>(0x0069C7C8) = sqrt_12_constant; // sub_62A360
    MC2_GLOBAL<float>(0x0069C7CC) = sqrt_12_constant; // sub_62A380
    MC2_GLOBAL<float>(0x0069C7D8) = sqrt_12_constant; // sub_62A3A0
    MC2_GLOBAL<float>(0x0069C7E0) = sqrt_12_constant; // sub_62A3C0
    MC2_GLOBAL<float>(0x006C2600) = sqrt_12_constant; // sub_62A3F0
    MC2_GLOBAL<float>(0x006C39A4) = 50.0f; // sub_62A480
    MC2_GLOBAL<float>(0x006C39A0) = 90.0f; // sub_62A490
    MC2_GLOBAL<float>(0x006C520C) = 26.8224f; /* 1609.344f / 60.0f */ // sub_62A4C0
    MC2_GLOBAL<float>(0x006C521C) = sqrt_12_constant; // sub_62A500
    MC2_GLOBAL<float>(0x006C5220) = 0.02f; /* 1.0f / 50.0f */ // sub_62A520
    MC2_GLOBAL<float>(0x006C9034) = 9.8f; /* (float) fabs((double) -9.8f) */ // sub_62C580
    MC2_GLOBAL<float>(0x006C9030) = 0.00525f; /* 0.035f * 0.15f */ // sub_62C590
    MC2_GLOBAL<float>(0x006C902C) = sqrt_9_8_constant; // sub_62C5B0
    MC2_GLOBAL<float>(0x006CE510) = 1.0f / 330.0f; // sub_62C670
}

static void mc2_xc() {
    mc2___security_init_cookie();
    init_float_constants();

    new (&glo_692E68) unk_611C60; // sub_629D00
    MC2_PROC<void>(0x00629DB0);
    new (&glo_6967C0) unk_4701A0; // sub_629E30
    new (&glo_69685C) unk_612850; std::atexit([]() { glo_69685C.~unk_612850(); }); // sub_629E60
    new (&glo_6968B8) unk_47BEA0; std::atexit([]() { glo_6968B8.~unk_47BEA0(); }); // sub_629E80
    new (&glo_697E24) unk_612850; std::atexit([]() { glo_697E24.~unk_612850(); }); // sub_629EE0
    MC2_PROC<void>(0x00629F00);
    MC2_PROC<void>(0x00629F20);
    MC2_PROC<void>(0x00629F40);
    MC2_PROC<void>(0x00629F60);
    MC2_PROC<void>(0x00629FD0);
    MC2_PROC<void>(0x00629FF0);
    MC2_PROC<void>(0x0062A020);
    new (&glo_6993A4) unk_611C60; // sub_62A090
    MC2_GLOBAL<std::uint8_t>(0x0069939E) = MC2_GLOBAL<std::uint8_t>(0x0085843E); // sub_62A0A0
    MC2_GLOBAL<std::uint8_t>(0x0069939D) = MC2_GLOBAL<std::uint8_t>(0x00858404); // sub_62A0B0
    MC2_GLOBAL<std::uint32_t>(0x006993A8) = MC2_GLOBAL<std::uint32_t>(0x008583F8); // sub_62A0C0
    new (&glo_69B6A0) unk_579410; std::atexit([]() { glo_69B6A0.~unk_579410(); }); // sub_62A160
    new (&glo_699890) unk_579410; std::atexit([]() { glo_699890.~unk_579410(); }); // sub_62A180
    new (&glo_6C2578) unk_515240; // sub_62A3E0
    new (&glo_6C32C8) unk_53AF00; // sub_62A410
    new (&glo_6C2E88) unk_53AF00; // sub_62A420
    new (&glo_Settings) Settings; // sub_62A430
    new (&glo_6C2C70) unk_53E8D0; // sub_62A440
    new (&glo_6C32C4) unk_5406A0; // sub_62A450
    new (&glo_6C3908) unk_546DA0; std::atexit([]() { glo_6C3908.~unk_546DA0(); }); // sub_62A460
    new (&glo_6C50F0) unk_612850; std::atexit([]() { glo_6C50F0.~unk_612850(); }); // sub_62A4A0
    new (&glo_6C5224) unk_612850; std::atexit([]() { glo_6C5224.~unk_612850(); }); // sub_62A540
    MC2_PROC<void>(0x0062A580);
    MC2_PROC<void>(0x0062A650);
    MC2_PROC<void>(0x0062A7E0);
    MC2_PROC<void>(0x0062AA80);
    MC2_PROC<void>(0x0062AE60);
    MC2_PROC<void>(0x0062B400);
    MC2_PROC<void>(0x0062BBB0);
    new (&glo_6C933C) unk_59D370; std::atexit([]() { glo_6C933C.~unk_59D370(); }); // sub_62C5D0
    new (&glo_6C93A8) unk_59D370; std::atexit([]() { glo_6C93A8.~unk_59D370(); }); // sub_62C610
    new (&glo_6CE228) unk_612850; std::atexit([]() { glo_6CE228.~unk_612850(); }); // sub_62C650
    MC2_PROC<void>(0x0062C690);
    new (&glo_6CE52C) unk_5D6A30; std::atexit([]() { glo_6CE52C.~unk_5D6A30(); }); // sub_62C6B0
    new (&glo_6CE520) unk_5D6A30; std::atexit([]() { glo_6CE520.~unk_5D6A30(); }); // sub_62C6D0
    new (&glo_6CE550) unk_5D6A30; std::atexit([]() { glo_6CE550.~unk_5D6A30(); }); // sub_62C6F0
    new (&glo_6CE544) unk_5D6A30; std::atexit([]() { glo_6CE544.~unk_5D6A30(); }); // sub_62C710
    new (&glo_6CE55C) unk_5D6A30; std::atexit([]() { glo_6CE55C.~unk_5D6A30(); }); // sub_62C730
    new (&glo_6CE538) unk_5D6A30; std::atexit([]() { glo_6CE538.~unk_5D6A30(); }); // sub_62C750
    new (&glo_6CE568) unk_5D6A30; std::atexit([]() { glo_6CE568.~unk_5D6A30(); }); // sub_62C770
    MC2_PROC<void>(0x0062C7A0);
    new (&glo_857850) unk_612850; std::atexit([]() { glo_857850.~unk_612850(); }); // sub_62C7E0
    new (&glo_857868) unk_612850; std::atexit([]() { glo_857868.~unk_612850(); }); // sub_62C800
    new (&glo_858288) unk_612850; std::atexit([]() { glo_858288.~unk_612850(); }); // sub_62C870
    new (&glo_8582AC) unk_612850; std::atexit([]() { glo_8582AC.~unk_612850(); }); // sub_62C8B0
    new (&glo_8582C8) unk_5E14C0; // sub_62C8D0
    MC2_PROC<void>(0x0062C8F0);
    new (&glo_858358) unk_611C60; // sub_62C900
    new (&glo_85835C) unk_611C60; // sub_62C910
    new (&glo_858354) unk_611C60; // sub_62C920
    new (&glo_858500) unk_5FB2E0; // sub_62C930
    new (&glo_858608) unk_5EDA70; // sub_62C940
    new (&glo_8586B8) unk_612850; std::atexit([]() { glo_8586B8.~unk_612850(); }); // sub_62C950
    new (&glo_85ADDC) unk_612850; std::atexit([]() { glo_85ADDC.~unk_612850(); }); // sub_62C970
    new (&glo_85AE60) unk_612850; std::atexit([]() { glo_85AE60.~unk_612850(); }); // sub_62C990
    new (&glo_pal_cmdline) cmdline_info(0, "pal", "Force PAL mode"); // sub_62C9D0
    new (&glo_85D400) unk_602740; std::atexit([]() { glo_85D400.~unk_602740(); }); // sub_62CA30
    MC2_PROC<void>(0x0062CA50);
    new (&glo_8600F8) unk_612850; std::atexit([]() { glo_8600F8.~unk_612850(); }); // sub_62CA80
    new (&glo_8602FC) unk_611C60; // sub_62CAB0
    new (&glo_860608) unk_614370; // sub_62CAC0
    MC2_PROC<void>(0x0062CAD0);
    new (&glo_860300) unk_6144B0(loc_860308, 32); // sub_62CAF0
    MC2_PROC<void>(0x0062CB10);
    new (&glo_860618) unk_6144B0(loc_860508, 16); // sub_62CAF0
    std::atexit([]() { sub_617AA0(); }); // sub_62CB50
};

static int(__cdecl *const xi[])() = {
    &MC2_PROC_PTR<int>(0x0061A77F), // ___onexitinit
    &MC2_PROC_PTR<int>(0x0061B21E), // ___inittime
    &MC2_PROC_PTR<int>(0x0061BB72), // ___initstdio
    &MC2_PROC_PTR<int>(0x0061C002), // ___initmbctable
    &test_sse2,
    &MC2_PROC_PTR<int>(0x0061EED2), // __CxxSetUnhandledExceptionFilter(void)
};

int mc2_cinit() {
    mc2__FPinit_proc();

    for (int(__cdecl *x)() : xi) {
        int ret = x();
        if (ret != 0) return ret;
    }

    mc2_xc();

    return 0;
}
