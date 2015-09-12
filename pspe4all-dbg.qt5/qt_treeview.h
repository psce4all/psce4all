/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QDockWidget>
#include <QMenu>
#include <QTreeView>

#include <vector>

class qt_TreeView : public QDockWidget
{
    Q_OBJECT

    QTreeView *treeView_;
    QAction   *copyAction_;
    QAction   *openSearchAction_;
    QAction   *findNextAction_;
    QAction   *findPreviousAction_;
    QAction   *selectFontAction_;

public:
    qt_TreeView(const QString &title, QWidget *parent = nullptr);

    QTreeView *treeView() const { return treeView_; }

    const QFont &documentFont() const;

public slots:
    void copy();
    void zoomIn(int delta = 1);
    void zoomOut(int delta = 1);
    virtual void setDocumentFont(const QFont &font);
    void selectFont();

signals:
    void contextMenuCreated(QMenu *menu);

private slots:
    void showContextMenu(const QPoint &pos);
    void populateContextMenu(QMenu *menu);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
