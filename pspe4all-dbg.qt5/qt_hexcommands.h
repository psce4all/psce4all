/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QUndoStack>

#include "qt_hexchunks.h"

class qt_HexUndoStack : public QUndoStack
{
    Q_OBJECT

public:
    qt_HexUndoStack(qt_HexChunks *chunks, QObject * parent=0);
    void insert(qint64 pos, char c);
    void insert(qint64 pos, const QByteArray &ba);
    void removeAt(qint64 pos, qint64 len=1);
    void overwrite(qint64 pos, char c);
    void overwrite(qint64 pos, int len, const QByteArray &ba);

private:
    qt_HexChunks * _chunks;
    QObject * _parent;
};
