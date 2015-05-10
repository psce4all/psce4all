/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "hle.kd.h"

bool hle::kd::KernelLoadExec(const wchar_t* filename, u32 param_ptr)
{
    SceKernelLoadExecParam parameters;
    if (param_ptr)
    {
        debugf(kd, "hleKernelLoadExec TODO param_ptr not NULL");
    }
    else
    {
        memset(&parameters, 0, sizeof(SceKernelLoadExecParam));
    }
    //TODO the following be done when vfs once ready
    FILE * pFile;

    pFile = _wfsopen(filename, L"rb", _SH_DENYNO);
    if (pFile)
    {
        long size;
        fseek(pFile, 0, SEEK_END);
        size = ftell(pFile);
        rewind(pFile);
        u8 * buf = new u8[(int)size + 0x01000000];
        fread(buf, 1, size, pFile);
        fclose(pFile);

        if (memcmp(buf, "\0PBP", 4) == 0)
        {
            debugf(kd, "hleLoadExec File is pbp");
        }

        /*Module * module = */hle::kd::LoadModule(buf, 0);

        delete[] buf;

        //debugf(hle, "LoadedExec loaded");

        return true;
    }

    return false;
}
