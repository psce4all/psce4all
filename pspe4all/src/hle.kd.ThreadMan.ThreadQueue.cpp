/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

int hle::kd::ThreadQueue::AddWaitingThread(Thread * this_thread, int wait_type)
{
    this->Append(this_thread);
    this_thread->m_status          = Thread::STATUS_WAIT;
    this_thread->m_wait_type       = wait_type;
    this_thread->m_wait_queue      = 0; // no KernelWaitQueue
    this_thread->m_callback_status = 0;

    return 0;
}

void hle::kd::ThreadQueue::InsertWaitingThread(Thread * this_thread)
{
    Thread * that_thread = this->First();

    if (!that_thread)
    {
        this->Append(this_thread);
    }
    else
    {
        for (; that_thread; that_thread = that_thread->Next(that_thread))
        {
            if (that_thread->m_current_priority > this_thread->m_current_priority)
            {
                break;
            }
        }

        this_thread->InsertInListBefore(that_thread);
    }
}
