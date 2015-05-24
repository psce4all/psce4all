/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifdef __cplusplus

#if defined(__x86_64__) /* gcc */ || defined(__amd64__) /* gcc */ || defined(_M_X64) /* msvc */ || defined(_M_AMD64) /* msvc */
#   define __arch_x86__
#   define __arch_x86_64__
#elif defined(__i386__) /* gcc */ || defined(_M_IX86) /* msvc */
#   define __arch_x86__
#   define __arch_x86_32__
#else
#   define __arch_unknown__
#endif

#if defined(_WIN64) || defined(__WIN64__)
#   define __win64__
#elif defined(_WIN32) || defined(__WIN32__)
#   define __win32__
#elif defined(__BEOS__)
#   define __beos__
#elif defined(macintosh)
#   define __macintosh__
#elif defined(__APPLE__)
#   define __macosx__
#elif defined(__sgi)
#   define __irix__
#elif defined(_AIX)
#   define __aix__
#elif defined(SOLARIS) || defined(sun)
#   define __solaris__
#elif defined(hpux)
#   define __hpux__
#elif (defined(__unix__) || defined(unix)) && !defined(USG)
#   define __bsd__
#endif

#if defined(__win32__) || defined(__win64__)
#   if defined(__CYGWIN__)
#       define __cygwin__
#       define __gnuc__
#   elif defined(_MSC_VER)
#       define __msvc__
#   elif defined(__GNUC__)
#       define __mingw__
#       define __gnuc__
#   endif
#elif defined(__GNUC__)
#   define __gnuc__
#endif

#if defined(__msvc__) || defined(__mingw__)
#   define _WIN32_WINNT 0x601
#   define WINVER 0x0600
#   ifndef _WIN32_IE
#       define _WIN32_IE 0x0601
#   endif
#   define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   include <intrin.h>
#   define HAS_NATIVE_FIBERS 1
#   include <wchar.h>
#   include <tchar.h>
#   include <process.h>
#   include <mmsystem.h>
#else
#   include <sys/time.h>
#   include <sys/mman.h>
#   include <sys/stat.h>
#   include <fcntl.h>
#   include <unistd.h>
#   include <cerrno>
#   include <cstring>
#   if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#       define MAP_ANONYMOUS MAP_ANON
#   endif
#endif

#if defined(__arch_x86_32__) || defined(__arch_x86_64__)
#   include <xmmintrin.h>
#endif

#define bswap16(x) ((x)>>8 | ((x)&255)<<8)
#define bswap32(x) ((bswap16((x)>>16)&65535)|(bswap16((x)&65535)<<16))

#define _USE_MATH_DEFINES
#include <cfloat>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <queue>

typedef int64_t   s64, i64;
typedef int32_t   s32, i32;
typedef int16_t   s16, i16;
typedef int8_t    s8,  i8;
typedef uint64_t  u64;
typedef uint32_t  u32;
typedef uint16_t  u16;
typedef uint8_t   u8;
typedef float     f32;
typedef double    f64;

//typedef intptr_t  sint;
//typedef uintptr_t uint;

struct u16le
{
    u16 value;
    u16le(u32 const & source) : value(*((u16 *)&source)) {}
    u16le(u8  const & source) : value(*((u16 *)&source)) {}
    u16le(u16 const & source) : value(*((u16 *)&source)) {}
    operator u16       & ()                              { return value; }
    operator u16 const & () const                        { return value; }
};

struct u32le
{
    u32 value;
    u32le(u32 const & source) : value(*((u32 *)&source)) {}
    u32le(u8  const & source) : value(*((u32 *)&source)) {}
    u32le(u16 const & source) : value(*((u32 *)&source)) {}
    operator u32       & ()                              { return value; }
    operator u32 const & () const                        { return value; }
};

struct u64le
{
    u64 value;
    u64le(u64 const & source) : value(*((u64 *)&source)) {}
    u64le(u8  const & source) : value(*((u64 *)&source)) {}
    u64le(u16 const & source) : value(*((u64 *)&source)) {}
    u64le(u32 const & source) : value(*((u64 *)&source)) {}
    operator u64       & ()                              { return value; }
    operator u64 const & () const                        { return value; }
};

#if defined(__msvc__)
#   pragma warning(disable:4100;disable:4127;disable:4200;disable:4706;disable:4714;disable:4996)
#   define __weaksymbol         __declspec(selectany)
#   define __aligned(n)       __declspec(align(n))
#   define aligned__(n)
#   define __noinline           __declspec(noinline)
#   define __returnaddress      _ReturnAddress
#   define __returnaddressptr   _AddressOfReturnAddress
#   undef  Yield // This windows macro is never used in our project so we un-define it as we need it as name of a method
#elif defined(__gnuc__)
#   define __weaksymbol         __attribute__((weak))
#   define __aligned(n)
#   define aligned__(n)         __attribute__((aligned(n)))
#   define __forceinline        inline __attribute__((always_inline))
#   define __noinline           __attribute__((noinline))
#   define __debugbreak         __builtin_trap
#   define __returnaddress()    (__builtin_return_address(0))
#   define __returnaddressptr() (&(((void **)(__builtin_frame_address(0)))[1]))
#endif

#if defined(__msvc__)
#   if defined(NDEBUG)
#       define __release__
#   else
#       define __debug__
#   endif
#   define inline   __inline
#   define snprintf _snprintf
#   include <assert.h>
#elif defined(__gnuc__)
#   define _scalb  ldexp
#   define _isnan  isnan
#   define _finite finite
#endif

#undef min
#undef max

template< typename T > T min(T a, T b) { return a <= b ? a : b; }
template< typename T > T max(T a, T b) { return a >= b ? a : b; }

#undef __min
#undef __max

template< typename T > T __min(T x, T y) { return x < y ? x : y; }
template< typename T > T __max(T x, T y) { return x > y ? x : y; }
template< typename T > T __clamp(T x, T v, T y) { return __max(x, __min(v, y)); }

namespace detail { template< typename T, size_t N > char (&SIZEOF_ARRAY_REQUIRES_ARRAY_ARGUMENT(T (&)[N]))[N]; }

#define sizeof_array(x) sizeof(detail::SIZEOF_ARRAY_REQUIRES_ARRAY_ARGUMENT(x))

template< typename T > bool __inrange(T a, T x, T b) { return a <= x && x < b; }

#define _STR_(x) #x
#define __STR__(x) _STR_(x)

// NO_TODO: to be uncommented if you don't want to see TODOs when compiling
#define NO_TODO

#ifndef NO_TODO
#   if defined(__msvc__)
#       define TODO(x) __pragma (message (__FILE__ "(" __STR__(__LINE__) ") : TODO[" __FUNCTION__ "] - " #x))
#   elif defined(__gnuc__)
#       define DO_PRAGMA(x) _Pragma (#x)
#       define TODO(x) DO_PRAGMA(message ("TODO[" __FILE__ ":" __STR__(__LINE__) ":" __FUNCTION__ "] - " #x))
#   else
#       define TODO(x)
#   endif
#else
#   define TODO(x)
#endif

#if 1
#define __new       new
#define __delete    delete
//#include "mmgr.h"
//#define USE_MMGR
#endif

#if defined(__debug__)
#   define __Configuration(debug,release) debug
#   define __ConfigurationDll(name) name##d.dll
#   define __ConfigurationDllStringA(name) name "d.dll"
#   define __ConfigurationDllStringW(name) name L"d.dll"
#else
#   define __Configuration(debug,release) release
#   define __ConfigurationDll(name) name##.dll
#   define __ConfigurationDllStringA(name) name ".dll"
#   define __ConfigurationDllStringW(name) name L".dll"
#endif

#if defined(__win32__) || defined(__win64__)
#include "Winternl.h"

extern "C"
{
    extern PVOID   __declspec(dllimport) NTAPI RtlCreateHeap(ULONG Flags, PVOID HeapBase, SIZE_T ReserveSize, SIZE_T CommitSize, PVOID Lock, PVOID Parameters);
    extern PVOID   __declspec(dllimport) NTAPI RtlDestroyHeap(PVOID HeapHandle);
    extern PVOID   __declspec(dllimport) NTAPI RtlAllocateHeap(PVOID HeapHandle, ULONG Flags, SIZE_T Size);
    extern BOOLEAN __declspec(dllimport) NTAPI RtlFreeHeap(PVOID HeapHandle, ULONG Flags, PVOID HeapBase);
}

#if 0
extern "C"
{
    extern NTSTATUS NTAPI NtClose(HANDLE Handle);

    extern NTSTATUS NTAPI NtCreateIoCompletion(PHANDLE IoCompletionHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes, ULONG NumberOfConcurrentThreads);
    extern NTSTATUS NTAPI NtSetIoCompletion(HANDLE IoCompletionPortHandle, PVOID CompletionKey, PVOID CompletionContext, NTSTATUS CompletionStatus, ULONG CompletionInformation);
    extern NTSTATUS NTAPI NtRemoveIoCompletion(HANDLE IoCompletionHandle, PVOID * KeyContext, PVOID * ApcContext, PIO_STATUS_BLOCK IoStatusBlock, PLARGE_INTEGER Timeout = 0);

    extern NTSTATUS NTAPI NtQueryPerformanceCounter(PLARGE_INTEGER Counter, PLARGE_INTEGER Frequency = 0);

    extern NTSTATUS NTAPI NtSetTimerResolution(ULONG DesiredResolution, BOOLEAN SetResolution, PULONG CurrentResolution);
    extern NTSTATUS NTAPI NtQueryTimerResolution(PULONG MinimumResolution, PULONG MaximumResolution, PULONG ActualResolution);

    extern NTSTATUS NTAPI NtYieldExecution(VOID);
    extern NTSTATUS NTAPI NtDelayExecution(BOOLEAN Alertable, PLARGE_INTEGER DelayInterval);
};
#endif
#endif

#endif // __cplusplus
