#ifndef QT_MEMORYCURSOR_H
#define QT_MEMORYCURSOR_H

class Qt_MemoryCursor
{
  public:
    Qt_MemoryCursor(
        int byteOffset = 0,
        int charOffset = 0,
        int low        = 0,
        int high       = 1,
        int charsPerByte = 2);
    Qt_MemoryCursor(const Qt_MemoryCursor &c);

    int incrByChar(int n);
    int incrByByte(int n);
    int decrByChar(int n);
    int decrByByte(int n);

    int byteOffset() const;
    int charOffset() const;
    int charOffsetAbsolute() const;

    bool setRange(int low, int high);
    int setCharsPerByte(int charsPerByte);
    void setOffset(int byteOffset, int charOffset);

  protected:
    void assignClamped(int &dst, int src, int low, int high);

    enum
    {
      OutOfRange = -1,
    };

  protected:
    int m_byteOffset;
    int m_charOffset;
    int m_low;
    int m_high;
    int m_charsPerByte;
};

#endif // QMEMORYCURSOR_H
