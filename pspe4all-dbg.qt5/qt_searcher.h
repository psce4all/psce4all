/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QString>

class qt_Searcher
{
public:
    enum FindFlag
    {
        FindBackward        = 0x1,
        FindCaseSensitive   = 0x2,
        FindWholeWords      = 0x4,
        FindRegexp          = 0x8
    };

    typedef int FindFlags;

    virtual ~qt_Searcher() {}

    virtual void      rememberViewport() = 0;
    virtual void      restoreViewport() = 0;
    virtual void      startTrackingViewport() = 0;
    virtual void      stopTrackingViewport() = 0;
    virtual FindFlags supportedFlags() const = 0;
    virtual bool      find(const QString &expression, FindFlags flags) = 0;
};
