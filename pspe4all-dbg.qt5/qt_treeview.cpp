/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_treeview.h"

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QEvent>
#include <QFontDialog>
#include <QMenu>
#include <QTreeView>
#include <QVBoxLayout>
#include <QtAlgorithms>
#include <QWheelEvent>

#include "qt_searchwidget.h"
#include "qt_treeviewsearcher.h"

qt_TreeView::qt_TreeView(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
    treeView_ = new QTreeView(this);

    treeView_->setContextMenuPolicy(Qt::CustomContextMenu);
    treeView_->viewport()->installEventFilter(this);

    connect(treeView_, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
    connect(this, SIGNAL(contextMenuCreated(QMenu *)), this, SLOT(populateContextMenu(QMenu *)));

    auto searchWidget = new qt_SearchWidget(std::make_unique< qt_TreeViewSearcher >(treeView_), this);
    searchWidget->hide();

    QWidget *widget = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(QMargins());
    layout->addWidget(treeView_);
    layout->addWidget(searchWidget);

    setWidget(widget);

    QList<QKeySequence> searchShortcuts;
    searchShortcuts.append(QKeySequence::Find);
    searchShortcuts.append(tr("/"));

    copyAction_ = new QAction(tr("Copy"), this);
    copyAction_->setShortcut(QKeySequence::Copy);
    copyAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    treeView()->addAction(copyAction_);

    connect(copyAction_, SIGNAL(triggered()), this, SLOT(copy()));

    openSearchAction_ = new QAction(tr("Find..."), this);
    openSearchAction_->setShortcuts(searchShortcuts);
    openSearchAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addAction(openSearchAction_);
    connect(openSearchAction_, SIGNAL(triggered()), searchWidget, SLOT(activate()));

    findNextAction_ = new QAction(tr("Find Next"), this);
    findNextAction_->setShortcut(QKeySequence::FindNext);
    findNextAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addAction(findNextAction_);
    connect(findNextAction_, SIGNAL(triggered()), searchWidget, SLOT(findNext()));

    findPreviousAction_ = new QAction(tr("Find Previous"), this);
    findPreviousAction_->setShortcut(QKeySequence::FindPrevious);
    findPreviousAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addAction(findPreviousAction_);
    connect(findPreviousAction_, SIGNAL(triggered()), searchWidget, SLOT(findPrevious()));

    QAction *closeEverythingAction = new QAction(this);
    closeEverythingAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    closeEverythingAction->setShortcut(Qt::Key_Escape);
    addAction(closeEverythingAction);

    connect(closeEverythingAction, SIGNAL(triggered()), searchWidget, SLOT(deactivate()));
    connect(closeEverythingAction, SIGNAL(triggered()), treeView_, SLOT(setFocus()));

    selectFontAction_ = new QAction(tr("Select Font..."), this);
    addAction(selectFontAction_);

    connect(selectFontAction_, SIGNAL(triggered()), this, SLOT(selectFont()));
}

void qt_TreeView::showContextMenu(const QPoint &pos)
{
    auto menu = std::make_unique<QMenu>();

    emit contextMenuCreated(menu.get());

    if (!menu->isEmpty())
    {
        menu->exec(treeView()->viewport()->mapToGlobal(pos));
    }
}

void qt_TreeView::populateContextMenu(QMenu *menu)
{
    if (!treeView_->selectionModel())
    {
        return;
    }
    if (!treeView_->selectionModel()->selectedIndexes().isEmpty())
    {
        menu->addSeparator();
        menu->addAction(copyAction_);
    }

    menu->addSeparator();
    menu->addAction(tr("Select All"), treeView(), SLOT(selectAll()), QKeySequence::SelectAll);
    menu->addSeparator();
    menu->addAction(openSearchAction_);
    menu->addAction(findNextAction_);
    menu->addAction(findPreviousAction_);
    menu->addSeparator();
    menu->addAction(selectFontAction_);
    menu->addSeparator();
}

void qt_TreeView::copy()
{
    auto indexes = treeView()->selectionModel()->selectedIndexes();

    if (indexes.isEmpty())
    {
        return;
    }

    qSort(indexes.begin(), indexes.end(), [](const QModelIndex &a, const QModelIndex &b) -> bool
    {
        if (a.parent() == b.parent())
        {
            return a.row() < b.row() || (a.row() == b.row() && a.column() < b.column());
        }
        else
        {
            return a < b;
        }
    });

    QString text;

    QModelIndex last;
    foreach (const auto &index, indexes)
    {
        if (last.parent() != index.parent() || last.row() != index.row()) {
            if (!text.isEmpty())
            {
                text += '\n';
            }
            last = index;
        }
        else
        {
            text += '\t';
        }
        text += index.data().toString();
    }

    QApplication::clipboard()->setText(text);
}

void qt_TreeView::zoomIn(int delta)
{
    QFont font = documentFont();
    font.setPointSize(std::max(font.pointSize() + delta, 1));
    setDocumentFont(font);
}

void qt_TreeView::zoomOut(int delta)
{
    zoomIn(-delta);
}

const QFont &qt_TreeView::documentFont() const
{
    return treeView()->font();
}

void qt_TreeView::setDocumentFont(const QFont &font)
{
    treeView()->setFont(font);
}

void qt_TreeView::selectFont()
{
    setDocumentFont(QFontDialog::getFont(nullptr, documentFont(), this, QString(), QFontDialog::MonospacedFonts));
}

bool qt_TreeView::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == treeView()->viewport())
    {
        if (event->type() == QEvent::Wheel)
        {
            auto wheelEvent = static_cast<QWheelEvent *>(event);

            if (wheelEvent->orientation() == Qt::Vertical && wheelEvent->modifiers() & Qt::ControlModifier)
            {
                if (wheelEvent->delta() > 0)
                {
                    zoomIn(1 + wheelEvent->delta() / 360);
                }
                else
                {
                    zoomOut(1 - wheelEvent->delta() / 360);
                }
                return true;
            }
        }
    }
    return QDockWidget::eventFilter(watched, event);
}
