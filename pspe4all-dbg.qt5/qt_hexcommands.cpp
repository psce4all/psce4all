/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_hexcommands.h"
#include <QUndoCommand>

class qt_HexCharCommand : public QUndoCommand
{
public:
    enum CCmd {insert, removeAt, overwrite};

    qt_HexCharCommand(qt_HexChunks * chunks, CCmd cmd, qint64 charPos, char newChar, QUndoCommand *parent=0);

    void undo();
    void redo();
    bool mergeWith(const QUndoCommand *command);
    int id() const { return 1234; }

private:
    qt_HexChunks * _chunks;
    qint64 _charPos;
    bool _wasChanged;
    char _newChar;
    char _oldChar;
    CCmd _cmd;
};

qt_HexCharCommand::qt_HexCharCommand(qt_HexChunks * chunks, CCmd cmd, qint64 charPos, char newChar, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    _chunks = chunks;
    _charPos = charPos;
    _newChar = newChar;
    _cmd = cmd;
}

bool qt_HexCharCommand::mergeWith(const QUndoCommand *command)
{
    const qt_HexCharCommand *nextCommand = static_cast<const qt_HexCharCommand *>(command);
    bool result = false;

    if (_cmd != qt_HexCharCommand::removeAt)
    {
        if (nextCommand->_cmd == overwrite)
            if (nextCommand->_charPos == _charPos)
            {
                _newChar = nextCommand->_newChar;
                result = true;
            }
    }
    return result;
}

void qt_HexCharCommand::undo()
{
    switch (_cmd)
    {
        case insert:
            _chunks->removeAt(_charPos);
            break;
        case overwrite:
            _chunks->overwrite(_charPos, _oldChar);
            _chunks->setDataChanged(_charPos, _wasChanged);
            break;
        case removeAt:
            _chunks->insert(_charPos, _oldChar);
            _chunks->setDataChanged(_charPos, _wasChanged);
            break;
    }
}

void qt_HexCharCommand::redo()
{
    switch (_cmd)
    {
        case insert:
            _chunks->insert(_charPos, _newChar);
            break;
        case overwrite:
            _oldChar = (*_chunks)[_charPos];
            _wasChanged = _chunks->dataChanged(_charPos);
            _chunks->overwrite(_charPos, _newChar);
            break;
        case removeAt:
            _oldChar = (*_chunks)[_charPos];
            _wasChanged = _chunks->dataChanged(_charPos);
            _chunks->removeAt(_charPos);
            break;
    }
}

qt_HexUndoStack::qt_HexUndoStack(qt_HexChunks * chunks, QObject * parent)
    : QUndoStack(parent)
{
    _chunks = chunks;
    _parent = parent;
}

void qt_HexUndoStack::insert(qint64 pos, char c)
{
    if ((pos >= 0) && (pos <= _chunks->size()))
    {
        QUndoCommand *cc = new qt_HexCharCommand(_chunks, qt_HexCharCommand::insert, pos, c);
        this->push(cc);
    }
}

void qt_HexUndoStack::insert(qint64 pos, const QByteArray &ba)
{
    if ((pos >= 0) && (pos <= _chunks->size()))
    {
        QString txt = QString(tr("Inserting %1 bytes")).arg(ba.size());
        beginMacro(txt);
        for (int idx=0; idx < ba.size(); idx++)
        {
            QUndoCommand *cc = new qt_HexCharCommand(_chunks, qt_HexCharCommand::insert, pos + idx, ba.at(idx));
            this->push(cc);
        }
        endMacro();
    }
}

void qt_HexUndoStack::removeAt(qint64 pos, qint64 len)
{
    if ((pos >= 0) && (pos < _chunks->size()))
    {
        if (len==1)
        {
            QUndoCommand *cc = new qt_HexCharCommand(_chunks, qt_HexCharCommand::removeAt, pos, char(0));
            this->push(cc);
        }
        else
        {
            QString txt = QString(tr("Delete %1 chars")).arg(len);
            beginMacro(txt);
            for (qint64 cnt=0; cnt<len; cnt++)
            {
                QUndoCommand *cc = new qt_HexCharCommand(_chunks, qt_HexCharCommand::removeAt, pos, char(0));
                push(cc);
            }
            endMacro();
        }
    }
}

void qt_HexUndoStack::overwrite(qint64 pos, char c)
{
    if ((pos >= 0) && (pos < _chunks->size()))
    {
        QUndoCommand *cc = new qt_HexCharCommand(_chunks, qt_HexCharCommand::overwrite, pos, c);
        this->push(cc);
    }
}

void qt_HexUndoStack::overwrite(qint64 pos, int len, const QByteArray &ba)
{
    if ((pos >= 0) && (pos < _chunks->size()))
    {
        QString txt = QString(tr("Overwrite %1 chars")).arg(len);
        beginMacro(txt);
        removeAt(pos, len);
        insert(pos, ba);
        endMacro();
    }
}
