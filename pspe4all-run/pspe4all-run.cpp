/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

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
