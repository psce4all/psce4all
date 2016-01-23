/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_WebView.h"
#include "markdowncxx.h"
/*#include <QWebEngineView>
#include <QWebFrame>*/

qt_WebView::qt_WebView(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
   /* webView_ = new QWebEngineView(this);

    setWidget(webView_);*/
}

void qt_WebView::setMarkdownDocument(const QString & text)
{
    /*std::string htmlRes;
    markdown2html(text.toStdString(), htmlRes);
    webView_->page()->mainFrame()->setHtml(QString(htmlRes.c_str()));*/
}
