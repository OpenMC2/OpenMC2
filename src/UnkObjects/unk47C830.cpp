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

MC2_DEF_GLOBAL(glo_697B88, 0x00697B88);
