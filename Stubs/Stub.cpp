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

#define STUB_SYMBOL(S, X) static_assert(X % 4 == 0, "Invalid Arguments Size For " #S ": " #X);
#include STUB_SYMBOL_FILE
#undef STUB_SYMBOL

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <boost/dll/shared_library.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/preprocessor.hpp>
#include <cstdint>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

static boost::dll::shared_library _dll;
#define STUB_SYMBOL(S, X) static std::uint32_t (__stdcall *_##S)(BOOST_PP_ENUM(BOOST_PP_DIV(X, 4), BOOST_PP_IDENTITY_N(std::uint32_t, 3), ));
#include STUB_SYMBOL_FILE
#undef STUB_SYMBOL

void __declspec(dllexport) INIT_FUNCTION(const boost::filesystem::path &path) {
    _dll.load(path);
#define STUB_SYMBOL(S, X) \
    _##S = _dll.get<std::uint32_t (__stdcall)(BOOST_PP_ENUM(BOOST_PP_DIV(X, 4), BOOST_PP_IDENTITY_N(std::uint32_t, 3), ))>(BOOST_PP_STRINGIZE(_##S##@X));
#include STUB_SYMBOL_FILE
#undef STUB_SYMBOL
}

#define STUB_SYMBOL(S, X) \
extern "C" __declspec(dllexport) std::uint32_t __stdcall S(BOOST_PP_ENUM_PARAMS(BOOST_PP_DIV(X, 4), std::uint32_t param_)) {\
    return _##S(BOOST_PP_ENUM_PARAMS(BOOST_PP_DIV(X, 4), param_));\
}
#include STUB_SYMBOL_FILE
#undef STUB_SYMBOL
