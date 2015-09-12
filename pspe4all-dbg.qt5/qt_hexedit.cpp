/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include <QApplication>
#include <QClipboard>
#include <QKeyEvent>
#include <QPainter>
#include <QScrollBar>

#include "qt_hexedit.h"

const int HEXCHARS_IN_LINE = 47;
const int BYTES_PER_LINE = 16;

namespace
{
    QAction *addMenuToggleAction(QMenu *menu, const QString &caption, bool checked, QObject *receiver, const char *slot)
    {
        QAction *const action = new QAction(caption, menu);
        action->setCheckable(true);
        action->setChecked(checked);
        menu->addAction(action);
        QObject::connect(action, SIGNAL(toggled(bool)), receiver, slot);
        return action;
    }
}

qt_HexEdit::qt_HexEdit(QWidget *parent) : QAbstractScrollArea(parent)
{
    _chunks = new qt_HexChunks();
    _undoStack = new qt_HexUndoStack(_chunks, this);
#ifdef Q_OS_WIN32
    setFont(QFont("Courier", 10));
#else
    setFont(QFont("Monospace", 10));
#endif
    setAddressAreaColor(this->palette().alternateBase().color());
    setHighlightingColor(QColor(0xff, 0xff, 0x99, 0xff));
    setSelectionColor(this->palette().highlight().color());

    connect(&_cursorTimer, SIGNAL(timeout()), this, SLOT(updateCursor()));
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(adjust()));
    connect(_undoStack, SIGNAL(indexChanged(int)), this, SLOT(dataChangedPrivate(int)));

    _cursorTimer.setInterval(500);
    _cursorTimer.start();

    setAddressWidth(8);
    setAddressArea(true);
    setAsciiArea(true);
    setOverwriteMode(true);
    setHighlighting(true);
    setReadOnly(false);

    init();
}

qt_HexEdit::~qt_HexEdit()
{
}

void qt_HexEdit::setAddressArea(bool addressArea)
{
    _addressArea = addressArea;
    adjust();
    setCursorPosition(_cursorPosition);
    viewport()->update();
}

bool qt_HexEdit::addressArea()
{
    return _addressArea;
}

void qt_HexEdit::setAddressAreaColor(const QColor &color)
{
    _addressAreaColor = color;
    viewport()->update();
}

QColor qt_HexEdit::addressAreaColor()
{
    return _addressAreaColor;
}

void qt_HexEdit::setAddressOffset(qint64 addressOffset)
{
    _addressOffset = addressOffset;
    adjust();
    setCursorPosition(_cursorPosition);
    viewport()->update();
}

qint64 qt_HexEdit::addressOffset()
{
    return _addressOffset;
}

void qt_HexEdit::setAddressWidth(int addressWidth)
{
    _addressWidth = addressWidth;
    adjust();
    setCursorPosition(_cursorPosition);
    viewport()->update();
}

int qt_HexEdit::addressWidth()
{
    qint64 size = _chunks->size();
    int n = 1;
    if (size > Q_INT64_C(0x100000000)){ n += 8; size /= Q_INT64_C(0x100000000);}
    if (size > 0x10000){ n += 4; size /= 0x10000;}
    if (size > 0x100){ n += 2; size /= 0x100;}
    if (size > 0x10){ n += 1; size /= 0x10;}

    if (n > _addressWidth)
        return n;
    else
        return _addressWidth;
}

void qt_HexEdit::setAsciiArea(bool asciiArea)
{
    _asciiArea = asciiArea;
    viewport()->update();
}

bool qt_HexEdit::asciiArea()
{
    return _asciiArea;
}

void qt_HexEdit::setCursorPosition(qint64 position)
{
    _blink = false;
    viewport()->update(_cursorRect);

    if (_overwriteMode && (position > (_chunks->size() * 2 - 1)))
        position = _chunks->size() * 2 - 1;
    if (!_overwriteMode && (position > (_chunks->size() * 2)))
        position = _chunks->size() * 2;
    if (position < 0)
        position = 0;

    _cursorPosition = position;
    _bPosCurrent = position / 2;
    _pxCursorY = ((position/2 - _bPosFirst) / BYTES_PER_LINE + 1) * _pxCharHeight;
    int x = (position % (2 * BYTES_PER_LINE));
    _pxCursorX = (((x / 2) * 3) + (x % 2)) * _pxCharWidth + _pxPosHexX;

    if (_overwriteMode)
        _cursorRect = QRect(_pxCursorX, _pxCursorY + _pxCursorWidth, _pxCharWidth, _pxCursorWidth);
    else
        _cursorRect = QRect(_pxCursorX, _pxCursorY - _pxCharHeight + 4, _pxCursorWidth, _pxCharHeight);

    _blink = true;
    viewport()->update(_cursorRect);
    emit currentAddressChanged(_bPosCurrent);
}

qint64 qt_HexEdit::cursorPosition(QPoint pos)
{
    qint64 result = -1;
    if ((pos.x() >= _pxPosHexX) && (pos.x() < (_pxPosHexX + (1 + HEXCHARS_IN_LINE) * _pxCharWidth)))
    {
        int x = (pos.x() - _pxPosHexX - _pxCharWidth / 2) / _pxCharWidth;
        x = (x / 3) * 2 + x % 3;
        int y = ((pos.y() - 3) / _pxCharHeight) * 2 * BYTES_PER_LINE;
        result = _bPosFirst * 2 + x + y;
    }
    return result;
}

qint64 qt_HexEdit::cursorPosition()
{
    return _cursorPosition;
}

void qt_HexEdit::setData(const QByteArray &data)
{
    _chunks->setData(data);
    init();
    dataChangedPrivate();
}

QByteArray qt_HexEdit::data()
{
    return _chunks->data(0, -1);
}

void qt_HexEdit::setHighlighting(bool highlighting)
{
    _highlighting = highlighting;
    viewport()->update();
}

bool qt_HexEdit::highlighting()
{
    return _highlighting;
}

void qt_HexEdit::setHighlightingColor(const QColor &color)
{
    _brushHighlighted = QBrush(color);
    _penHighlighted = QPen(viewport()->palette().color(QPalette::WindowText));
    viewport()->update();
}

QColor qt_HexEdit::highlightingColor()
{
    return _brushHighlighted.color();
}

void qt_HexEdit::setOverwriteMode(bool overwriteMode)
{
    _overwriteMode = overwriteMode;
    emit overwriteModeChanged(overwriteMode);
}

bool qt_HexEdit::overwriteMode()
{
    return _overwriteMode;
}

void qt_HexEdit::setSelectionColor(const QColor &color)
{
    _brushSelection = QBrush(color);
    _penSelection = QPen(Qt::white);
    viewport()->update();
}

QColor qt_HexEdit::selectionColor()
{
    return _brushSelection.color();
}

bool qt_HexEdit::isReadOnly()
{
    return _readOnly;
}

void qt_HexEdit::setReadOnly(bool readOnly)
{
    _readOnly = readOnly;
}

QByteArray qt_HexEdit::dataAt(qint64 pos, qint64 count)
{
    return _chunks->data(pos, count);
}

bool qt_HexEdit::write(QIODevice &iODevice, qint64 pos, qint64 count)
{
    return _chunks->write(iODevice, pos, count);
}

void qt_HexEdit::insert(qint64 index, char ch)
{
    _undoStack->insert(index, ch);
    refresh();
}

void qt_HexEdit::remove(qint64 index, qint64 len)
{
    _undoStack->removeAt(index, len);
    refresh();
}

void qt_HexEdit::replace(qint64 index, char ch)
{
    _undoStack->overwrite(index, ch);
    refresh();
}

void qt_HexEdit::insert(qint64 pos, const QByteArray &ba)
{
    _undoStack->insert(pos, ba);
    refresh();
}

void qt_HexEdit::replace(qint64 pos, qint64 len, const QByteArray &ba)
{
    _undoStack->overwrite(pos, len, ba);
    refresh();
}

void qt_HexEdit::ensureVisible()
{
    if (_cursorPosition < (_bPosFirst * 2))
    {
        verticalScrollBar()->setValue((int)(_cursorPosition / 2 / BYTES_PER_LINE));
    }
    if (_cursorPosition > ((_bPosFirst + (_rowsShown - 1)*BYTES_PER_LINE) * 2))
    {
        verticalScrollBar()->setValue((int)(_cursorPosition / 2 / BYTES_PER_LINE) - _rowsShown + 1);
    }
    viewport()->update();
}

qint64 qt_HexEdit::indexOf(const QByteArray &ba, qint64 from)
{
    qint64 pos = _chunks->indexOf(ba, from);
    if (pos > -1)
    {
        qint64 curPos = pos*2;
        setCursorPosition(curPos + ba.length()*2);
        resetSelection(curPos);
        setSelection(curPos + ba.length()*2);
        ensureVisible();
    }
    return pos;
}

bool qt_HexEdit::isModified()
{
    return _modified;
}

qint64 qt_HexEdit::lastIndexOf(const QByteArray &ba, qint64 from)
{
    qint64 pos = _chunks->lastIndexOf(ba, from);
    if (pos > -1)
    {
        qint64 curPos = pos*2;
        setCursorPosition(curPos - 1);
        resetSelection(curPos);
        setSelection(curPos + ba.length()*2);
        ensureVisible();
    }
    return pos;
}

void qt_HexEdit::redo()
{
    _undoStack->redo();
    setCursorPosition(_chunks->pos()*2);
    refresh();
}

QString qt_HexEdit::selectionToReadableString()
{
    QByteArray ba = _chunks->data(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
    return toReadable(ba);
}

void qt_HexEdit::setFont(const QFont &font)
{
    QWidget::setFont(font);
    _pxCharWidth = fontMetrics().width(QLatin1Char('2'));
    _pxCharHeight = fontMetrics().height();
    _pxGapAdr = _pxCharWidth / 2;
    _pxGapAdrHex = _pxCharWidth;
    _pxGapHexAscii = 2 * _pxCharWidth;
    _pxCursorWidth = _pxCharHeight / 7;
    _pxSelectionSub = _pxCharHeight / 5;
    viewport()->update();
}

QString qt_HexEdit::toReadableString()
{
    QByteArray ba = _chunks->data();
    return toReadable(ba);
}

void qt_HexEdit::undo()
{
    _undoStack->undo();
    setCursorPosition(_chunks->pos()*2);
    refresh();
}

void qt_HexEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::MoveToNextChar))
    {
        setCursorPosition(_cursorPosition + 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousChar))
    {
        setCursorPosition(_cursorPosition - 1);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfLine))
    {
        setCursorPosition(_cursorPosition | (2 * BYTES_PER_LINE -1));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfLine))
    {
        setCursorPosition(_cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousLine))
    {
        setCursorPosition(_cursorPosition - (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToNextLine))
    {
        setCursorPosition(_cursorPosition + (2 * BYTES_PER_LINE));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToNextPage))
    {
        setCursorPosition(_cursorPosition + (((_rowsShown - 1) * 2 * BYTES_PER_LINE)));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToPreviousPage))
    {
        setCursorPosition(_cursorPosition - (((_rowsShown - 1) * 2 * BYTES_PER_LINE)));
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToEndOfDocument))
    {
        setCursorPosition(_chunks->size() * 2);
        resetSelection(_cursorPosition);
    }
    if (event->matches(QKeySequence::MoveToStartOfDocument))
    {
        setCursorPosition(0);
        resetSelection(_cursorPosition);
    }

    if (event->matches(QKeySequence::SelectAll))
    {
        resetSelection(0);
        setSelection(2*_chunks->size() + 1);
    }
    if (event->matches(QKeySequence::SelectNextChar))
    {
        qint64 pos = _cursorPosition + 1;
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousChar))
    {
        qint64 pos = _cursorPosition - 1;
        setSelection(pos);
        setCursorPosition(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfLine))
    {
        qint64 pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE)) + (2 * BYTES_PER_LINE);
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfLine))
    {
        qint64 pos = _cursorPosition - (_cursorPosition % (2 * BYTES_PER_LINE));
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousLine))
    {
        qint64 pos = _cursorPosition - (2 * BYTES_PER_LINE);
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectNextLine))
    {
        qint64 pos = _cursorPosition + (2 * BYTES_PER_LINE);
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectNextPage))
    {
        qint64 pos = _cursorPosition + (((viewport()->height() / _pxCharHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectPreviousPage))
    {
        qint64 pos = _cursorPosition - (((viewport()->height() / _pxCharHeight) - 1) * 2 * BYTES_PER_LINE);
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectEndOfDocument))
    {
        qint64 pos = _chunks->size() * 2;
        setCursorPosition(pos);
        setSelection(pos);
    }
    if (event->matches(QKeySequence::SelectStartOfDocument))
    {
        qint64 pos = 0;
        setCursorPosition(pos);
        setSelection(pos);
    }

    if (!_readOnly)
    {
        if ((QApplication::keyboardModifiers() == Qt::NoModifier) || (QApplication::keyboardModifiers() == Qt::KeypadModifier))
        {
            int key = int(event->text()[0].toLatin1());
            if ((key >= '0' && key <= '9') || (key >= 'a' && key <= 'f') || (key >= 'A' && key <= 'F'))
            {
                if (getSelectionBegin() != getSelectionEnd())
                {
                    if (_overwriteMode)
                    {
                        qint64 len = getSelectionEnd() - getSelectionBegin();
                        replace(getSelectionBegin(), (int)len, QByteArray((int)len, char(0)));
                    }
                    else
                    {
                        remove(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
                        _bPosCurrent = getSelectionBegin();
                    }
                    setCursorPosition(2*_bPosCurrent);
                    resetSelection(2*_bPosCurrent);
                }

                if (_overwriteMode == false)
                {
                    if ((_cursorPosition % 2) == 0)
                    {
                        insert(_bPosCurrent, char(0));
                    }
                }

                if (_chunks->size() > 0)
                {
                    QByteArray hexValue = _chunks->data(_bPosCurrent, 1).toHex();
                    hexValue[int(_cursorPosition & 1)] = key;

                    replace(_bPosCurrent, QByteArray().fromHex(hexValue)[0]);

                    setCursorPosition(_cursorPosition + 1);
                    resetSelection(_cursorPosition);
                }
            }
        }

        if (event->matches(QKeySequence::Cut))
        {
            QByteArray ba = _chunks->data(getSelectionBegin(), getSelectionEnd() - getSelectionBegin()).toHex();
            for (qint64 idx = 32; idx < ba.size(); idx +=33)
            {
                ba.insert(idx, "\n");
            }
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->setText(ba);
            if (_overwriteMode)
            {
                qint64 len = getSelectionEnd() - getSelectionBegin();
                replace(getSelectionBegin(), (int)len, QByteArray((int)len, char(0)));
            }
            else
            {
                remove(getSelectionBegin(), getSelectionEnd() - getSelectionBegin());
            }
            setCursorPosition(2*getSelectionBegin());
            resetSelection(2*getSelectionBegin());
        }

        if (event->matches(QKeySequence::Paste))
        {
            QClipboard *clipboard = QApplication::clipboard();
            QByteArray ba = QByteArray().fromHex(clipboard->text().toLatin1());
            if (_overwriteMode)
            {
                replace(_bPosCurrent, ba.size(), ba);
            }
            else
            {
                insert(_bPosCurrent, ba);
            }
            setCursorPosition(_cursorPosition + 2 * ba.size());
            resetSelection(getSelectionBegin());
        }

        if (event->matches(QKeySequence::Delete))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                _bPosCurrent = getSelectionBegin();
                if (_overwriteMode)
                {
                    QByteArray ba = QByteArray(getSelectionEnd() - getSelectionBegin(), char(0));
                    replace(_bPosCurrent, ba.size(), ba);
                }
                else
                {
                    remove(_bPosCurrent, getSelectionEnd() - getSelectionBegin());
                }
            }
            else
            {
                if (_overwriteMode)
                {
                    replace(_bPosCurrent, char(0));
                }
                else
                {
                    remove(_bPosCurrent, 1);
                }
            }
            setCursorPosition(2 * _bPosCurrent);
            resetSelection(2 * _bPosCurrent);
        }

        if ((event->key() == Qt::Key_Backspace) && (event->modifiers() == Qt::NoModifier))
        {
            if (getSelectionBegin() != getSelectionEnd())
            {
                _bPosCurrent = getSelectionBegin();
                setCursorPosition(2 * _bPosCurrent);
                if (_overwriteMode)
                {
                    QByteArray ba = QByteArray(getSelectionEnd() - getSelectionBegin(), char(0));
                    replace(_bPosCurrent, ba.size(), ba);
                }
                else
                {
                    remove(_bPosCurrent, getSelectionEnd() - getSelectionBegin());
                }
                resetSelection(2 * _bPosCurrent);
            }
            else
            {
                _bPosCurrent -= 1;
                if (_overwriteMode)
                {
                    replace(_bPosCurrent, char(0));
                }
                else
                {
                    remove(_bPosCurrent, 1);
                }
                _bPosCurrent -= 1;
                setCursorPosition(2 * _bPosCurrent);
                resetSelection(2 * _bPosCurrent);
            }
        }

        if (event->matches(QKeySequence::Undo))
        {
            undo();
        }

        if (event->matches(QKeySequence::Redo))
        {
            redo();
        }

    }

    if (event->matches(QKeySequence::Copy))
    {
        QByteArray ba = _chunks->data(getSelectionBegin(), getSelectionEnd() - getSelectionBegin()).toHex();
        for (qint64 idx = 32; idx < ba.size(); idx +=33)
        {
            ba.insert(idx, "\n");
        }
        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(ba);
    }

    if ((event->key() == Qt::Key_Insert) && (event->modifiers() == Qt::NoModifier))
    {
        setOverwriteMode(!overwriteMode());
        setCursorPosition(_cursorPosition);
    }

    refresh();
}

void qt_HexEdit::mouseMoveEvent(QMouseEvent * event)
{
    _blink = false;
    viewport()->update();
    qint64 actPos = cursorPosition(event->pos());
    if (actPos >= 0)
    {
        setCursorPosition(actPos);
        setSelection(actPos);
    }
}

void qt_HexEdit::mousePressEvent(QMouseEvent * event)
{
    _blink = false;
    viewport()->update();
    qint64 cPos = cursorPosition(event->pos());
    if (cPos >= 0)
    {
        resetSelection(cPos);
        setCursorPosition(cPos);
    }
}

void qt_HexEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(viewport());

    if (event->rect() != _cursorRect)
    {
        int pxOfsX = horizontalScrollBar()->value();
        int pxPosStartY = _pxCharHeight;

        painter.fillRect(event->rect(), viewport()->palette().color(QPalette::Base));
        if (_addressArea)
        {
            painter.fillRect(QRect(-pxOfsX, event->rect().top(), _pxPosHexX - _pxGapAdrHex / 2 - pxOfsX, height()), _addressAreaColor);
        }
        if (_asciiArea)
        {
            int linePos = _pxPosAsciiX - (_pxGapHexAscii / 2);
            painter.setPen(Qt::gray);
            painter.drawLine(linePos - pxOfsX, event->rect().top(), linePos - pxOfsX, height());
        }

        painter.setPen(viewport()->palette().color(QPalette::WindowText));

        if (_addressArea)
        {
            QString address;
            for (int row=0, pxPosY = _pxCharHeight; row <= (_dataShown.size()/BYTES_PER_LINE); row++, pxPosY +=_pxCharHeight)
            {
                address = QString("%1").arg(_bPosFirst + row*BYTES_PER_LINE + _addressOffset, _addrDigits, 16, QChar('0')).toUpper();
                painter.drawText(_pxPosAdrX - pxOfsX, pxPosY, address);
            }
        }

        QPen colStandard = QPen(viewport()->palette().color(QPalette::WindowText));

        painter.setBackgroundMode(Qt::TransparentMode);

        for (int row = 0, pxPosY = pxPosStartY; row <= _rowsShown; row++, pxPosY +=_pxCharHeight)
        {
            QByteArray hex;
            int pxPosX = _pxPosHexX  - pxOfsX;
            int pxPosAsciiX2 = _pxPosAsciiX  - pxOfsX;
            qint64 bPosLine = row * BYTES_PER_LINE;
            for (int colIdx = 0; ((bPosLine + colIdx) < _dataShown.size() && (colIdx < BYTES_PER_LINE)); colIdx++)
            {
                QColor c = viewport()->palette().color(QPalette::Base);
                painter.setPen(colStandard);

                qint64 posBa = _bPosFirst + bPosLine + colIdx;
                if ((getSelectionBegin() <= posBa) && (getSelectionEnd() > posBa))
                {
                    c = _brushSelection.color();
                    painter.setPen(_penSelection);
                }
                else
                {
                    if (_highlighting)
                    {
                        if (_markedShown.at((int)(posBa - _bPosFirst)))
                        {
                            c = _brushHighlighted.color();
                            painter.setPen(_penHighlighted);
                        }
                    }
                }

                QRect r;
                if (colIdx == 0)
                {
                    r.setRect(pxPosX, pxPosY - _pxCharHeight + _pxSelectionSub, 2 * _pxCharWidth, _pxCharHeight);
                }
                else
                {
                    r.setRect(pxPosX - _pxCharWidth, pxPosY - _pxCharHeight + _pxSelectionSub, 3 * _pxCharWidth, _pxCharHeight);
                }
                painter.fillRect(r, c);
                hex = _hexDataShown.mid((bPosLine + colIdx) * 2, 2);
                painter.drawText(pxPosX, pxPosY, hex);
                pxPosX += 3*_pxCharWidth;

                if (_asciiArea)
                {
                    char ch = _dataShown.at(bPosLine + colIdx);
                    if ((ch < 0x20) || (ch > 0x7e))
                    {
                        ch = '.';
                    }
                    r.setRect(pxPosAsciiX2, pxPosY - _pxCharHeight + _pxSelectionSub, _pxCharWidth, _pxCharHeight);
                    painter.fillRect(r, c);
                    painter.drawText(pxPosAsciiX2, pxPosY, QChar(ch));
                    pxPosAsciiX2 += _pxCharWidth;
                }
            }
        }
        painter.setBackgroundMode(Qt::TransparentMode);
        painter.setPen(viewport()->palette().color(QPalette::WindowText));
    }

    if (_blink && !_readOnly && hasFocus())
    {
        painter.fillRect(_cursorRect, this->palette().color(QPalette::WindowText));
    }
    else
    {
        painter.drawText(_pxCursorX, _pxCursorY, _hexDataShown.mid(_cursorPosition - _bPosFirst * 2, 1));
    }

    if (_lastEventSize != _chunks->size())
    {
        _lastEventSize = _chunks->size();
        emit currentSizeChanged(_lastEventSize);
    }
}

void qt_HexEdit::resizeEvent(QResizeEvent *)
{
    adjust();
}

void qt_HexEdit::resetSelection()
{
    _bSelectionBegin = _bSelectionInit;
    _bSelectionEnd = _bSelectionInit;
}

void qt_HexEdit::resetSelection(qint64 pos)
{
    if (pos < 0)
    {
        pos = 0;
    }
    pos = pos / 2;
    _bSelectionInit = pos;
    _bSelectionBegin = pos;
    _bSelectionEnd = pos;
}

void qt_HexEdit::setSelection(qint64 pos)
{
    if (pos < 0)
    {
        pos = 0;
    }
    pos = pos / 2;
    if (pos >= _bSelectionInit)
    {
        _bSelectionEnd = pos;
        _bSelectionBegin = _bSelectionInit;
    }
    else
    {
        _bSelectionBegin = pos;
        _bSelectionEnd = _bSelectionInit;
    }
}

int qt_HexEdit::getSelectionBegin()
{
    return _bSelectionBegin;
}

int qt_HexEdit::getSelectionEnd()
{
    return _bSelectionEnd;
}

void qt_HexEdit::init()
{
    _undoStack->clear();
    setAddressOffset(0);
    resetSelection(0);
    setCursorPosition(0);
    verticalScrollBar()->setValue(0);
    _modified = false;
}

void qt_HexEdit::adjust()
{
    if (_addressArea)
    {
        _addrDigits = addressWidth();
        _pxPosHexX = _pxGapAdr + _addrDigits*_pxCharWidth + _pxGapAdrHex;
    }
    else
    {
        _pxPosHexX = _pxGapAdrHex;
    }
    _pxPosAdrX = _pxGapAdr;
    _pxPosAsciiX = _pxPosHexX + HEXCHARS_IN_LINE * _pxCharWidth + _pxGapHexAscii;

    int pxWidth = _pxPosAsciiX;
    if (_asciiArea)
    {
        pxWidth += BYTES_PER_LINE*_pxCharWidth;
    }
    horizontalScrollBar()->setRange(0, pxWidth - viewport()->width());
    horizontalScrollBar()->setPageStep(viewport()->width());

    _rowsShown = ((viewport()->height()-4)/_pxCharHeight);
    int lineCount = (int)(_chunks->size() / (qint64)BYTES_PER_LINE) + 1;
    verticalScrollBar()->setRange(0, lineCount - _rowsShown);
    verticalScrollBar()->setPageStep(_rowsShown);

    int value = verticalScrollBar()->value();
    _bPosFirst = (qint64)value * BYTES_PER_LINE;
    _bPosLast = _bPosFirst + (qint64)(_rowsShown * BYTES_PER_LINE) - 1;
    if (_bPosLast >= _chunks->size())
    {
        _bPosLast = _chunks->size() - 1;
    }
    readBuffers();
    setCursorPosition(_cursorPosition);
}

void qt_HexEdit::dataChangedPrivate(int)
{
    _modified = _undoStack->index() != 0;
    adjust();
    emit dataChanged();
}

void qt_HexEdit::refresh()
{
    ensureVisible();
    readBuffers();
}

void qt_HexEdit::readBuffers()
{
    _dataShown = _chunks->data(_bPosFirst, _bPosLast - _bPosFirst + BYTES_PER_LINE + 1, &_markedShown);
    _hexDataShown = _dataShown.toHex().toUpper();
}

QString qt_HexEdit::toReadable(const QByteArray &ba)
{
    QString result;

    for (int i=0; i < ba.size(); i += 16)
    {
        QString addrStr = QString("%1").arg(_addressOffset + i, addressWidth(), 16, QChar('0')).toUpper();
        QString hexStr;
        QString ascStr;
        for (int j=0; j<16; j++)
        {
            if ((i + j) < ba.size())
            {
                hexStr.append(" ").append(ba.mid(i+j, 1).toHex());
                char ch = ba[i + j];
                if ((ch < 0x20) || (ch > 0x7e))
                {
                    ch = '.';
                }
                ascStr.append(QChar(ch));
            }
        }
        result += addrStr + " " + QString("%1").arg(hexStr, -48) + "  " + QString("%1").arg(ascStr, -17) + "\n";
    }
    return result;
}

void qt_HexEdit::updateCursor()
{
    _blink = !_blink;
    viewport()->update(_cursorRect);
}

QMenu *qt_HexEdit::createStandardContextMenu()
{
    QMenu *const menu = new QMenu(this);

    menu->addAction(tr("Set &Font"), this, SLOT(onMenuSetFont()));
    menu->addSeparator();
    addMenuToggleAction(menu, tr("Show A&ddress"), _addressArea, this, SLOT(setAddressArea(bool)));
    //addMenuToggleAction(menu, tr("Show &Hex"), show_hex_, this, SLOT(setShowHexDump(bool)));
    addMenuToggleAction(menu, tr("Show &Ascii"), _asciiArea, this, SLOT(setAsciiArea(bool)));
    //addMenuToggleAction(menu, tr("Show &Comments"), show_comments_, this, SLOT(setShowComments(bool)));

    QSignalMapper *wordWidthMapper = new QSignalMapper(menu);

    //QMenu *const wordMenu = new QMenu(tr("Set Word Width"), menu);
    //QAction *const a1 = addMenuToggleAction(wordMenu, tr("1 Byte"), word_width_ == 1, wordWidthMapper, SLOT(map()));
    //QAction *const a2 = addMenuToggleAction(wordMenu, tr("2 Bytes"), word_width_ == 2, wordWidthMapper, SLOT(map()));
    //QAction *const a3 = addMenuToggleAction(wordMenu, tr("4 Bytes"), word_width_ == 4, wordWidthMapper, SLOT(map()));
    //QAction *const a4 = addMenuToggleAction(wordMenu, tr("8 Bytes"), word_width_ == 8, wordWidthMapper, SLOT(map()));

    //wordWidthMapper->setMapping(a1, 1);
    //wordWidthMapper->setMapping(a2, 2);
    //wordWidthMapper->setMapping(a3, 4);
    //wordWidthMapper->setMapping(a4, 8);

    //connect(wordWidthMapper, SIGNAL(mapped(int)), SLOT(setWordWidth(int)));

    //QSignalMapper *rowWidthMapper = new QSignalMapper(menu);

    //QMenu *const rowMenu = new QMenu(tr("Set Row Width"), menu);
    //QAction *const a5 = addMenuToggleAction(rowMenu, tr("1 Word"), row_width_ == 1, rowWidthMapper, SLOT(map()));
    //QAction *const a6 = addMenuToggleAction(rowMenu, tr("2 Words"), row_width_ == 2, rowWidthMapper, SLOT(map()));
    //QAction *const a7 = addMenuToggleAction(rowMenu, tr("4 Words"), row_width_ == 4, rowWidthMapper, SLOT(map()));
    //QAction *const a8 = addMenuToggleAction(rowMenu, tr("8 Words"), row_width_ == 8, rowWidthMapper, SLOT(map()));
    //QAction *const a9 = addMenuToggleAction(rowMenu, tr("16 Words"), row_width_ == 16, rowWidthMapper, SLOT(map()));

    //rowWidthMapper->setMapping(a5, 1);
    //rowWidthMapper->setMapping(a6, 2);
    //rowWidthMapper->setMapping(a7, 4);
    //rowWidthMapper->setMapping(a8, 8);
    //rowWidthMapper->setMapping(a9, 16);

    //connect(rowWidthMapper, SIGNAL(mapped(int)), SLOT(setRowWidth(int)));

    //menu->addSeparator();
    //menu->addMenu(wordMenu);
    //menu->addMenu(rowMenu);

    //menu->addSeparator();
    //menu->addAction(tr("&Copy Selection To Clipboard"), this, SLOT(onMenuCopy()));

    return menu;
}

void qt_HexEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *const menu = createStandardContextMenu();
    menu->exec(event->globalPos());
    delete menu;
}
