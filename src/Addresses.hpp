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

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#define safe_strncpy(dest, src, len) ((void) strncpy_s((dest), (len), (src), (len) - 1))
#define safe_strcat(dest, len, src) ((void) strcat_s((dest), (len), (src)))
#define stricmp(A, B) (_stricmp((A), (B)))

// Helper Functions

template<class Ret, class... Args> class MC2_PROC_PTR;
template<class Ret, class... Args> class MC2_PROC_VARARG_PTR;
template<class Ret, class... Args> class MC2_PROC_STDCALL_PTR;
template<class Ret, class C, class... Args> class MC2_PROC_MEMBER_PTR;

namespace detail {
    extern "C" __declspec(dllimport) void mc2_import_start();
    template<class T>
    inline T MC2_POINTER_BASIC(const std::uintptr_t address) {
        return reinterpret_cast<T>(reinterpret_cast<std::uintptr_t>(&mc2_import_start) + address - 0x00401000);
    }

    template<class F, class X, class Ret, class... Args>
    class MC2_PROC_PTR_BASE {
    protected:
        F func;
        using ptr_type = F;
        template<class T> friend class Auto_Hook_x86_Obj;
        template<class T> friend class Auto_Hook_Fnptr_Obj;
        template<class... Ts> friend void Hook_x86(const MC2_PROC_PTR_BASE<Ts...> &in, const MC2_PROC_PTR_BASE<Ts...> &out);

        constexpr MC2_PROC_PTR_BASE(F func) : func(func) { }
        explicit MC2_PROC_PTR_BASE(std::uint32_t address) : func(detail::MC2_POINTER_BASIC<F>(address)) { }

    public:
        Ret operator()(Args... args) const { return this->func(args...); }
        friend constexpr bool operator==(const X &a, const X &b) { return a.func == b.func; }
        friend constexpr bool operator!=(const X &a, const X &b) { return a.func != b.func; }
    };
#define MC2_PROC_PTR_CONSTRUCTORS(X, ...) \
constexpr X(typename __VA_ARGS__::ptr_type func) : __VA_ARGS__(func) { }\
explicit X(std::uint32_t address) : __VA_ARGS__(address) { }

    template<class Ret, class... Args> using CDECL_PTR = Ret(__cdecl *)(Args...);
    template<class Ret, class... Args> using CDECL_BASE = MC2_PROC_PTR_BASE<CDECL_PTR<Ret, Args...>, MC2_PROC_PTR<Ret, Args...>, Ret, Args...>;
    template<class Ret, class... Args> using VARARG_PTR = Ret(__cdecl *)(Args..., ...);
    template<class Ret, class... Args> using VARARG_BASE = MC2_PROC_PTR_BASE<VARARG_PTR<Ret, Args...>, MC2_PROC_VARARG_PTR<Ret, Args...>, Ret, Args...>;
    template<class Ret, class... Args> using STDCALL_PTR = Ret(__stdcall *)(Args...);
    template<class Ret, class... Args> using STDCALL_BASE = MC2_PROC_PTR_BASE<STDCALL_PTR<Ret, Args...>, MC2_PROC_STDCALL_PTR<Ret, Args...>, Ret, Args...>;
    template<class Ret, class C, class... Args> using MEMBER_PTR = Ret(__thiscall *)(C *, Args...);
    template<class Ret, class C, class... Args> using MEMBER_MPTR = Ret(__thiscall C::*)(Args...);
    template<class Ret, class C, class... Args> using MEMBER_BASE =  MC2_PROC_PTR_BASE<MEMBER_PTR<Ret, C, Args...>, MC2_PROC_MEMBER_PTR<Ret, C, Args...>, Ret, C *, Args...>;

    template<class T, class Ret, class C, class... Args>
    inline MEMBER_PTR<Ret, T, Args...> CAST(MEMBER_MPTR<Ret, C, Args...> mptr) {
        union { MEMBER_MPTR<Ret, C, Args...> member; MEMBER_PTR<Ret, T, Args...> thiscall; };
        member = mptr; return thiscall;
    }
    template<class T, class Ret, class C, class... Args>
    inline MEMBER_PTR<Ret, T, Args...> CAST(MEMBER_PTR<Ret, C, Args...> ptr) {
        return reinterpret_cast<MEMBER_PTR<Ret, T, Args...>>(ptr);
    }

    // Type Safety Magic
    template<class T> using remove_ref_t = typename std::enable_if<std::is_lvalue_reference<T>::value, typename std::remove_reference<T>::type>::type;
    template<class T> using remove_ptr_t = typename std::enable_if<std::is_pointer<T>::value, typename std::remove_pointer<T>::type>::type;
    template<class T> class is_func : public std::conditional<std::is_pointer<T>::value, is_func<typename std::remove_pointer<T>::type>, std::is_function<T>>::type { };
    template<class T> using non_func_t = typename std::enable_if<!is_func<T>::value, T>::type;


    template<class... Ts>
    inline void Hook_x86(const MC2_PROC_PTR_BASE<Ts...> &in, const MC2_PROC_PTR_BASE<Ts...> &out) {
#pragma pack(push, 1)
        struct x86_jump {
            const std::uint8_t cmd = 0xE9;
            std::uintptr_t addr;
        };
#pragma pack(pop)
        static_assert(sizeof(x86_jump) == 5, "pragma pack failed");

        x86_jump cmd;
        cmd.addr = reinterpret_cast<std::uintptr_t>(out.func) - reinterpret_cast<std::uintptr_t>(in.func) - 5;
        WriteProcessMemory(GetCurrentProcess(), in.func, &cmd, 5, nullptr);
    }

    template<size_t N> inline void Hook_Raw(const std::uintptr_t address, const std::uint8_t (&data)[N]) {
        WriteProcessMemory(GetCurrentProcess(), MC2_POINTER_BASIC<void *>(address), data, N, nullptr);
    }

    template<class T> class Auto_Hook_x86_Obj { public: Auto_Hook_x86_Obj(std::uintptr_t in, const T &out) { Hook_x86(T(in), out); } };
    template<class Ret, class... Args> Auto_Hook_x86_Obj<MC2_PROC_PTR<Ret, Args...>> Auto_Hook_x86(std::uintptr_t in, CDECL_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class... Args> Auto_Hook_x86_Obj<MC2_PROC_VARARG_PTR<Ret, Args...>> Auto_Hook_Vararg_x86(std::uintptr_t in, VARARG_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class... Args> Auto_Hook_x86_Obj<MC2_PROC_STDCALL_PTR<Ret, Args...>> Auto_Hook_Stdcall_x86(std::uintptr_t in, STDCALL_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class C, class... Args> Auto_Hook_x86_Obj<MC2_PROC_MEMBER_PTR<Ret, C, Args...>> Auto_Hook_Member_x86(std::uintptr_t in, MEMBER_PTR<Ret, C, Args...> out) { return { in, out }; }
    template<class Ret, class C, class... Args> Auto_Hook_x86_Obj<MC2_PROC_MEMBER_PTR<Ret, C, Args...>> Auto_Hook_Member_x86(std::uintptr_t in, MEMBER_MPTR<Ret, C, Args...> out) { return { in, out }; }

    template<class T> class Auto_Hook_Fnptr_Obj { public: Auto_Hook_Fnptr_Obj(std::uintptr_t in, const T &out) { *MC2_POINTER_BASIC<T *>(in) = out; } };
    template<class Ret, class... Args> Auto_Hook_Fnptr_Obj<MC2_PROC_PTR<Ret, Args...>> Auto_Hook_Fnptr(std::uintptr_t in, CDECL_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class... Args> Auto_Hook_Fnptr_Obj<MC2_PROC_VARARG_PTR<Ret, Args...>> Auto_Hook_Vararg_Fnptr(std::uintptr_t in, VARARG_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class... Args> Auto_Hook_Fnptr_Obj<MC2_PROC_STDCALL_PTR<Ret, Args...>> Auto_Hook_Stdcall_Fnptr(std::uintptr_t in, STDCALL_PTR<Ret, Args...> out) { return { in, out }; }
    template<class Ret, class C, class... Args> Auto_Hook_Fnptr_Obj<MC2_PROC_MEMBER_PTR<Ret, C, Args...>> Auto_Hook_Member_Fnptr(std::uintptr_t in, MEMBER_PTR<Ret, C, Args...> out) { return { in, out }; }
    template<class Ret, class C, class... Args> Auto_Hook_Fnptr_Obj<MC2_PROC_MEMBER_PTR<Ret, C, Args...>> Auto_Hook_Member_Fnptr(std::uintptr_t in, MEMBER_MPTR<Ret, C, Args...> out) { return { in, out }; }
    
    template<class T>
    inline void *scalar_deleter(T *_this, std::uint32_t flags) {
        assert((flags & ~1) == 0);
        _this->destructor();
        if (flags & 1) ::operator delete(_this);
        return _this;
    }
#define MC2_SCALAR_DELETING_DESTRUCTOR(X) \
    void *scalar_deleter(std::uint32_t flags) { return detail::scalar_deleter<>(this, flags); } \
    ~X() { static_cast<const vtable_t *>(this->vtable)->deleter(this, 0); } \
    void destructor()
}

// some common virtual function implementations for simplicity
class mc2_thiscall {
public:
    template<class... Args> void null(Args...) { }
    template<class Ret, Ret V, class... Args>
    Ret retval(Args...) { return V; }
    template<class Ret, class... Args>
    Ret pure(Args...) {
        throw std::logic_error("Called pure virtual member function");
    }
};

template<class T> inline detail::non_func_t<T> &MC2_GLOBAL(const std::uintptr_t address) { return *detail::MC2_POINTER_BASIC<T *>(address); }
template<class T> inline detail::non_func_t<T> *MC2_POINTER(const std::uintptr_t address) { return detail::MC2_POINTER_BASIC<T *>(address); }
#define MC2_DEF_GLOBAL(var, address) decltype(var) var = MC2_GLOBAL<detail::remove_ref_t<decltype(var)>>(address)
#define MC2_DEF_POINTER(var, address) decltype(var) var = MC2_POINTER<detail::remove_ptr_t<decltype(var)>>(address)
#define MC2_DEF_PROC(proc, address) decltype(proc) proc(address)

template<class Ret, class... Args>
class MC2_PROC_PTR : public detail::CDECL_BASE<Ret, Args...> {
public:
    MC2_PROC_PTR_CONSTRUCTORS(MC2_PROC_PTR, detail::CDECL_BASE<Ret, Args...>)
};

template<class Ret, class... Args>
class MC2_PROC_VARARG_PTR : public detail::VARARG_BASE<Ret, Args...> {
public:
    MC2_PROC_PTR_CONSTRUCTORS(MC2_PROC_VARARG_PTR, detail::VARARG_BASE<Ret, Args...>)
    template<class... VARGS> Ret operator()(Args... args, VARGS... vargs) const { return this->func(args..., vargs...); }
};

template<class Ret, class... Args>
class MC2_PROC_STDCALL_PTR : public detail::STDCALL_BASE<Ret, Args...> {
public:
    MC2_PROC_PTR_CONSTRUCTORS(MC2_PROC_STDCALL_PTR, detail::STDCALL_BASE<Ret, Args...>)
};

template<class Ret, class C, class... Args>
class MC2_PROC_MEMBER_PTR : public detail::MEMBER_BASE<Ret, C, Args...> {
private:
    using super = detail::MEMBER_BASE<Ret, C, Args...>;
public:
    MC2_PROC_PTR_CONSTRUCTORS(MC2_PROC_MEMBER_PTR, super)
    MC2_PROC_MEMBER_PTR(detail::MEMBER_MPTR<Ret, C, Args...> func) : super(detail::CAST<C>(func)) { }
    constexpr MC2_PROC_MEMBER_PTR(std::nullptr_t) : super(nullptr) { }
};

template<class Ret, class... Args>
class MC2_PROC_MEMBER_PTR<Ret, void, Args...> : public detail::MEMBER_BASE<Ret, void, Args...> {
private:
    using super = detail::MEMBER_BASE<Ret, void, Args...>;
public:
    MC2_PROC_PTR_CONSTRUCTORS(MC2_PROC_MEMBER_PTR, super)
    template<class C> MC2_PROC_MEMBER_PTR(detail::MEMBER_PTR<Ret, C, Args...> func) : super(detail::CAST<void>(func)) { }
    template<class C> MC2_PROC_MEMBER_PTR(detail::MEMBER_MPTR<Ret, C, Args...> func) : super(detail::CAST<void>(func)) { }
    constexpr MC2_PROC_MEMBER_PTR(std::nullptr_t) : super(nullptr) { }
};

using MC2_DELETING_DESTRUCTOR = MC2_PROC_MEMBER_PTR<void *, void, std::uint32_t>;

#undef MC2_PROC_PTR_CONSTRUCTORS

template<std::uintptr_t addr, class T, class X, class... Args>
T MC2_CALL_MEMBER(X *x, Args... args) {
    static const MC2_PROC_MEMBER_PTR<T, X, Args...> func(addr);
    return func(x, args...);
}

#define AUTO_HOOK_X86(in, out) static const auto _hookobj_##in (detail::Auto_Hook_x86(in, out))
#define AUTO_HOOK_VARARG_X86(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Vararg_x86(in, out))
#define AUTO_HOOK_STDCALL_X86(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Stdcall_x86(in, out))
#define AUTO_HOOK_MEMBER_X86(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Member_x86(in, out))

#define AUTO_HOOK_FNPTR(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Fnptr(in, out))
#define AUTO_HOOK_VARARG_FNPTR(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Vararg_Fnptr(in, out))
#define AUTO_HOOK_STDCALL_FNPTR(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Stdcall_Fnptr(in, out))
#define AUTO_HOOK_MEMBER_FNPTR(in, out) static const auto _hookobj_##in (detail::Auto_Hook_Member_Fnptr(in, out))


// Functions

extern MC2_PROC_PTR<std::uint32_t, char *> sub_61A5DC;

// Global Variables

extern void *&glo_67A760;
extern void *loc_67A770;
extern bool &glo_682E18;
extern std::uint32_t &glo_8602C8;
extern std::uint8_t &glo_679778;
