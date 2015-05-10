/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

namespace hal
{
    namespace os
    {
        struct Module
        {
            Module() : module(0), loaded(false)
            {
            }
            Module(char const modulename[], bool load_module = true)
            {
                module = load_module ? ::LoadLibraryA(modulename) : GetFirstModule(modulename);
                loaded = load_module && module;
            }
            template< typename F > Module(F * f)
            {
                module = GetCurrentModule((void *)f);
            }
            ~Module()
            {
                if (loaded)
                {
                    ::FreeLibrary(module);
                }
            }
            template< typename F > F * GetFunction(char const * name) const
            {
                return (F *)::GetProcAddress(module, name);
            }
            void * operator[] (char const name[])
            {
                return GetFunction< void * >(name);
            }
            bool operator == (hal::os::Module const & another) const
            {
                return module == another.module;
            }
            bool operator != (hal::os::Module const & another) const
            {
                return module != another.module;
            }
        private:
            static HMODULE GetCurrentModule(void *);
            static HMODULE GetFirstModule(char const []);

            HMODULE module;
            bool    loaded;
        };
    }
}
