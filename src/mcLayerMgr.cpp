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

#include "mcLayerMgr.hpp"

#include "UnkObjects/unk612850.hpp"

const mcLayerMgr_p::vtable_t mcLayerMgr_p::vtable_values = {
    &mcLayerMgr_p::scalar_deleter,
};

// mc2: 0x00402800
mcLayerMgr_p::mcLayerMgr_p() : ptrs(ptrs_init()) {
    vtable = &vtable_values;
    sub_612E30("layerDebug", 0, &glo_6622B8);
    sub_612E30("layerHeapSanity", 0, &glo_6622BC);
}

// mc2: 0x004029d0
void mcLayerMgr_p::destructor() {
    vtable = &vtable_values;
    sub_402970();
    // call member destructors
    unk118.destroy();
    unk104.destroy();
    unkE8.destroy();
    unkD4.destroy();
    unkB8.destroy();
    unk94.destroy();
    unk78.destroy();
    unk5C.destroy();
    unk28.destroy();
}

std::array<unk_4094A0 *, 9> mcLayerMgr_p::ptrs_init() {
    return {
        class_cast<unk_4094A0>(&unk28),
        class_cast<unk_4094A0>(&unk5C),
        class_cast<unk_4094A0>(&unk78),
        class_cast<unk_4094A0>(&unk94),
        class_cast<unk_4094A0>(&unkB8),
        class_cast<unk_4094A0>(&unkD4),
        class_cast<unk_4094A0>(&unkE8),
        class_cast<unk_4094A0>(&unk104),
        class_cast<unk_4094A0>(&unk118),
    };
}

bool mcLayerMgr_p::ptrs_verify() {
    return this->ptrs == ptrs_init();
}

MC2_DEF_GLOBAL(glo_6622B8, 0x006622B8);
MC2_DEF_GLOBAL(glo_6622BC, 0x006622BC);
MC2_DEF_GLOBAL(glo_692E88, 0x00692E88);

AUTO_HOOK_MEMBER_X86(0x004025C0, &mcLayerMgr::sub_4025C0);
