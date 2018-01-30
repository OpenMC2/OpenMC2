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

#include "unk860688.hpp"

unk_860688::unk_860688(std::array<char, 4> signature, void(__cdecl *callback)(void *)) :
    signature(signature), callback(callback) {
    next = glo_860688;
    glo_860688 = this;
}

unk_860688 glo_673E3C({ 'V', 'B', 'N', '0' }, &MC2_PROC_PTR<void, void *>(0x0056CDE0));
unk_860688 glo_673EE0({ 'P', 'I', 'V', '0' }, [](void *) { });
unk_860688 glo_674100({ 'B', 'N', 'D', '0' }, &MC2_PROC_PTR<void, void *>(0x0059E510));
unk_860688 glo_6743E4({ 'P', 'M', 'T', '0' }, &MC2_PROC_PTR<void, void *>(0x005D2850));
unk_860688 glo_674580({ 'A', 'N', 'I', '0' }, &MC2_PROC_PTR<void, void *>(0x005DD1C0));
unk_860688 glo_674590({ 'S', 'K', 'E', '0' }, &MC2_PROC_PTR<void, void *>(0x005DED50));
unk_860688 glo_6745AC({ 'F', 'N', 'T', '0' }, &MC2_PROC_PTR<void, void *>(0x005E0F70));
unk_860688 glo_675494({ 'M', 'I', 'P', '0' }, &MC2_PROC_PTR<void, void *>(0x005F5520));
unk_860688 glo_675508({ 'T', 'E', 'X', '0' }, &MC2_PROC_PTR<void, void *>(0x005FA060));
unk_860688 glo_6781B0({ 'P', 'A', 'L', '0' }, &MC2_PROC_PTR<void, void *>(0x005FC400));

unk_860688 *&glo_860688 = MC2_GLOBAL<unk_860688 *>(0x00860688);
