/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <windows.h>
#include <userenv.h>

#include "hal.Atomic.h"

namespace hal
{
    template< size_t S = 2048, size_t N = 16 >
    class AsyncFile
    {
    protected:
        struct Overlapped : OVERLAPPED
        {
            char Buffer[S];
        };

        static const long overlapped_bit = N; // up to 2^N synchronous write calls without blocking the caller execution
        static const long overlapped_max = 1<<overlapped_bit;

        long              overlapped_key;
        wchar_t        *  filename;
        HANDLE            file;
        long              offset;
        Overlapped        overlapped_array[overlapped_max];

    public:
        AsyncFile() : overlapped_key(0), filename(nullptr), file(INVALID_HANDLE_VALUE), offset(0)
        {
            memset(overlapped_array, 0, sizeof(overlapped_array));
        }

        virtual ~AsyncFile()
        {
            Close();
        }

        bool Open(wchar_t const * pathfilename)
        {
            if (pathfilename)
            {
                if (pathfilename && *pathfilename == L'~')
                {
                    HANDLE hprocess = ::GetCurrentProcess();
                    HANDLE token    = 0;
                    BOOL   ok       = ::OpenProcessToken(hprocess, TOKEN_QUERY, &token);
                    if (ok)
                    {
                        DWORD     dwBufferSize = 0;
                        wchar_t * path         = 0;

                        // Retrieve Home Directory
                        ok = ::GetUserProfileDirectoryW(token, NULL, &dwBufferSize);
                        if (!ok && dwBufferSize != 0)
                        {
                            path = new wchar_t[dwBufferSize];
                            ok = ::GetUserProfileDirectoryW(token, path, &dwBufferSize);
                            if (ok)
                            {
                                filename = new wchar_t[dwBufferSize+sizeof(L"\\pspe4all\\") + wcslen(filename)];

                                ::wsprintfW(filename, L"%s\\pspe4all", path);
                                _wmkdir(filename);

                                ::wsprintfW(filename, L"%s\\pspe4all\\%s", path, pathfilename + 1);
                            }

                            delete[] path;
                        }

                        ::CloseHandle(token);
                    }
                }
                else
                {
                    filename = new wchar_t[wcslen(pathfilename) + 1];
                    ::wsprintfW(filename, L"%s", pathfilename);
                }

                if (filename)
                {
                    file = ::CreateFileW(filename, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED|FILE_ATTRIBUTE_NORMAL, NULL);
                    if (INVALID_HANDLE_VALUE != file)
                    {
                        offset = 0;

                        for (long i = 0; i < overlapped_max; ++i)
                        {
                            memset(overlapped_array + i, 0, sizeof(Overlapped));
                            overlapped_array[i].hEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
                        }

                        return true;
                    }
                    else
                    {
                        delete[] filename;
                        filename = nullptr;
                    }
                }
            }

            return false;
        }

        void Close()
        {
            HANDLE hFile = AtomicExchange(&file, INVALID_HANDLE_VALUE);

            if (INVALID_HANDLE_VALUE != hFile)
            {
                for (long i = 0; i < overlapped_max; ++i)
                {
                    DWORD  dummy;
                    auto & overlapped = overlapped_array[i];

                    // wait for previous asynchronous I/O completion if any
                    ::GetOverlappedResult(file, &overlapped, &dummy, TRUE);

                    ::CloseHandle(overlapped.hEvent);
                }

                // it is safe to close the file here because the file will be closed internally by the kernel
                // only after all I/O asynchronous operations on this file complete
                ::CloseHandle(hFile);
            }

            delete[] filename;
            filename = nullptr;
        }

        void Write(char const buffer[], size_t length)
        {
            static size_t const maxlength  = sizeof(overlapped_array[0].Buffer);
            DWORD               dummy;
            long                index      = AtomicFetchAdd(&overlapped_key, 1)&(overlapped_max-1);
            auto              & overlapped = overlapped_array[index];

            // wait for previous asynchronous I/O completion if any
            ::GetOverlappedResult(file, &overlapped, &dummy, TRUE);

            length = std::min(length, maxlength);

            memcpy(overlapped.Buffer, buffer, length);

            overlapped.Offset = (DWORD)AtomicFetchAdd(&offset, long(length));

            // starts a new asynchronous I/O
            ::WriteFile(file, overlapped.Buffer, long(length), &dummy, &overlapped);
        }
    };
}
