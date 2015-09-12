/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_searchwidget.h"

#include <cassert>

#include <QAction>
#include <QCompleter>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPalette>
#include <QPushButton>
#include <QStringListModel>
#include <QTimer>

#include "qt_searcher.h"

qt_SearchWidget::qt_SearchWidget(std::unique_ptr< qt_Searcher > searcher, QWidget *parent)
    : QWidget(parent)
    , searcher_(std::move(searcher))
{
    assert(searcher_ != nullptr);

    auto supportedFlags = searcher_->supportedFlags();

    completionModel_ = new QStringListModel(this);

    QLabel *findLabel = new QLabel(tr("Find:"), this);

    lineEdit_ = new QLineEdit(this);
    lineEdit_->setCompleter(new QCompleter(completionModel_, this));
    lineEdit_->completer()->setCaseSensitivity(Qt::CaseInsensitive);
    lineEdit_->setMinimumWidth(lineEdit_->fontMetrics().boundingRect("X").width() * 8);
    connect(lineEdit_, SIGNAL(textChanged(const QString &)), this, SLOT(scheduleIncrementalSearch()));
    connect(lineEdit_, SIGNAL(returnPressed()), this, SLOT(findNext()));
    connect(lineEdit_, SIGNAL(returnPressed()), this, SLOT(rememberCompletion()));

    normalPalette_ = lineEdit_->palette();
    failurePalette_ = lineEdit_->palette();
    failurePalette_.setColor(QPalette::Base, QColor(255, 192, 192));

    QPushButton *nextButton = new QPushButton(tr("&Next"), this);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(findNext()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(rememberCompletion()));

    QPushButton *previousButton = nullptr;
    if (supportedFlags & qt_Searcher::FindBackward)
    {
        previousButton = new QPushButton(tr("&Previous"), this);
        connect(previousButton, SIGNAL(clicked()), this, SLOT(findPrevious()));
        connect(previousButton, SIGNAL(clicked()), this, SLOT(rememberCompletion()));
    }

    incrementalSearchAction_ = new QAction(tr("&Incremental Search"), this);
    incrementalSearchAction_->setCheckable(true);
    incrementalSearchAction_->setChecked(true);

    caseSensitiveAction_ = new QAction(tr("&Case Sensitive"), this);
    caseSensitiveAction_->setCheckable(true);

    wholeWordsAction_ = new QAction(tr("&Whole Words"), this);
    wholeWordsAction_->setCheckable(true);

    regexpAction_ = new QAction(tr("&Regular Expression"), this);
    regexpAction_->setCheckable(true);

    QMenu *optionsMenu = new QMenu(this);
    optionsMenu->addAction(incrementalSearchAction_);
    if (supportedFlags & qt_Searcher::FindCaseSensitive)
    {
        optionsMenu->addAction(caseSensitiveAction_);
    }
    if (supportedFlags & qt_Searcher::FindWholeWords)
    {
        optionsMenu->addAction(wholeWordsAction_);
    }
    if (supportedFlags & qt_Searcher::FindRegexp)
    {
        regexpAction_->setChecked(true);
        optionsMenu->addAction(regexpAction_);
    }

    QPushButton *optionsButton = new QPushButton(tr("&Options"), this);
    optionsButton->setMenu(optionsMenu);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(4, 0, 4, 4);
    layout->addWidget(findLabel);
    layout->addWidget(lineEdit_);
    layout->addWidget(nextButton);
    if (previousButton) layout->addWidget(previousButton);
    layout->addWidget(optionsButton);

    incrementalSearchTimer_ = new QTimer(this);
    incrementalSearchTimer_->setInterval(250);
    incrementalSearchTimer_->setSingleShot(true);

    connect(incrementalSearchTimer_, SIGNAL(timeout()), this, SLOT(performIncrementalSearch()));
}

qt_SearchWidget::~qt_SearchWidget()
{
}

void qt_SearchWidget::activate()
{
    show();

    lineEdit_->selectAll();
    lineEdit_->setFocus();

    searcher()->startTrackingViewport();
    searcher()->rememberViewport();
}

void qt_SearchWidget::deactivate()
{
    if (!isVisible())
    {
        return;
    }

    searcher()->stopTrackingViewport();
    searcher()->restoreViewport();

    incrementalSearchTimer_->stop();

    hide();
}

void qt_SearchWidget::findNext()
{
    searcher()->stopTrackingViewport();
    searcher()->restoreViewport();

    if (searcher()->find(lineEdit_->text(), searchFlags()))
    {
        searcher()->rememberViewport();
        indicateSuccess();
    }
    else
    {
        searcher()->restoreViewport();
        indicateFailure();
    }

    searcher()->startTrackingViewport();
}

void qt_SearchWidget::findPrevious()
{
    searcher()->stopTrackingViewport();
    searcher()->restoreViewport();

    if (searcher()->find(lineEdit_->text(), searchFlags() | qt_Searcher::FindBackward))
    {
        searcher()->rememberViewport();
        indicateSuccess();
    }
    else
    {
        searcher()->restoreViewport();
        indicateFailure();
    }

    searcher()->startTrackingViewport();
}

void qt_SearchWidget::scheduleIncrementalSearch()
{
    if (!incrementalSearchAction_->isChecked())
    {
        indicateSuccess();
        return;
    }

    incrementalSearchTimer_->start();
}

void qt_SearchWidget::performIncrementalSearch()
{
    searcher()->stopTrackingViewport();
    searcher()->restoreViewport();

    if (searcher()->find(lineEdit_->text(), searchFlags()))
    {
        indicateSuccess();
    }
    else
    {
        searcher()->restoreViewport();
        indicateFailure();
    }

    searcher()->startTrackingViewport();
}

int qt_SearchWidget::searchFlags() const
{
    return
        (caseSensitiveAction_->isChecked() ? qt_Searcher::FindCaseSensitive : 0) |
        (wholeWordsAction_->isChecked() ? qt_Searcher::FindWholeWords : 0) |
        (regexpAction_->isChecked() ? qt_Searcher::FindRegexp : 0);
}

void qt_SearchWidget::indicateSuccess()
{
    lineEdit_->setPalette(normalPalette_);
}

void qt_SearchWidget::indicateFailure()
{
    lineEdit_->setPalette(failurePalette_);
}

void qt_SearchWidget::rememberCompletion()
{
    QStringList list = completionModel_->stringList();
    if (!list.contains(lineEdit_->text(), lineEdit_->completer()->caseSensitivity()))
    {
        list.append(lineEdit_->text());
        completionModel_->setStringList(list);
    }
}
