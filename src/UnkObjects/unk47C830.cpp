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

#include "unk47C830.hpp"

#include "unk404B90.hpp"
#include "unk47DFB0.hpp"
#include "unk52AA80.hpp"
#include "unk53AF00.hpp"

// mc2: 0x0063E7CC
const unk_47C830::vtable_t unk_47C830::vtable_values = {
    &unk_47C830::scalar_deleter,
};

unk_47C830::unk_47C830() {
    vtable = &vtable_values;
    sub_5E11E0("popup", 0);
    this->unk08 = new unk_5D5C30("HUD:accept");
    this->unk08->sub_5D5800(glo_6CE2E4);
    this->sub_47BFF0();
}

void unk_47C830::sub_47BFF0() {
    switch (glo_6C32C8.unk18) {
    case RaceType::roam:
    case RaceType::hookman_cruise:
    case RaceType::follow:
        this->unk04 = new unk_496BF0;
        break;
    case RaceType::find_hook:
        this->unk04 = new unk_496B30(glo_6C32C8.unk338);
        break;
    case RaceType::cp_unordered:
    case RaceType::cp_unordered_time_local:
    case RaceType::cp_unordered_time_global:
    case RaceType::cp_ordered:
    case RaceType::cp_ordered_time_local:
    case RaceType::cp_ordered_time_global:
        this->unk04 = new unk_48C470(glo_6C32C8.unk18);
        break;
    case RaceType::capture_the_flag:
        this->unk04 = new unk_48F9F0;
        break;
    case RaceType::bomb_tag:
        this->unk04 = new unk_48D540;
        break;
    case RaceType::lose_the_cops:
        this->unk04 = new unk_495510;
        break;
    case RaceType::destroy:
        this->unk04 = new unk_4951A0;
        break;
    default:
        break;
    }
}

void unk_47C830::sub_47C7A0() {
    if (glo_6C3890->unk09 == 0) this->unk04->vir14();
    if (glo_697B90->unk54->unk178 != 6) {
        this->sub_47C3C0();
        this->sub_47C5E0();
    }
    if (glo_6C3890->unk09 == 0) {
        this->unk04->vir18();
        this->unk04->sub_485530();
    }
}

MC2_DEF_PROC(sub_5E11E0, 0x005E11E0);

MC2_DEF_GLOBAL(glo_697B88, 0x00697B88);
