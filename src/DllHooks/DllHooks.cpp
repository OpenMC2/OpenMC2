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

#include "DllHooks.hpp"
#include "BinkSymbols.hpp"
#include "MssSymbols.hpp"

#include "../Addresses.hpp"

#include <array>

#include <boost/dll.hpp>
#include <boost/range/combine.hpp>

static boost::dll::shared_library BinkDll;
static boost::dll::shared_library AIL_Dll;

std::array<void *, BinkCount> &BinkPointers = MC2_GLOBAL<std::array<void *, BinkCount>>(0x0062D260);
std::array<void *, AIL_Count> &AIL_Pointers = MC2_GLOBAL<std::array<void *, AIL_Count>>(0x0062D290);

template<size_t N>
void set_pointers(const boost::dll::shared_library &dll,
    const std::array<const char *, N> &names, std::array<void *, N> &pointers) {
    for (boost::tuple<const char *, void *&> v : boost::combine(names, pointers)) {
        boost::get<1>(v) = &dll.get<char>(boost::get<0>(v));
    }
}

void AddDllHooks(const boost::filesystem::path &mc2_dir) {
    BinkDll.load(mc2_dir / "binkw32.dll");
    set_pointers(BinkDll, BinkNames, BinkPointers);

    AIL_Dll.load(mc2_dir / "mss32.dll");
    set_pointers(AIL_Dll, AIL_Names, AIL_Pointers);
}
