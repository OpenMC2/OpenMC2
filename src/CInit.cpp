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

#define mc2__FPinit_proc MC2_PROC_PTR<void>(0x006193B7)

static void init_2sqrt_constant() {
    // A ton of variables are initialized to the
    // same value, so I've combined them all here
    static float *const vars[] = {
        &MC2_GLOBAL<float>(0x00692E80), // sub_629D10
        &MC2_GLOBAL<float>(0x00692EAC), // sub_629D30
        &MC2_GLOBAL<float>(0x00692EBC), // sub_629D50
        &MC2_GLOBAL<float>(0x00692EC4), // sub_629D70
        &MC2_GLOBAL<float>(0x00692EC8), // sub_629D90
        &MC2_GLOBAL<float>(0x00696764), // sub_629DF0
        &MC2_GLOBAL<float>(0x006967B0), // sub_629E10
        &MC2_GLOBAL<float>(0x00696850), // sub_629E40
        &MC2_GLOBAL<float>(0x00697B8C), // sub_629EA0
        &MC2_GLOBAL<float>(0x00697C18), // sub_629EC0
        &MC2_GLOBAL<float>(0x00698490), // sub_629F90
        &MC2_GLOBAL<float>(0x00698620), // sub_629FB0
        &MC2_GLOBAL<float>(0x0069910C), // sub_62A050
        &MC2_GLOBAL<float>(0x006993A0), // sub_62A070
        &MC2_GLOBAL<float>(0x0069948C), // sub_62A0D0
        &MC2_GLOBAL<float>(0x00699690), // sub_62A0F0
        &MC2_GLOBAL<float>(0x0069B5F8), // sub_62A110
        &MC2_GLOBAL<float>(0x0069B78C), // sub_62A260
        &MC2_GLOBAL<float>(0x0069C7A8), // sub_62A280
        &MC2_GLOBAL<float>(0x0069C7AC), // sub_62A2A0
        &MC2_GLOBAL<float>(0x0069C7B0), // sub_62A2C0
        &MC2_GLOBAL<float>(0x0069C7B4), // sub_62A2E0
        &MC2_GLOBAL<float>(0x0069C7BC), // sub_62A300
        &MC2_GLOBAL<float>(0x0069C7C0), // sub_62A320
        &MC2_GLOBAL<float>(0x0069C7C4), // sub_62A340
        &MC2_GLOBAL<float>(0x0069C7C8), // sub_62A360
        &MC2_GLOBAL<float>(0x0069C7CC), // sub_62A380
        &MC2_GLOBAL<float>(0x0069C7D8), // sub_62A3A0
        &MC2_GLOBAL<float>(0x0069C7E0), // sub_62A3C0
        &MC2_GLOBAL<float>(0x006C2600), // sub_62A3F0
        &MC2_GLOBAL<float>(0x006C521C), // sub_62A500
    };

    for (float *v : vars) *v = 7.136496544f; // 2 * sqrt(12.732395)
}

static void(__cdecl *const xc[])() = {
    &MC2_PROC_PTR<void>(0x00625D30), // ___security_init_cookie
    &init_2sqrt_constant,
    &MC2_PROC_PTR<void>(0x00629D00),
    &MC2_PROC_PTR<void>(0x00629DB0),
    &MC2_PROC_PTR<void>(0x00629E30),
    &MC2_PROC_PTR<void>(0x00629E60),
    &MC2_PROC_PTR<void>(0x00629E80),
    &MC2_PROC_PTR<void>(0x00629EE0),
    &MC2_PROC_PTR<void>(0x00629F00),
    &MC2_PROC_PTR<void>(0x00629F20),
    &MC2_PROC_PTR<void>(0x00629F40),
    &MC2_PROC_PTR<void>(0x00629F60),
    &MC2_PROC_PTR<void>(0x00629FD0),
    &MC2_PROC_PTR<void>(0x00629FF0),
    &MC2_PROC_PTR<void>(0x0062A020),
    &MC2_PROC_PTR<void>(0x0062A090),
    &MC2_PROC_PTR<void>(0x0062A0A0),
    &MC2_PROC_PTR<void>(0x0062A0B0),
    &MC2_PROC_PTR<void>(0x0062A0C0),
    &MC2_PROC_PTR<void>(0x0062A130),
    &MC2_PROC_PTR<void>(0x0062A140),
    &MC2_PROC_PTR<void>(0x0062A160),
    &MC2_PROC_PTR<void>(0x0062A180),
    &MC2_PROC_PTR<void>(0x0062A1A0),
    &MC2_PROC_PTR<void>(0x0062A1B0),
    &MC2_PROC_PTR<void>(0x0062A1C0),
    &MC2_PROC_PTR<void>(0x0062A1D0),
    &MC2_PROC_PTR<void>(0x0062A1E0),
    &MC2_PROC_PTR<void>(0x0062A1F0),
    &MC2_PROC_PTR<void>(0x0062A200),
    &MC2_PROC_PTR<void>(0x0062A210),
    &MC2_PROC_PTR<void>(0x0062A220),
    &MC2_PROC_PTR<void>(0x0062A240),
    &MC2_PROC_PTR<void>(0x0062A250),
    &MC2_PROC_PTR<void>(0x0062A3E0),
    &MC2_PROC_PTR<void>(0x0062A410),
    &MC2_PROC_PTR<void>(0x0062A420),
    &MC2_PROC_PTR<void>(0x0062A430),
    &MC2_PROC_PTR<void>(0x0062A440),
    &MC2_PROC_PTR<void>(0x0062A450),
    &MC2_PROC_PTR<void>(0x0062A460),
    &MC2_PROC_PTR<void>(0x0062A480),
    &MC2_PROC_PTR<void>(0x0062A490),
    &MC2_PROC_PTR<void>(0x0062A4A0),
    &MC2_PROC_PTR<void>(0x0062A4C0),
    &MC2_PROC_PTR<void>(0x0062A4E0),
    &MC2_PROC_PTR<void>(0x0062A520),
    &MC2_PROC_PTR<void>(0x0062A540),
    &MC2_PROC_PTR<void>(0x0062A560),
    &MC2_PROC_PTR<void>(0x0062A580),
    &MC2_PROC_PTR<void>(0x0062A650),
    &MC2_PROC_PTR<void>(0x0062A7E0),
    &MC2_PROC_PTR<void>(0x0062AA80),
    &MC2_PROC_PTR<void>(0x0062AE60),
    &MC2_PROC_PTR<void>(0x0062B400),
    &MC2_PROC_PTR<void>(0x0062BBB0),
    &MC2_PROC_PTR<void>(0x0062C580),
    &MC2_PROC_PTR<void>(0x0062C590),
    &MC2_PROC_PTR<void>(0x0062C5B0),
    &MC2_PROC_PTR<void>(0x0062C5D0),
    &MC2_PROC_PTR<void>(0x0062C5F0),
    &MC2_PROC_PTR<void>(0x0062C610),
    &MC2_PROC_PTR<void>(0x0062C630),
    &MC2_PROC_PTR<void>(0x0062C650),
    &MC2_PROC_PTR<void>(0x0062C670),
    &MC2_PROC_PTR<void>(0x0062C690),
    &MC2_PROC_PTR<void>(0x0062C6B0),
    &MC2_PROC_PTR<void>(0x0062C6D0),
    &MC2_PROC_PTR<void>(0x0062C6F0),
    &MC2_PROC_PTR<void>(0x0062C710),
    &MC2_PROC_PTR<void>(0x0062C730),
    &MC2_PROC_PTR<void>(0x0062C750),
    &MC2_PROC_PTR<void>(0x0062C770),
    &MC2_PROC_PTR<void>(0x0062C790),
    &MC2_PROC_PTR<void>(0x0062C7A0),
    &MC2_PROC_PTR<void>(0x0062C7D0),
    &MC2_PROC_PTR<void>(0x0062C7E0),
    &MC2_PROC_PTR<void>(0x0062C800),
    &MC2_PROC_PTR<void>(0x0062C820),
    &MC2_PROC_PTR<void>(0x0062C840),
    &MC2_PROC_PTR<void>(0x0062C850),
    &MC2_PROC_PTR<void>(0x0062C870),
    &MC2_PROC_PTR<void>(0x0062C890),
    &MC2_PROC_PTR<void>(0x0062C8B0),
    &MC2_PROC_PTR<void>(0x0062C8D0),
    &MC2_PROC_PTR<void>(0x0062C8F0),
    &MC2_PROC_PTR<void>(0x0062C900),
    &MC2_PROC_PTR<void>(0x0062C910),
    &MC2_PROC_PTR<void>(0x0062C920),
    &MC2_PROC_PTR<void>(0x0062C930),
    &MC2_PROC_PTR<void>(0x0062C940),
    &MC2_PROC_PTR<void>(0x0062C950),
    &MC2_PROC_PTR<void>(0x0062C970),
    &MC2_PROC_PTR<void>(0x0062C990),
    &MC2_PROC_PTR<void>(0x0062C9B0),
    &MC2_PROC_PTR<void>(0x0062C9D0),
    &MC2_PROC_PTR<void>(0x0062C9F0),
    &MC2_PROC_PTR<void>(0x0062CA10),
    &MC2_PROC_PTR<void>(0x0062CA30),
    &MC2_PROC_PTR<void>(0x0062CA50),
    &MC2_PROC_PTR<void>(0x0062CA80),
    &MC2_PROC_PTR<void>(0x0062CAA0),
    &MC2_PROC_PTR<void>(0x0062CAB0),
    &MC2_PROC_PTR<void>(0x0062CAC0),
    &MC2_PROC_PTR<void>(0x0062CAD0),
    &MC2_PROC_PTR<void>(0x0062CAF0),
    &MC2_PROC_PTR<void>(0x0062CB10),
    &MC2_PROC_PTR<void>(0x0062CB30),
    &MC2_PROC_PTR<void>(0x0062CB50),
};

static int(__cdecl *const xi[])() = {
    &MC2_PROC_PTR<int>(0x0061A77F), // ___onexitinit
    &MC2_PROC_PTR<int>(0x0061B21E), // ___inittime
    &MC2_PROC_PTR<int>(0x0061BB72), // ___initstdio
    &MC2_PROC_PTR<int>(0x0061C002), // ___initmbctable
    &MC2_PROC_PTR<int>(0x0062032A), // Check for SSE2?
    &MC2_PROC_PTR<int>(0x0061EED2), // __CxxSetUnhandledExceptionFilter(void)
};

int mc2_cinit() {
    mc2__FPinit_proc();

    for (int(__cdecl *x)() : xi) {
        int ret = x();
        if (ret != 0) return ret;
    }

    for (void(__cdecl *x)() : xc) x();

    return 0;
}
