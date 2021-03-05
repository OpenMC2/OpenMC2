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

#include "unk53AF00.hpp"

// originally malloc'd in raceeditor.cpp
class unk_489330_p {
protected:
    struct vtable_t {
        MC2_DELETING_DESTRUCTOR deleter;
        MC2_PROC_MEMBER_PTR<void, void> vir_04;
        MC2_PROC_MEMBER_PTR<void, void> vir_08;
        MC2_PROC_MEMBER_PTR<void, void> vir_0C;
        MC2_PROC_MEMBER_PTR<void, void> vir_10;
        MC2_PROC_MEMBER_PTR<void, void> vir_14;
        MC2_PROC_MEMBER_PTR<void, void> vir_18;
        MC2_PROC_MEMBER_PTR<void, void> vir_1C;
        // ...
    };

    const void *vtable;
public:
    std::uint8_t pad04[0x550];
    const char *unk554;
    std::uint8_t pad558[0xB90];

protected:
    unk_489330_p() = default; // for sub-classes without reimplemented constructors

public:
    unk_489330_p(std::uint32_t arg1) {
        MC2_CALL_MEMBER<0x00489330, void>(this, arg1);
    }
    MC2_SCALAR_DELETING_DESTRUCTOR(unk_489330_p) {
        MC2_CALL_MEMBER<0x00489540, void>(this);
    }

    void sub_485530() {
        return MC2_CALL_MEMBER<0x00485530, void>(this);
    }

    void vir10() {
        return static_cast<const vtable_t *>(this->vtable)->vir_10(this);
    }
    void vir14() {
        return static_cast<const vtable_t *>(this->vtable)->vir_14(this);
    }
    void vir18() {
        return static_cast<const vtable_t *>(this->vtable)->vir_18(this);
    }
};
static_assert(sizeof(unk_489330_p) == 0x10E8, "Wrong size for unk_489330_p");
static_assert(std::is_trivially_destructible<unk_489330_p>::value, "unk_489330_p is not trivially destructible");

using unk_489330 = MC2_DestroyingWrapper<unk_489330_p>;

// originally malloc'd in racemgr.c
// cruise mode?
class unk_496BF0_p : public unk_489330_p {
public:
    unk_496BF0_p() {
        MC2_CALL_MEMBER<0x00496BF0, void>(this);
    }
};
static_assert(sizeof(unk_496BF0_p) == 0x10E8, "Wrong size for unk_496BF0_p");
static_assert(std::is_trivially_destructible<unk_496BF0_p>::value, "unk_496BF0_p is not trivially destructible");

using unk_496BF0 = MC2_DestroyingWrapper<unk_496BF0_p>;

// originally malloc'd in racemgr.c
// "find_hook"
class unk_496B30_p : public unk_489330_p {
public:
    std::uint8_t pad10E8[0x40];

public:
    unk_496B30_p(std::uint32_t arg0) {
        MC2_CALL_MEMBER<0x00496B30, void>(this, arg0);
    }
};
static_assert(sizeof(unk_496B30_p) == 0x1128, "Wrong size for unk_496B30_p");
static_assert(std::is_trivially_destructible<unk_496B30_p>::value, "unk_496B30_p is not trivially destructible");

using unk_496B30 = MC2_DestroyingWrapper<unk_496B30_p>;

// originally malloc'd in racemgr.c
// checkpoint races
class unk_48C470_p : public unk_489330_p {
public:
    std::uint8_t pad10E8[0x10];

protected:
    unk_48C470_p() = default; // for sub-classes without reimplemented constructors

public:
    unk_48C470_p(RaceType arg0) {
        MC2_CALL_MEMBER<0x0048C470, void>(this, arg0);
    }
};
static_assert(sizeof(unk_48C470_p) == 0x10F8, "Wrong size for unk_48C470_p");
static_assert(std::is_trivially_destructible<unk_48C470_p>::value, "unk_48C470_p is not trivially destructible");

using unk_48C470 = MC2_DestroyingWrapper<unk_48C470_p>;

// originally malloc'd in racemgr.c
// capture the flag
class unk_48F9F0_p : public unk_489330_p {
public:
    std::uint8_t pad10E8[0xA0];

public:
    unk_48F9F0_p() {
        MC2_CALL_MEMBER<0x0048F9F0, void>(this);
    }
};
static_assert(sizeof(unk_48F9F0_p) == 0x1188, "Wrong size for unk_48F9F0_p");
static_assert(std::is_trivially_destructible<unk_48F9F0_p>::value, "unk_48F9F0_p is not trivially destructible");

using unk_48F9F0 = MC2_DestroyingWrapper<unk_48F9F0_p>;

// originally malloc'd in racemgr.c
// detonate
class unk_48D540_p : public unk_489330_p {
public:
    std::uint8_t pad10E8[0x80];

public:
    unk_48D540_p() {
        MC2_CALL_MEMBER<0x0048D540, void>(this);
    }
};
static_assert(sizeof(unk_48D540_p) == 0x1168, "Wrong size for unk_48D540_p");
static_assert(std::is_trivially_destructible<unk_48D540_p>::value, "unk_48D540_p is not trivially destructible");

using unk_48D540 = MC2_DestroyingWrapper<unk_48D540_p>;

// originally malloc'd in racemgr.c
// lose the cops
class unk_495510_p : public unk_48C470_p {
public:
    std::uint8_t pad10E8[0x28];

public:
    unk_495510_p() {
        MC2_CALL_MEMBER<0x00495510, void>(this);
    }
};
static_assert(sizeof(unk_495510_p) == 0x1120, "Wrong size for unk_495510_p");
static_assert(std::is_trivially_destructible<unk_495510_p>::value, "unk_495510_p is not trivially destructible");

using unk_495510 = MC2_DestroyingWrapper<unk_495510_p>;

// originally malloc'd in racemgr.c
// destroy (as the cop)
class unk_4951A0_p : public unk_48C470_p {
public:
    std::uint8_t pad10E8[0x38];

public:
    unk_4951A0_p() {
        MC2_CALL_MEMBER<0x004951A0, void>(this);
    }
};
static_assert(sizeof(unk_4951A0_p) == 0x1130, "Wrong size for unk_4951A0_p");
static_assert(std::is_trivially_destructible<unk_4951A0_p>::value, "unk_4951A0_p is not trivially destructible");

using unk_4951A0 = MC2_DestroyingWrapper<unk_4951A0_p>;
