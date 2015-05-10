#include "hal.String.h"

hal::StringList hal::String::split(wchar_t separator, EmptyParts skip) const
{
    StringList result;
    size_t i = 0;
    if (skip == SkipEmptyParts)
    {
        for (;;)
        {
            size_t j = find(separator, i);
            if (j == String::npos)
            {
                String part(substr(i));
                if (!part.empty()) result.push_back(part);
                break;
            }
            else
            {
                String part(substr(i, j - i - 1));
                if (!part.empty()) result.push_back(part);
            }
            i = j + 1;
        }
    }
    else
    {
        for (;;)
        {
            size_t j = find(separator, i);
            if (j == String::npos)
            {
                result.push_back(substr(i));
                break;
            }
            else
            {
                result.push_back(substr(i, j - i - 1));
                i = j + 1;
            }
        }
    }
    return result;
}

hal::String hal::Stringfv(wchar_t const * fmt, va_list ap)
{
    String result;
    size_t size = _vscwprintf(fmt, ap);
    result.resize(size);
    _vsnwprintf_s((wchar_t *)result.data(), size, _TRUNCATE, fmt, ap);
    return result;
}

hal::String & hal::Stringfv(String & result, wchar_t const * fmt, va_list ap)
{
    result.append(Stringfv(fmt, ap));
    return result;
}

hal::String hal::Stringf(wchar_t const * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    String result = Stringfv(fmt, ap);
    va_end(ap);
    return result;
}

hal::String & hal::Stringf(String & result, wchar_t const * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    result.append(Stringfv(fmt, ap));
    va_end(ap);
    return result;
}
