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

#include "unk41FB40.hpp"

// originally malloc'd in layermgr.c
// originally called "mcLayer"?
class unk_4094A0 {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<bool, void> is_loaded; // 0x04
        MC2_PROC_MEMBER_PTR<void, void> load; // 0x08
        MC2_PROC_MEMBER_PTR<void, void> unload; // 0x0C
        MC2_PROC_MEMBER_PTR<void, void> reload; // 0x10
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<void, void> post_unload; // 0x18
        MC2_PROC_MEMBER_PTR<const char *, void> vir_1C;
        MC2_PROC_MEMBER_PTR<void, void> vir_20;
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t> display_loading_screen; // 0x24
        MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> post_loading_screen; // 0x28
    };
    static const vtable_t vtable_values;

protected:
    const void *vtable;
    bool loaded = false;
    std::uint8_t pad05[0x03];
    std::uint32_t unk08;
    std::uint32_t unk0C;
    std::uint32_t unk10;

protected:
    unk_4094A0() { vtable = &vtable_values; }
public:
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_4094A0) { }

    bool is_loaded() /* vir04 */ {
        return static_cast<const vtable_t *>(this->vtable)->is_loaded(this);
    }
    void load() /* vir08 */ {
        return static_cast<const vtable_t *>(this->vtable)->load(this);
    }
    void unload() /* vir0C */ {
        return static_cast<const vtable_t *>(this->vtable)->unload(this);
    }
    void reload() /* vir10 */ {
        return static_cast<const vtable_t *>(this->vtable)->reload(this);
    }
    void vir14() {
        return static_cast<const vtable_t *>(this->vtable)->vir_14(this);
    }
    void post_unload() /* vir18 */ {
        return static_cast<const vtable_t *>(this->vtable)->post_unload(this);
    }
    const char *vir1C() {
        return static_cast<const vtable_t *>(this->vtable)->vir_1C(this);
    }
    void vir20() {
        return static_cast<const vtable_t *>(this->vtable)->vir_20(this);
    }
    void display_loading_screen(std::uint32_t arg0, std::uint32_t arg1) /* vir24 */ {
        return static_cast<const vtable_t *>(this->vtable)->display_loading_screen(this, arg0, arg1);
    }
    void post_loading_screen(std::uint32_t arg0) /* vir28 */ {
        return static_cast<const vtable_t *>(this->vtable)->post_loading_screen(this, arg0);
    }

protected:
    // mc2: 0x00408FC0
    bool impl_is_loaded() { return loaded; }
    void impl_load();
    void impl_unload();
    void impl_reload();
};
static_assert(sizeof(unk_4094A0) == 0x14, "Wrong size for unk_4094A0");

class unk_40AE70 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;
    std::uint32_t unk1C = 0;
    std::uint32_t unk20 = 0;
    std::uint32_t unk24 = 0;
    std::uint32_t unk28 = 0;
    std::uint32_t unk2C = 0;
    std::uint32_t unk30 = 0;

public:
    unk_40AE70() { vtable = &vtable_values; }
protected:
    const char *impl_vir1C() { return "city"; }

};
static_assert(sizeof(unk_40AE70) == 0x34, "Wrong size for unk_40AE70");

class unk_40AB30 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;

public:
    unk_40AB30() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "cpvs"; }
};
static_assert(sizeof(unk_40AB30) == 0x1C, "Wrong size for unk_40AB30");

class unk_40A940 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;

public:
    unk_40A940() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "conditions"; }
};
static_assert(sizeof(unk_40A940) == 0x1C, "Wrong size for unk_40A940");

class unk_40A4A0 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;
    std::uint32_t unk1C = 0;
    std::uint32_t unk20 = 0;

public:
    unk_40A4A0() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "ambients"; }
};
static_assert(sizeof(unk_40A4A0) == 0x24, "Wrong size for unk_40A4A0");

class unk_409ED0 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint8_t pad18[0x04];

public:
    unk_409ED0() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "race"; }
};
static_assert(sizeof(unk_409ED0) == 0x1C, "Wrong size for unk_409ED0");

class unk_409DF0 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

public:
    unk_409DF0() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "movie"; }
};
static_assert(sizeof(unk_409DF0) == 0x14, "Wrong size for unk_409DF0");

class unk_409A70 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

public:
    unk_41FB40 *unk14 = 0;
    std::uint32_t unk18 = 0;

public:
    unk_409A70() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_409A70) { delete unk14; }

protected:
    const char *impl_vir1C() { return "frontend"; }
};
static_assert(sizeof(unk_409A70) == 0x1C, "Wrong size for unk_409A70");

class unk_409CF0 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

public:
    unk_409CF0() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "race editor"; }
};
static_assert(sizeof(unk_409CF0) == 0x14, "Wrong size for unk_409CF0");

class unk_409C50 : public unk_4094A0 {
protected:
    static const vtable_t vtable_values;

public:
    unk_409C50() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "carviewer"; }
};
static_assert(sizeof(unk_409C50) == 0x14, "Wrong size for unk_409C50");
