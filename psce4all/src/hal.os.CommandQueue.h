/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "hal.os.win32.h"
#include "hal.os.Thread.h"

namespace hal
{
    namespace os
    {
        struct CommandQueue : protected win32::IoCompletionPort
        {
        private:
            struct Command : win32::SinglyLinkedList::Entry
            {
                /**/        Command()
                {
                }

                virtual    ~Command()
                {
                }

                void      * operator new(size_t size)
                {
                    (void)size;
                    assert(size <= 64*sizeof(u32));

                    Command * new_command = m_command_pool.Pop< Command >();

                    if (!new_command)
                    {
                        // no more command free so allocate one
                        new_command = (Command *)_aligned_malloc(64*sizeof(u32), MEMORY_ALLOCATION_ALIGNMENT);
                    }

                    return new_command;
                }

                void        operator delete(void * pointer)
                {
                    if (pointer)
                    {
                        m_command_pool.Push((Command *)pointer);
                    }
                }

                static ::hal::os::win32::SinglyLinkedList m_command_pool;
            };

        public:
            template< typename T >
            struct Command$ : Command
            {
                virtual void Run(T *) = 0;
            };

            /**/             CommandQueue(bool initialize = true)
            {
                if (initialize) Create();
            }

            /**/            ~CommandQueue()
            {
            }

            void             Create()
            {
                win32::IoCompletionPort::Create();
            }

            void             Delete()
            {
                win32::IoCompletionPort::Delete();
            }

            template< typename T >
            bool             Enqueue(Command$< T > * command)
            {
                Packet packet;
                packet.key_context = command;
                packet.apc_context = 0;
                packet.information = 0;
                packet.status      = 0;
                return win32::IoCompletionPort::Post(packet);
            }

            template< typename T >
            Command$< T >  * Dequeue(u64 timeout = -1LL)
            {
                Command$< T > * command = 0;
                Packet          packet;
                LARGE_INTEGER   timeout_100ns;
                bool            result;

                if (timeout)
                {
                    timeout_100ns.QuadPart = timeout * -10LL;

                    //__ThreadPriority(THREAD_PRIORITY_TIME_CRITICAL)
                    {
                        result = win32::IoCompletionPort::Wait(packet, (timeout == -1LL ? 0 : &timeout_100ns));
                    }
                }
                else
                {
                    result = win32::IoCompletionPort::Peek(packet);
                }

                return result ? command : 0;
            }

            template< typename T >
            bool             Dequeue(Command$< T > *& command, u64 timeout = -1LL)
            {
                return 0 != (Dequeue< T >(timeout));
            }

            template< typename T >
            void             Proceed(T * that, s64 timeout = -1LL, bool one = false)
            {
                Command$< T > * command = 0;

                while ((command = Dequeue< T >(timeout)) != 0)
                {
                    command->Run(that);

                    delete command;

                    timeout = 0LL;

                    if (one) break;
                }
            }

        private:
        };

        __weaksymbol ::hal::os::win32::SinglyLinkedList CommandQueue::Command::m_command_pool;
    }
}
