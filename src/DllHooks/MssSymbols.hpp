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

#include "../Addresses.hpp"

constexpr std::uintptr_t AIL_Start = 0x0062D290;

constexpr const char *AIL_Names[] = {
    "_AIL_stream_status@4",
    "_AIL_open_stream@12",
    "_AIL_start_stream@4",
    "_AIL_pause_stream@8",
    "_AIL_close_stream@4",
    "_AIL_set_stream_volume_pan@12",
    "_AIL_allocate_3D_sample_handle@4",
    "_AIL_set_3D_sample_info@8",
    "_AIL_set_3D_sample_loop_block@12",
    "_AIL_set_3D_sample_loop_count@8",
    "_AIL_allocate_sample_handle@4",
    "_AIL_init_sample@4",
    "_AIL_set_sample_address@12",
    "_AIL_set_sample_type@12",
    "_AIL_set_sample_loop_block@12",
    "_AIL_set_sample_loop_count@8",
    "_AIL_start_sample@4",
    "_AIL_start_3D_sample@4",
    "_AIL_sample_status@4",
    "_AIL_3D_sample_status@4",
    "_AIL_set_3D_sample_distances@12",
    "_AIL_set_3D_position@16",
    "_AIL_set_sample_playback_rate@8",
    "_AIL_set_3D_sample_playback_rate@8",
    "_AIL_set_sample_volume_pan@12",
    "_AIL_set_3D_sample_volume@8",
    "_AIL_resume_sample@4",
    "_AIL_resume_3D_sample@4",
    "_AIL_stop_sample@4",
    "_AIL_stop_3D_sample@4",
    "_AIL_release_sample_handle@4",
    "_AIL_release_3D_sample_handle@4",
    "_AIL_close_3D_provider@4",
    "_AIL_set_3D_rolloff_factor@8",
    "_AIL_open_3D_provider@4",
    "_AIL_set_redist_directory@4",
    "_AIL_quick_startup@20",
    "_AIL_last_error@0",
    "_AIL_quick_handles@12",
    "_AIL_set_file_callbacks@16",
    "_AIL_enumerate_3D_providers@12",
};
