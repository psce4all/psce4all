/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

namespace hal
{
    template < typename T >
    struct LinkedList // T must derive from LinkedList::Node
    {
        T * m_next;
        T * m_prev;

        typedef LinkedList Node;

        LinkedList() { ClearList(); }

        __forceinline void ClearList() { m_next = m_prev = static_cast<T *>(this); }
        __forceinline void InsertInListBefore(T * that) { this->m_next = that; this->m_prev = that->m_prev; that->m_prev = static_cast<T *>(this); this->m_prev->m_next = static_cast<T *>(this); }
        __forceinline void InsertInListAfter(T * that) { this->InsertInListBefore(that->m_next); }
        __forceinline void Append(T * that) { that->InsertInListBefore(static_cast<T *>(this)); }
        __forceinline void Prepend(T * that) { that->InsertInListAfter(static_cast<T *>(this)); }
        __forceinline void RemoveFromList() { T * n = this->m_next; n->m_prev = this->m_prev; this->m_prev->m_next = n; this->m_next = static_cast<T *>(this); this->m_prev = static_cast<T *>(this); }

        __forceinline T * Next(T * that) { return (that->m_next == static_cast<T *>(this)) ? 0 : that->m_next; }
        __forceinline T * Prev(T * that) { return (that->m_prev == static_cast<T *>(this)) ? 0 : that->m_prev; }
        __forceinline T * First() { return (this->m_next == static_cast<T *>(this)) ? 0 : this->m_next; }
        __forceinline T * Last() { return (this->m_prev == static_cast<T *>(this)) ? 0 : this->m_prev; }

        __forceinline void Clear() { ClearList(); }
        __forceinline bool Empty() const { return m_next == static_cast<T const *>(this); }
        __forceinline size_t Count() const { size_t result = 0; for (T * i = this->m_next; i != static_cast<T const *>(this); i = i->m_next) ++result; return result; }
        __forceinline size_t Size() const { return this->Count(); }
        __forceinline T const & Front() const { return *this->m_next; }
        __forceinline T & Front() { return *this->m_next; }
        __forceinline T const & Back() const { return *this->m_prev; }
        __forceinline T & Back() { return *this->m_prev; }
        __forceinline void PushFront(T & that) { this->Prepend(&that); }
        __forceinline void PushBack(T & that) { this->Append(&that); }
        __forceinline void PopFront() { if (!this->Empty()) this->m_prev->RemoveFromList(); }
        __forceinline void PopBack() { if (!this->Empty()) this->m_next->RemoveFromList(); }

        struct iterator
        {
            typedef T                          value_type;
            typedef ptrdiff_t                  difference_type;
            typedef T                        * pointer;
            typedef T                        & reference;
            typedef std::forward_iterator_tag  iterator_category;

            T * cur;
            T * end;

            __forceinline iterator & operator ++() { cur = cur->m_next; return *this; }
            __forceinline iterator & operator ++(int) { cur = cur->m_next; return *this; }
            __forceinline operator T *() const { return (cur != end) ? cur : 0; }
            __forceinline T const * operator *() const { return cur; }
            __forceinline T * operator *() { return cur; }
            __forceinline T const * operator ->() const { return cur; }
            __forceinline T * operator ->() { return cur; }

            iterator() : cur(0), end(0) {}
            iterator(iterator const &i) : cur(i.cur), end(i.end) {}

            // not std-like

            __forceinline bool operator !() const { return cur == end; }

            iterator(LinkedList const & list) : cur(list.m_next), end(&list) {}
        };
    };
}
