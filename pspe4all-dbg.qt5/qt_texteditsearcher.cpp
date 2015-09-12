/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_texteditsearcher.h"

#include <cassert>

#include <QPlainTextEdit>
#include <QScrollBar>

qt_TextEditSearcher::qt_TextEditSearcher(QPlainTextEdit *textEdit)
    : textEdit_(textEdit)
    , hvalue_(-1)
    , vvalue_(-1)
{
    assert(textEdit != nullptr);
}

void qt_TextEditSearcher::startTrackingViewport()
{
    connect(textEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(rememberViewport()));
}

void qt_TextEditSearcher::stopTrackingViewport()
{
    disconnect(textEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(rememberViewport()));
}

void qt_TextEditSearcher::rememberViewport()
{
    cursor_ = textEdit_->textCursor();
    hvalue_ = textEdit_->horizontalScrollBar()->value();
    vvalue_ = textEdit_->verticalScrollBar()->value();
}

void qt_TextEditSearcher::restoreViewport()
{
    if (hvalue_ == -1)
    {
        return;
    }

    textEdit_->setTextCursor(cursor_);
    textEdit_->horizontalScrollBar()->setValue(hvalue_);
    textEdit_->verticalScrollBar()->setValue(vvalue_);
}

qt_Searcher::FindFlags qt_TextEditSearcher::supportedFlags() const
{
    return FindBackward | FindCaseSensitive | FindWholeWords;
}

bool qt_TextEditSearcher::find(const QString &expression, FindFlags flags)
{
    if (expression.isEmpty())
    {
        return true;
    }

    auto options = QTextDocument::FindFlags();

    if (flags & FindBackward)
    {
        options |= QTextDocument::FindBackward;
    }
    if (flags & FindCaseSensitive)
    {
        options |= QTextDocument::FindCaseSensitively;
    }
    if (flags & FindWholeWords)
    {
        options |= QTextDocument::FindWholeWords;
    }

    if (textEdit_->find(expression, options))
    {
        return true;
    }
    else
    {
        QTextCursor cursor = textEdit_->textCursor();
        cursor.movePosition((flags & FindBackward) ? QTextCursor::End : QTextCursor::Start);
        textEdit_->setTextCursor(cursor);

        return textEdit_->find(expression, options);
    }
}
