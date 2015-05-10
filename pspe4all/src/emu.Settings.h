#ifndef emu_settings_h__
#define emu_settings_h__


#include <string>
#include <map>

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

#endif