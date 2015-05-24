/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#ifdef MINIMAL_EMU_LOG

namespace emu
{
    namespace log
    {
        enum Level
        {
            E_OFF = 0,
            E_FATAL = 1,
            E_ERROR = 2,
            E_WARN = 3,
            E_INFO = 4,
            E_DEBUG = 5,
            E_TRACE = 6,
            E_FORCE = 7,
            E_DEFAULT = E_FORCE
        };
    }
}

// __LINE__ == -1 instead of 0 because while(0) triggers a C4127: “Conditional expression is constant” when using /W4
#define lprintf( name, level, fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define fatalf(  name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define errorf(  name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define warnf(   name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define infof(   name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define debugf(  name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define tracef(  name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define forcef(  name,        fmt, ... ) do { fstderrf(fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#define lprintfv(name, level, fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define fatalfv( name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define errorfv( name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define warnfv(  name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define infofv(  name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define debugfv( name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define tracefv( name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)
#define forcefv( name,        fmt, args) do { fstderrf(fmt, args); } while (__LINE__ == -1)

#else

#include <set>

#include "emu.h"

namespace emu
{
    namespace log
    {
#if defined(EMU_EXPORTS)
        void   Startup();
        void   Cleanup();
#endif

        enum Level
        {
            E_OFF       = 0,
            E_FATAL     = 1,
            E_ERROR     = 2,
            E_WARN      = 3,
            E_INFO      = 4,
            E_DEBUG     = 5,
            E_TRACE     = 6,
            E_FORCE     = 7,
            E_DEFAULT   = E_FORCE
        };

        class Category;
        class SubCategory;

        struct Interface : emu::Interface
        {
            /**/     Interface() {}
            virtual ~Interface() {}

            /* interface v 1.0 */
            void (* Log_           )(Category const * that, Level level, char const src[]);
            void (* Register_      )(Category *& that, Category * parent                 );
            void (* Unregister_    )(Category *& that, Category * parent                 );

            __forceinline void Log(Category const * that, Level level, char const src[]) { return Log_(that, level, src); }
            __forceinline void Register(Category *& that, Category * parent)             { return Register_(that, parent); }
            __forceinline void Unregister(Category *& that, Category * parent)           { return Unregister_(that, parent); }
        };

        extern Interface * instance;

        typedef std::set< Category    * > Categories;
        typedef std::set< SubCategory * > SubCategories;

        class That
        {
        public:
            /**/                        That() {}
            virtual                    ~That() {}

            Level                    (* GetLevel$  )(Category const *);
            bool                     (* CheckLevel$)(Category const *, Level level);
            void                     (* LogfA$     )(Category const *, Level level, char    const fmt[], va_list args);
            void                     (* LogfW$     )(Category const *, Level level, wchar_t const fmt[], va_list args);

            Level                       GetLevel() const                                      { return GetLevel$(that); }
            bool                        CheckLevel(Level level) const                         { return CheckLevel$(that, level); }
            void                        Logf(Level level, char    const fmt[], ...)           { va_list args; va_start(args, fmt); LogfA$(that, level, fmt, args); va_end(args); }
            void                        Logf(Level level, wchar_t const fmt[], ...)           { va_list args; va_start(args, fmt); LogfW$(that, level, fmt, args); va_end(args); }
            void                        Logfv(Level level, char    const fmt[], va_list args) { LogfA$(that, level, fmt, args); }
            void                        Logfv(Level level, wchar_t const fmt[], va_list args) { LogfW$(that, level, fmt, args); }

        protected:
            Category                  * that;

        private:
            /**/                        That(That const &);
            void                        operator = (That const &);

            // dynamically allocated [Sub]Category instances are forbidden
            void                      * operator new (size_t);
            void                      * operator new [] (size_t);
        };

        class Category : public That
        {
        public:
            /**/                        Category(char const * name, char const * labelname = 0);

            /**/                       ~Category();


            void                        Reset()                                     { that->m_level = E_DEFAULT; }
            void                        SetLevel(Level level)                       { that->m_level = level; }
            std::string const         & GetName() const                             { return that->m_name; }
            std::string const         & GetLabelName() const                        { return that->m_labelname; }
            SubCategories             & GetSubCategories()                          { return that->m_subcategories; }

        protected:
            /**/                        Category(std::string const & name, char const * labelname);

            static Level                GetLevel$Category(Category const * that);
            static bool                 CheckLevel$Category(Category const * that, Level level);
            static void                 LogfA$Category(Category const * that, Level level, char    const fmt[], va_list args);
            static void                 LogfW$Category(Category const * that, Level level, wchar_t const fmt[], va_list args);

            void                        Print(Level level, char const * msg) const;

            u32                         GetKernelThreadUid();

            Level                       m_level;
            std::string                 m_name;
            std::string                 m_labelname;
            SubCategories               m_subcategories;

        private:
            /**/                        Category(Category const &);
            void                        operator = (Category const &);

            Interface                 * GetInstance();
        };

        class SubCategory : public Category
        {
        public:
            /**/                        SubCategory(Category & category, char const * subname, char const * labelname = 0);
            /**/                       ~SubCategory();

            bool                        IsOff() const                  { return ((SubCategory *)that)->m_off; }
            void                        SetOff(bool off)               { ((SubCategory *)that)->m_off = off; }
            std::string const         & GetShortName() const           { return ((SubCategory *)that)->m_subname; }

        protected:
            static Level                GetLevel$SubCategory(Category const * that);
            static bool                 CheckLevel$SubCategory(Category const * that, Level level);

            Category                  & m_category;
            std::string                 m_subname;
            bool                        m_off;

        private:
            /**/                        SubCategory(SubCategory const &);
            void                        operator = (SubCategory const &);
        };

        extern Category emu;
        extern Category hal;
        extern Category lle;
        extern Category hle;
    }
}

void __forceinline fstderrf(wchar_t const fmt[], ...) { va_list args; va_start(args, fmt); fputc('\n', stderr); vfwprintf(stderr, fmt, args); va_end(args); }
void __forceinline fstderrf(char    const fmt[], ...) { va_list args; va_start(args, fmt); fputc('\n', stderr); vfprintf (stderr, fmt, args); va_end(args); }

// __LINE__ == -1 instead of 0 because while(0) triggers a C4127: “Conditional expression is constant” when using /W4
#if defined(NO_LOGGING)
#   define lprintf( name, level, fmt, ... ) do {} while (__LINE__ == -1)
#   define fatalf(  name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define errorf(  name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define warnf(   name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define infof(   name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define debugf(  name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define tracef(  name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define forcef(  name,        fmt, ... ) do {} while (__LINE__ == -1)
#   define lprintfv(name, level, fmt, args) do {} while (__LINE__ == -1)
#   define fatalfv( name,        fmt, args) do {} while (__LINE__ == -1)
#   define errorfv( name,        fmt, args) do {} while (__LINE__ == -1)
#   define warnfv(  name,        fmt, args) do {} while (__LINE__ == -1)
#   define infofv(  name,        fmt, args) do {} while (__LINE__ == -1)
#   define debugfv( name,        fmt, args) do {} while (__LINE__ == -1)
#   define tracefv( name,        fmt, args) do {} while (__LINE__ == -1)
#   define forcefv( name,        fmt, args) do {} while (__LINE__ == -1)
#else
#   define lprintf( name, level, fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::Level(level))) emu::log::name.Logf( emu::log::Level(level), fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define fatalf(  name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_FATAL     )) emu::log::name.Logf( emu::log::E_FATAL     , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define errorf(  name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_ERROR     )) emu::log::name.Logf( emu::log::E_ERROR     , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define warnf(   name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_WARN      )) emu::log::name.Logf( emu::log::E_WARN      , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define infof(   name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_INFO      )) emu::log::name.Logf( emu::log::E_INFO      , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define debugf(  name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_DEBUG     )) emu::log::name.Logf( emu::log::E_DEBUG     , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define tracef(  name,        fmt, ... ) do { if (emu::log::name.CheckLevel(emu::log::E_TRACE     )) emu::log::name.Logf( emu::log::E_TRACE     , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define forcef(  name,        fmt, ... ) do {                                                        emu::log::name.Logf( emu::log::E_FORCE     , fmt, ## __VA_ARGS__); } while (__LINE__ == -1)
#   define lprintfv(name, level, fmt, args) do { if (emu::log::name.CheckLevel(emu::log::Level(level))) emu::log::name.Logfv(emu::log::Level(level), fmt, args          ); } while (__LINE__ == -1)
#   define fatalfv( name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_FATAL     )) emu::log::name.Logfv(emu::log::E_FATAL     , fmt, args          ); } while (__LINE__ == -1)
#   define errorfv( name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_ERROR     )) emu::log::name.Logfv(emu::log::E_ERROR     , fmt, args          ); } while (__LINE__ == -1)
#   define warnfv(  name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_WARN      )) emu::log::name.Logfv(emu::log::E_WARN      , fmt, args          ); } while (__LINE__ == -1)
#   define infofv(  name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_INFO      )) emu::log::name.Logfv(emu::log::E_INFO      , fmt, args          ); } while (__LINE__ == -1)
#   define debugfv( name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_DEBUG     )) emu::log::name.Logfv(emu::log::E_DEBUG     , fmt, args          ); } while (__LINE__ == -1)
#   define tracefv( name,        fmt, args) do { if (emu::log::name.CheckLevel(emu::log::E_TRACE     )) emu::log::name.Logfv(emu::log::E_TRACE     , fmt, args          ); } while (__LINE__ == -1)
#   define forcefv( name,        fmt, args) do {                                                        emu::log::name.Logfv(emu::log::E_FORCE     , fmt, args          ); } while (__LINE__ == -1)
#endif

#if !defined(EMU_EXPORTS)
extern "C"                       emu::log::Interface * emu_log$GetInterface(long version);
#else
extern "C" __declspec(dllexport) emu::log::Interface * emu_log$GetInterface(long version);
#endif

__forceinline emu::log::Interface * emu::log::Category::GetInstance()
{
    return emu_log$GetInterface(emu::log::Interface::version);
}

#endif