#ifndef hal_String_h__
#define hal_String_h__

#include <deque>

namespace hal
{
    class StringList;

    class String : public std::wstring
    {
    public:
        String() : std::wstring() {}
        String(wchar_t const * source) : std::wstring(source) {}
        String(std::wstring const & source) : std::wstring(source) {}
        String(String const & source) : std::wstring(source) {}
        String(size_t count, wchar_t source) : std::wstring(count, source) {}

        enum EmptyParts
        {
            KeepEmptyParts = false, SkipEmptyParts = true
        };

        StringList split(wchar_t separator, EmptyParts skip) const;
    };

    String Stringfv(wchar_t const * fmt, va_list ap);

    String Stringf(wchar_t const * fmt, ...);

    String & Stringfv(String & result, wchar_t const * fmt, va_list ap);

    String & Stringf(String & result, wchar_t const * fmt, ...);

    class StringList : public std::deque< String >
    {
    public:
        String join(wchar_t separator)
        {
            String result;
            auto i = begin();
            auto e = end();
            if (i != e)
            {
                result.append(*i);
            }
            for (++i; i != e; ++i)
            {
                result.append(1, separator);
                result.append(*i);
            }
            return result;
        }
    };
}

#endif // hal.String_h__