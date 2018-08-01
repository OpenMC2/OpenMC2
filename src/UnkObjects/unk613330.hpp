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

class unk_613330;
extern unk_613330 *&glo_860220;

class unk_613330 {
protected:
    struct vtable_t{
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void, char *, std::uint32_t, char *, char *> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<void, void> vir_18;
        MC2_PROC_MEMBER_PTR<FileHandler *, void, char *, char *, std::uint32_t, bool> vir_1C;
        MC2_PROC_MEMBER_PTR<FileHandler *, void, char *, char *, std::uint32_t> vir_20;
        MC2_PROC_MEMBER_PTR<bool, void, char *> vir_24;
        MC2_PROC_MEMBER_PTR<void, void, char *, const char *, const char *> vir_28;
    };
private:
    static const vtable_t vtable_values;

protected:
    const void *vtable;

protected:
    unk_613330() { vtable = &vtable_values; glo_860220 = this; }
public:
    // mc2: 0x00613340
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_613330) { glo_860220 = nullptr; }
    
    FileHandler *impl_1C(char *unk1, char *unk2, std::uint32_t unk3, bool extension); //0x1C
    FileHandler *impl_20(char *unk1, char *unk2, std::uint32_t unk3); // 0x20
    bool impl_24(char *unk1); //0x24
    void impl_28(char *destination, const char *unk2, const char *extension); //0x28

    void vir_04(char *destination, std::uint32_t unk2, char *unk3, char *unk4){
        return static_cast<const vtable_t *>(vtable)->vir_04(this, destination, unk2, unk3, unk4);
    }
    void vir_08(){
        return static_cast<const vtable_t *>(vtable)->vir_08(this);
    }
    void vir_0C(){
        return static_cast<const vtable_t *>(vtable)->vir_0C(this);
    }
    void vir_10(){
        return static_cast<const vtable_t *>(vtable)->vir_10(this);
    }
    void vir_14(){
        return static_cast<const vtable_t *>(vtable)->vir_14(this);
    }
    void vir_18(){
        return static_cast<const vtable_t *>(vtable)->vir_18(this);
    }
    FileHandler *vir_1C(char* unk1, char* unk2, std::uint32_t unk3, bool extension){
        return static_cast<const vtable_t *>(vtable)->vir_1C(this, unk1, unk2, unk3, extension);
    }
    FileHandler *vir_20(char* unk1, char* unk2, std::uint32_t unk3){
        return static_cast<const vtable_t *>(vtable)->vir_20(this, unk1, unk2, unk3);
    }
    bool vir_24(char *unk1){
        return static_cast<const vtable_t *>(vtable)->vir_24(this, unk1);
    }
    void vir_28(char *destination, const char *unk2, const char *extension){
        return static_cast<const vtable_t *>(vtable)->vir_28(this, destination, unk2, extension);
    }
};
static_assert(sizeof(unk_613330) == 4, "Bad Size: unk_613330");
