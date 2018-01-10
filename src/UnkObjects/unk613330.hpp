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

class FileHandler;

class unk_613330 {
private:
    struct vtable_t{
        mc2_proc_thiscall_ptr<void, unk_613330> vir_00;
        mc2_proc_thiscall_ptr<void, unk_613330, char *, std::uint32_t, char *, char *> vir_04;
        mc2_proc_thiscall_ptr<void, unk_613330> vir_08;
        mc2_proc_thiscall_ptr<void, unk_613330> vir_0C;
        mc2_proc_thiscall_ptr<void, unk_613330> vir_10;
        mc2_proc_thiscall_ptr<void, unk_613330> vir_14;
        mc2_proc_thiscall_ptr<void, unk_613330> vir_18;
        mc2_proc_thiscall_ptr<FileHandler *, unk_613330, char *, char *, std::uint32_t, bool> vir_1C;
        mc2_proc_thiscall_ptr<FileHandler *, unk_613330, char *, char *, std::uint32_t> vir_20;
        mc2_proc_thiscall_ptr<bool, unk_613330, char *> vir_24;
        mc2_proc_thiscall_ptr<void, unk_613330, char *, const char *, const char *> vir_28;
    };
    static vtable_t vtable_values;

protected:
    void *vtable;

public:
    unk_613330();
    
    FileHandler *__thiscall impl_1C(char *unk1, char *unk2, std::uint32_t unk3, bool extension); //0x1C
    FileHandler *__thiscall impl_20(char *unk1, char *unk2, std::uint32_t unk3); // 0x20
    bool __thiscall impl_24(char *unk1); //0x24
    void __thiscall impl_28(char *destination, const char *unk2, const char *extension); //0x28

    inline void vir_00() {
        static_cast<vtable_t*>(vtable)->vir_00(this);
    }
    inline void vir_04(char *destination, std::uint32_t unk2, char *unk3, char *unk4){
        static_cast<vtable_t*>(vtable)->vir_04(this, destination, unk2, unk3, unk4);
    }
    inline void vir_08(){
        static_cast<vtable_t*>(vtable)->vir_08(this);
    }
    inline void vir_0C(){
        static_cast<vtable_t*>(vtable)->vir_0C(this);
    }
    inline void vir_10(){
        static_cast<vtable_t*>(vtable)->vir_10(this);
    }
    inline void vir_14(){
        static_cast<vtable_t*>(vtable)->vir_14(this);
    }
    inline void vir_18(){
        static_cast<vtable_t*>(vtable)->vir_18(this);
    }
    inline FileHandler *vir_1C(char* unk1, char* unk2, std::uint32_t unk3, bool extension){
        return static_cast<vtable_t*>(vtable)->vir_1C(this, unk1, unk2, unk3, extension);
    }
    inline FileHandler *vir_20(char* unk1, char* unk2, std::uint32_t unk3) {
        return static_cast<vtable_t*>(vtable)->vir_20(this, unk1, unk2, unk3);
    }
    inline bool vir_24(char *unk1) {
        return static_cast<vtable_t*>(vtable)->vir_24(this, unk1);
    }
    inline void vir_28(char *destination, const char *unk2, const char *extension) {
        return static_cast<vtable_t*>(vtable)->vir_28(this, destination, unk2, extension);
    }
};

static_assert(sizeof(unk_613330) == 4, "Bad Size: unk_613330");

constexpr mc2_pointer<0x00860220, unk_613330 *> loc_860220;
