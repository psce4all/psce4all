/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_logview.h"

qt_LogView::qt_LogView(QWidget *parent)
    : qt_TextView(tr("Log"), parent)
{
    textEdit()->document()->setMaximumBlockCount(10000);
    setDocumentFont(QFont("Courier New"));
}

void qt_LogView::log(const QString &text)
{
    if (text.endsWith("\r\n"))
    {
        textEdit()->appendPlainText(text.mid(0, text.size() - 2));
    }
    else
    {
        textEdit()->appendPlainText(text);
    }
}
