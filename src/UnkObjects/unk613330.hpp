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

#pragma once

#include "../Addresses.hpp"

class unk_613330 {
public:
    struct unk_613330_vTable{
        void (__thiscall *vir_00)(unk_613330 *);
        void (__thiscall *vir_04)(unk_613330 *);
        void (__thiscall *vir_08)(unk_613330 *);
        void (__thiscall *vir_0C)(unk_613330 *);
        void (__thiscall *vir_10)(unk_613330 *);
        void (__thiscall *vir_14)(unk_613330 *);
        void (__thiscall *vir_18)(unk_613330 *);
        void (__thiscall unk_613330::* vir_1C)(char* unk1, char* unk2, int32_t unk3, int32_t unk4);
        void (__thiscall *vir_20)(unk_613330 *);
        void (__thiscall *vir_24)(unk_613330 *);
        void (__thiscall *vir_28)(unk_613330 *);
    };
protected:
    void *vtable;
public:
    unk_613330();
    
    void __thiscall impl_1C(char* unk1, char* unk2, int32_t unk3, int32_t unk4); //0x1C

    inline void vir_00() {
        static_cast<unk_613330_vTable*>(vtable)->vir_00(this);
    }
    inline void vir_04(){
        static_cast<unk_613330_vTable*>(vtable)->vir_04(this);
    }
    inline void vir_08(){
        static_cast<unk_613330_vTable*>(vtable)->vir_08(this);
    }
    inline void vir_0C(){
        static_cast<unk_613330_vTable*>(vtable)->vir_0C(this);
    }
    inline void vir_10(){
        static_cast<unk_613330_vTable*>(vtable)->vir_10(this);
    }
    inline void vir_14(){
        static_cast<unk_613330_vTable*>(vtable)->vir_14(this);
    }
    inline void vir_18(){
        static_cast<unk_613330_vTable*>(vtable)->vir_18(this);
    }
    inline void vir_1C(char* unk1, char* unk2, int32_t unk3, int32_t unk4){
        (this->*static_cast<unk_613330_vTable*>(vtable)->vir_1C)(unk1, unk2, unk3, unk4);
    }
    inline void vir_20(){
        static_cast<unk_613330_vTable*>(vtable)->vir_20(this);
    }
    inline void vir_24(){
        static_cast<unk_613330_vTable*>(vtable)->vir_24(this);
    }
    inline void vir_28(){
        static_cast<unk_613330_vTable*>(vtable)->vir_28(this);
    }
};

#define glo_860220 (MC2_GLOBAL<unk_613330*>(0x00860220))