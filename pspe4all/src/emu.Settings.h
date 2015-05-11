/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <string>

namespace emu
{
    class Settings
    {
    public:
        /**/        Settings();
        /**/       ~Settings();

        std::string cpumode;
        std::string gerenderer;

        void        Save(char const * filename);
        void        Load(char const * filename);
        void        CreateDefaultXml(char const * filename);

    };

    extern Settings * settings;
}
