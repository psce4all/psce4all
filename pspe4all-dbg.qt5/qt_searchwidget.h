/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <memory>

#include <QTextDocument>
#include <QWidget>

#include <QAction>
#include <QLineEdit>
#include <QStringListModel>

class qt_Searcher;

class qt_SearchWidget : public QWidget
{
    Q_OBJECT

public:
    qt_SearchWidget(std::unique_ptr<qt_Searcher> searcher, QWidget *parent = nullptr);

    ~qt_SearchWidget();

    qt_Searcher *searcher() const { return searcher_.get(); }

public slots:
    void activate();
    void deactivate();
    void findNext();
    void findPrevious();

private slots:
    void scheduleIncrementalSearch();
    void performIncrementalSearch();
    void rememberCompletion();

private:
    std::unique_ptr< qt_Searcher> searcher_;
    QLineEdit                    *lineEdit_;
    QStringListModel             *completionModel_;
    QAction                      *incrementalSearchAction_;
    QAction                      *caseSensitiveAction_;
    QAction                      *wholeWordsAction_;
    QAction                      *regexpAction_;
    QPalette                      normalPalette_;
    QPalette                      failurePalette_;
    QTimer                       *incrementalSearchTimer_;

    int searchFlags() const;
    void indicateSuccess();
    void indicateFailure();
};
