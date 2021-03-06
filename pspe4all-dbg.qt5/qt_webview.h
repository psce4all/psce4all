/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QDockWidget>
//#include <QWebEngineView>

class qt_WebView : public QDockWidget
{
    Q_OBJECT

	//QWebEngineView *webView_;
public:
    qt_WebView(const QString &title, QWidget *parent = 0);

	//QWebEngineView *webView() const { return webView_; }

public slots:
    void setMarkdownDocument(const QString & text);
};
