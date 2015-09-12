/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_treeviewsearcher.h"

#include <cassert>

#include <QScrollBar>
#include <QTreeView>

qt_TreeViewSearcher::qt_TreeViewSearcher(QTreeView *treeView)
    : treeView_(treeView)
    , hvalue_(-1)
    , vvalue_(-1)
{
    assert(treeView != nullptr);
}

void qt_TreeViewSearcher::startTrackingViewport()
{
    if (treeView_->selectionModel())
    {
        connect(treeView_->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(rememberViewport()));
    }
}

void qt_TreeViewSearcher::stopTrackingViewport()
{
    if (treeView_->selectionModel())
    {
        disconnect(treeView_->selectionModel(), SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(rememberViewport()));
    }
}

void qt_TreeViewSearcher::rememberViewport()
{
    if (!treeView_->selectionModel())
    {
        hvalue_ = vvalue_ = -1;
        selectedIndexes_.clear();
        currentIndex_ = QModelIndex();
        return;
    }

    selectedIndexes_ = treeView_->selectionModel()->selectedIndexes();
    currentIndex_ = treeView_->selectionModel()->currentIndex();
    hvalue_ = treeView_->horizontalScrollBar()->value();
    vvalue_ = treeView_->verticalScrollBar()->value();
}

void qt_TreeViewSearcher::restoreViewport()
{
    if (hvalue_ == -1 || !treeView_->selectionModel())
    {
        return;
    }

    treeView_->setCurrentIndex(currentIndex_);

    treeView_->selectionModel()->blockSignals(true);
    treeView_->selectionModel()->clearSelection();
    foreach (const auto &index, selectedIndexes_)
    {
        treeView_->selectionModel()->select(index, QItemSelectionModel::Select);
    }
    treeView_->selectionModel()->blockSignals(false);

    // Trigger TreeView update.
    treeView_->selectionModel()->select(QModelIndex(), QItemSelectionModel::NoUpdate);

    treeView_->horizontalScrollBar()->setValue(hvalue_);
    treeView_->verticalScrollBar()->setValue(vvalue_);
}

qt_Searcher::FindFlags qt_TreeViewSearcher::supportedFlags() const
{
    return FindBackward | FindCaseSensitive | FindRegexp;
}

namespace
{
    bool match(const QModelIndex &index, const QString &expression, qt_Searcher::FindFlags flags)
    {
        Qt::CaseSensitivity caseSensitivity = flags & qt_Searcher::FindCaseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

        auto data = index.data().toString();

        if (flags & qt_Searcher::FindRegexp)
        {
            return data.contains(QRegExp(expression, caseSensitivity));
        }
        else
        {
            return data.contains(expression, caseSensitivity);
        }
    }

    QModelIndex findFirst(const QModelIndex &start, const QString &expression, qt_Searcher::FindFlags flags)
    {
        if (!start.isValid())
        {
            return QModelIndex();
        }

        auto model = start.model();
        auto parent = start.parent();

        int rowCount = model->rowCount(parent);
        int columnCount = model->columnCount(parent);

        if (!(flags & qt_Searcher::FindBackward))
        {
            // Process the end of the same row.
            for (int column = start.column() + 1; column < columnCount; ++column)
            {
                auto index = model->index(start.row(), column, parent);
                if (match(index, expression, flags))
                {
                    return index;
                }
            }

            // Process all rows below.
            for (int row = start.row() + 1; row < rowCount; ++row)
            {
                for (int column = 0; column < columnCount; ++column)
                {
                    auto index = model->index(row, column, parent);
                    if (match(index, expression, flags))
                    {
                        return index;
                    }
                }
            }

            // Start from the beginning.
            for (int row = 0; row < start.row(); ++row)
            {
                for (int column = 0; column < columnCount; ++column)
                {
                    auto index = model->index(row, column, parent);
                    if (match(index, expression, flags))
                    {
                        return index;
                    }
                }
            }

            // Process the beginning of the same row.
            for (int column = 0; column <= start.column(); ++column)
            {
                auto index = model->index(start.row(), column, parent);
                if (match(index, expression, flags))
                {
                    return index;
                }
            }
        }
        else
        {
            // Process the beginning of the same row.
            for (int column = start.column() - 1; column >= 0; --column)
            {
                auto index = model->index(start.row(), column, parent);
                if (match(index, expression, flags))
                {
                    return index;
                }
            }

            // Process all rows above.
            for (int row = start.row() - 1; row >= 0; --row)
            {
                for (int column = columnCount - 1; column >= 0; --column)
                {
                    auto index = model->index(row, column, parent);
                    if (match(index, expression, flags))
                    {
                        return index;
                    }
                }
            }

            // Start from the end.
            for (int row = rowCount - 1; row > start.row(); --row)
            {
                for (int column = columnCount - 1; column >= 0; --column)
                {
                    auto index = model->index(row, column, parent);
                    if (match(index, expression, flags))
                    {
                        return index;
                    }
                }
            }

            // Process the end of the same row.
            for (int column = columnCount - 1; column >= start.column(); --column)
            {
                auto index = model->index(start.row(), column, parent);
                if (match(index, expression, flags))
                {
                    return index;
                }
            }
        }

        return QModelIndex();
    }
} // anonymous namespace

bool qt_TreeViewSearcher::find(const QString &expression, FindFlags flags)
{
    if (expression.isEmpty())
    {
        return true;
    }

    if (treeView_->model() == nullptr)
    {
        return false;
    }

    QModelIndex result = findFirst(treeView_->currentIndex(), expression, flags);

    if (result.isValid())
    {
        treeView_->setCurrentIndex(result);
        treeView_->scrollTo(result);
        return true;
    }
    else
    {
        return false;
    }
}
