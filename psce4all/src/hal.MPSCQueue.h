/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "hal.hmm.h"
#include "hal.Atomic.h"
#include "hal.os.win32.h"

namespace hal
{
    template < typename T = void >
    struct MPSCQueue /* Intrusive Multiple Producers Single Consumer Queue */
    {
        struct Node // T must derive from MPSCQueue<>::Node
        {
            Node * volatile m_next;
        };

        Node * volatile m_head;
        Node *          m_tail;
        Node            m_stub;

        /**/            MPSCQueue()
        {
            this->m_stub.m_next = 0;
            this->m_head        = &m_stub;
            this->m_tail        = &m_stub;
        }

        /**/           ~MPSCQueue()
        {
            assert( // wow, that's a very powerful way to execute a complex expression inside assert through a call to a lambda function!
                (
                    "Queue must be empty",
                    (
                        [](MPSCQueue * that)
                        {
                            Node * tail = that->m_tail;
                            Node * next = tail->m_next;
                            return (tail == &that->m_stub && 0 == next);
                        }
                    )(this)
                )
            );
        }

        void            Enqueue(T * that)
        {
            Enqueue(static_cast< Node * >(that));
        }

        bool            Dequeue(T *& data)
        {
            Node * that = this->Dequeue();
            if (that)
            {
                data = static_cast< T * >(that);
                return true;
            }
            return false;
        }

    protected:
        void            Enqueue(Node * that)
        {
            that->m_next = 0;
            AtomicExchange(&this->m_head, that)->m_next = that;
        }

        Node          * Dequeue()
        {
            Node * tail = this->m_tail;
            Node * next = tail->m_next;
            if (tail == &this->m_stub)
            {
                if (0 == next)
                {
                    return 0;
                }
                this->m_tail = next;
                tail = next;
                next = next->m_next;
            }
            if (next)
            {
                this->m_tail = next;
                return tail;
            }
            Node * head = this->m_head;
            if (tail != head)
            {
                return 0;
            }
            Enqueue(&this->m_stub);
            next = tail->m_next;
            if (next)
            {
                this->m_tail = next;
                return tail;
            }
            return 0;
        }
    };

    template< >
    struct MPSCQueue< void > /* Non-intrusive Multiple Producers Single Consumer Queue */
    {
        struct Node : os::win32::SinglyLinkedList::Entry
        {
            Node * volatile m_next;
            void *          m_data;

            /**/        Node()         : m_next(0), m_data(0)
            {

            }

            template< typename T >
            /**/        Node(T * data) : m_next(0), m_data(data)
            {

            }

            /**/       ~Node()
            {
                m_data = 0;
            }

            void      * operator new(size_t size)
            {
                Node * new_node = m_node_pool.Pop< Node >();

                if (!new_node)
                {
                    // no more free node so allocate one
                    new_node = (Node *)hal::hmm::Allocate(typeid(Node).name(), size, __alignof(Node));
                }

                return new_node;
            }

            void        operator delete(void * pointer)
            {
                if (pointer)
                {
                    m_node_pool.Push((Node *)pointer);
                }
            }

            static void Flush()
            {
                m_done = true;
                Node * node, * next;
                if (m_node_pool.Flush(node))
                {
                    while (node)
                    {
                        next = static_cast< Node * >(node->Next);
                        hal::hmm::Free(node);
                        node = next;
                    }
                }
            }

            static os::win32::SinglyLinkedList m_node_pool;
            static bool                        m_done;
        };

        Node * volatile m_head;
        Node *          m_tail;
        Node            m_stub;

        /**/            MPSCQueue()
        {
            m_head     = &m_stub;
            m_tail     = &m_stub;
        }

        /**/           ~MPSCQueue()
        {
            assert(("Queue must be empty", (0 == this->m_tail->m_next)));
        }

        template< typename T >
        void            Enqueue(T * that)
        {
            if (!Node::m_done)
            {
                Enqueue(new Node(that));
            }
        }

        template< typename T >
        bool            Dequeue(T *& data)
        {
            Node * that = this->Dequeue();
            if (that)
            {
                data = static_cast< T * >(that);
                delete that;
                return true;
            }
            return false;
        }

    protected:
        void            Enqueue(Node * that)
        {
            that->m_next = 0;
            AtomicExchange(&this->m_head, that)->m_next = that;
        }

        Node          * Dequeue()
        {
            Node * tail = this->m_tail;
            Node * next = tail->m_next;
            if (next)
            {
                this->m_tail = next;
                return tail;
            }
            return 0;
        }
    };

    using MPSCQueuePool = MPSCQueue< void >::Node;
}
