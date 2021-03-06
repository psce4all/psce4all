/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <vector>

namespace qt_translate
{
    const char *ByteToHex(u8 b);
    void ByteToHex(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
    void ByteToChar(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
    void ByteToOctal(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
    void ByteToBinary(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);


    void ByteToHex(QString &dst, const u8 *src, int len, int mask = 0);
    void ByteToChar(QString &dst, const u8 *src, int len, int mask = 0);
    void ByteToOctal(QString &dst, const u8 *src, int len, int mask = 0);
    void ByteToBinary(QString &dst, const u8 *src, int len, int mask = 0);

    void BinaryToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);

    void OctalToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);

    void CharToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
    void CharToByte(std::vector< u8 > &dst, const QString &src, int mask = 0);

    void HexToByte(std::vector< u8 > &dst, const std::vector< u8 > &src, int mask = 0);
    void HexToByte(std::vector< u8 > &dst, const QString &src, int mask = 0);
};
