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

#include "Addresses.hpp"

void * __cdecl mc2_malloc(std::uint32_t size);
void * __cdecl mc2_malloc_info(std::uint32_t size, const char *file, std::int32_t line);
void __cdecl mc2_free(void *ptr);

void * __cdecl mc2_aligned_malloc(std::uint32_t size, std::uint32_t align);
void __cdecl mc2_aligned_free(void *ptr);

char * __cdecl mc2_strdup(const char *str);
char * _cdecl mc2_strdup_info(const char *str, const char * file, std::int32_t line);
