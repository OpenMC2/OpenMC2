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

#include "sndVoice.hpp"
#include "../Logging.hpp"

using namespace audio;

// mc2: 0x00654E68
const sndVoice_p::vtable_t sndVoice_p::vtable_values = {
    &sndVoice_p::scalar_deleter, // 0x00
    &mc2_thiscall::null<std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t>, // 0x04
    &sndVoice_p::impl_play, // 0x08
    &mc2_thiscall::retval<bool, false>, // 0x0C
    &mc2_thiscall::null<>, // 0x10
    &sndVoice_p::impl_stop, // 0x14
    &sndVoice_p::impl_release, // 0x18
    &mc2_thiscall::null<std::uint32_t>, // 0x1C
    &mc2_thiscall::null<std::uint32_t>, // 0x20
    &mc2_thiscall::null<std::uint32_t>, // 0x24
    &mc2_thiscall::null<std::uint32_t>, // 0x28
    &mc2_thiscall::null<std::uint32_t>, // 0x2C
    &mc2_thiscall::null<std::uint32_t, std::uint32_t, std::uint32_t>, // 0x30
    &mc2_thiscall::null<std::uint32_t, std::uint32_t, std::uint32_t>, // 0x34
    &mc2_thiscall::null<std::uint32_t, std::uint32_t>, // 0x38
    &mc2_thiscall::null<std::uint32_t>, // 0x3C
    &sndVoice_p::impl_isPlaying, // 0x40
    &mc2_thiscall::retval<std::uint32_t, 0>, // 0x44
    &mc2_thiscall::retval<std::int32_t, -1>, // 0x48
    &mc2_thiscall::retval<std::int32_t, -1>, // 0x4C
};

// mc2: 0x005D6AB0
sndVoice_p::sndVoice_p(sndVoice *arg0) {
    vtable = &vtable_values;
    if (arg0 != nullptr) {
        next = arg0->next;
        if (arg0->next != nullptr)
            arg0->next->prev = class_cast<sndVoice>(this);
        arg0->next = class_cast<sndVoice>(this);
        this->prev = arg0;
    } else {
        next = nullptr;
        prev = nullptr;
    }
}

// mc2: 0x005D6AF0
void sndVoice_p::destructor() {
    vtable = &vtable_values;
    if (next != nullptr) next->prev = this->prev;
    if (prev != nullptr) prev->next = this->next;
}

// mc2: 0x005D6A40
void sndVoice_p::impl_play(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t) {
    mc2_log_error("virtual sndVoice::Play used");
}

// mc2: 0x005D6A60
void sndVoice_p::impl_stop() {
    mc2_log_error("virtual sndVoice::Stop used");
}

// mc2: 0x005D6A70
void sndVoice_p::impl_release() {
    mc2_log_error("virtual sndVoice::Release used");
}

std::uint32_t sndVoice_p::impl_isPlaying() {
    mc2_log_error("virtual sndVoice::IsPlaying used");
    return 0;
}

MC2_DEF_GLOBAL(glo_6CE520, 0x006CE520);
MC2_DEF_GLOBAL(glo_6CE52C, 0x006CE52C);
MC2_DEF_GLOBAL(glo_6CE538, 0x006CE538);
MC2_DEF_GLOBAL(glo_6CE544, 0x006CE544);
MC2_DEF_GLOBAL(glo_6CE550, 0x006CE550);
MC2_DEF_GLOBAL(glo_6CE55C, 0x006CE55C);
MC2_DEF_GLOBAL(glo_6CE568, 0x006CE568);
