/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

//  0x00010000  0x00004000 (16 KiB) Scratch pad
//  0x04000000  0x00200000 (2 MiB)  Lower video ram
//  0x04800000  0x00200000 (2 MiB)  Upper video ram (SLIM only)
//  0x08000000  0x02000000 (32 MiB) Lower main ram
//  0x0A000000  0x02000000 (32 MiB) Upper main ram (SLIM only)

#define SRAM_SIZE 0x00004000
#define GARB_SIZE 0x00020000
#define VRAM_SIZE 0x00200000
#define MRAM_SIZE 0x04000000

#ifndef KB
#define KB *1024
#endif
#ifndef MB
#define MB *1024 KB
#endif
#ifndef GB
#define GB *1024 * MB
#endif

#define PAGE64K_ALIGN(x) ((x + 65535) & ~65535)

#include "emu.log.h"
#include "lle.mmu.h"

namespace emu
{
    namespace log
    {
        SubCategory mmu(lle, "mmu", "MMU - Memory Manager Unit");
    }
}

namespace lle
{
    namespace mmu
    {
        static HANDLE psp_memory_handle  = 0;
        static void * psp_memory_pointer = 0;

        class Segment
        {
        protected:
            uintptr_t    cache;
            uintptr_t    address;
            uintptr_t    times;
            u32          offset;
            u32          size;
            char const * name;

            Segment()
            {}

            Segment(uintptr_t cache, uintptr_t address, uintptr_t times, u32 offset, u32 size, char const * name) : cache(cache), address(address), times(times), offset(offset), size(size), name(name)
            {}

            static __forceinline bool MapView(uintptr_t cache, uintptr_t address, u32 offset, u32 size)
            {
                bool ok;

                ok = (NULL != ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(cache + address + 0x00000000)));
                if (!ok)
                {
                    fatalf(mmu, "^--- fails to map 0x%08X-0x%08X ---> 0x%016I64X-0x%016I64X", (address + 0x00000000), (address + 0x00000000 + size - 1), cache + address + 0x00000000, cache + address + 0x00000000 + size - 1);
                }
                else
                {
                    ok = (NULL != ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(cache + address + 0x40000000)));
                    if (!ok)
                    {
                        fatalf(mmu, "^--- fails to map 0x%08X-0x%08X ---> 0x%016I64X-0x%016I64X", (address + 0x40000000), (address + 0x40000000 + size - 1), cache + address + 0x40000000, cache + address + 0x40000000 + size - 1);
                    }
                    else if (DCACHE_MEMORY_ADDRESS == cache)
                    {
                        ok = (NULL != ::MapViewOfFileEx(psp_memory_handle, FILE_MAP_READ|FILE_MAP_WRITE, 0, offset, size, (LPVOID)(cache + address + 0x80000000)));
                        if (!ok)
                        {
                            fatalf(mmu, "^--- fails to map 0x%08X-0x%08X ---> 0x%016I64X-0x%016I64X", (address + 0x80000000), (address + 0x80000000 + size - 1), cache + address + 0x80000000, cache + address + 0x80000000 + size - 1);
                        }
                    }
                }

                return ok;
            }

            static __forceinline void UnmapView(uintptr_t cache, uintptr_t address, u32 /*offset*/, u32 /*size*/)
            {
                ::UnmapViewOfFile((LPVOID)(cache + address + 0x00000000));
                ::UnmapViewOfFile((LPVOID)(cache + address + 0x40000000));
                if (DCACHE_MEMORY_ADDRESS == cache)
                {
                    ::UnmapViewOfFile((LPVOID)(cache + address + 0x80000000));
                }
            }

        public:
            virtual bool Map() = 0;

            virtual void Unmap()
            {
                if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
                {
                    uintptr_t total = times * uintptr_t(size);
                    size = 65536;
                    times = (total + 65535) / 65536;
                }

                uintptr_t p = address;

                UnmapView(cache, p, offset, size);

                for (unsigned int i = 1; i < times; ++i)
                {
                    UnmapView(cache, (p += size), offset, size);
                }
            }
        };

        class MappedSegment : public Segment
        {
        protected:
            MappedSegment()
            {}

        public:
            MappedSegment(uintptr_t cache, uintptr_t address, uintptr_t times, u32 offset, u32 size, char const * name) : Segment(cache, address, times, offset, size, name)
            {}

            virtual bool Map()
            {
                bool ok = true;

                if (!(size & -65536)) // geez! windows has a pretty annoying restriction about the size of a virtual page
                {
                    uintptr_t total = times * uintptr_t(size);
                    size = 65536;
                    times = (total + 65535) / 65536;
                }

                uintptr_t p = address;

                infof(mmu, "%-8s - 0x%08X-0x%08X ---> 0x%016I64X-0x%016I64X", (name ? name : "------       "), p, p + size * uintptr_t(times) - 1, cache + p, cache + p + size * uintptr_t(times) - 1);

                if (!MapView(cache, p, offset, size))
                {
                    ok = false;
                }

                for (unsigned int i = 1; i < times; ++i)
                {
                    if (!MapView(cache, (p += size), offset, size))
                    {
                        ok = false;
                    }
                }

                return ok;
            }
        };

        class UnusedSegment : public MappedSegment
        {
        public:
            UnusedSegment(uintptr_t cache, uintptr_t start, uintptr_t last)
            {
                this->cache = cache;

                address = PAGE64K_ALIGN(start);
                times = (last - address + 65536) / 65536;
                offset = PAGE64K_ALIGN(MRAM_SIZE);
                size = 65536;
                name = 0;
            }

            virtual bool Map()
            {
                // map a mirror of 64KB pages to eat read/write in "unmapped" memory instead of raising an exception
                if (MappedSegment::Map())
                {
                    return true;
                }
                return false;
            }
        };

        // 0x00010000 - 0x00004000 (16 KiB)     Scratch pad
        // 0x04000000 - 0x00200000 (2  MiB)     Lower video ram
        // 0x04200000 - 0x00200000 (2  MiB)     Upper video ram (SLIM only) NOT MAPPED HERE FOR COMPATIBILITY SAFETY
        // 0x08000000 - 0x02000000 (32 MiB)     Lower main ram
        // 0x0A000000 - 0x02000000 (32 MiB)     Upper main ram (SLIM only)

        UnusedSegment dpad0(DCACHE_MEMORY_ADDRESS, 0x00000000, 0x0000FFFF);
        UnusedSegment dpad1(DCACHE_MEMORY_ADDRESS, 0x00014000, 0x03FFFFFF);
        UnusedSegment dpad2(DCACHE_MEMORY_ADDRESS, 0x05000000, 0x07FFFFFF);
        UnusedSegment dpad3(DCACHE_MEMORY_ADDRESS, 0x0C000000, 0x0FFFFFFF);

        MappedSegment dseg0(DCACHE_MEMORY_ADDRESS, 0x00010000, 1, 2*MRAM_SIZE + 1*VRAM_SIZE + 0*4*SRAM_SIZE, SRAM_SIZE, "[SRAM] dcache");
        MappedSegment dseg1(DCACHE_MEMORY_ADDRESS, 0x04000000, 4, 2*MRAM_SIZE + 0*VRAM_SIZE + 0*4*SRAM_SIZE, VRAM_SIZE, "[VRAM] dcache");
        MappedSegment dseg2(DCACHE_MEMORY_ADDRESS, 0x04800000, 4, 2*MRAM_SIZE + 0*VRAM_SIZE + 0*4*SRAM_SIZE, VRAM_SIZE, "[VRAM] dcache");
        MappedSegment dseg3(DCACHE_MEMORY_ADDRESS, 0x08000000, 1, 0*MRAM_SIZE + 0*VRAM_SIZE + 0*4*SRAM_SIZE, MRAM_SIZE, "[MRAM] dcache");

        MappedSegment iseg0(ICACHE_MEMORY_ADDRESS, 0x00010000, 1, 2*MRAM_SIZE + 1*VRAM_SIZE + 1*4*SRAM_SIZE, SRAM_SIZE, "[SRAM] icache");
        MappedSegment iseg3(ICACHE_MEMORY_ADDRESS, 0x08000000, 1, 1*MRAM_SIZE + 0*VRAM_SIZE + 0*4*SRAM_SIZE, MRAM_SIZE, "[MRAM] icache");

        Segment * segment_array[] =
        {
            &dpad0,
            &dseg0,
            &iseg0,
            &dpad1,
            &dseg1,
            &dseg2,
            &dpad2,
            &dseg3,
            &iseg3,
            &dpad3
        };

        static void * jitasm_base = 0;
        static HANDLE jitasm_filemapping = 0;

        bool Reserve()
        {
            psp_memory_handle = ::CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, PAGE64K_ALIGN(2*4*SRAM_SIZE + 1*VRAM_SIZE + 2*MRAM_SIZE + 1*GARB_SIZE - 1), 0);
            if (!psp_memory_handle)
            {
                return false;
            }

            bool ok = true;

            for (auto segment : segment_array)
            {
                if (!segment->Map())
                {
                    ok = false;
                }
            }

            if (ok)
            {
                ok = 0 != (jitasm_filemapping = ::CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, SEC_COMMIT|PAGE_EXECUTE_READWRITE, 0, JITASM_MEMORY_SIZE, NULL));

                if (ok)
                {
                    size_t size = JITASM_MEMORY_SIZE;
                    do
                    {
                        ok = 0 != (jitasm_base = ::MapViewOfFileEx(jitasm_filemapping, FILE_MAP_READ|FILE_MAP_WRITE|FILE_MAP_EXECUTE, 0, 0, size, (LPVOID)JITASM_MEMORY_ADDRESS));
                        if (!ok)
                        {
                            size -= 1024*1024;
                        }
                    }
                    while (!ok && size > 64*1024*1024);

                    forcef(mmu, "jitasm heap size = %f", size/1024./1024.);

                    if (ok)
                    {
                        ok = 0 != (lle_jitasm$heap = ::RtlCreateHeap(HEAP_CREATE_ENABLE_EXECUTE|HEAP_CREATE_ALIGN_16|HEAP_GENERATE_EXCEPTIONS, jitasm_base, size, 0, NULL, NULL));

                        if (!ok)
                        {
                            ::UnmapViewOfFile(jitasm_base);
                            jitasm_base = 0;
                        }
                    }

                    if (!ok)
                    {
                        ::CloseHandle(jitasm_filemapping);
                        jitasm_filemapping = 0;
                    }
                }
            }

            if (ok)
            {
                psp_memory_pointer = (void *)DCACHE_MEMORY_ADDRESS;
            }
            else
            {
                ::CloseHandle(psp_memory_handle);
                psp_memory_handle = 0;
            }

            return ok;
        }

        void Release()
        {
            if (psp_memory_pointer)
            {
                if (jitasm_filemapping)
                {
                    if (lle_jitasm$heap)
                    {
                        ::RtlDestroyHeap(lle_jitasm$heap);
                        lle_jitasm$heap = 0;
                    }

                    if (jitasm_base)
                    {
                        ::UnmapViewOfFile(jitasm_base);
                        jitasm_base = 0;
                    }

                    ::CloseHandle(jitasm_filemapping);
                    jitasm_filemapping = 0;
                }

                for (auto segment : segment_array)
                {
                    segment->Unmap();
                }

                if (psp_memory_handle)
                {
                    ::CloseHandle(psp_memory_handle);
                    psp_memory_handle = 0;
                }
            }
        }

        struct Implementation : Interface
        {
            bool DllProcessAttach();

            void DllProcessDetach();
        };

        bool Implementation::DllProcessAttach()
        {
            infof(mmu, "Reserving a virtual memory to map PSP memory...");

            if (!lle::mmu::Reserve())
            {
                fatalf(mmu, "Mapping fails...");

                Sleep(5000);

                return false;
            }

            return true;
        }

        void Implementation::DllProcessDetach()
        {
            infof(mmu, "Releasing the virtual memory mapping PSP memory...");

            lle::mmu::Release();
        }

        Implementation implementation;
    }
}

extern "C" __declspec(dllexport) lle::mmu::Interface * lle_mmu$GetInterface(long /*version*/)
{
    return &lle::mmu::implementation;
}
