/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QDockWidget>
#include <QEvent>
#include <QMenu>
#include <QPlainTextEdit>
#include <QTextDocument>

#include <vector>

class qt_TextView : public QDockWidget
{
    Q_OBJECT

    QPlainTextEdit                     *textEdit_;
    QAction                            *saveAsAction_;
    QAction                            *openSearchAction_;
    QAction                            *findNextAction_;
    QAction                            *findPreviousAction_;
    QAction                            *openGotoLineAction_;
    QAction                            *selectFontAction_;
    std::vector< std::pair< int,int > > highlighting_;

public:
    qt_TextView(const QString &title, QWidget *parent = 0);

    QPlainTextEdit *textEdit() const { return textEdit_; }

    void setDocument(QTextDocument *document);

public slots:
    void highlight(std::vector< std::pair< int, int > > ranges, bool ensureVisible = true);
    void moveCursor(int position, bool ensureVisible = true);
    void saveAs();
    void zoomIn(int delta = 1);
    void zoomOut(int delta = 1);

public:
    const QFont &documentFont() const;

public slots:
    void setDocumentFont(const QFont &font);
    void selectFont();

signals:
    void contextMenuCreated(QMenu *menu);
    void status(const QString &message = QString());

private slots:
    void updateExtraSelections();
    void updatePositionStatus();
    void showContextMenu(const QPoint &pos);
    void populateContextMenu(QMenu *menu);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
};
