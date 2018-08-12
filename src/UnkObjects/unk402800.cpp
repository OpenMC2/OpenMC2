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

#include "unk402800.hpp"
#include "unk612850.hpp"

const unk_402800::vtable_t unk_402800::vtable_values = {
    &unk_402800::scalar_deleter,
};

unk_402800::unk_402800() : ptrs(ptrs_init()),
unk28(), unk5C(), unk78(),
unk94(), unkB8(), unkD4(),
unkE8(), unk104(), unk118() {
    vtable = &vtable_values;
    sub_612E30("layerDebug", 0, &glo_6622B8);
    sub_612E30("layerHeapSanity", 0, &glo_6622BC);
}

void unk_402800::destructor() {
    sub_402970();
    // call member destructors
    unk118.~unk_409C50();
    unk104.~unk_409CF0();
    unkE8.~unk_409A70();
    unkD4.~unk_409DF0();
    unkB8.~unk_409ED0();
    unk94.~unk_40A4A0();
    unk78.~unk_40A940();
    unk5C.~unk_40AB30();
    unk28.~unk_40AE70();
}

std::array<unk_4094A0 *, 9> unk_402800::ptrs_init() {
    return {
        &unk28, &unk5C, &unk78,
        &unk94, &unkB8, &unkD4,
        &unkE8, &unk104, &unk118,
    };
}

bool unk_402800::ptrs_verify() {
    return this->ptrs == ptrs_init();
}

MC2_DEF_GLOBAL(glo_6622B8, 0x006622B8);
MC2_DEF_GLOBAL(glo_6622BC, 0x006622BC);
MC2_DEF_GLOBAL(glo_692E88, 0x00692E88);

AUTO_HOOK_MEMBER_X86(0x004025C0, &unk_402800::sub_4025C0);
