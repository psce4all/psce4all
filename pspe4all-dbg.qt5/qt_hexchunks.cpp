/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_hexchunks.h"
#include <limits.h>

#define NORMAL 0
#define HIGHLIGHTED 1

#define BUFFER_SIZE 0x10000
#define CHUNK_SIZE 0x1000
#define READ_CHUNK_MASK Q_INT64_C(0xfffffffffffff000)

qt_HexChunks::qt_HexChunks()
{
    _data = QByteArray();
    _size = 0;
    _pos = 0;
}

bool qt_HexChunks::setData(const QByteArray &data)
{
    _data = data;
    _size = data.size();
    _chunks.clear();
    _pos = 0;
    return true;
}

QByteArray qt_HexChunks::data(qint64 pos, qint64 maxSize, QByteArray *highlighted)
{
    QByteArray buffer;

    if (_size)
    {
        qint64 ioDelta = 0;
        int chunkIdx = 0;

        qt_HexChunk chunk;

        if (highlighted)
        {
            highlighted->clear();
        }

        if (pos >= _size)
        {
            return buffer;
        }

        if (maxSize < 0)
        {
            maxSize = _size;
        }
        else
        {
            if ((pos + maxSize) > _size)
            {
                maxSize = _size - pos;
            }
        }

        while (maxSize > 0)
        {
            chunk.absPos = 0x7FFFFFFFFFFFFFFFLL;
            bool chunksLoopOngoing = true;
            while ((chunkIdx < _chunks.count()) && chunksLoopOngoing)
            {
                chunk = _chunks[chunkIdx];
                if (chunk.absPos > pos)
                {
                    chunksLoopOngoing = false;
                }
                else
                {
                    chunkIdx += 1;
                    qint64 count;
                    qint64 chunkOfs = pos - chunk.absPos;
                    if (maxSize > ((qint64)chunk.data.size() - chunkOfs))
                    {
                        count = (qint64)chunk.data.size() - chunkOfs;
                        ioDelta += CHUNK_SIZE - chunk.data.size();
                    }
                    else
                    {
                        count = maxSize;
                    }
                    if (count > 0)
                    {
                        buffer += chunk.data.mid(chunkOfs, (int)count);
                        maxSize -= count;
                        pos += count;
                        if (highlighted)
                        {
                            *highlighted += chunk.dataChanged.mid(chunkOfs, (int)count);
                        }
                    }
                }
            }

            if ((maxSize > 0) && (pos < chunk.absPos))
            {
                qint64 byteCount;
                QByteArray readBuffer;
                if ((chunk.absPos - pos) > maxSize)
                {
                    byteCount = maxSize;
                }
                else
                {
                    byteCount = chunk.absPos - pos;
                }

                maxSize -= byteCount;
                readBuffer = _data.mid(pos + ioDelta, byteCount);
                buffer += readBuffer;
                if (highlighted)
                {
                    *highlighted += QByteArray(readBuffer.size(), NORMAL);
                }
                pos += readBuffer.size();
            }
        }
    }
    return buffer;
}

bool qt_HexChunks::write(QIODevice &iODevice, qint64 pos, qint64 count)
{
    if (count == -1)
    {
        count = _size;
    }
    bool ok = iODevice.open(QIODevice::WriteOnly);
    if (ok)
    {
        for (qint64 idx=pos; idx < count; idx += BUFFER_SIZE)
        {
            QByteArray ba = data(idx, BUFFER_SIZE);
            iODevice.write(ba);
        }
        iODevice.close();
    }
    return ok;
}


void qt_HexChunks::setDataChanged(qint64 pos, bool dataChanged)
{
    if ((pos < 0) || (pos >= _size))
    {
        return;
    }
    int chunkIdx = getChunkIndex(pos);
    qint64 posInBa = pos - _chunks[chunkIdx].absPos;
    _chunks[chunkIdx].dataChanged[(int)posInBa] = char(dataChanged);
}

bool qt_HexChunks::dataChanged(qint64 pos)
{
    QByteArray highlighted;
    data(pos, 1, &highlighted);
    return bool(highlighted.at(0));
}

qint64 qt_HexChunks::indexOf(const QByteArray &ba, qint64 from)
{
    qint64 result = -1;
    QByteArray buffer;

    for (qint64 pos=from; (pos < _size) && (result < 0); pos += BUFFER_SIZE)
    {
        buffer = data(pos, BUFFER_SIZE + ba.size() - 1);
        int findPos = buffer.indexOf(ba);
        if (findPos >= 0)
        {
            result = pos + (qint64)findPos;
        }
    }
    return result;
}

qint64 qt_HexChunks::lastIndexOf(const QByteArray &ba, qint64 from)
{
    qint64 result = -1;
    QByteArray buffer;

    for (qint64 pos=from; (pos > 0) && (result < 0); pos -= BUFFER_SIZE)
    {
        qint64 sPos = pos - BUFFER_SIZE - (qint64)ba.size() + 1;
        if (sPos < 0)
        {
            sPos = 0;
        }
        buffer = data(sPos, pos - sPos);
        int findPos = buffer.lastIndexOf(ba);
        if (findPos >= 0)
        {
            result = sPos + (qint64)findPos;
        }
    }
    return result;
}

bool qt_HexChunks::insert(qint64 pos, char b)
{
    if ((pos < 0) || (pos > _size))
    {
        return false;
    }
    int chunkIdx;
    if (pos == _size)
    {
        chunkIdx = getChunkIndex(pos - 1);
    }
    else
    {
        chunkIdx = getChunkIndex(pos);
    }
    qint64 posInBa = pos - _chunks[chunkIdx].absPos;
    _chunks[chunkIdx].data.insert(posInBa, b);
    _chunks[chunkIdx].dataChanged.insert(posInBa, char(1));
    for (int idx=chunkIdx+1; idx < _chunks.size(); idx++)
    {
        _chunks[idx].absPos += 1;
    }
    _size += 1;
    _pos = pos;
    return true;
}

bool qt_HexChunks::overwrite(qint64 pos, char b)
{
    if ((pos < 0) || (pos >= _size))
    {
        return false;
    }
    int chunkIdx = getChunkIndex(pos);
    qint64 posInBa = pos - _chunks[chunkIdx].absPos;
    _chunks[chunkIdx].data[(int)posInBa] = b;
    _chunks[chunkIdx].dataChanged[(int)posInBa] = char(1);
    _pos = pos;
    return true;
}

bool qt_HexChunks::removeAt(qint64 pos)
{
    if ((pos < 0) || (pos >= _size))
    {
        return false;
    }
    int chunkIdx = getChunkIndex(pos);
    qint64 posInBa = pos - _chunks[chunkIdx].absPos;
    _chunks[chunkIdx].data.remove(posInBa, 1);
    _chunks[chunkIdx].dataChanged.remove(posInBa, 1);
    for (int idx=chunkIdx+1; idx < _chunks.size(); idx++)
    {
        _chunks[idx].absPos -= 1;
    }
    _size -= 1;
    _pos = pos;
    return true;
}

char qt_HexChunks::operator[](qint64 pos)
{
    return data(pos, 1)[0];
}

qint64 qt_HexChunks::pos()
{
    return _pos;
}

qint64 qt_HexChunks::size()
{
    return _size;
}

int qt_HexChunks::getChunkIndex(qint64 absPos)
{
    int foundIdx = -1;
    int insertIdx = 0;
    qint64 ioDelta = 0;

    for (int idx=0; idx < _chunks.size(); idx++)
    {
        qt_HexChunk chunk = _chunks[idx];
        if ((absPos >= chunk.absPos) && (absPos < (chunk.absPos + chunk.data.size())))
        {
            foundIdx = idx;
            break;
        }
        if (absPos < chunk.absPos)
        {
            insertIdx = idx;
            break;
        }
        ioDelta += chunk.data.size() - CHUNK_SIZE;
        insertIdx = idx + 1;
    }

    if (foundIdx == -1)
    {
        qt_HexChunk newChunk;
        qint64 readAbsPos = absPos - ioDelta;
        qint64 readPos = (readAbsPos & READ_CHUNK_MASK);
        newChunk.data = _data.mid(readPos, CHUNK_SIZE);
        newChunk.absPos = absPos - (readAbsPos - readPos);
        newChunk.dataChanged = QByteArray(newChunk.data.size(), char(0));
        _chunks.insert(insertIdx, newChunk);
        foundIdx = insertIdx;
    }
    return foundIdx;
}
