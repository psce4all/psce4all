/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include "hal.npa.h"
#include "hal.dbg.h"

/** version info */
#define AG_PERFMON_VERSION 0x06121900

/** Required for Event Sink/Src */
#ifdef UNICODE
#   define AG_PERFMON_LIB_NAME L"AgPerfMon.dll"
#else
#   define AG_PERFMON_LIB_NAME  "AgPerfMon.dll"
#endif

#define AG_PERFMON_API_INIT_EVENT_NAME "AgPerfMonApiInitEvent"
#define AG_EVENT_NAME_LEN              129
#define AG_INVALID_EVENT_ID            ((u16)0xffff)
#define AG_INVALID_PCM_ID              ((u8 )0xff  )

typedef u16    AgEventID;
typedef u32    AgPCMID;
typedef void * AgPmHANDLE;

typedef enum AgPcmEventGroup
{
    _agMipsEvent,
    _agVcuEvent,
    _agVpuEvent,
} AgPcmEventGroup;


typedef union AgPerfMonEvent
{
    struct
    {
        u16 eventID;
        u8  destMask;
        u8  vpeID;
        u32 timeStamp;
        u8  taskListID;
        u8  pcmID;
        u8  taskSeq;
        u8  vpuID;
        u32 vpeTime;
    };
    struct
    {
        u64 data[2];
    };
} AgPerfMonRemoteEvent;

typedef enum AgPerfMonAppType
{
    _agEventSrc,
    _agEventSink,
    _agEventCollector,
} AgPerfMonAppType;

#define AG_PERFMON_DLL_API extern "C" __declspec(dllexport)

typedef bool(*AgPassiveEventCallback)(void * context, AgEventID id);

#if 0
/** Event Source API */
AG_PERFMON_DLL_API AgPmHANDLE       AgPmCreateSourceConnection(u32 version);
AG_PERFMON_DLL_API bool             AgPmDestroySourceConnection(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgEventID        AgPmRegisterEvent(AgPmHANDLE hconn, char * name);
AG_PERFMON_DLL_API bool             AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
AG_PERFMON_DLL_API bool             AgPmRegisterEventAsPassive(AgPmHANDLE hconn, AgEventID id, void * context, AgPassiveEventCallback funcPtr);
AG_PERFMON_DLL_API bool             AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool             AgPmEventLoggingEnabled(AgPmHANDLE hconn);

/** Event Sink API */
AG_PERFMON_DLL_API AgPmHANDLE       AgPmCreateSinkConnection(u32 version);
AG_PERFMON_DLL_API bool             AgPmDestroySinkConnection(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmStartLogging(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmStopLogging(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmEventAvailable(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgPerfMonEvent * AgPmGetCurrentEventPtr(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmPopEventPtr(AgPmHANDLE hconn);
AG_PERFMON_DLL_API AgEventID        AgPmGetEventID(AgPmHANDLE hconn, char *name);
AG_PERFMON_DLL_API char*            AgPmGetEventName(AgPmHANDLE hconn, AgEventID id);

/** Event Filtering API */
AG_PERFMON_DLL_API bool             AgPmEnableEvent(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool             AgPmDisableEvent(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool             AgPmEnableAllEvents(AgPmHANDLE hconn);
AG_PERFMON_DLL_API bool             AgPmDisableAllEvents(AgPmHANDLE hconn, AgEventID id);
AG_PERFMON_DLL_API bool             AgPmEnablePcmEvents(AgPmHANDLE hconn, AgPCMID pcmID, AgPcmEventGroup procID);
AG_PERFMON_DLL_API bool             AgPmDisablePcmEvents(AgPmHANDLE hconn, AgPCMID pcmID, AgPcmEventGroup procID);

/** Event Chaining API */
AG_PERFMON_DLL_API bool             AgPmChainEvent(AgPmHANDLE hconn, AgEventID leadID, AgEventID followerID);
AG_PERFMON_DLL_API bool             AgPmRemoveEventChain(AgPmHANDLE hconn, AgEventID leadID);
#endif

typedef AgPmHANDLE(AgPmCreateSourceConnection_FUNC)(u32 version);
typedef bool        (AgPmDestroySourceConnection_FUNC)(AgPmHANDLE hconn);
typedef AgEventID(AgPmRegisterEvent_FUNC)(AgPmHANDLE hconn, const char * name);
typedef bool        (AgPmSubmitEvent_FUNC)(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
typedef bool        (AgPmEventEnabled_FUNC)(AgPmHANDLE hconn, AgEventID id);
typedef bool        (AgPmEventLoggingEnabled_FUNC)(AgPmHANDLE hconn);

/** Event Source API */
AgPmHANDLE  AgPmCreateSourceConnection();
bool        AgPmDestroySourceConnection(AgPmHANDLE hconn);
AgEventID   AgPmRegisterEvent(AgPmHANDLE hconn, const char *name);
bool        AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2);
bool        AgPmRegisterEventAsPassive(AgPmHANDLE hconn, AgEventID id, void *context, AgPassiveEventCallback funcPtr);
bool        AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id);
bool        AgPmEventLoggingEnabled(AgPmHANDLE hconn);

#define AG_PERFMON_EV_START             0x00
#define AG_PERFMON_EV_STOP              0x01
#define AG_PERFMON_EV_STAT              0x02
#define AG_PERFMON_EV_DEBUG             0x03

static HMODULE AgPmDllHandle = 0;

static AgPmCreateSourceConnection_FUNC  * createFunc;
static AgPmDestroySourceConnection_FUNC * destroyFunc;
static AgPmRegisterEvent_FUNC           * registerEventFunc;
static AgPmSubmitEvent_FUNC             * submitEventFunc;
static AgPmEventEnabled_FUNC            * eventEnabledFunc;
static AgPmEventLoggingEnabled_FUNC     * eventLoggingEnabledFunc;

AgPmHANDLE AgPmCreateSourceConnection()
{
    /** load the DLL */
    AgPmDllHandle = ::LoadLibrary(AG_PERFMON_LIB_NAME);

    if (!AgPmDllHandle)
    {
        return 0;
    }

    /** get the function pointers to the event src api */
    createFunc              = (AgPmCreateSourceConnection_FUNC  *)::GetProcAddress(AgPmDllHandle, "AgPmCreateSourceConnection");
    destroyFunc             = (AgPmDestroySourceConnection_FUNC *)::GetProcAddress(AgPmDllHandle, "AgPmDestroySourceConnection");
    registerEventFunc       = (AgPmRegisterEvent_FUNC           *)::GetProcAddress(AgPmDllHandle, "AgPmRegisterEvent");
    submitEventFunc         = (AgPmSubmitEvent_FUNC             *)::GetProcAddress(AgPmDllHandle, "AgPmSubmitEvent");
    eventEnabledFunc        = (AgPmEventEnabled_FUNC            *)::GetProcAddress(AgPmDllHandle, "AgPmEventEnabled");
    eventLoggingEnabledFunc = (AgPmEventLoggingEnabled_FUNC     *)::GetProcAddress(AgPmDllHandle, "AgPmEventLoggingEnabled");

    if (!createFunc          ||
        !destroyFunc         ||
        !registerEventFunc   ||
        !submitEventFunc     ||
        !eventEnabledFunc    ||
        !eventLoggingEnabledFunc)
    {
#ifdef UNICODE
        ::MessageBox(NULL, L"The AGEIA PerfMON DLL does not contain all required entrypoints, PerfMON is disabled.  Install the latest AgPerfMon.dll.", L"AGEIA PerfMON ERROR", MB_OK|MB_ICONSTOP);
#else
        ::MessageBox(NULL, "The AGEIA PerfMON DLL does not contain all required entrypoints, PerfMON is disabled.  Install the latest AgPerfMon.dll.", "AGEIA PerfMON ERROR", MB_OK|MB_ICONSTOP);
#endif
        ::FreeLibrary(AgPmDllHandle);
        AgPmDllHandle = 0;
        return 0;
    }

    return createFunc(AG_PERFMON_VERSION);
}

bool AgPmDestroySourceConnection(AgPmHANDLE hconn)
{
    bool result = false;
    if (AgPmDllHandle)
    {
        result = destroyFunc(hconn);
        ::FreeLibrary(AgPmDllHandle);
        AgPmDllHandle = 0;
    }
    return result;
}

AgEventID AgPmRegisterEvent(AgPmHANDLE hconn, const char *name)
{
    AgEventID result = AG_INVALID_EVENT_ID;
    if (AgPmDllHandle)
    {
        result = registerEventFunc(hconn, name);
    }
    return result;
}

bool AgPmSubmitEvent(AgPmHANDLE hconn, AgEventID id, unsigned int data0, unsigned int data1, unsigned char data2)
{
    bool result = false;
    if (AgPmDllHandle)
    {
        result = submitEventFunc(hconn, id, data0, data1, data2);
    }
    return result;
}

bool AgPmEventEnabled(AgPmHANDLE hconn, AgEventID id)
{
    bool result = false;
    if (AgPmDllHandle)
    {
        result = eventEnabledFunc(hconn, id);
    }
    return result;
}

bool AgPmEventLoggingEnabled(AgPmHANDLE hconn)
{
    bool result = false;
    if (AgPmDllHandle)
    {
        result = eventLoggingEnabledFunc(hconn);
    }
    return result;
}

namespace hal
{
    namespace npa
    {
        struct Implementation : Interface
        {
            enum
            {
                EventMax = 1024
            };

            /**/                        Implementation();

            /* interface v 1.0 */
            virtual bool                DllProcessAttach();
            virtual void                DllProcessDetach();

            virtual int                 AllocateIndex();

            virtual void                StartEvent(Event const & event, u16 data = 0);
            virtual void                StopEvent(Event const & event, u16 data = 0);

            AgEventID                   GetEventId(Event const & event, char const * format = 0);
            AgEventID                   GetEventId(int index);

            u8                          GetProcId();

            AgEventID                   RegisterEvent(char const *);
            bool                        IsEnabled();
            bool                        IsEventEnabled(AgEventID id);
            bool                        IsLibraryLoaded();
            void                        StartEvent(AgEventID id, u16 data = 0);
            void                        StopEvent(AgEventID id, u16 data = 0);
            void                        StatEvent(AgEventID id, u32 stat);
            void                        StatEvent(AgEventID id, u32 stat, u32 ident);
            void                        DebugEvent(AgEventID id, u32 data0, u32 data1);

            Atomic< int        > m_count;
            Atomic< AgPmHANDLE > m_handle;
            AgEventID            m_id_array[EventMax];
        };
    }
}

static hal::npa::Implementation * implementation = 0;

extern "C" __declspec(dllexport) hal::npa::Interface * hal_npa$GetInterface(long version)
{
    long version_major = (version >> 8) & 255;
    long version_minor = (version >> 0) & 255;

    if (version_major == hal::npa::Implementation::version_major && version_minor <= hal::npa::Implementation::version_minor)
    {
        return implementation;
    }

    return 0;
}

extern void ForceLinkWithStartupCleanup();

void hal::npa::Startup()
{
    ForceLinkWithStartupCleanup();

    implementation = new Implementation;
}

void hal::npa::Cleanup()
{
    delete implementation;
}

hal::npa::Implementation::Implementation()
{
}

bool hal::npa::Implementation::DllProcessAttach()
{
    AgPmHANDLE local = m_handle.Load(hal::MemoryOrderAcquire);
    if (!local)
    {
        AgPmHANDLE shadow = AgPmCreateSourceConnection();

        if (!m_handle.CompareExchange(local, shadow, hal::MemoryOrderAcqRel))
        {
            AgPmDestroySourceConnection(shadow);
        }
    }
    m_count.FetchBeforeAdd(1);

    return true;
}

void hal::npa::Implementation::DllProcessDetach()
{
    if (m_count.FetchBeforeAdd(-1) == 1)
    {
        AgPmHANDLE local = m_handle.Exchange(0, hal::MemoryOrderAcqRel);

        if (local)
        {
            AgPmDestroySourceConnection(local);
        }
    }
}

int hal::npa::Implementation::AllocateIndex()
{
    static Atomic< int > count;
    int index = count.FetchBeforeAdd(1);
    if (EventMax < index) hal::dbg::DumpLastError("Too many allocated NPA Events", 0);
    m_id_array[index] = 0;
    return index;
}

__forceinline AgEventID hal::npa::Implementation::GetEventId(Event const & event, char const * format /*= 0*/)
{
    AgEventID id = m_id_array[event.m_index];
    if (!id)
    {
        char tmp[256];
        sprintf(tmp, "%s (%d)", event.m_name, event.m_index);
        id = RegisterEvent(tmp);
        m_id_array[event.m_index] = id;
    }
    if (format) forcef(hal, format, event.m_index, id, event.m_name);
    return id;
}

__forceinline AgEventID hal::npa::Implementation::GetEventId(int index)
{
    return m_id_array[index];
}

__forceinline u8 hal::npa::Implementation::GetProcId()
{
    int regs[4];
    __cpuid(regs, 1);
    return (u8)(regs[1] >> 24);
}

void hal::npa::Implementation::StartEvent(Event const & event, u16 data /*= 0*/)
{
    StartEvent(GetEventId(event), data);
}


void hal::npa::Implementation::StopEvent(Event const & event, u16 data /*= 0*/)
{
    StopEvent(GetEventId(event), data);
}


__forceinline AgEventID hal::npa::Implementation::RegisterEvent(const char *name)
{
    return AgPmRegisterEvent(m_handle, name);
}

__forceinline bool hal::npa::Implementation::IsEnabled()
{
    return AgPmEventLoggingEnabled(m_handle);
}

__forceinline void hal::npa::Implementation::StartEvent(AgEventID id, u16 data)
{
    AgPmSubmitEvent(m_handle, id, _GetCurrentThreadId(), ((GetProcId() << 8) | (data << 16)), AG_PERFMON_EV_START);
}

__forceinline void hal::npa::Implementation::StopEvent(AgEventID id, u16 data)
{
    AgPmSubmitEvent(m_handle, id, _GetCurrentThreadId(), ((GetProcId() << 8) | (data << 16)), AG_PERFMON_EV_STOP);
}

__forceinline void hal::npa::Implementation::StatEvent(AgEventID id, u32 stat)
{
    AgPmSubmitEvent(m_handle, id, stat, _GetCurrentThreadId(), AG_PERFMON_EV_STAT);
}

__forceinline void hal::npa::Implementation::StatEvent(AgEventID id, u32 stat, u32 thid)
{
    AgPmSubmitEvent(m_handle, id, stat, thid, AG_PERFMON_EV_STAT);
}

__forceinline void hal::npa::Implementation::DebugEvent(AgEventID id, u32 data0, u32 data1)
{
    AgPmSubmitEvent(m_handle, id, data0, data1, AG_PERFMON_EV_DEBUG);
}

__forceinline bool hal::npa::Implementation::IsEventEnabled(AgEventID id)
{
    return AgPmEventEnabled(m_handle, id);
}

__forceinline bool hal::npa::Implementation::IsLibraryLoaded()
{
    return !!AgPmDllHandle;
}
