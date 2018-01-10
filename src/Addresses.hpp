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

#include <cstdint>
#include <type_traits>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

 // Helper Functions
#define safe_strncpy(dest, src, len) ((void) strncpy_s((dest), (len), (src), (len) - 1))
#define safe_strcat(dest, len, src) ((void) strcat_s((dest), (len), (src)))
#define stricmp(A, B) (_stricmp((A), (B)))

// To avoid programming errors, make sure that mc2_pointer does not refer to (pointer to)* function
template<class T> class is_function_ptrs : public std::is_function<T> { };
template<class T> class is_function_ptrs<T *> : public is_function_ptrs<T> { };
template<class T> class is_function_ptrs<T * const> : public is_function_ptrs<T> { };
template<class T> class is_function_ptrs<T * volatile> : public is_function_ptrs<T> { };
template<class T> class is_function_ptrs<T * const volatile> : public is_function_ptrs<T> { };

extern "C" __declspec(dllimport) void mc2_import_start();

template<std::uintptr_t P, class T>
class mc2_pointer_impl {
public:
    T ptr() const { return reinterpret_cast<T>(reinterpret_cast<std::uintptr_t>(&mc2_import_start) + (P - 0x00401000)); }
};

template<class T, class X>
class mc2_proc_ptr_impl {
public:
    T ptr = nullptr;

    constexpr mc2_proc_ptr_impl() = default;
    constexpr mc2_proc_ptr_impl(T ptr) : ptr(ptr) { }
    X &operator=(T ptr) { this->ptr = ptr; return static_cast<X>(*this); }

    friend bool operator==(const X &a, const X &b) { return a.ptr == b.ptr; }
    friend bool operator!=(const X &a, const X &b) { return a.ptr != b.ptr; }
    friend bool operator==(const X &a, std::nullptr_t) { return a.ptr == nullptr; }
    friend bool operator!=(const X &a, std::nullptr_t) { return a.ptr != nullptr; }
    friend bool operator==(std::nullptr_t, const X &a) { return nullptr == a.ptr; }
    friend bool operator!=(std::nullptr_t, const X &a) { return nullptr != a.ptr; }
};


template<std::uintptr_t P, class T, class = typename std::enable_if<!is_function_ptrs<T>::value>::type>
class mc2_pointer : public mc2_pointer_impl<P, T *> {
public:
    operator T*() const { return ptr(); }
    T &operator*() const { return *ptr(); }
    T *operator->() const { return ptr(); }
    template<class I> auto operator[](I i) const -> decltype(ptr()[i]) { return ptr()[i]; }
};

template<std::uintptr_t P>
class mc2_pointer<P, void> : public mc2_pointer_impl<P, void *> {
public:
    operator void*() const { return ptr(); }
};


template<class Ret, class... Args>
class mc2_proc_ptr : public mc2_proc_ptr_impl<Ret(__cdecl *)(Args...), mc2_proc_ptr<Ret, Args...>>  {
public:
    using mc2_proc_ptr_impl::mc2_proc_ptr_impl;
    Ret operator()(Args... args) const { return ptr(args...); }
};

template<std::uintptr_t P, class Ret, class... Args>
class mc2_proc : public mc2_pointer_impl<P, Ret(__cdecl *)(Args...)> {
public:
    Ret operator()(Args... args) const { return ptr()(args...); }
    mc2_proc_ptr<Ret, Args...> operator&() const { return mc2_proc_ptr<Ret, Args...>(ptr()); }
};

template<std::uintptr_t P, class Ret, class... Args>
Ret mc2_call_proc(Args... args) { return mc2_proc<P, Ret, Args...>{}(args...); }

// Workaround for compiler bug?
template<class Ret, class... Args> struct mc2_proc_vararg_impl { using type = Ret(__cdecl *)(Args..., ...); };

template<class Ret, class... Args>
class mc2_proc_vararg_ptr : public mc2_proc_ptr_impl<typename mc2_proc_vararg_impl<Ret, Args...>::type, mc2_proc_vararg_ptr<Ret, Args...>> {
public:
    using mc2_proc_ptr_impl::mc2_proc_ptr_impl;
    template<class... VArgs> Ret operator()(Args... args, VArgs... vargs) const { return ptr(args..., vargs...); }
};

template<std::uintptr_t P, class Ret, class... Args>
class mc2_proc_vararg : public mc2_pointer_impl<P, typename mc2_proc_vararg_impl<Ret, Args...>::type> {
public:
    template<class... VArgs> Ret operator()(Args... args, VArgs... vargs) const { return ptr()(args..., vargs...); }
    mc2_proc_vararg_ptr<Ret, Args...> operator&() const { return mc2_proc_vararg_ptr<Ret, Args...>(ptr()); }
};

// mc2_call_proc_vararg would be identical to mc2_call_proc, so just use that

template<class Ret, class... Args>
class mc2_proc_stdcall_ptr : public mc2_proc_ptr_impl<Ret(__stdcall *)(Args...), mc2_proc_stdcall_ptr<Ret, Args...>> {
public:
    using mc2_proc_ptr_impl::mc2_proc_ptr_impl;
    Ret operator()(Args... args) const { return ptr(args...); }
};

template<std::uintptr_t P, class Ret, class... Args>
class mc2_proc_stdcall : public mc2_pointer_impl<P, Ret(__stdcall *)(Args...)> {
public:
    Ret operator()(Args... args) const { return ptr()(args...); }
    mc2_proc_stdcall_ptr<Ret, Args...> operator&() const { return mc2_proc_stdcall_ptr<Ret, Args...>(ptr()); }
};

template<class Ret, class... Args>
mc2_proc_stdcall_ptr<Ret, Args...> mc2_make_proc_stdcall_ptr(Ret(__stdcall *ptr)(Args...)) { return { ptr }; }

template<std::uintptr_t P, class Ret, class... Args>
Ret mc2_call_proc_stdcall(Args... args) { return mc2_proc_stdcall<P, Ret, Args...>{}(args...); }

template<class Ret, class T, class... Args>
class mc2_proc_thiscall_ptr : public mc2_proc_ptr_impl<Ret(__thiscall *)(T *, Args...), mc2_proc_thiscall_ptr<Ret, T, Args...>> {
public:
    using mc2_proc_ptr_impl::mc2_proc_ptr_impl;
    Ret operator()(T *_this, Args... args) const { return ptr(_this, args...); }

    // magic for member function pointers
    constexpr mc2_proc_thiscall_ptr() = default;
    template<class T2, class = std::enable_if<std::is_same<T, T2>::value>::type>
    mc2_proc_thiscall_ptr(Ret(__thiscall T2::*mptr)(Args...)) {
        union {
            Ret(__thiscall T2::*m)(Args...);
            Ret(__thiscall *p)(T *, Args...);
        } kptr;
        kptr.m = mptr;
        ptr = kptr.p;
    }
};

template<std::uintptr_t P, class Ret, class T, class... Args>
class mc2_proc_thiscall : public mc2_pointer_impl<P, Ret(__thiscall *)(T *, Args...)> {
public:
    Ret operator()(T *_this, Args... args) const { return ptr()(_this, args...); }
    mc2_proc_thiscall_ptr<Ret, T, Args...> operator&() const { return mc2_proc_thiscall_ptr<Ret, T, Args...>(ptr()); }
};

template<std::uintptr_t P, class Ret, class T, class... Args>
Ret mc2_call_proc_thiscall(T *_this, Args... args) { return mc2_proc_thiscall<P, Ret, T, Args...>{}(_this, args...); }


inline void mc2_hook_x86_impl(void *in, void *out) {
#pragma pack(push, 1)
    struct x86_jump {
        const std::uint8_t cmd = 0xE9;
        std::uintptr_t addr;
    };
#pragma pack(pop)
    static_assert(sizeof(x86_jump) == 5, "pragma pack failed");

    x86_jump cmd;
    cmd.addr = reinterpret_cast<std::uintptr_t>(out) - reinterpret_cast<std::uintptr_t>(in) - 5;
    WriteProcessMemory(GetCurrentProcess(), in, &cmd, 5, nullptr);
}

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc<P, Ret, Args...> in, mc2_proc_ptr<Ret, Args...> out) { return mc2_hook_x86_impl(in.ptr(), out.ptr); }

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc<P, Ret, Args...> in, Ret(__cdecl *out)(Args..., ...)) { return mc2_hook_x86_impl(in.ptr(), out); }

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc_vararg<P, Ret, Args...> in, mc2_proc_vararg_ptr<Ret, Args...> out) { return mc2_hook_x86_impl(in.ptr(), out.ptr); }

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc_vararg<P, Ret, Args...> in, Ret(__cdecl *out)(Args..., ...)) { return mc2_hook_x86_impl(in.ptr, out); }

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc_stdcall<P, Ret, Args...> in, mc2_proc_stdcall_ptr<Ret, Args...> out) { return mc2_hook_x86_impl(in.ptr(), out.ptr); }

template<std::uintptr_t P, class Ret, class... Args>
inline void mc2_hook_x86(mc2_proc_stdcall<P, Ret, Args...> in, Ret(__stdcall *out)(Args...)) { return mc2_hook_x86_impl(in.ptr(), out); }

template<std::uintptr_t P, class Ret, class T, class... Args>
inline void mc2_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, mc2_proc_thiscall_ptr<Ret, T, Args...> out) { return mc2_hook_x86_impl(in.ptr(), out.ptr); }

template<std::uintptr_t P, class Ret, class T, class... Args>
inline void mc2_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, Ret(__thiscall *out)(T *, Args...)) { return mc2_hook_x86_impl(in.ptr(), out); }

template<std::uintptr_t P, class Ret, class T, class... Args>
inline void mc2_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, Ret(__thiscall T::*out)(Args...))
{ return mc2_hook_x86_impl(in.ptr(), mc2_proc_thiscall_ptr<Ret, T, Args...>{out}.ptr); }

template<std::uintptr_t P, class... Ts>
struct mc2_auto_hook_x86_impl {
    mc2_auto_hook_x86_impl(mc2_proc<P, Ts...> in, mc2_proc_ptr<Ts...> out) { mc2_hook_x86_impl(in.ptr(), out.ptr); }
    mc2_auto_hook_x86_impl(mc2_proc_vararg<P, Ts...> in, mc2_proc_vararg_ptr<Ts...> out) { mc2_hook_x86_impl(in.ptr(), out.ptr); }
    mc2_auto_hook_x86_impl(mc2_proc_stdcall<P, Ts...> in, mc2_proc_stdcall_ptr<Ts...> out) { mc2_hook_x86_impl(in.ptr(), out.ptr); }
    mc2_auto_hook_x86_impl(mc2_proc_thiscall<P, Ts...> in, mc2_proc_thiscall_ptr<Ts...> out) { mc2_hook_x86_impl(in.ptr(), out.ptr); }
};


template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc<P, Ret, Args...> in, mc2_proc_ptr<Ret, Args...> out) { return { in, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc<P, Ret, Args...> in, Ret(__cdecl *out)(Args...)) { return { in, mc2_proc_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_vararg<P, Ret, Args...> in, mc2_proc_vararg_ptr<Ret, Args...> out) { return { in, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_vararg<P, Ret, Args...> in, Ret(__cdecl *out)(Args..., ...)) { return { in, mc2_proc_vararg_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_stdcall<P, Ret, Args...> in, mc2_proc_stdcall_ptr<Ret, Args...> out) { return { in, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_stdcall<P, Ret, Args...> in, Ret(__stdcall *out)(Args...)) { return { in, mc2_proc_stdcall_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, mc2_proc_thiscall_ptr<Ret, T, Args...> out) { return { in, out }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, Ret(__thiscall *out)(T *, Args...)) { return { in, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86(mc2_proc_thiscall<P, Ret, T, Args...> in, Ret(__thiscall T::*out)(Args...)) { return { in, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

#define AUTO_HOOK_X86(in, out) static const auto _hookobj_##in (mc2_auto_hook_x86(in, out))


template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86_addr(mc2_proc_ptr<Ret, Args...> out) { return { mc2_proc<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_x86_addr(Ret(__cdecl *out)(Args...)) { return { mc2_proc<P, Ret, Args...>{}, mc2_proc_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_vararg_x86_addr(mc2_proc_vararg_ptr<Ret, Args...> out) { return { mc2_proc_vararg<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_vararg_x86_addr(Ret(__cdecl *out)(Args..., ...)) { return { mc2_proc_vararg<P, Ret, Args...>{}, mc2_proc_vararg_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_stdcall_x86_addr(mc2_proc_stdcall_ptr<Ret, Args...> out) { return { mc2_proc_stdcall<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_stdcall_x86_addr(Ret(__stdcall *out)(Args...)) { return { mc2_proc_stdcall<P, Ret, Args...>{}, mc2_proc_stdcall_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_thiscall_x86_addr(mc2_proc_thiscall_ptr<Ret, T *, Args...> out) { return { mc2_proc_thiscall<P, T, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_thiscall_x86_addr(Ret(__thiscall *out)(T *, Args...)) { return { mc2_proc_thiscall<P, Ret, T, Args...>{}, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_x86_impl<P, Ret, Args...> mc2_auto_hook_thiscall_x86_addr(Ret(__thiscall T::*out)(Args...)) { return { mc2_proc_thiscall<P, Ret, T, Args...>{}, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

#define AUTO_HOOK_X86_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_x86_impl<(in)>((out)))
#define AUTO_HOOK_VARARG_X86_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_vararg_x86_addr<(in)>((out)))
#define AUTO_HOOK_STDCALL_X86_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_stdcall_x86_addr<(in)>((out)))
#define AUTO_HOOK_THISCALL_X86R_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_thiscall_x86_addr<(in)>((out)))


template<class... Ts>
struct mc2_auto_hook_fnptr_impl {
    mc2_auto_hook_fnptr_impl(mc2_proc_ptr<Ts...> &in, mc2_proc_ptr<Ts...> out) { in = out; }
    mc2_auto_hook_fnptr_impl(mc2_proc_vararg_ptr<Ts...> &in, mc2_proc_vararg_ptr<Ts...> out) { in = out; }
    mc2_auto_hook_fnptr_impl(mc2_proc_stdcall_ptr<Ts...> &in, mc2_proc_stdcall_ptr<Ts...> out) { in = out; }
    mc2_auto_hook_fnptr_impl(mc2_proc_thiscall_ptr<Ts...> &in, mc2_proc_thiscall_ptr<Ts...> out) { in = out; }
};


template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_ptr<Ret, Args...> &in, mc2_proc_ptr<Ret, Args...> out) { return { in, out }; }

template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_ptr<Ret, Args...> &in, Ret(__cdecl *out)(Args...)) { return { in, mc2_proc_ptr<Ret, Args...>(out) }; }

template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_vararg_ptr<Ret, Args...> &in, mc2_proc_vararg_ptr<Ret, Args...> out) { return { in, out }; }

template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_vararg_ptr<Ret, Args...> &in, Ret(__cdecl *out)(Args..., ...)) { return { in, mc2_proc_vararg_ptr<Ret, Args...>(out) }; }

template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_stdcall_ptr<Ret, Args...> &in, mc2_proc_stdcall_ptr<Ret, Args...> out) { return { in, out }; }

template<class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_stdcall_ptr<Ret, Args...> &in, Ret(__stdcall *out)(Args...)) { return { in, mc2_proc_stdcall_ptr<Ret, Args...>(out) }; }

template<class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_thiscall_ptr<Ret, Args...> &in, mc2_proc_thiscall_ptr<Ret, Args...> out) { return { in, out }; }

template<class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_thiscall_ptr<Ret, T, Args...> &in, Ret(__thiscall *out)(T *, Args...)) { return { in, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

template<class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr(mc2_proc_thiscall_ptr<Ret, T, Args...> &in, Ret(__thiscall T::*out)(Args...)) { return { in, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

#define AUTO_HOOK_FNPTR(in, out) static const auto _hookobj_##in (mc2_auto_hook_fnptr((in), (out)))


template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr_addr(mc2_proc_ptr<Ret, Args...> out) { return { &mc2_proc<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_fnptr_addr(Ret(__cdecl *out)(Args...)) { return { &mc2_proc<P, Ret, Args...>{}, mc2_proc_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_vararg_fnptr_addr(mc2_proc_vararg_ptr<Ret, Args...> out) { return { &mc2_proc_vararg<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_vararg_fnptr_addr(Ret(__cdecl *out)(Args..., ...)) { return { &mc2_proc_vararg<P, Ret, Args...>{}, mc2_proc_vararg_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_stdcall_fnptr_addr(mc2_proc_stdcall_ptr<Ret, Args...> out) { return { &mc2_proc_stdcall<P, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_stdcall_fnptr_addr(Ret(__stdcall *out)(Args...)) { return { &mc2_proc_stdcall<P, Ret, Args...>{}, mc2_proc_stdcall_ptr<Ret, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_thiscall_fnptr_addr(mc2_proc_thiscall_ptr<Ret, T *, Args...> out) { return { &mc2_proc_thiscall<P, T, Ret, Args...>{}, out }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_thiscall_fnptr_addr(Ret(__thiscall *out)(T *, Args...)) { return { &mc2_proc_thiscall<P, Ret, T, Args...>{}, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

template<std::uintptr_t P, class Ret, class T, class... Args>
mc2_auto_hook_fnptr_impl<Ret, Args...> mc2_auto_hook_thiscall_fnptr_addr(Ret(__thiscall T::*out)(Args...)) { return { &mc2_proc_thiscall<P, Ret, T, Args...>{}, mc2_proc_thiscall_ptr<Ret, T, Args...>(out) }; }

#define AUTO_HOOK_FNPTR_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_fnptr_addr<(in)>((out)))
#define AUTO_HOOK_VARARG_FNPTR_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_vararg_fnptr_addr<(in)>((out)))
#define AUTO_HOOK_STDCALL_FNPTR_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_stdcall_fnptr_addr<(in)>((out)))
#define AUTO_HOOK_THISCALL_FNPTR_ADDR(in, out) static const auto _hookobj_##in (mc2_auto_hook_thiscall_fnptr_addr<(in)>((out)))


// Functions

constexpr mc2_proc<0x0061AB10, char *, char *, char> MC2_STRRCHR; // Dont use
constexpr mc2_proc<0x0061A5DC, std::uint32_t, char *> sub_61A5DC;
constexpr mc2_proc<0x006198B5, int, char *, char *, va_list> MC2_VSPRINTF; // Use vsnprintf instead

// Global Variables

constexpr mc2_pointer<0x0067A760, void *> loc_67A760;
constexpr mc2_pointer<0x0067A770, void> loc_67A770;
constexpr mc2_pointer<0x00682E18, bool> loc_682E18;
constexpr mc2_pointer<0x008602C8, std::uint32_t> loc_8602C8;
constexpr mc2_pointer<0x00679778, bool> loc_679778;

// MC2 Pre-Main Stuff
constexpr mc2_proc<0x0061958A, void> mc2_crt_start_main;
constexpr mc2_proc<0x0061970D, void> mc2_crt_call_main;
constexpr mc2_proc<0x00619754, void> mc2_crt_end_main;
