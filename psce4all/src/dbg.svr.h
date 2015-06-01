/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <stdio.h>
#include <tchar.h>

#ifdef UNICODE
#define DBGHELP_TRANSLATE_TCHAR
#endif

#include <dbghelp.h>
#include <psapi.h>

#include "emu.log.h"
#include "lle.mmu.h"

namespace dbg
{
    namespace svr
    {
        typedef std::basic_string<TCHAR> String;
        typedef std::vector<String>      StringList;

        struct ModuleInfo
        {
            ModuleInfo() : m_BaseAddr(0), m_Size(0)
            {
            }

            ModuleInfo(LPVOID BaseAddr, DWORD Size, String const & FullName) : m_BaseAddr(BaseAddr), m_Size(Size), m_FullName(FullName)
            {
            }

            ModuleInfo(ModuleInfo const & o) : m_BaseAddr(o.m_BaseAddr), m_Size(o.m_Size), m_FullName(o.m_FullName)
            {
            }

            ~ModuleInfo()
            {
            }

            ModuleInfo & operator=(ModuleInfo const & o)
            {
                if (&o != this)
                {
                    m_BaseAddr = o.m_BaseAddr;
                    m_Size = o.m_Size;
                    m_FullName = o.m_FullName;
                }
                return *this;
            }

            void SetBaseAddress(LPVOID BaseAddr)
            {
                m_BaseAddr = BaseAddr;
            }

            LPVOID BaseAddress() const
            {
                return m_BaseAddr;
            }

            void SetSize(DWORD Size)
            {
                m_Size = Size;
            }

            DWORD Size() const
            {
                return m_Size;
            }

            void SetFullName(String const & FullName)
            {
                m_FullName = FullName;
            }

            String FullName() const
            {
                return m_FullName;
            }

            String FileName() const
            {
                String rv;
                if (!m_FullName.empty())
                {
                    TCHAR szFileName[_MAX_FNAME] = { 0 };
                    _tsplitpath(m_FullName.c_str(), NULL, NULL, szFileName, NULL);
                    rv = szFileName;
                }
                return rv;
            }

            String FileNameExt() const
            {
                String rv;

                if (!m_FullName.empty())
                {
                    TCHAR szFileName[_MAX_FNAME] = { 0 };
                    TCHAR szFileExt[_MAX_EXT] = { 0 };
                    _tsplitpath(m_FullName.c_str(), NULL, NULL, szFileName, szFileExt);

                    rv = szFileName;
                    rv += szFileExt;
                }

                return rv;
            }

            String ModuleName() const
            {
                if (!FileName().empty())
                {
                    return FileName();
                }
                else
                {
                    const size_t cBufSize = 18;
                    TCHAR szBuffer[cBufSize + 1] = { 0 };
                    _sntprintf(szBuffer, cBufSize, _T("<%08p>"), m_BaseAddr);
                    szBuffer[cBufSize] = 0;
                    return String(szBuffer);
                }
            }

            bool IsValidAddress(LPVOID Address) const
            {
                if (Address == 0 || m_BaseAddr == 0 || m_Size == 0 || Address < m_BaseAddr || Address >= ((BYTE*)m_BaseAddr + m_Size))
                {
                    return false;
                }
                return true;
            }

        protected:
            LPVOID          m_BaseAddr;
            DWORD           m_Size;
            String          m_FullName;
        };

        struct SymbolInfoPackage : public SYMBOL_INFO_PACKAGE
        {
            SymbolInfoPackage()
            {
                si.SizeOfStruct = sizeof(SYMBOL_INFO);
                si.MaxNameLen = sizeof(name) / sizeof(TCHAR);
            }
        };

        struct ImageHlpLine64 : public IMAGEHLP_LINE64
        {
            ImageHlpLine64()
            {
                SizeOfStruct = sizeof(IMAGEHLP_LINE64);
            }
        };

        struct SymbolEngine
        {
            struct Frame
            {
                DWORD64 Ip;
                DWORD64 RetAddr;
                DWORD64 Bp;

                Frame(DWORD64 Ip, DWORD64 RetAddr, DWORD64 Bp) : Ip(Ip), RetAddr(RetAddr), Bp(Bp)
                {}
            };

            typedef std::vector< Frame > FrameList;

            SymbolEngine() : m_hProcess(nullptr), m_LastError(0)
            {
            }

            virtual ~SymbolEngine()
            {
                Close();
            }

            bool Init(HANDLE hProcess = GetCurrentProcess(), PCTSTR SearchPath = nullptr, bool Invade = false, bool Notify = false)
            {
                if (m_hProcess != nullptr)
                {
                    if (hProcess != m_hProcess)
                    {
                        m_LastError = ERROR_INVALID_FUNCTION;
                        return false;
                    }
                    else
                    {
                        return true;
                    }
                }
                if (!::SymInitialize(hProcess, SearchPath, Invade ? TRUE : FALSE))
                {
                    m_LastError = ::GetLastError();
                    return false;
                }
                if (Notify)
                {
                    if (!::SymRegisterCallback64(hProcess, DebugInfoCallback, (ULONG64)this))
                    {
                        m_LastError = ::GetLastError();
                        return false;
                    }
                }
                m_hProcess = hProcess;
                return true;
            }

            void Close()
            {
                if (m_hProcess != nullptr)
                {
                    ::SymCleanup(m_hProcess);

                    m_hProcess = nullptr;
                }
            }

            DWORD64 LoadModuleSymbols(String const &  ImageName, DWORD64 ModBase = 0, DWORD ModSize = 0)
            {
                if (ImageName.empty())
                {
                    m_LastError = ERROR_INVALID_PARAMETER;
                    return false;
                }
                return LoadModuleSymbols(NULL, ImageName, ModBase, ModSize);
            }

            DWORD64 LoadModuleSymbols(HANDLE hFile, DWORD64 ModBase = 0, DWORD ModSize = 0)
            {
                if ((hFile == NULL) || (hFile == INVALID_HANDLE_VALUE))
                {
                    m_LastError = ERROR_INVALID_PARAMETER;
                    return false;
                }
                return LoadModuleSymbols(hFile, String(), ModBase, ModSize);
            }

            DWORD64 LoadModuleSymbols(HANDLE hFile, String const &  ImageName, DWORD64 ModBase = 0, DWORD ModSize = 0)
            {
                if (m_hProcess == NULL)
                {
                    m_LastError = ERROR_INVALID_FUNCTION;
                    return 0;
                }
#ifdef _UNICODE
                char * pImageName = 0;
                if (!ImageName.empty())
                {
                    size_t BufSize = 2 * ImageName.length();
                    pImageName = (char*)_alloca(BufSize + 2);
                    size_t res = wcstombs(pImageName, ImageName.c_str(), BufSize);
                    pImageName[BufSize] = 0;
                    if (res == -1)
                    {
                        m_LastError = ERROR_INVALID_PARAMETER;
                        return false;
                    }
                }
#else
                const char * pImageName = ImageName.empty() ? 0 : ImageName.c_str();
#endif //_UNICODE
                DWORD64 rv = ::SymLoadModule64(m_hProcess, hFile, pImageName, NULL, ModBase, ModSize);
                if (rv == 0)
                {
                    m_LastError = GetLastError();
                    return 0;
                }
                return rv;
            }

            bool UnloadModuleSymbols(DWORD64 ModBase)
            {
                if (m_hProcess == NULL)
                {
                    m_LastError = ERROR_INVALID_FUNCTION;
                    return false;
                }
                if (ModBase == 0)
                {
                    m_LastError = ERROR_INVALID_PARAMETER;
                    return false;
                }
                if (!::SymUnloadModule64(m_hProcess, ModBase))
                {
                    m_LastError = ::GetLastError();
                    return false;
                }
                return true;
            }

            bool GetModuleInfo(DWORD64 Addr, IMAGEHLP_MODULE64 & Info)
            {
                if (m_hProcess == NULL)
                {
                    m_LastError = ERROR_INVALID_FUNCTION;
                    return false;
                }
                memset(&Info, 0, sizeof(Info));
                Info.SizeOfStruct = sizeof(Info);
                if (!::SymGetModuleInfo64(m_hProcess, Addr, &Info))
                {
                    m_LastError = ::GetLastError();
                    return false;
                }
                return true;
            }

            bool FindSymbolByAddress(DWORD64 Address, String & Name, DWORD64 & Displacement)
            {
                if (m_hProcess == NULL)
                {
                    m_LastError = ERROR_INVALID_FUNCTION;
                    return false;
                }
                SymbolInfoPackage sip;
                DWORD64 Disp = 0;
                if (!::SymFromAddr(m_hProcess, Address, &Disp, &sip.si))
                {
                    m_LastError = ::GetLastError();
                    return false;
                }
                Name = sip.si.Name;
                Displacement = Disp;
                return true;
            }

            bool FindLineByAddress(DWORD64 Address, String & File, DWORD & Line, DWORD64 & Displacement)
            {
                if (m_hProcess == NULL)
                {
                    m_LastError = ERROR_INVALID_FUNCTION;
                    return false;
                }
                ImageHlpLine64 LineInfo;
                DWORD Disp = 0;
                if (!SymGetLineFromAddr64(m_hProcess, Address, &Disp, &LineInfo))
                {
                    m_LastError = ::GetLastError();
                    return false;
                }
                File = LineInfo.FileName;
                Line = LineInfo.LineNumber;
                Displacement = Disp;
                return true;
            }

            bool WalkStack(FrameList & Frames, int FramesToSkip = 1, HANDLE hThread = GetCurrentThread(), CONTEXT * pContext = 0)
            {
                m_LastError = 0;
                Frames.clear();
                if (FramesToSkip < 0)
                {
                    FramesToSkip = 0;
                }
                DWORD MachineType = IMAGE_FILE_MACHINE_AMD64;
                STACKFRAME64 StackFrame;
                memset(&StackFrame, 0, sizeof(StackFrame));
                CONTEXT Context;
                if (pContext == nullptr)
                {
                    pContext = &Context;
                    ::RtlCaptureContext(pContext);
                }
                StackFrame.AddrPC.Offset = pContext->Rip;
                StackFrame.AddrPC.Mode = AddrModeFlat;
                StackFrame.AddrStack.Offset = pContext->Rsp;
                StackFrame.AddrStack.Mode = AddrModeFlat;
                StackFrame.AddrFrame.Offset = pContext->Rsp;
                StackFrame.AddrFrame.Mode = AddrModeFlat;
                while (1)
                {
                    if (!::StackWalk64(MachineType, m_hProcess, hThread, &StackFrame, pContext, 0, SymFunctionTableAccess64, SymGetModuleBase64, 0))
                    {
                        m_LastError = GetLastError();
                        break;
                    }
                    bool bSaveFrame = true;
                    if (StackFrame.AddrPC.Offset == 0)
                    {
                        bSaveFrame = false;
                    }
                    if (StackFrame.AddrPC.Offset == StackFrame.AddrReturn.Offset)
                    {
                        bSaveFrame = false;
                    }
                    if (FramesToSkip > 0)
                    {
                        bSaveFrame = false;
                        FramesToSkip--;
                    }
                    if (bSaveFrame)
                    {
                        Frames.push_back(Frame(StackFrame.AddrPC.Offset, StackFrame.AddrReturn.Offset, StackFrame.AddrFrame.Offset));
                    }
                }
                return (Frames.size() > 0);
            }


            DWORD GetOptions() const
            {
                return ::SymGetOptions();
            }

            void SetOptions(DWORD Options)
            {
                ::SymSetOptions(Options);
            }

            void AddOptions(DWORD Options)
            {
                DWORD CurOptions = GetOptions();

                CurOptions |= Options;

                SetOptions(CurOptions);
            }

            virtual void OnEngineNotify(String const &  /*Message*/)
            {
            }

            static BOOL CALLBACK DebugInfoCallback(HANDLE hProcess, ULONG ActionCode, ULONG64 CallbackData, ULONG64 UserContext)
            {
                SymbolEngine * pEngine = (SymbolEngine *)UserContext;
                if (pEngine == 0)
                {
                    return FALSE;
                }
                if (ActionCode == CBA_DEBUG_INFO)
                {
                    if (CallbackData != 0)
                    {
                        pEngine->OnEngineNotify(String((TCHAR const *)CallbackData));
                        return TRUE;
                    }
                }
                return FALSE;
            }

            HANDLE ProcessHandle() const
            {
                return m_hProcess;
            }

            DWORD LastError() const
            {
                return m_LastError;
            }

        protected:
            HANDLE m_hProcess;
            DWORD  m_LastError;
        };


        struct Debugger
        {
            Debugger() : m_hProcess(nullptr)
            {
                bContinue = true;
                bSeenInitialBreakpoint = false;

                EnableDebugPrivilege_(true);
            }

            virtual ~Debugger()
            {
            }

            bool AttachToProcess(DWORD ProcessId)
            {
                if (!::DebugActiveProcess(ProcessId))
                {
                    return false;
                }
                return true;
            }

            bool WaitForDebugEvent(DEBUG_EVENT & DebugEvent, DWORD Timeout, DWORD & ContinueStatus)
            {
                if (::WaitForDebugEvent(&DebugEvent, Timeout))
                {
                    switch (DebugEvent.dwDebugEventCode)
                    {
                    case CREATE_PROCESS_DEBUG_EVENT:
                        m_hProcess = DebugEvent.u.CreateProcessInfo.hProcess;
                        OnCreateProcessEvent(DebugEvent.dwProcessId);
                        OnCreateThreadEvent(DebugEvent.dwThreadId, DebugEvent.u.CreateProcessInfo.hThread);
                        OnLoadModuleEvent(DebugEvent.u.CreateProcessInfo.lpBaseOfImage, DebugEvent.u.CreateProcessInfo.hFile);
                        ::CloseHandle(DebugEvent.u.CreateProcessInfo.hFile);
                        break;

                    case EXIT_PROCESS_DEBUG_EVENT:
                        OnExitProcessEvent(DebugEvent.dwProcessId);
                        m_hProcess = NULL;
                        bContinue = false;
                        break;

                    case CREATE_THREAD_DEBUG_EVENT:
                        OnCreateThreadEvent(DebugEvent.dwThreadId, DebugEvent.u.CreateThread.hThread);
                        break;

                    case EXIT_THREAD_DEBUG_EVENT:
                        OnExitThreadEvent(DebugEvent.dwThreadId);
                        break;

                    case LOAD_DLL_DEBUG_EVENT:
                        OnLoadModuleEvent(DebugEvent.u.LoadDll.lpBaseOfDll, DebugEvent.u.LoadDll.hFile);
                        ::CloseHandle(DebugEvent.u.LoadDll.hFile);
                        break;

                    case UNLOAD_DLL_DEBUG_EVENT:
                        OnUnloadModuleEvent(DebugEvent.u.UnloadDll.lpBaseOfDll);
                        break;

                    case OUTPUT_DEBUG_STRING_EVENT:
                        OnDebugStringEvent(DebugEvent.dwThreadId, DebugEvent.u.DebugString);
                        break;

                    case RIP_EVENT:
                        break;

                    case EXCEPTION_DEBUG_EVENT:
                        ContinueStatus = OnExceptionEvent(DebugEvent.dwThreadId, DebugEvent.u.Exception);
                        DWORD ExceptionCode = DebugEvent.u.Exception.ExceptionRecord.ExceptionCode;
                        if (!bSeenInitialBreakpoint && (ExceptionCode == EXCEPTION_BREAKPOINT))
                        {
                            ContinueStatus = DBG_CONTINUE;
                            bSeenInitialBreakpoint = true;
                        }
                        break;
                    }
                }
                else
                {
                    DWORD ErrCode = ::GetLastError();
                    if (ErrCode == ERROR_SEM_TIMEOUT)
                    {
                        OnTimeout();
                    }
                    else
                    {
                        return false;
                    }
                }
                return true;
            }

            bool ContinueDebugEvent(DEBUG_EVENT & DebugEvent, DWORD ContinueStatus)
            {
                return FALSE != ::ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, ContinueStatus);
            }

            bool DebugLoop(DWORD Timeout)
            {
                DEBUG_EVENT DebugEvent;

                bContinue = true;
                bSeenInitialBreakpoint = false;

                while (bContinue)
                {
                    DWORD ContinueStatus = DBG_CONTINUE;
                    if (WaitForDebugEvent(DebugEvent, Timeout, ContinueStatus))
                    {
                        if (!ContinueDebugEvent(DebugEvent, ContinueStatus))
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }

                return true;
            }

        protected:
            bool bContinue;
            bool bSeenInitialBreakpoint;

            virtual void OnCreateProcessEvent(DWORD ProcessId)
            {
                ::OutputDebugStringA("BOF[OnCreateProcessEvent]");

                if (m_hProcess == NULL)
                {
                    ::OutputDebugStringA("BOF[OnCreateProcessEvent] *FAILURE*");

                    return;
                }

                m_SymbolEngine.AddOptions(SYMOPT_DEBUG | SYMOPT_LOAD_LINES);
                m_SymbolEngine.Init(m_hProcess, 0, false, false);

                ::OutputDebugStringA("BOF[OnCreateProcessEvent]");
            }

            virtual void OnExitProcessEvent(DWORD ProcessId)
            {
                ::OutputDebugStringA("BOF[OnExitProcessEvent]");

                m_SymbolEngine.Close();

                ::OutputDebugStringA("EOF[OnExitProcessEvent]");
            }

            virtual void OnCreateThreadEvent(DWORD ThreadId, HANDLE hThread)
            {
                ::OutputDebugStringA("BOF[OnCreateThreadEvent]");

                if (hThread)
                {
                    m_ThreadHandles[ThreadId] = hThread;
                }

                ::OutputDebugStringA("EOF[OnCreateThreadEvent]");
            }

            virtual void OnExitThreadEvent(DWORD ThreadId)
            {
                ::OutputDebugStringA("BOF[OnExitThreadEvent]");

                m_ThreadHandles.erase(ThreadId);

                ::OutputDebugStringA("EOF[OnExitThreadEvent]");
            }

            virtual void OnLoadModuleEvent(LPVOID ImageBase, HANDLE hFile)
            {
                ::OutputDebugStringA("BOF[OnLoadModuleEvent]");

                if (m_hProcess == NULL)
                {
                    ::OutputDebugStringA("EOF[OnLoadModuleEvent] *FAILURE*");

                    return;
                }

                String ImageName;
                if (!GetFileNameFromHandle_(hFile, ImageName))
                {
                    ImageName = _T("");
                }

                DWORD ModuleSize = 0;
                if (!GetModuleSize_(m_hProcess, ImageBase, ModuleSize))
                {
                    ModuleSize = 0;
                }

                LPVOID ImageEnd = (BYTE *)ImageBase + ModuleSize;
                m_Modules[ImageBase] = ModuleInfo(ImageBase, ModuleSize, ImageName);

                if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
                {
                    if (m_SymbolEngine.LoadModuleSymbols(hFile, ImageName, (DWORD64)ImageBase, ModuleSize))
                    {
                        //ShowSymbolInfo(ImageBase);
                    }
                }

                ::OutputDebugStringA("EOF[OnLoadModuleEvent]");
            }

            virtual void OnUnloadModuleEvent(LPVOID ImageBase)
            {
                ::OutputDebugStringA("BOF[OnUnloadModuleEvent]");

                String ImageName(_T("<unknown>"));

                ModuleList::iterator pm = m_Modules.find(ImageBase);
                if (pm != m_Modules.end())
                {
                    ImageName = pm->second.FullName();
                }

                m_SymbolEngine.UnloadModuleSymbols((DWORD64)ImageBase);

                if (pm != m_Modules.end())
                {
                    m_Modules.erase(pm);
                }

                ::OutputDebugStringA("EOF[OnUnloadModuleEvent]");
            }

            virtual DWORD OnExceptionEvent(DWORD ThreadId, EXCEPTION_DEBUG_INFO const & Info)
            {
                ::OutputDebugStringA("BOF[OnExceptionEvent]");

                TCHAR szMessage[4096];

                size_t len = 0;
                len += _stprintf(szMessage + len, _T("EXCEPTION (%s)\n"), Info.dwFirstChance ? _T("first-chance") : _T("second-chance"));
                len += _stprintf(szMessage + len, _T("  Code:        %08x\n"), Info.ExceptionRecord.ExceptionCode);
                len += _stprintf(szMessage + len, _T("  Address:     %08p\n"), Info.ExceptionRecord.ExceptionAddress);
                len += _stprintf(szMessage + len, _T("  ThreadId:    %u\n"), ThreadId);
                len += _stprintf(szMessage + len, _T("  Flags:       %08x\n"), Info.ExceptionRecord.ExceptionFlags);
                len += _stprintf(szMessage + len, _T("  NumberParameters:  %u\n"), Info.ExceptionRecord.NumberParameters);

                DWORD NumParameters = Info.ExceptionRecord.NumberParameters;

                if (NumParameters > EXCEPTION_MAXIMUM_PARAMETERS)
                {
                    NumParameters = EXCEPTION_MAXIMUM_PARAMETERS;
                }

                for (DWORD i = 0; i < NumParameters; i++)
                {
                    len += _stprintf(szMessage + len, _T("    Parameter[%d]:     %08p\n"), i, Info.ExceptionRecord.ExceptionInformation[i]);
                }

                ::MessageBox(0, szMessage, _T("OnExceptionEvent"), MB_OK);

                switch (Info.ExceptionRecord.ExceptionCode)
                {
                case EXCEPTION_ACCESS_VIOLATION:
                    // First chance: Pass this on to the system.
                    // Last chance: Display an appropriate error.
                    break;

                case EXCEPTION_BREAKPOINT:
                    // First chance: Display the current
                    // instruction and register values.
                    break;

                case EXCEPTION_DATATYPE_MISALIGNMENT:
                    // First chance: Pass this on to the system.
                    // Last chance: Display an appropriate error.
                    break;

                case EXCEPTION_SINGLE_STEP:
                    // First chance: Update the display of the
                    // current instruction and register values.
                    break;

                case DBG_CONTROL_C:
                    // First chance: Pass this on to the system.
                    // Last chance: Display an appropriate error.
                    break;

                default:
                    // Handle other exceptions.
                    break;
                }

                //ShowCallStack(ThreadId);

                ::OutputDebugStringA("EOF[OnExceptionEvent]");

                return DBG_EXCEPTION_NOT_HANDLED;
            }

            virtual void OnDebugStringEvent(DWORD ThreadId, OUTPUT_DEBUG_STRING_INFO const & Info)
            {
                ::OutputDebugStringA("BOF[OnDebugStringEvent]");

                if (m_hProcess == NULL)
                {
                    ::OutputDebugStringA("EOF[OnDebugStringEvent]");

                    return;
                }

                if ((Info.lpDebugStringData == 0) || (Info.nDebugStringLength == 0))
                {
                    ::OutputDebugStringA("EOF[OnDebugStringEvent]");

                    return;
                }

                if (Info.fUnicode)
                {
                    SIZE_T const cMaxChars = 0xFFFF;
                    WCHAR Buffer[cMaxChars + 1] = { 0 };

                    size_t len = 0;
                    len += _swprintf(Buffer + len, L"ODS(%u):", ThreadId);

                    SIZE_T CharsToRead = Info.nDebugStringLength;
                    if (CharsToRead > cMaxChars)
                    {
                        CharsToRead = cMaxChars;
                    }

                    SIZE_T BytesRead = 0;
                    if (!::ReadProcessMemory(m_hProcess, Info.lpDebugStringData, Buffer + len, CharsToRead * sizeof(WCHAR), &BytesRead) || (BytesRead == 0))
                    {
                        ::OutputDebugStringA("EOF[OnDebugStringEvent] *FAILURE*");

                        return;
                    }

                    ::MessageBoxW(0, Buffer, L"OnDebugStringEvent", MB_OK);
                    //wprintf(L"ODS(%u): %s\n", ThreadId, Buffer);
                }
                else
                {
                    SIZE_T const cMaxChars = 0xFFFF;
                    CHAR Buffer[cMaxChars + 1] = { 0 };

                    size_t len = 0;
                    len += sprintf(Buffer + len, "ODS(%u):", ThreadId);

                    SIZE_T CharsToRead = Info.nDebugStringLength;
                    if (CharsToRead > cMaxChars)
                    {
                        CharsToRead = cMaxChars;
                    }

                    SIZE_T BytesRead = 0;
                    if (!::ReadProcessMemory(m_hProcess, Info.lpDebugStringData, Buffer + len, CharsToRead * sizeof(CHAR), &BytesRead) || (BytesRead == 0))
                    {
                        ::OutputDebugStringA("EOF[OnDebugStringEvent] *FAILURE*");

                        return;
                    }

                    ::MessageBoxA(0, Buffer, "OnDebugStringEvent", MB_OK);
                    //printf("ODS(%u): %s\n", ThreadId, Buffer);
                }

                ::OutputDebugStringA("EOF[OnDebugStringEvent]");
            }

            virtual void OnTimeout()
            {
                ::OutputDebugStringA("BOF[OnTimeout]");

                ::OutputDebugStringA("EOF[OnTimeout]");
            }

            typedef std::map< LPVOID, ModuleInfo > ModuleList;
            typedef std::map< DWORD, HANDLE >      ThreadHandleList;

            HANDLE           m_hProcess;
            ThreadHandleList m_ThreadHandles;
            ModuleList       m_Modules;
            SymbolEngine     m_SymbolEngine;

            void GetFileNameFromHandleHelper_(String & FileName)
            {
                DWORD ErrCode = 0;
                if (FileName.length() == 0)
                {
                    return;
                }
                DWORD const cBufSize = 512;
                TCHAR szDrives[cBufSize + 1] = { 0 };
                DWORD rv = ::GetLogicalDriveStrings(cBufSize, szDrives);
                if ((rv == 0) || (rv > cBufSize))
                {
                    return;
                }
                TCHAR * p = szDrives;
                do
                {
                    TCHAR szDrive[3] = _T(" :");
                    _tcsncpy(szDrive, p, 2);
                    TCHAR szDevice[cBufSize + 1] = { 0 };
                    rv = ::QueryDosDevice(szDrive, szDevice, cBufSize);
                    if ((rv != 0) && (rv >= cBufSize))
                    {
                        size_t DevNameLen = _tcslen(szDevice);
                        if (_tcsnicmp(FileName.c_str(), szDevice, DevNameLen) == 0)
                        {
                            TCHAR szNewFileName[cBufSize + 1] = { 0 };
                            _stprintf(szNewFileName, _T("%s%s"), szDrive, FileName.c_str() + DevNameLen);
                            FileName = szNewFileName;
                            return;
                        }
                    }
                    while (*p++);
                }
                while (*p);
            }

            bool GetFileNameFromHandle_(HANDLE hFile, String & FileName)
            {
                DWORD ErrCode = 0;
                FileName = _T("");
                if ((hFile == NULL) || (hFile == INVALID_HANDLE_VALUE))
                {
                    return false;
                }
                DWORD FileSizeHi = 0;
                DWORD FileSizeLo = 0;
                FileSizeLo = ::GetFileSize(hFile, &FileSizeHi);
                if ((FileSizeLo == INVALID_FILE_SIZE) && (GetLastError() != NO_ERROR))
                {
                    return false;
                }
                else if ((FileSizeLo == 0) && (FileSizeHi == 0))
                {
                    return false;
                }
                bool bSuccess = false;
                HANDLE hMapFile = NULL;
                PVOID pViewOfFile = NULL;
                for (;;)
                {
                    hMapFile = ::CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 1, NULL);
                    if (hMapFile == NULL)
                    {
                        break;
                    }
                    pViewOfFile = ::MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 1);
                    if (pViewOfFile == NULL)
                    {
                        break;
                    }
                    const DWORD cBufSize = MAX_PATH;
                    TCHAR szFileName[cBufSize + 1] = { 0 };
                    if (!GetMappedFileName(::GetCurrentProcess(), pViewOfFile, szFileName, cBufSize))
                    {
                        break;
                    }
                    FileName = szFileName;
                    GetFileNameFromHandleHelper_(FileName);
                    bSuccess = true;
                    break;
                }
                if (pViewOfFile != NULL)
                {
                    ::UnmapViewOfFile(pViewOfFile);
                }
                if (hMapFile != NULL)
                {
                    ::CloseHandle(hMapFile);
                }
                return bSuccess;
            }

            bool GetModuleSize_(HANDLE hProcess, LPVOID ImageBase, DWORD & Size)
            {
                if (hProcess == NULL)
                {
                    return false;
                }
                if (ImageBase == 0)
                {
                    return false;
                }
                bool bFound = false;
                MEMORY_BASIC_INFORMATION mbi;
                BYTE * QueryAddress = (BYTE *)ImageBase;
                while (!bFound)
                {
                    if (::VirtualQueryEx(hProcess, QueryAddress, &mbi, sizeof(mbi)) != sizeof(mbi))
                    {
                        break;
                    }
                    if (mbi.AllocationBase != ImageBase)
                    {
                        Size = (DWORD)(QueryAddress - (BYTE *)ImageBase);
                        bFound = true;
                        break;
                    }
                    QueryAddress += mbi.RegionSize;
                }
                return bFound;
            }

            bool EnableDebugPrivilege_(bool Enable)
            {
                bool Success = false;
                HANDLE hToken = NULL;
                DWORD ec = 0;
                for (;;)
                {
                    if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
                    {
                        break;
                    }
                    TOKEN_PRIVILEGES tp;
                    tp.PrivilegeCount = 1;
                    if (!::LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
                    {
                        break;
                    }
                    tp.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;
                    if (!::AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
                    {
                        break;
                    }
                    Success = true;
                    break;
                }

                if (hToken != NULL)
                {
                    ::CloseHandle(hToken);
                }
                return Success;
            }
        };
    }
}