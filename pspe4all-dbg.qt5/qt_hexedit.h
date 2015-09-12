/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QAbstractScrollArea>
#include <QPen>
#include <QBrush>

#include "qt_hexchunks.h"
#include "qt_hexcommands.h"

class qt_HexEdit : public QAbstractScrollArea
{
    Q_OBJECT

    Q_PROPERTY(QColor addressAreaColor READ addressAreaColor WRITE setAddressAreaColor)

    Q_PROPERTY(qint64 addressOffset READ addressOffset WRITE setAddressOffset)

    Q_PROPERTY(qint64 cursorPosition READ cursorPosition WRITE setCursorPosition)

    Q_PROPERTY(QByteArray data READ data WRITE setData)

    Q_PROPERTY(QColor highlightingColor READ highlightingColor WRITE setHighlightingColor)

    Q_PROPERTY(bool overwriteMode READ overwriteMode WRITE setOverwriteMode)

    Q_PROPERTY(QColor selectionColor READ selectionColor WRITE setSelectionColor)

    Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)

    Q_PROPERTY(QFont font READ font WRITE setFont)

public:
    qt_HexEdit(QWidget *parent=0);

    QByteArray dataAt(qint64 pos, qint64 count=-1);

    bool write(QIODevice &iODevice, qint64 pos=0, qint64 count=-1);

    void insert(qint64 pos, char ch);

    void remove(qint64 pos, qint64 len=1);

    void replace(qint64 pos, char ch);

    void insert(qint64 pos, const QByteArray &ba);

    void replace(qint64 pos, qint64 len, const QByteArray &ba);

    bool addressArea();

    int addressWidth();

    bool asciiArea();

    qint64 cursorPosition(QPoint point);

    void ensureVisible();

    qint64 indexOf(const QByteArray &ba, qint64 from);

    bool isModified();

    bool highlighting();

    qint64 lastIndexOf(const QByteArray &ba, qint64 from);

    QString selectionToReadableString();

    virtual void setFont(const QFont &font);

    QString toReadableString();

    QMenu *createStandardContextMenu();

public slots:
    void redo();

    void setAddressArea(bool addressArea);

    void setAddressWidth(int addressWidth);

    void setAsciiArea(bool asciiArea);

    void setHighlighting(bool mode);

    void undo();

signals:
    void currentAddressChanged(qint64 address);

    void currentSizeChanged(qint64 size);

    void dataChanged();

    void overwriteModeChanged(bool state);

public:
    ~qt_HexEdit();

    QColor addressAreaColor();
    void setAddressAreaColor(const QColor &color);

    qint64 addressOffset();
    void setAddressOffset(qint64 addressArea);

    qint64 cursorPosition();
    void setCursorPosition(qint64 position);

    QByteArray data();
    void setData(const QByteArray &ba);

    QColor highlightingColor();
    void setHighlightingColor(const QColor &color);

    bool overwriteMode();
    void setOverwriteMode(bool overwriteMode);

    bool isReadOnly();
    void setReadOnly(bool readOnly);

    QColor selectionColor();
    void setSelectionColor(const QColor &color);

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

private:
    void resetSelection(qint64 pos);
    void resetSelection();
    void setSelection(qint64 pos);
    int getSelectionBegin();
    int getSelectionEnd();

    void init();
    void readBuffers();
    QString toReadable(const QByteArray &ba);

private slots:
    void adjust();
    void dataChangedPrivate(int idx=0);
    void refresh();
    void updateCursor();

private:
    int _pxCharWidth, _pxCharHeight;
    int _pxPosHexX;
    int _pxPosAdrX;
    int _pxPosAsciiX;
    int _pxGapAdr;
    int _pxGapAdrHex;
    int _pxGapHexAscii;
    int _pxCursorWidth;
    int _pxSelectionSub;
    int _pxCursorX;
    int _pxCursorY;
    
    qint64 _bSelectionBegin;
    qint64 _bSelectionEnd;
    qint64 _bSelectionInit;
    qint64 _bPosFirst;
    qint64 _bPosLast;
    qint64 _bPosCurrent;
    
    bool _addressArea;
    bool _asciiArea;
    QColor _addressAreaColor;
    int _addressWidth;
    qint64 _addressOffset;
    bool _highlighting;
    bool _overwriteMode;
    QBrush _brushSelection;
    QPen _penSelection;
    QBrush _brushHighlighted;
    QPen _penHighlighted;
    bool _readOnly;

    int _addrDigits;
    bool _blink;
    qt_HexChunks *_chunks;
    QTimer _cursorTimer;
    qint64 _cursorPosition;
    QRect _cursorRect;
    QByteArray _data;
    QByteArray _dataShown;
    QByteArray _hexDataShown;
    qint64 _lastEventSize;
    QByteArray _markedShown;
    bool _modified;
    int _rowsShown;
    qt_HexUndoStack * _undoStack;
};
