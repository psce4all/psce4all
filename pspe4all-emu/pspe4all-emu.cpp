/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma comment(lib, "userenv.lib")
#pragma comment(lib, "ntdll.lib")
#pragma comment(lib, "Shell32.lib")

#include <shellapi.h>

#include "hle.kd.h"
#include "emu.h"
#include "emu.log.h"
#include "emu.settings.h"
#include "lle.mmu.h"
#include "hal.video.h"
#include "hal.os.h"
#include "hal.os.Thread.h"
#include "hal.npa.h"
#include "hal.dbg.h"
#include "hal.hmm.h"

#include "getopt.h"

#include <string>

#include "emu.minifire.h"

HDC         hDC  = NULL;
HWND        hWnd = NULL;
HINSTANCE   hInstance;
HMONITOR    hMonitor;

bool        keys[256];
bool        active     = true;
bool        fullscreen = false;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc

static hal::video::Interface * hal_video = 0;

void KillDisplayWindow() // Properly Kill The Window
{
    if (fullscreen)
    {
        ::ChangeDisplaySettings(NULL, 0);
        ::ShowCursor(TRUE);
    }

    if (!hal_video->ReleaseDisplay())
    {
        ::MessageBoxA(NULL, "Release Of The Display Renderer Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
    }

    if (hDC && !ReleaseDC(hWnd,hDC))
    {
        ::MessageBoxA(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        hDC = NULL;
    }

    if (hWnd && !DestroyWindow(hWnd))
    {
        ::MessageBoxA(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
        hWnd = NULL;
    }

    if (!::UnregisterClassA("OpenGL", hInstance))
    {
        ::MessageBoxA(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
        hInstance = NULL;
    }
}

BOOL CreateDisplayWindow(wchar_t const * const title, int width, int height, int bits, bool fullscreenflag)
{
    int         PixelFormat;
    WNDCLASSW   wc;
    DWORD       dwExStyle;	
    DWORD       dwStyle;	
    RECT        WindowRect;
    RECT        MonitorRect;

    MONITORINFOEXA pmi;
    memset(&pmi, 0, sizeof(pmi));
    pmi.cbSize = sizeof(pmi);

    if (!::GetMonitorInfoA(hMonitor, &pmi))
    {
        ::MessageBoxA(NULL, "Failed To Access A Monitor.", "ERROR", MB_OK|MB_ICONEXCLAMATION);

        return FALSE;			
    }

    MonitorRect = pmi.rcMonitor;

    WindowRect.left   = (MonitorRect.left + (long)width ) >> 1;
    WindowRect.top    = (MonitorRect.top  + (long)height) >> 1;
    WindowRect.right  = WindowRect.left + (long)width;
    WindowRect.bottom = WindowRect.top  + (long)height;

    // fullscreen variable
    fullscreen = fullscreenflag;

    hInstance        = ::GetModuleHandle(NULL);
    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = ::LoadIcon(NULL, IDI_WINLOGO);	
    wc.hCursor       = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;			
    wc.lpszMenuName  = NULL;		
    wc.lpszClassName = L"OpenGL";	

    // Register the window class
    if (!::RegisterClassW(&wc))		
    {
        ::MessageBoxA(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK|MB_ICONEXCLAMATION);

        return FALSE;			
    }

    // If fullscreen flag is set
    if (fullscreen)	
    {
        DEVMODEA dm;
        memset(&dm, 0, sizeof(dm));
        dm.dmSize             = sizeof(dm);
        dm.dmPelsWidth        = MonitorRect.right - MonitorRect.left;
        dm.dmPelsHeight       = MonitorRect.bottom - MonitorRect.top;
        dm.dmBitsPerPel       = bits;
        dm.dmDisplayFrequency = 60;
        dm.dmFields           = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

        // Try to set selected mode and get results
        if (::ChangeDisplaySettingsExA(pmi.szDevice, &dm, NULL, CDS_FULLSCREEN, NULL) != DISP_CHANGE_SUCCESSFUL)
        {
            if (::MessageBoxA(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "OPENGL", MB_YESNO|MB_ICONEXCLAMATION) == IDYES)
            {
                fullscreen = FALSE;
            }
            else
            {
                ::MessageBoxA(NULL, "Program Will Now Close.", "ERROR", MB_OK|MB_ICONSTOP);

                return FALSE;
            }
        }
    }

    if (fullscreen)	
    {
        dwExStyle = WS_EX_APPWINDOW;
        dwStyle   = WS_POPUP;	
        ::ShowCursor(FALSE);	
        WindowRect = MonitorRect;
    }
    else
    {
        dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	
        dwStyle   = WS_OVERLAPPEDWINDOW;	
    }

    ::AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

    // Create the window
    if (!(hWnd = ::CreateWindowExW(dwExStyle, L"OpenGL", title, dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WindowRect.left, WindowRect.top, WindowRect.right-WindowRect.left, WindowRect.bottom-WindowRect.top, NULL, NULL, hInstance, NULL)))
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Window Creation Error.", "ERROR", MB_OK|MB_ICONEXCLAMATION);

        return FALSE;			
    }

    // Tell the window how we want things to be..
    static PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                              // Version Number
        PFD_DRAW_TO_WINDOW |            // Format Must Support Window
        PFD_SUPPORT_OPENGL |            // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,               // Double Buffering
        PFD_TYPE_RGBA,                  // Request An RGBA Format
        (BYTE)bits,                     // Select Our Color Depth
        0, 0, 0, 0, 0, 0,               // Color Bits Ignored
        8,                              // No Alpha Buffer
        0,                              // Shift Bit Ignored
        0,                              // No Accumulation Buffer
        0, 0, 0, 0,                     // Accumulation Bits Ignored
        16,                             // 16Bit Z-Buffer (Depth Buffer)  
        8,                              // No Stencil Buffer
        0,                              // No Auxiliary Buffer
        PFD_MAIN_PLANE,                 // Main Drawing Layer
        0,                              // Reserved
        0, 0, 0                         // Layer Masks Ignored	
    };

    // Did We Get A Device Context?
    if (!(hDC = ::GetDC(hWnd)))	
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Can't Create A Device Context.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
        
        return FALSE;
    }

    // Did windows find a matching pixel format?
    if (!(PixelFormat = ::ChoosePixelFormat(hDC, &pfd)))	
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
        
        return FALSE;
    }

    // Are we able to set the pixel format?
    if (!::SetPixelFormat(hDC, PixelFormat, &pfd))		
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
        
        return FALSE;
    }

    // Are we able to get an activated rendering context?
    if (!hal_video->CreateDisplay(hDC))
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Can't Create Or Activate The Display Renderer.", "ERROR", MB_OK|MB_ICONEXCLAMATION);

        return FALSE;
    }

    ::ShowWindow(hWnd, SW_SHOW);
    ::SetForegroundWindow(hWnd);
    ::SetFocus(hWnd);

    if (fullscreen)
    {
        hal_video->ResizeDisplay(MonitorRect.right - MonitorRect.left, MonitorRect.bottom - MonitorRect.top);
    }
    else
    {
        hal_video->ResizeDisplay(width, height);
    }

    // Initialize our newly created display window
    if (!hal_video->PrepareDisplay())
    {
        KillDisplayWindow();
        ::MessageBoxA(NULL, "Initialization Failed.", "ERROR", MB_OK|MB_ICONEXCLAMATION);
        
        return FALSE;
    }

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_ACTIVATE: // Watch for window activate message
        {
            active = !HIWORD(wParam);
            return 0;
        }

        case WM_SYSCOMMAND: // Intercept system commands
        {
            switch (wParam)
            {
                case SC_SCREENSAVE:
                case SC_MONITORPOWER:
                    return 0; // Prevent from happening
            }
            break;
        }

        case WM_CLOSE: // Did we receive a close message?
        {
            ::PostQuitMessage(0);
            return 0;
        }

        case WM_KEYDOWN: // Is a key being held down?
        {
            keys[wParam] = TRUE;
            return 0;
        }

        case WM_KEYUP: // Has a key been released?
        {
            keys[wParam] = FALSE;

            if (VK_F2 == wParam)
            {
                hal_video->ToggleVsync();
                return TRUE;
            }

            return 0;
        }

        case WM_SIZE: // Resize the OpenGL window
        {
            hal_video->ResizeDisplay(LOWORD(lParam), HIWORD(lParam));
            return 0;
        }

        case WM_ERASEBKGND:
        {
            return TRUE;
        }
    }

    // Pass all unhandled messages to defwindowproc
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#if 0 // just a way to force a leak
struct Int : hal::MPSCQueue< Int >::Node, hal::heap::Allocator< Int > {};

hal::MPSCQueue< Int > myQueue;
#endif

static hal::npa::Event syscall_event("Syscall Event");

static LONG WINAPI FatalFilter(EXCEPTION_POINTERS * pep)
{
    int code = hal::dbg::MidiDumpFilter(pep);
    if (EXCEPTION_CONTINUE_SEARCH == code)
    {
        ::MessageBoxA(NULL, "A fatal exception occurs.\nPlease report it to PSPE4ALL team by sending pspe4all.log and pspe4all.dmp.", "PSPE4ALL Crash Report", MB_OK | MB_ICONHAND);
        ::RaiseFailFastException(pep->ExceptionRecord, pep->ContextRecord, 0);
    }
    return code;
}

static HACCEL hAccel = 0;

extern emu::StartupCleanup startup_cleanup;

extern "C" __noinline __declspec(dllexport) int Run(int argc, wchar_t * argv[])
{
    LPTOP_LEVEL_EXCEPTION_FILTER old_filter = nullptr;
	//emu::settings = __new emu::Settings;

    int verbose_flag = 0;
    int c;
    int option_index = 0;

    static struct option long_options[] =
    {
        { L"verbose", no_argument, &verbose_flag, 1 },
        { L"brief", no_argument, &verbose_flag, 0 },
        { L"use-interpreter", required_argument, 0, L'1' },
        { L"use-cross-interpreter", no_argument, 0, L'2' },
        { L"no-register-allocation", no_argument, 0, L'3' },
        { L"trace-allegrex", optional_argument, 0, L'4' },
        { L"jitasm-trace-cfg", optional_argument, 0, L'5' },
        { L"allegrex-icache", optional_argument, 0, L'6' },
        { L"use-debugger", required_argument, 0, L'D' },
        { L"help", no_argument, 0, L'h' },
        { 0, 0, 0, 0 }
    };

    while (-1 != (c = getopt_long_only(argc, argv, L"1:234:5:6:D:h", long_options, &option_index)))
    {
        switch (c)
        {
            case 0:
                break;
            case L'h':
                printf("HELP:\n"
                       "\t--verbose\tset verbose ON\n"
                       "\t--brief\t\tset verbose OFF\n"
                       "\t--use-interpreter=slow\tuse real interpreter\n"
                       "\t--use-interpreter=fast\tuse interpreter-like dynarec\n"
                       "\t--use-interpreter=none\tuse full dynarec\n"
                       "\t--use-cross-interpreter\tuse cross interpreter\n"
                       "\t--use-debugger=<name>\tuse a debug server\n"
                       "\t-help\t\tdisplay this help message\n"
                       );
                return 1;
            case L'1':
                if (!wcsicmp(optarg, L"slow"))
                {
                    Allegrex::use_real_interpreter  = true;
                    Allegrex::use_cross_interpreter = false;
                    Allegrex::interpreter_like_mode = false;
                }
                else if (!wcsicmp(optarg, L"fast"))
                {
                    Allegrex::use_real_interpreter = false;
                    Allegrex::interpreter_like_mode = true;
                }
                else if (!wcsicmp(optarg, L"none"))
                {
                    Allegrex::use_real_interpreter = false;
                    Allegrex::interpreter_like_mode = false;
                    Allegrex::icache_fast_mode = true;
                }
                else
                {
                    fprintf(stderr, "option --use-interpreter with unknown value `%ls'\n", optarg);
                }
                break;
            case L'2':
                Allegrex::use_real_interpreter = false;
                Allegrex::use_cross_interpreter = true;
                break;
            case L'3':
                Allegrex::no_register_allocation = true;
                break;
            case L'4':
                if (optarg)
                {
                    if (!wcsicmp(optarg, L"yes"))
                    {
                        Allegrex::trace_instruction = true;
                    }
                    else if (!wcsicmp(optarg, L"no"))
                    {
                        Allegrex::trace_instruction = false;
                    }
                    else
                    {
                        fprintf(stderr, "option --trace-allegrex with unknown value `%ls'\n", optarg);
                    }
                }
                else
                {
                    Allegrex::trace_instruction = true;
                }
                break;
            case L'5':
                if (optarg)
                {
                    if (!wcsicmp(optarg, L"yes"))
                    {
                        Allegrex::jitasm_trace_cfg = true;
                    }
                    else if (!wcsicmp(optarg, L"no"))
                    {
                        Allegrex::jitasm_trace_cfg = false;
                    }
                    else
                    {
                        fprintf(stderr, "option --jitasm-trace-cfg with unknown value `%ls'\n", optarg);
                    }
                }
                else
                {
                    Allegrex::jitasm_trace_cfg = true;
                }
                break;
            case L'6':
                if (optarg)
                {
                    if (!wcsicmp(optarg, L"fast"))
                    {
                        Allegrex::icache_fast_mode = true;
                    }
                    else if (!wcsicmp(optarg, L"slow") && Allegrex::interpreter_like_mode)
                    {
                        Allegrex::icache_fast_mode = false;
                    }
                    else
                    {
                        fprintf(stderr, "option --allegrex-icache with unknown value `%ls'\n", optarg);
                    }
                }
                else
                {
                    Allegrex::icache_fast_mode = true;
                }
                break;
            case L'D':
                Allegrex::use_debugger = optarg;
                Allegrex::use_debug_server = !!wcsicmp(optarg, L"none");
                break;
            case ':':
                /* missing option argument */
                fprintf(stderr, "option --%s requires an argument\n", argv[0], long_options[option_index].name);
                break;
            case '?':
                break;
            default:
                return -1;
        }
    }

    if (argc <= optind)
    {
        return -1;
    }

    // warning: Windows 7 or later just ignore FatalFilter when running in a debugger
    old_filter = hal::dbg::EnforceFilter(true, FatalFilter);

    MSG	 msg;

    msg.wParam = 0;

    BOOL done = FALSE;

#if 0 // just a way to force a leak
    myQueue.Enqueue(new Int);
#endif

    hal_video = hal_video$GetInterface(emu::Interface::version);
    if (!hal_video)
    {
        errorf(emu, "pspe4all-emu: Cannot retrieve hal::video interface");
    }

    hal::dbg::Refresh();

    hMonitor = ::MonitorFromWindow(NULL, MONITOR_DEFAULTTOPRIMARY);

    // Create our OpenGL window
    if (!::CreateDisplayWindow(L"PSPE4ALL - test", 480, 272, 32, fullscreen))
    {
        return 0;
    }

    Cpu.Initialize(argv[optind]);
    Cpu.StartThread();

    while (!done)
    {
        // Is there a message waiting?
        switch (::MsgWaitForMultipleObjects(1, Cpu.syscall.event, FALSE, INFINITE, QS_ALLEVENTS))
        {
            case WAIT_OBJECT_0 + 0: // Syscall Event
            {
                hal::npa::StartEvent(syscall_event);
                switch (Cpu.syscall.code)
                {
                    case CCpu::DoNothing:
                        break;
                    case CCpu::DoSceSetDisplayMode:
                        hal_video->width  = Cpu.gpr[5];
                        hal_video->height = Cpu.gpr[6];
                        break;
                    case CCpu::DoSceDisplaySetFrameBuf:
                        hal_video->UpdateDisplay();
                        hal_video->address = Cpu.gpr[4];
                        hal_video->stride  = Cpu.gpr[5];
                        hal_video->format  = Cpu.gpr[6];
                        break;
                    case CCpu::DoSceDisplayWaitVblankStart:
                        hal_video->RenderDisplay();
                        hal_video->PresentDisplay();
                        break;
                    default:
                        break;
                }
                Cpu.syscall.Leave();
                hal::npa::StopEvent(syscall_event);
            }
            case WAIT_OBJECT_0 + 1: // Message
            {
                while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                {
                    // Have we received a quit message?
                    if (msg.message == WM_QUIT)
                    {
                        Cpu.syscall.Leave();
                        done = TRUE;
                        break;
                    }
                    else if (!hAccel || !::TranslateAccelerator(msg.hwnd, hAccel, &msg))
                    {
                        ::TranslateMessage(&msg);
                        ::DispatchMessage(&msg);
                    }
                }
                break;
            }
            default:
            {
                done = true;
                break;
            }
        }
        // Was there a quit received?
        if (keys[VK_ESCAPE])
        {
            keys[VK_ESCAPE] = FALSE;
            // ESC or DrawGLScene signaled a quit
            done = TRUE;
        }
        else
        {
            if (keys[VK_F1])
            {
                keys[VK_F1] = FALSE;

                hMonitor = ::MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY);

                KillDisplayWindow();
                fullscreen = !fullscreen;
                if (!CreateDisplayWindow(L"PSPE4ALL - test", 480, 272, 32, fullscreen))
                {
                    return 0;
                }
            }
        }
    }

    Cpu.StopThread();
    Cpu.Terminate();

    __DbgCheckLastError("LastErrorCode test using GetProcessId(NULL)", GetProcessId(NULL));

    // Shutdown
    KillDisplayWindow();

    if (old_filter)
    {
        hal::dbg::EnforceFilter(false, old_filter);
    }

    return int(msg.wParam);
}

emu::Interface * emulator = 0;

extern "C" BOOL WINAPI DllMain(HINSTANCE /*hinstDLL*/, DWORD fdwReason, LPVOID /*lpvReserved*/)
{
    // see this link for best practice with DllMain : http://msdn.microsoft.com/en-us/windows/hardware/gg487379.aspx
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        {
            long version = emu::Interface::version;

            emulator = emu$GetInterface(version);

            if (!emulator->DllProcessAttach())
            {
                return FALSE;
            }

            break;
        }
    case DLL_THREAD_ATTACH:
        {
            break;
        }
    case DLL_THREAD_DETACH:
        {
            break;
        }
    case DLL_PROCESS_DETACH:
        {
            emulator->DllProcessDetach();

            break;
        }
    }

    return TRUE;
}

