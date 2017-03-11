/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "../psce4all/ext/Remotery/Remotery.c"

double delay()
{
    int i, end;
    double j = 0;

    rmt_BeginCPUSample(delay);
    for (i = 0, end = rand() / 100; i < end; ++i) {
        j += sin(i);
    }
    rmt_EndCPUSample();
    return j;
}

extern "C" { _declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }

int _tmain(int argc, _TCHAR* argv[])
{
    int result = -1;

    HMODULE hEmuDll = LoadLibraryA(__ConfigurationDllStringA("pspe4all-emu"));

    if (hEmuDll)
    {
        auto Run = (int(*)(int, wchar_t *[]))GetProcAddress(hEmuDll, "Run");

        result = Run(argc, argv);
    }
    else
    {
        fprintf(stderr, "Cannot load pspe4all-emu.dll.");
    }

    return result;
}
