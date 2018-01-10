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

#include <boost/dll.hpp>

static boost::dll::shared_library BinkDll;
static boost::dll::shared_library AIL_Dll;

void AddDllHooks(const boost::filesystem::path &mc2_dir) {
    BinkDll.load(mc2_dir / "binkw32.dll");
    AIL_Dll.load(mc2_dir / "mss32.dll");

    void **func = mc2_pointer<BinkStart, void *>();
    for (const char *bink_func : BinkNames) {
        *func = &BinkDll.get<char>(bink_func);
        ++func;
    }

    func = mc2_pointer<AIL_Start, void *>();
    for (const char *ail_func : AIL_Names) {
        *func = &AIL_Dll.get<char>(ail_func);
        ++func;
    }
}
