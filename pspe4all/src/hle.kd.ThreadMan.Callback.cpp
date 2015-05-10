/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

////

char const * hle::kd::Callback::m_object_type = "KernelCallback";

void hle::kd::Callback::GetQuickInfos(char * data, size_t size)
{
    ::strncpy(data, GetType(), size-1);
}

hle::kd::Callback::Callback(char const * name, SceKernelCallbackFunction callback, u32 cookie)
:   WaitQueue(name, 0)
,   m_uses(0)
,   m_invalid(false)
,   m_thread(0)
,   m_notify_count(0)
,   m_notify_arg(0)
,   m_function(callback)
,   m_cookie(cookie)
,   m_gp(0)
{
}

hle::kd::Callback::~Callback()
{
    //TODO: not the right place...
    if (this->m_thread)
    {
        this->RemoveFromList();
    }
}

int hle::kd::Callback::Create(char const * name, SceKernelCallbackFunction function, u32 cookie, int intr)
{
    (void)intr;

    Callback * callback       = new Callback(name, function, cookie);
    Thread   * current_thread = g_scheduler->GetCurrentThread();

    callback->m_thread = current_thread;
    callback->m_gp     = current_thread->m_thread_context.gpr[ALLEGREX_GP];

    g_scheduler->GetCurrentThread()->m_callbacks.Append(callback);

    return callback->GetUid();
}

int hle::kd::Callback::Delete(int intr)
{
    if (intr && g_scheduler->m_dispatch_thread_suspended)
    {
        return SCE_KERNEL_ERROR_CAN_NOT_WAIT;
    }

    if (this->m_invalid)
    {
        return SCE_KERNEL_ERROR_UNKNOWN_CBID;
    }

    this->m_invalid = true;

    while (this->m_uses > 0)
    {
        int result = AddWaitingThread(this->m_thread, WAITTYPE_CALLBACK, 0, 0);

        if (result)
        {
            return result;
        }
    }

    return WaitQueue::Delete(intr);
}

int hle::kd::Callback::Notify(int arg, int intr)
{
    Thread * owner_thread = this->m_thread;

    int is_intr_context = hleKernelIsIntrContext();

    owner_thread->m_callback_notify = true;

    this->m_notify_arg = arg;
    this->m_notify_count++;

    if (owner_thread->m_check_callbacks)
    {
        if (owner_thread->m_status & Thread::STATUS_WAIT)
        {
            bool released = owner_thread->ReleaseWaitingThread();
            if (released)
            {
                g_scheduler->AddThreadToReadyQueue(owner_thread);
            }

            owner_thread->m_callback_status = SCE_KERNEL_ERROR_NOTIFY_CALLBACK;

            if (released)
            {
                g_scheduler->m_elected_thread = 0;

                if (!is_intr_context)
                {
                    owner_thread->ReleaseWait(0, intr);
                }
            }
        }
    }

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Callback::Cancel(int)
{
    this->m_notify_arg   = 0;
    this->m_notify_count = 0;

    return SCE_KERNEL_ERROR_OK;
}

int hle::kd::Callback::GetCount(int)
{
    return this->m_notify_count;
}

int hle::kd::Callback::Check(int intr)
{
    if (this->m_thread->m_callback_notify)
    {
        return int(this->m_thread->DispatchCallbacks(intr) > 0);
    }

    return 0;
}

int hle::kd::Callback::ReferStatus(SceKernelCallbackInfo * info, int)
{
    size_t size = info->size < sizeof(SceKernelCallbackInfo) ? info->size : sizeof(SceKernelCallbackInfo);

    if (size >= sizeof(SceKernelStructureSize))
    {
        ::memset(info, 0, size);

        info->size = sizeof(SceKernelCallbackInfo);

        if (size >= sizeof(SceKernelStructureName))
        {
            if (this->m_name)
            {
                ::strncpy(info->name, this->m_name, sizeof(this->m_name) - 1);
            }

            if (size >= sizeof(SceKernelStructureAttr))
            {
                info->attributes = this->m_attributes;

                if (size >= sizeof(SceKernelCallbackInfo))
                {
                    info->thread_id       = this->m_thread->m_uid;
                    info->callback        = this->m_function;
                    info->cookie          = this->m_cookie;
                    info->notify_count    = this->m_notify_count;
                    info->notify_arg      = this->m_notify_arg;
                }
            }
        }
    }

    return 0;
}


int sub_00002574(u32 /*function*/, int /*notify_count*/, int /*arg*/, u32 /*cookie*/, int /*gp*/)
{
    return 0;
}

int hle::kd::Thread::DispatchCallbacks(int intr)
{
    this->m_callback_notify = false;

    int deleted = 0;
    int count = 0;

    Callback * callback, * next_callback = nullptr;

    for (callback = this->m_callbacks.First(); callback; callback = next_callback)
    {
        int notify_count = callback->m_notify_count;
        if (notify_count && !callback->m_invalid)
        {
            u32 notify_arg = callback->m_notify_arg;
            callback->m_notify_count = false;
            callback->m_notify_arg   = 0;
            callback->m_uses++;
            count++;

            this->m_callback = callback;

            if (sub_00002574(callback->m_function, notify_count, notify_arg, callback->m_cookie, callback->m_gp))
            {
                callback->m_invalid = 1;
            }

            this->m_callback = 0;

            callback->m_uses--;

            next_callback = this->m_callbacks.Next(callback);

            if (callback->m_invalid && !callback->m_uses)
            {
                callback->RemoveFromList();

                deleted += 0/*sub_000004C0(cb, 0)*/; // cancel_timeout ?
            }
        }
    }

    if (deleted)
    {
        g_scheduler->m_elected_thread = 0;
        this->ReleaseWait(0, intr);
    }

    return count;
}

#if 0
int sub_00002574(int user_mode, int EPC, int a0, int a1, int a2, int gp)
{
    struct SceThreadContext context;

    int tmp1 = gInfo.currentThread->kStackPointer;
    int tmp2 = gInfo.currentThread->scContext;
    int tmp3 = gInfo.currentThread->callbackContext;

    _CheckThreadKernelStack();

    if(SaveThreadContext(&context) != 0)
    {
        gInfo.currentThread->kStackPointer = tmp1;
        gInfo.currentThread->scContext = tmp2;
        gInfo.currentThread->callbackContext = tmp3;

        _CTC0(tmp1, COP0_CR_GPR_SP_USER);

        return gInfo.currentThread->callbackStatus;
    }

    gInfo.currentThread->callbackContext = &context;

    void *stack;
    {
        if(gInfo.currentThread->scContext == 0)
        {
            stack = gInfo.currentThread->stackPointer;
        }
        else
        {
            stack = gInfo.currentThread->scContext->sp;
        }

        //265c
        stack -= 0x40;

        ((u32 *)stack)[0] = MAKE_SYSCALL(gInfo.unk_69C);
        ((u32 *)stack)[1] = 0;
        ((u32 *)stack)[2] = 0;
        ((u32 *)stack)[3] = 0;
        _CACHE(0x1B, stack);
        _CACHE(0x8, stack);
    }

    //clear the thread's context
    ResetThreadContext(gInfo.currentThread->threadContext);

    gInfo.currentThread->threadContext->type = 0x4;
    gInfo.currentThread->threadContext->gpr[GPREG_A0 - 1] = a0;
    gInfo.currentThread->threadContext->gpr[GPREG_A1 - 1] = a1;
    gInfo.currentThread->threadContext->gpr[GPREG_A2 - 1] = a2;
    gInfo.currentThread->threadContext->gpr[GPREG_A3 - 1] = a3;
    gInfo.currentThread->threadContext->gpr[GPREG_GP - 1] = gp;
    gInfo.currentThread->threadContext->gpr[GPREG_SP - 1] = stack;
    gInfo.currentThread->threadContext->gpr[GPREG_FP - 1] = stack;
    gInfo.currentThread->threadContext->gpr[GPREG_RA - 1] = stack;
    gInfo.currentThread->threadContext->EPC = EPC;
    gInfo.currentThread->kStackPointer = gInfo.currentThread->callbackContext->gpr[GPREG_SP - 1];

    _CTC0(gInfo.currentThread->kStackPointer, COP0_CR_GPR_SP_USER);

    ReturnToThread(gInfo.currentThread->threadContext);

    return SCE_KERNEL_ERROR_OK;
}
#endif
