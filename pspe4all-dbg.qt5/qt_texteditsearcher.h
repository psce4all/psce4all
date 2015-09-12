/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QObject>
#include <QTextCursor>

#include "qt_searcher.h"

#include <QPlainTextEdit>

class qt_TextEditSearcher : public QObject, public qt_Searcher
{
    Q_OBJECT

    QPlainTextEdit *textEdit_;
    QTextCursor     cursor_;
    int             hvalue_;
    int             vvalue_;

public:
    qt_TextEditSearcher(QPlainTextEdit *textEdit);

public slots:
    virtual void      rememberViewport() override;
    virtual void      restoreViewport() override;

public:
    virtual void      startTrackingViewport() override;
    virtual void      stopTrackingViewport() override;

    virtual FindFlags supportedFlags() const override;
    virtual bool      find(const QString &expression, FindFlags flags) override;
};
