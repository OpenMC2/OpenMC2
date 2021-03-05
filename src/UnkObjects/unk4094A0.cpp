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

#include "unk4094A0.hpp"
#include "unk5769E0.hpp"

#include "../Logging.hpp"
#include "../mcLayerMgr.hpp"

// mc2: 0x0062ED8C
const unk_4094A0_p::vtable_t unk_4094A0_p::vtable_values = {
    &unk_4094A0_p::scalar_deleter,
    &unk_4094A0_p::impl_is_loaded,
    &unk_4094A0_p::impl_load,
    &unk_4094A0_p::impl_unload,
    &unk_4094A0_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &mc2_thiscall::pure<const char *>,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x00408FD0
void unk_4094A0_p::impl_load() {
    if (glo_6622BC > 0) {
        mc2_log_display("mcLayer:Load - heap sanity check");
        global_primary_unk5769E0->sub_576210();
        mc2_log_display(" - done");
    }
    loaded = true;
}

// mc2: 0x004091B0
void unk_4094A0_p::impl_unload() {
    loaded = false;
    if (glo_6622BC > 0) {
        mc2_log_display("mcLayer:Unload - heap sanity check");
        global_primary_unk5769E0->sub_576210();
        mc2_log_display(" - done");
    }
}

// mc2: 0x004091E0
void unk_4094A0_p::impl_reload() {
    mc2_log_error("mcLayer::Reload() - not implemented");
}

// mc2: 0x0062F7C4
const unk_40AE70_p::vtable_t unk_40AE70_p::vtable_values = {
    &unk_40AE70_p::scalar_deleter,
    &unk_40AE70_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x0040B480),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040B9E0),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040AFA0),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_40AE70_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F740
const unk_40AB30_p::vtable_t unk_40AB30_p::vtable_values = {
    &unk_40AB30_p::scalar_deleter,
    &unk_40AB30_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x0040ABB0),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040AB70),
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_40AB30_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F708
const unk_40A940_p::vtable_t unk_40A940_p::vtable_values = {
    &unk_40A940_p::scalar_deleter,
    &unk_40A940_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x0040A980),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040AAC0),
    &unk_40A940_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_40A940_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F5B0
const unk_40A4A0_p::vtable_t unk_40A4A0_p::vtable_values = {
    &unk_40A4A0_p::scalar_deleter,
    &unk_40A4A0_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x0040A4E0),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040A830),
    &unk_40A4A0_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_40A4A0_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F3E4
const unk_409ED0_p::vtable_t unk_409ED0_p::vtable_values = {
    &unk_409ED0_p::scalar_deleter,
    &unk_409ED0_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409F10),
    MC2_PROC_MEMBER_PTR<void, void>(0x0040A2F0),
    &unk_409ED0_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_409ED0_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F370
const unk_409DF0_p::vtable_t unk_409DF0_p::vtable_values = {
    &unk_409DF0_p::scalar_deleter,
    &unk_409DF0_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409E30),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409E80),
    &unk_409DF0_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_409DF0_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F278
const unk_409A70_p::vtable_t unk_409A70_p::vtable_values = {
    &unk_409A70_p::scalar_deleter,
    &unk_409A70_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409AC0),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409BD0),
    &unk_409A70_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_409A70_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F334
const unk_409CF0_p::vtable_t unk_409CF0_p::vtable_values = {
    &unk_409CF0_p::scalar_deleter,
    &unk_409CF0_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409D30),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409DA0),
    &unk_409CF0_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_409CF0_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};

// mc2: 0x0062F2F0
const unk_409C50_p::vtable_t unk_409C50_p::vtable_values = {
    &unk_409C50_p::scalar_deleter,
    &unk_409C50_p::impl_is_loaded,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409C90),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409CC0),
    &unk_409C50_p::impl_reload,
    MC2_PROC_MEMBER_PTR<void, void>(0x00409000),
    MC2_PROC_MEMBER_PTR<void, void>(0x00409080),
    &unk_409C50_p::impl_vir1C,
    &mc2_thiscall::null<>,
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t>(0x004094D0),
    MC2_PROC_MEMBER_PTR<void, void, std::uint32_t>(0x004091F0),
};
