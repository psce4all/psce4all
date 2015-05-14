/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include "pspe4all.pch.h"

#include <stdio.h>
#include <tchar.h>

#ifdef UNICODE
#define DBGHELP_TRANSLATE_TCHAR
#endif

typedef std::basic_string<TCHAR> String;
typedef std::vector<String>      StringList;

//#include "SymbolEngine.h"

#include <dbghelp.h>
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

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

#if 0
struct SymbolEngineEx : public SymbolEngine
{
    virtual void OnEngineNotify(string const & Message)
    {
        //_tprintf(_T("%s%s"), m_Prefix.c_str(), Message.c_str());
    }

    void SetPrefix(string const & Prefix)
    {
        m_Prefix = Prefix;
    }

protected:
    string m_Prefix;
};
#endif


struct Debugger
{
    Debugger() : m_hProcess(nullptr)
    {
        EnableDebugPrivilege_(true);

        //m_SymbolEngine.SetPrefix(_T("  "));
    }

    virtual ~Debugger()
    {
    }

    bool AttachToProcess(DWORD ProcessId)
    {
        if (!DebugActiveProcess(ProcessId))
        {
            return false;
        }

        return true;
    }

    bool DebugLoop()
    {
        DEBUG_EVENT DebugEvent;

        bool bContinue = true;
        bool bSeenInitialBreakpoint = false;

        while (bContinue)
        {
            if (WaitForDebugEvent(&DebugEvent, INFINITE))
            {
                DWORD ContinueStatus = DBG_CONTINUE;

                switch (DebugEvent.dwDebugEventCode)
                {
                case CREATE_PROCESS_DEBUG_EVENT:
                    m_hProcess = DebugEvent.u.CreateProcessInfo.hProcess;
                    OnCreateProcessEvent(DebugEvent.dwProcessId);
                    OnCreateThreadEvent(DebugEvent.dwThreadId, DebugEvent.u.CreateProcessInfo.hThread);
                    OnLoadModuleEvent(DebugEvent.u.CreateProcessInfo.lpBaseOfImage, DebugEvent.u.CreateProcessInfo.hFile);
                    CloseHandle(DebugEvent.u.CreateProcessInfo.hFile);
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
                    CloseHandle(DebugEvent.u.LoadDll.hFile);
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
                    OnExceptionEvent(DebugEvent.dwThreadId, DebugEvent.u.Exception);
                    ContinueStatus = DBG_EXCEPTION_NOT_HANDLED;
                    DWORD ExceptionCode = DebugEvent.u.Exception.ExceptionRecord.ExceptionCode;
                    if (!bSeenInitialBreakpoint && (ExceptionCode == EXCEPTION_BREAKPOINT))
                    {
                        ContinueStatus = DBG_CONTINUE;
                        bSeenInitialBreakpoint = true;
                    }
                    break;
                }

                if (!ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, ContinueStatus))
                {
                    return false;
                }
            }
            else
            {
                DWORD ErrCode = GetLastError();
                if (ErrCode == ERROR_SEM_TIMEOUT)
                {
                    OnTimeout();
                }
                else
                {
                    return false;
                }
            }
        }

        return true;
    }



protected:
    virtual void OnCreateProcessEvent(DWORD ProcessId)
    {
        if (m_hProcess == NULL)
        {
            return;
        }

        //m_SymbolEngine.AddOptions(SYMOPT_DEBUG | SYMOPT_LOAD_LINES);
        //m_SymbolEngine.Init(m_hProcess, 0, false, false);
    }

    virtual void OnExitProcessEvent(DWORD ProcessId)
    {
        //m_SymbolEngine.Close();
    }

    virtual void OnCreateThreadEvent(DWORD ThreadId, HANDLE hThread)
    {
        if (hThread)
        {
            m_ThreadHandles[ThreadId] = hThread;
        }
    }

    virtual void OnExitThreadEvent(DWORD ThreadId)
    {
        m_ThreadHandles.erase(ThreadId);
    }

    virtual void OnLoadModuleEvent(LPVOID ImageBase, HANDLE hFile)
    {
        if (m_hProcess == NULL)
        {
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
#if 0
            if (!m_SymbolEngine.LoadModuleSymbols(hFile, ImageName, (DWORD64)ImageBase, ModuleSize))
            {
                _tprintf(_T("  Symbols cannot be loaded (error code: %u)\n"), m_SymbolEngine.LastError());
            }
            else
            {
                ShowSymbolInfo(ImageBase);
            }
#endif
        }
    }

    virtual void OnUnloadModuleEvent(LPVOID ImageBase)
    {
        String ImageName(_T("<unknown>"));

        ModuleList::iterator pm = m_Modules.find(ImageBase);
        if (pm != m_Modules.end())
        {
            ImageName = pm->second.FullName();
        }

        //m_SymbolEngine.UnloadModuleSymbols((DWORD64)ImageBase);

        if (pm != m_Modules.end())
        {
            m_Modules.erase(pm);
        }
    }

    virtual void OnExceptionEvent(DWORD ThreadId, EXCEPTION_DEBUG_INFO const & Info)
    {
        //_tprintf(_T("EXCEPTION (%s)\n"), Info.dwFirstChance ? _T("first-chance") : _T("second-chance"));
        //_tprintf(_T("  Code:        %08x\n"), Info.ExceptionRecord.ExceptionCode);
        //_tprintf(_T("  Address:     %08p\n"), Info.ExceptionRecord.ExceptionAddress);
        //_tprintf(_T("  ThreadId:    %u\n"), ThreadId);
        //_tprintf(_T("  Flags:       %08x\n"), Info.ExceptionRecord.ExceptionFlags);
        //_tprintf(_T("  NumberParameters:  %u\n"), Info.ExceptionRecord.NumberParameters);

        DWORD NumParameters = Info.ExceptionRecord.NumberParameters;

        if (NumParameters > EXCEPTION_MAXIMUM_PARAMETERS)
        {
            NumParameters = EXCEPTION_MAXIMUM_PARAMETERS;
        }

        for (DWORD i = 0; i < NumParameters; i++)
        {
            _tprintf(_T("    Parameter[%d]:     %08p\n"), i, Info.ExceptionRecord.ExceptionInformation[i]);
        }

        //ShowCallStack(ThreadId);
    }

    virtual void OnDebugStringEvent(DWORD ThreadId, OUTPUT_DEBUG_STRING_INFO const & Info)
    {
        if (m_hProcess == NULL)
        {
            return;
        }

        if ((Info.lpDebugStringData == 0) || (Info.nDebugStringLength == 0))
        {
            return;
        }

        if (Info.fUnicode)
        {
            SIZE_T const cMaxChars = 0xFFFF;
            WCHAR Buffer[cMaxChars + 1] = { 0 };

            SIZE_T CharsToRead = Info.nDebugStringLength;
            if (CharsToRead > cMaxChars)
            {
                CharsToRead = cMaxChars;
            }

            SIZE_T BytesRead = 0;
            if (!ReadProcessMemory(m_hProcess, Info.lpDebugStringData, Buffer, CharsToRead * sizeof(WCHAR), &BytesRead) || (BytesRead == 0))
            {
                return;
            }

            //wprintf(L"ODS(%u): %s\n", ThreadId, Buffer);
        }
        else
        {
            SIZE_T const cMaxChars = 0xFFFF;
            CHAR Buffer[cMaxChars + 1] = { 0 };

            SIZE_T CharsToRead = Info.nDebugStringLength;
            if (CharsToRead > cMaxChars)
            {
                CharsToRead = cMaxChars;
            }

            SIZE_T BytesRead = 0;
            if (!ReadProcessMemory(m_hProcess, Info.lpDebugStringData, Buffer, CharsToRead * sizeof(CHAR), &BytesRead) || (BytesRead == 0))
            {
                return;
            }

            //printf("ODS(%u): %s\n", ThreadId, Buffer);
        }
    }

    virtual void OnTimeout()
    {
    }

    typedef std::map< LPVOID, ModuleInfo > ModuleList;
    typedef std::map< DWORD, HANDLE >      ThreadHandleList;

    HANDLE           m_hProcess;
    ThreadHandleList m_ThreadHandles;
    ModuleList       m_Modules;

    void GetFileNameFromHandleHelper_(String & FileName)
    {
        DWORD ErrCode = 0;
        if (FileName.length() == 0)
        {
            return;
        }
        DWORD const cBufSize = 512;
        TCHAR szDrives[cBufSize + 1] = { 0 };
        DWORD rv = GetLogicalDriveStrings(cBufSize, szDrives);
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
            rv = QueryDosDevice(szDrive, szDevice, cBufSize);
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
        } while (*p);
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
        FileSizeLo = GetFileSize(hFile, &FileSizeHi);
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
        do
        {
            hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 1, NULL);
            if (hMapFile == NULL)
            {
                break;
            }
            pViewOfFile = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 1);
            if (pViewOfFile == NULL)
            {
                break;
            }
            const DWORD cBufSize = MAX_PATH;
            TCHAR szFileName[cBufSize + 1] = { 0 };
            if (!GetMappedFileName(GetCurrentProcess(), pViewOfFile, szFileName, cBufSize))
            {
                break;
            }
            FileName = szFileName;
            GetFileNameFromHandleHelper_(FileName);
            bSuccess = true;
        } while (0);
        if (pViewOfFile != NULL)
        {
            UnmapViewOfFile(pViewOfFile);
        }
        if (hMapFile != NULL)
        {
            CloseHandle(hMapFile);
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
            if (VirtualQueryEx(hProcess, QueryAddress, &mbi, sizeof(mbi)) != sizeof(mbi))
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
        do
        {
            if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
            {
                break;
            }
            TOKEN_PRIVILEGES tp;
            tp.PrivilegeCount = 1;
            if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
            {
                break;
            }
            tp.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;
            if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL))
            {
                break;
            }
            Success = true;
        } while (0);

        if (hToken != NULL)
        {
            CloseHandle(hToken);
        }
        return Success;
    }
};
