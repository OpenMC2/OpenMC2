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

namespace audio {
    class sndVoice_p;
    using sndVoice = MC2_DestroyingWrapper<sndVoice_p>;

    class sndVoice_p {
    protected:
        struct vtable_t {
            MC2_DELETING_DESTRUCTOR deleter; // 0x00
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t> vir_04;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t> play; // 0x08
            MC2_PROC_MEMBER_PTR<bool, void> vir_0C;
            MC2_PROC_MEMBER_PTR<void, void> vir_10;
            MC2_PROC_MEMBER_PTR<void, void> stop; // 0x14
            MC2_PROC_MEMBER_PTR<void, void> release; // 0x18
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_1C;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_20;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_24;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_28;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_2C;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t, std::uint32_t> vir_30;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t, std::uint32_t> vir_34;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t, std::uint32_t> vir_38;
            MC2_PROC_MEMBER_PTR<void, void, std::uint32_t> vir_3C;
            MC2_PROC_MEMBER_PTR<std::uint32_t, void> isPlaying; // 0x40
            MC2_PROC_MEMBER_PTR<std::uint32_t, void> vir_44;
            MC2_PROC_MEMBER_PTR<std::int32_t, void> vir_48;
            MC2_PROC_MEMBER_PTR<std::int32_t, void> vir_4C;
        };

    private:
        static const vtable_t vtable_values;

    protected:
        const void *vtable;
        sndVoice *next;
        sndVoice *prev;

    public:
        sndVoice_p() : next(class_cast<sndVoice>(this)),
            prev(class_cast<sndVoice>(this)) { vtable = &vtable_values; }
        sndVoice_p(sndVoice *arg0);
        MC2_SCALAR_DELETING_DESTRUCTOR(sndVoice_p);

        // vir_08
        void play(std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3, std::uint32_t arg4, std::uint32_t arg5) {
            static_cast<const vtable_t *>(this->vtable)->play(this, arg1, arg2, arg3, arg4, arg5);
        }
        // vir_14
        void stop() {
            static_cast<const vtable_t *>(this->vtable)->stop(this);
        }
        // vir_18
        void release() {
            static_cast<const vtable_t *>(this->vtable)->release(this);
        }
        // vir_40
        std::uint32_t isPlaying() {
            static_cast<const vtable_t *>(this->vtable)->isPlaying(this);
        }

    private:
        void impl_play(std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t, std::uint32_t);
        void impl_stop();
        void impl_release();
        std::uint32_t impl_isPlaying();
    };
    static_assert(std::is_trivially_destructible<sndVoice_p>::value, "sndVoice_p is not trivially destructible");
}

extern audio::sndVoice &glo_6CE520;
extern audio::sndVoice &glo_6CE52C;
extern audio::sndVoice &glo_6CE538;
extern audio::sndVoice &glo_6CE544;
extern audio::sndVoice &glo_6CE550;
extern audio::sndVoice &glo_6CE55C;
extern audio::sndVoice &glo_6CE568;
