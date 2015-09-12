/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QtCore>

struct qt_HexChunk
{
    QByteArray data;
    QByteArray dataChanged;
    qint64 absPos;
};

class qt_HexChunks
{
public:
    // Constructors and file settings
    qt_HexChunks();
    bool setData(const QByteArray &data);

    // Getting data out of Chunks
    QByteArray data(qint64 pos=0, qint64 count=-1, QByteArray *highlighted=0);
    bool write(QIODevice &iODevice, qint64 pos=0, qint64 count=-1);

    // Set and get highlighting infos
    void setDataChanged(qint64 pos, bool dataChanged);
    bool dataChanged(qint64 pos);

    // Search API
    qint64 indexOf(const QByteArray &ba, qint64 from);
    qint64 lastIndexOf(const QByteArray &ba, qint64 from);

    // Char manipulations
    bool insert(qint64 pos, char b);
    bool overwrite(qint64 pos, char b);
    bool removeAt(qint64 pos);

    // Utility functions
    char operator[](qint64 pos);
    qint64 pos();
    qint64 size();


private:
    int getChunkIndex(qint64 absPos);

    QByteArray _data;
    qint64 _pos;
    qint64 _size;
    QList<qt_HexChunk> _chunks;
};
