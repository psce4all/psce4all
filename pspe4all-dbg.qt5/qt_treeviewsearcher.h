/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QModelIndex>
#include <QObject>

#include "qt_searcher.h"

#include <QTreeView>

class qt_TreeViewSearcher: public QObject, public qt_Searcher
{
    Q_OBJECT

    QTreeView      *treeView_;
    QModelIndex     currentIndex_;
    QModelIndexList selectedIndexes_;
    int             hvalue_;
    int             vvalue_;

public:
    qt_TreeViewSearcher(QTreeView *treeView);

public slots:
    virtual void rememberViewport() override;
    virtual void restoreViewport() override;

public:
    virtual void startTrackingViewport() override;
    virtual void stopTrackingViewport() override;

    virtual FindFlags supportedFlags() const override;
    virtual bool find(const QString &string, int flags) override;
};
