/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "hal.win32.h"

namespace hal
{
    enum MemoryOrder
    {
        MemoryOrderRelaxed,
        MemoryOrderConsume,
        MemoryOrderAcquire,
        MemoryOrderRelease,
        MemoryOrderAcqRel,
        MemoryOrderSeqCst,
    };

    template< typename T, int bytes = sizeof(T) >
    class Atomic_select;

    template< typename T >
    class Atomic_select< T, 1 >
    {
    protected:
        typedef char R;
    };

    template< typename T >
    class Atomic_select< T, 2 >
    {
    protected:
        typedef short R;
    };

    template< typename T >
    class Atomic_select< T, 4 >
    {
    protected:
        typedef long R;
    };

    template< typename T >
    class Atomic_select< T, 8 >
    {
    protected:
        typedef long long R;
    };

    template< typename T > class Atomic : public Atomic_select< T >
    {
    public:
        Atomic() : m_value(T()) {}
        Atomic(T const &value) : m_value(value) {}

        // non-volatile
        __forceinline T Load(MemoryOrder mo = MemoryOrderSeqCst) const
        {
            (void)mo;
            assert(mo == MemoryOrderRelaxed
                || mo == MemoryOrderConsume
                || mo == MemoryOrderAcquire
                || mo == MemoryOrderSeqCst);
            T v = m_value;
            AtomicReadWriteBarrier();
            return v;
        }

        __forceinline void Store(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            assert(mo == MemoryOrderRelaxed
                || mo == MemoryOrderRelease
                || mo == MemoryOrderSeqCst);

            if (mo == MemoryOrderSeqCst)
            {
                AtomicExchange((R volatile*)&m_value, R(v));
            }
            else
            {
                AtomicReadWriteBarrier();
                m_value = v;
            }
        }

        __forceinline T Exchange(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicExchange((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline bool CompareExchange(T & cmp, T xchg, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicCompareExchange((R volatile*)&m_value, R(xchg), R(cmp));
            if (prev == cmp)
            {
                return true;
            }
            cmp = prev;
            return false;
        }

        __forceinline T FetchBeforeAdd(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicFetchAdd((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline T FetchBeforeSub(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicFetchSub((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline T FetchBeforeAnd(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicFetchAnd((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline T FetchBeforeOr(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicFetchOr((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline T FetchBeforeXor(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            (void)mo;
            T prev = (T)AtomicFetchXor((R volatile*)&m_value, R(v));
            return prev;
        }

        __forceinline T FetchAfterAdd(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            return FetchBeforeAdd(v, mo) + v;
        }

        __forceinline T FetchAfterSub(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            return FetchBeforeSub(v, mo) - v;
        }

        __forceinline T FetchAfterAnd(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            return FetchBeforeAnd(v, mo) & v;
        }

        __forceinline T FetchAfterOr(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            return FetchBeforeOr(v, mo) | v;
        }

        __forceinline T FetchAfterXor(T v, MemoryOrder mo = MemoryOrderSeqCst)
        {
            return FetchBeforeXor(v, mo) ^ v;
        }


    //  Atomic()                                     = default;
    //   ~Atomic()                                     = default;
        Atomic(Atomic const &)                       /*= delete*/;
        Atomic & operator = (Atomic const&)          /*= delete*/;

        operator T() const              { return Load(); }
        T operator =(T value)           { Store(value); return value; }

        T operator ++()                 { return FetchAfterAdd(T(1)); }
        T operator --()                 { return FetchAfterSub(T(1)); }
        T operator ++(int)              { return FetchBeforeAdd(T(1)); }
        T operator --(int)              { return FetchBeforeSub(T(1)); }

        T operator +=(T value)          { return FetchBeforeAdd(value); }
        T operator -=(T value)          { return FetchBeforeSub(value); }
        T operator &=(T value)          { return FetchBeforeAnd(value); }
        T operator |=(T value)          { return FetchBeforeOr (value); }
        T operator ^=(T value)          { return FetchBeforeXor(value); }

    private:
        T volatile m_value;
    };
}
