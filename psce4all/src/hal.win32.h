/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

namespace hal
{
    namespace win32
    {
        __forceinline char    AtomicExchange       (char    volatile * target, char    value             ) { return _InterlockedExchange8        (target,  value     ); }
        __forceinline char    AtomicCompareExchange(char    volatile * target, char    value, char    old) { return _InterlockedCompareExchange8 (target,  value, old); }
        __forceinline char    AtomicFetchAdd       (char    volatile * target, char    value             ) { return _InterlockedExchangeAdd8     (target,  value     ); }
        __forceinline char    AtomicFetchSub       (char    volatile * target, char    value             ) { return _InterlockedExchangeAdd8     (target, -value     ); }
        __forceinline char    AtomicFetchAnd       (char    volatile * target, char    value             ) { return _InterlockedAnd8             (target,  value     ); }
        __forceinline char    AtomicFetchOr        (char    volatile * target, char    value             ) { return _InterlockedOr8              (target,  value     ); }
        __forceinline char    AtomicFetchXor       (char    volatile * target, char    value             ) { return _InterlockedXor8             (target,  value     ); }

        __forceinline short   AtomicExchange       (short   volatile * target, short   value             ) { return _InterlockedExchange16       (target,  value     ); }
        __forceinline short   AtomicCompareExchange(short   volatile * target, short   value, short   old) { return _InterlockedCompareExchange16(target,  value, old); }
        __forceinline short   AtomicFetchAdd       (short   volatile * target, short   value             ) { return _InterlockedExchangeAdd16    (target,  value     ); }
        __forceinline short   AtomicFetchSub       (short   volatile * target, short   value             ) { return _InterlockedExchangeAdd16    (target, -value     ); }
        __forceinline short   AtomicFetchAnd       (short   volatile * target, short   value             ) { return _InterlockedAnd16            (target,  value     ); }
        __forceinline short   AtomicFetchOr        (short   volatile * target, short   value             ) { return _InterlockedOr16             (target,  value     ); }
        __forceinline short   AtomicFetchXor       (short   volatile * target, short   value             ) { return _InterlockedXor16            (target,  value     ); }

        __forceinline long    AtomicExchange       (long    volatile * target, long    value             ) { return _InterlockedExchange         (target,  value     ); }
        __forceinline long    AtomicCompareExchange(long    volatile * target, long    value, long    old) { return _InterlockedCompareExchange  (target,  value, old); }
        __forceinline long    AtomicFetchAdd       (long    volatile * target, long    value             ) { return _InterlockedExchangeAdd      (target,  value     ); }
        __forceinline long    AtomicFetchSub       (long    volatile * target, long    value             ) { return _InterlockedExchangeAdd      (target, -value     ); }
        __forceinline long    AtomicFetchAnd       (long    volatile * target, long    value             ) { return _InterlockedAnd              (target,  value     ); }
        __forceinline long    AtomicFetchOr        (long    volatile * target, long    value             ) { return _InterlockedOr               (target,  value     ); }
        __forceinline long    AtomicFetchXor       (long    volatile * target, long    value             ) { return _InterlockedXor              (target,  value     ); }

#if defined(__win64__)
        __forceinline __int64 AtomicExchange       (__int64 volatile * target, __int64 value             ) { return _InterlockedExchange64       (target,  value     ); }
        __forceinline __int64 AtomicCompareExchange(__int64 volatile * target, __int64 value, __int64 old) { return _InterlockedCompareExchange64(target,  value, old); }
        __forceinline __int64 AtomicFetchAdd       (__int64 volatile * target, __int64 value             ) { return _InterlockedExchangeAdd64    (target,  value     ); }
        __forceinline __int64 AtomicFetchSub       (__int64 volatile * target, __int64 value             ) { return _InterlockedExchangeAdd64    (target, -value     ); }
        __forceinline __int64 AtomicFetchAnd       (__int64 volatile * target, __int64 value             ) { return _InterlockedAnd64            (target,  value     ); }
        __forceinline __int64 AtomicFetchOr        (__int64 volatile * target, __int64 value             ) { return _InterlockedOr64             (target,  value     ); }
        __forceinline __int64 AtomicFetchXor       (__int64 volatile * target, __int64 value             ) { return _InterlockedXor64            (target,  value     ); }
#endif
        __forceinline void    AtomicReadWriteBarrier() { _ReadWriteBarrier(); }

#if   defined(__win32__)
        template< typename T >
        __forceinline T * AtomicExchange       (T * volatile * target, T     * value         ) { return (T *)AtomicExchange       ((long    volatile *)target, (long   )value              ); }
        template< typename T >
        __forceinline T * AtomicCompareExchange(T * volatile * target, T     * value, T * old) { return (T *)AtomicCompareExchange((long    volatile *)target, (long   )value, (long   )old); }
        template< typename T >
        __forceinline T * AtomicFetchAdd       (T * volatile * target, long    value         ) { return (T *)AtomicFetchAdd       ((long    volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchSub       (T * volatile * target, long    value         ) { return (T *)AtomicFetchSub       ((long    volatile *)target,         -value              ); }
        template< typename T >
        __forceinline T * AtomicFetchAnd       (T * volatile * target, long    value         ) { return (T *)AtomicFetchAnd       ((long    volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchOr        (T * volatile * target, long    value         ) { return (T *)AtomicFetchOr        ((long    volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchXor       (T * volatile * target, long    value         ) { return (T *)AtomicFetchXor       ((long    volatile *)target,          value              ); }
#elif defined(__win64__)
        template< typename T >
        __forceinline T * AtomicExchange       (T * volatile * target, T     * value         ) { return (T *)AtomicExchange       ((__int64 volatile *)target, (__int64)value              ); }
        template< typename T >
        __forceinline T * AtomicCompareExchange(T * volatile * target, T     * value, T * old) { return (T *)AtomicCompareExchange((__int64 volatile *)target, (__int64)value, (__int64)old); }
        template< typename T >
        __forceinline T * AtomicFetchAdd       (T * volatile * target, __int64 value         ) { return (T *)AtomicFetchAdd       ((__int64 volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchSub       (T * volatile * target, __int64 value         ) { return (T *)AtomicFetchSub       ((__int64 volatile *)target,         -value              ); }
        template< typename T >
        __forceinline T * AtomicFetchAnd       (T * volatile * target, __int64 value         ) { return (T *)AtomicFetchAnd       ((__int64 volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchOr        (T * volatile * target, __int64 value         ) { return (T *)AtomicFetchOr        ((__int64 volatile *)target,          value              ); }
        template< typename T >
        __forceinline T * AtomicFetchXor       (T * volatile * target, __int64 value         ) { return (T *)AtomicFetchXor       ((__int64 volatile *)target,          value              ); }
#endif
    }

    using namespace win32;
}
