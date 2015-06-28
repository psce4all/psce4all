/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_TextView.h"

#include <algorithm>
#include <memory>

#include <QAction>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFontDialog>
#include <QMenu>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWheelEvent>

//#include "GotoLineWidget.h"
//#include "SearchWidget.h"
//#include "TextEditSearcher.h"

qt_TextView::qt_TextView(const QString &title, QWidget *parent)
    : QDockWidget(title, parent)
{
    textEdit_ = new QPlainTextEdit(this);
    textEdit_->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);
    textEdit_->setLineWrapMode(QPlainTextEdit::NoWrap);
    textEdit_->installEventFilter(this);
    textEdit_->viewport()->installEventFilter(this);
    textEdit_->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(textEdit_, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(showContextMenu(const QPoint &)));
    connect(this, SIGNAL(contextMenuCreated(QMenu *)), this, SLOT(populateContextMenu(QMenu *)));
    connect(textEdit_->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateExtraSelections()));
    connect(textEdit_->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(updateExtraSelections()));

    //auto searchWidget = new SearchWidget(std::make_unique<TextEditSearcher>(textEdit_), this);
    //searchWidget->hide();

    //GotoLineWidget *gotoLineWidget = new GotoLineWidget(textEdit_, this);
    //gotoLineWidget->hide();

    QWidget *widget = new QWidget(this);

    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(QMargins());
    layout->addWidget(textEdit_);
    //layout->addWidget(searchWidget);
    //layout->addWidget(gotoLineWidget);

    setWidget(widget);

    saveAsAction_ = new QAction(tr("Save As..."), this);
    saveAsAction_->setShortcut(QKeySequence::Save);
    saveAsAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    addAction(saveAsAction_);

    connect(saveAsAction_, SIGNAL(triggered()), this, SLOT(saveAs()));

    QList<QKeySequence> searchShortcuts;
    searchShortcuts.append(QKeySequence::Find);
    searchShortcuts.append(tr("/"));

    //openSearchAction_ = new QAction(tr("Find..."), this);
    //openSearchAction_->setShortcuts(searchShortcuts);
    //openSearchAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    //addAction(openSearchAction_);

    //connect(openSearchAction_, SIGNAL(triggered()), searchWidget, SLOT(activate()));

    //findNextAction_ = new QAction(tr("Find Next"), this);
    //findNextAction_->setShortcut(QKeySequence::FindNext);
    //findNextAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    //addAction(findNextAction_);

    //connect(findNextAction_, SIGNAL(triggered()), searchWidget, SLOT(findNext()));

    //findPreviousAction_ = new QAction(tr("Find Previous"), this);
    //findPreviousAction_->setShortcut(QKeySequence::FindPrevious);
    //findPreviousAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    //addAction(findPreviousAction_);

    //connect(findPreviousAction_, SIGNAL(triggered()), searchWidget, SLOT(findPrevious()));

    //QList<QKeySequence> gotoLineShortcuts;
    //gotoLineShortcuts.append(Qt::CTRL + Qt::Key_G);

    //openGotoLineAction_ = new QAction(tr("Go to Line..."), this);
    //openGotoLineAction_->setShortcuts(gotoLineShortcuts);
    //openGotoLineAction_->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    //addAction(openGotoLineAction_);

    //connect(openGotoLineAction_, SIGNAL(triggered()), gotoLineWidget, SLOT(activate()));

    QAction *closeEverythingAction = new QAction(this);
    closeEverythingAction->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    closeEverythingAction->setShortcut(Qt::Key_Escape);
    addAction(closeEverythingAction);

    //connect(closeEverythingAction, SIGNAL(triggered()), searchWidget, SLOT(deactivate()));
    //connect(closeEverythingAction, SIGNAL(triggered()), gotoLineWidget, SLOT(deactivate()));
    connect(closeEverythingAction, SIGNAL(triggered()), textEdit(), SLOT(setFocus()));

    selectFontAction_ = new QAction(tr("Select Font..."), this);
    addAction(selectFontAction_);

    connect(selectFontAction_, SIGNAL(triggered()), this, SLOT(selectFont()));
}

void qt_TextView::setDocument(QTextDocument *document)
{
    /* QTextEdit crashes when extra selections get out of range. */
    textEdit()->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    highlighting_.clear();

    textEdit_->setDocument(document);
    setDocumentFont(documentFont());
}

void qt_TextView::updatePositionStatus()
{
    QTextCursor cursor = textEdit()->textCursor();
    int line = cursor.blockNumber() + 1;
    int column = cursor.columnNumber() + 1;

    emit status(tr("Line %1, Column %2").arg(line).arg(column));
}

void qt_TextView::showContextMenu(const QPoint &pos)
{
    std::unique_ptr<QMenu> menu(textEdit()->createStandardContextMenu());

    emit contextMenuCreated(menu.get());

    if (!menu->isEmpty())
    {
        menu->exec(textEdit()->mapToGlobal(pos));
    }
}

void qt_TextView::populateContextMenu(QMenu *menu)
{
    menu->addSeparator();
    menu->addAction(saveAsAction_);
    //menu->addSeparator();
    //menu->addAction(openSearchAction_);
    //menu->addAction(findNextAction_);
    //menu->addAction(findPreviousAction_);
    //menu->addSeparator();
    //menu->addAction(openGotoLineAction_);
    menu->addSeparator();
    menu->addAction(selectFontAction_);
    menu->addSeparator();
}

void qt_TextView::highlight(std::vector< std::pair< int, int > > ranges, bool ensureVisible)
{
    if (!ranges.empty())
    {
        std::sort(ranges.begin(), ranges.end());

        if (ensureVisible)
        {
            std::vector< std::pair< int, int > > difference;

            set_difference(
                ranges.begin(), ranges.end(),
                highlighting_.begin(), highlighting_.end(),
                std::back_inserter(difference));

            if (difference.empty())
            {
                set_difference(
                    highlighting_.begin(), highlighting_.end(),
                    ranges.begin(), ranges.end(),
                    std::back_inserter(difference));
            }

            if (!difference.empty())
            {
                textEdit()->blockSignals(true);
                moveCursor(difference.front().second, true);
                moveCursor(difference.front().first, true);
                textEdit()->blockSignals(false);
            }
        }

        highlighting_.swap(ranges);
    }
    else
    {
        highlighting_.clear();
    }

    updateExtraSelections();
}

void qt_TextView::updateExtraSelections()
{
    auto size = textEdit()->viewport()->size();
    auto firstVisiblePosition = textEdit()->cursorForPosition(QPoint(0, 0)).position();
    auto lastVisiblePosition = textEdit()->cursorForPosition(QPoint(size.width() - 1, size.height() - 1)).position();

    auto first = std::lower_bound(highlighting_.begin(), highlighting_.end(), firstVisiblePosition,
                                  [](const std::pair< int, int > &range, int pos) { return range.second < pos; });

    QList<QTextEdit::ExtraSelection> selections;

    for (auto i = first; i != highlighting_.end() && i->first <= lastVisiblePosition; ++i)
    {
        QTextEdit::ExtraSelection selection;
        selection.cursor = textEdit()->textCursor();
        selection.cursor.setPosition(i->first);
        selection.cursor.setPosition(i->second, QTextCursor::KeepAnchor);
        selection.format.setBackground(qApp->palette().highlight());
        selections.append(selection);
    }

    textEdit()->setExtraSelections(selections);
}

void qt_TextView::moveCursor(int position, bool ensureVisible)
{
    QTextCursor cursor = textEdit()->textCursor();
    cursor.setPosition(position);
    textEdit()->setTextCursor(cursor);
    if (ensureVisible)
    {
        textEdit()->ensureCursorVisible();
    }
}

void qt_TextView::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Choose the location where to save"));
    if (!filename.isEmpty())
    {
        QFile file(filename);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QMessageBox::critical(this, tr("Error"), tr("File %1 could not be opened for writing.").arg(filename));
        }

        QTextStream out(&file);
        out << textEdit()->toPlainText();
    }
}

void qt_TextView::zoomIn(int delta)
{
    QFont font = documentFont();
    font.setPointSize(std::max(font.pointSize() + delta, 1));
    setDocumentFont(font);
}

void qt_TextView::zoomOut(int delta)
{
    zoomIn(-delta);
}

const QFont &qt_TextView::documentFont() const
{
    return textEdit()->font();
}

void qt_TextView::setDocumentFont(const QFont &font)
{
    textEdit()->setFont(font);
    textEdit()->document()->setDefaultFont(font);
}

void qt_TextView::selectFont()
{
    setDocumentFont(QFontDialog::getFont(nullptr, documentFont(), this));
}

bool qt_TextView::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == textEdit())
    {
        if (event->type() == QEvent::FocusIn) {
            connect(textEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(updatePositionStatus()));
            updatePositionStatus();
        }
        else if (event->type() == QEvent::FocusOut)
        {
            disconnect(textEdit_, SIGNAL(cursorPositionChanged()), this, SLOT(updatePositionStatus()));
        }
    }
    if (watched == textEdit()->viewport())
    {
        if (event->type() == QEvent::Resize)
        {
            updateExtraSelections();
        }
        else if (event->type() == QEvent::Wheel)
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
