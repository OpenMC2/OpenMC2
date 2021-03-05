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
class unk_4094A0_p {
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
    unk_4094A0_p() { vtable = &vtable_values; }
public:
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_4094A0_p) { }

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
static_assert(sizeof(unk_4094A0_p) == 0x14, "Wrong size for unk_4094A0_p");
static_assert(std::is_trivially_destructible<unk_4094A0_p>::value, "unk_4094A0_p is not trivially destructible");

using unk_4094A0 = MC2_DestroyingWrapper<unk_4094A0_p>;

class unk_40AE70_p : public unk_4094A0_p {
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
    unk_40AE70_p() { vtable = &vtable_values; }
protected:
    const char *impl_vir1C() { return "city"; }

};
static_assert(sizeof(unk_40AE70_p) == 0x34, "Wrong size for unk_40AE70_p");
static_assert(std::is_trivially_destructible<unk_40AE70_p>::value, "unk_40AE70_p is not trivially destructible");

using unk_40AE70 = MC2_DestroyingWrapper<unk_40AE70_p>;

class unk_40AB30_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;

public:
    unk_40AB30_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "cpvs"; }
};
static_assert(sizeof(unk_40AB30_p) == 0x1C, "Wrong size for unk_40AB30_p");
static_assert(std::is_trivially_destructible<unk_40AB30_p>::value, "unk_40AB30_p is not trivially destructible");

using unk_40AB30 = MC2_DestroyingWrapper<unk_40AB30_p>;

class unk_40A940_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;

public:
    unk_40A940_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "conditions"; }
};
static_assert(sizeof(unk_40A940_p) == 0x1C, "Wrong size for unk_40A940_p");
static_assert(std::is_trivially_destructible<unk_40A940_p>::value, "unk_40A940_p is not trivially destructible");

using unk_40A940 = MC2_DestroyingWrapper<unk_40A940_p>;

class unk_40A4A0_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint32_t unk18 = 0;
    std::uint32_t unk1C = 0;
    std::uint32_t unk20 = 0;

public:
    unk_40A4A0_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "ambients"; }
};
static_assert(sizeof(unk_40A4A0_p) == 0x24, "Wrong size for unk_40A4A0_p");
static_assert(std::is_trivially_destructible<unk_40A4A0_p>::value, "unk_40A4A0_p is not trivially destructible");

using unk_40A4A0 = MC2_DestroyingWrapper<unk_40A4A0_p>;

class unk_409ED0_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

private:
    std::uint32_t unk14 = 0;
    std::uint8_t pad18[0x04];

public:
    unk_409ED0_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "race"; }
};
static_assert(sizeof(unk_409ED0_p) == 0x1C, "Wrong size for unk_409ED0_p");
static_assert(std::is_trivially_destructible<unk_409ED0_p>::value, "unk_409ED0_p is not trivially destructible");

using unk_409ED0 = MC2_DestroyingWrapper<unk_409ED0_p>;

class unk_409DF0_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

public:
    unk_409DF0_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "movie"; }
};
static_assert(sizeof(unk_409DF0_p) == 0x14, "Wrong size for unk_409DF0_p");
static_assert(std::is_trivially_destructible<unk_409DF0_p>::value, "unk_409DF0_p is not trivially destructible");

using unk_409DF0 = MC2_DestroyingWrapper<unk_409DF0_p>;

class unk_409A70_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

public:
    unk_41FB40 *unk14 = nullptr;
    std::uint32_t unk18 = 0;

public:
    unk_409A70_p() { vtable = &vtable_values; }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_409A70_p) { delete unk14; }

protected:
    const char *impl_vir1C() { return "frontend"; }
};
static_assert(sizeof(unk_409A70_p) == 0x1C, "Wrong size for unk_409A70_p");
static_assert(std::is_trivially_destructible<unk_409A70_p>::value, "unk_409A70_p is not trivially destructible");

using unk_409A70 = MC2_DestroyingWrapper<unk_409A70_p>;

class unk_409CF0_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

public:
    unk_409CF0_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "race editor"; }
};
static_assert(sizeof(unk_409CF0_p) == 0x14, "Wrong size for unk_409CF0_p");
static_assert(std::is_trivially_destructible<unk_409CF0_p>::value, "unk_409CF0_p is not trivially destructible");

using unk_409CF0 = MC2_DestroyingWrapper<unk_409CF0_p>;

class unk_409C50_p : public unk_4094A0_p {
protected:
    static const vtable_t vtable_values;

public:
    unk_409C50_p() { vtable = &vtable_values; }

protected:
    const char *impl_vir1C() { return "carviewer"; }
};
static_assert(sizeof(unk_409C50_p) == 0x14, "Wrong size for unk_409C50_p");
static_assert(std::is_trivially_destructible<unk_409C50_p>::value, "unk_409C50_p is not trivially destructible");

using unk_409C50 = MC2_DestroyingWrapper<unk_409C50_p>;
