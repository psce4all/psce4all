/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QAbstractScrollArea>
#include <QSharedPointer>

class QBuffer;
class QByteArray;
class QIODevice;
class QMenu;
class QString;
class QTextStream;

class qt_HexWidget : public QAbstractScrollArea
{
    Q_OBJECT

public:
    qt_HexWidget(QWidget *parent = 0);
    virtual ~qt_HexWidget();

    enum AddressSize
    {
        Address32 = 4,
        Address64 = 8
    };

    typedef quint64 address_t;

    class CommentProvider
    {
    public:
        typedef QSharedPointer< CommentProvider > Ptr;
        virtual ~CommentProvider() {}
        virtual void setComment(address_t address, const QString &comment) = 0;
        virtual QString comment(address_t address, int size) const = 0;
        virtual void clear() = 0;
    };

    typedef QSharedPointer< CommentProvider > CommentProviderPointer;

    CommentProviderPointer  commentServer() const;
    void                    setCommentServer(const CommentProviderPointer &p);

    address_t               firstVisibleAddress() const;
    address_t               addressOffset() const;
    bool                    showHexDump() const;
    bool                    showAddress() const;
    bool                    showAsciiDump() const;
    bool                    showComments() const;
    QColor                  lineColor() const;
    QColor                  addressColor() const;
    int                     wordWidth() const;
    int                     rowWidth() const;
    AddressSize             addressSize() const;

    QByteArray              data() const { return data_; }

    void                    setData(const QByteArray &d);
    void                    setAddressOffset(address_t offset);
    void                    scrollTo(address_t offset);
    void                    setAddressSize(AddressSize address_size);
    void                    setColdZoneEnd(address_t offset);

    address_t               selectedBytesAddress() const;
    quint64                 selectedBytesSize() const;
    QByteArray              selectedBytes() const;
    QByteArray              allBytes() const;
    QMenu                  *createStandardContextMenu();

protected:
    void                    paintEvent(QPaintEvent *event) override;
    void                    resizeEvent(QResizeEvent *event) override;
    void                    mousePressEvent(QMouseEvent *event) override;
    void                    mouseMoveEvent(QMouseEvent *event) override;
    void                    mouseReleaseEvent(QMouseEvent *event) override;
    void                    keyPressEvent(QKeyEvent *event) override;
    void                    mouseDoubleClickEvent(QMouseEvent *event) override;
    void                    contextMenuEvent(QContextMenuEvent *event) override;

public slots:
    void                    setShowAddress(bool);
    void                    setShowAsciiDump(bool);
    void                    setShowHexDump(bool);
    void                    setShowComments(bool);
    void                    setWordWidth(int);
    void                    setRowWidth(int);
    void                    setFont(const QFont &font);
    void                    setShowAddressSeparator(bool value);
    void                    repaint();

    void                    clear();
    void                    selectAll();
    void                    deselect();
    bool                    hasSelectedText() const;
    void                    onMenuSelectFont();
    void                    onMenuCopy();

private:
    QString                 formatAddress(address_t address);
    QString                 formatBytes(const QByteArray &row_data, int index) const;
    bool                    isInViewableArea(qint64 index) const;
    bool                    isSelected(qint64 index) const;
    int                     asciiDumpLeft() const;
    int                     commentLeft() const;
    int                     hexDumpLeft() const;
    int                     line1() const;
    int                     line2() const;
    int                     line3() const;
    qint64                  dataSize() const;
    qint64                  pixelToWord(int x, int y) const;
    unsigned int            addressLen() const;
    unsigned int            bytesPerRow() const;
    unsigned int            charsPerWord() const;
    void                    drawAsciiDump(QPainter &painter, quint64 offset, unsigned int row, quint64 size, const QByteArray &row_data) const;
    void                    drawAsciiDumpToBuffer(QTextStream &stream, quint64 offset, quint64 size, const QByteArray &row_data) const;
    void                    drawComments(QPainter &painter, quint64 offset, unsigned int row, quint64 size) const;
    void                    drawCommentsToBuffer(QTextStream &stream, quint64 offset, quint64 size) const;
    void                    drawHexDump(QPainter &painter, quint64 offset, unsigned int row, quint64 size, int *word_count, const QByteArray &row_data) const;
    void                    drawHexDumpToBuffer(QTextStream &stream, quint64 offset, quint64 size, const QByteArray &row_data) const;
    void                    updateScrollbars();

    CommentProviderPointer  comment_server_;
    QBuffer                *internal_buffer_;
    QColor                  address_color_;
    QColor                  even_word_;
    QColor                  non_printable_text_;
    QByteArray              data_;
    address_t  				address_offset_;
    address_t  				origin_;
    address_t               cold_zone_end_;
    bool       				show_address_;
    bool       				show_ascii_;
    bool       				show_comments_;
    bool       				show_hex_;
    bool 					show_address_separator_;
    bool 					show_line1_;
    bool 					show_line2_;
    bool 					show_line3_;
    char   					unprintable_char_;
    int       				font_height_;
    int        				row_width_;
    int       				word_width_;
    qint64    				selection_end_;
    qint64    				selection_start_;
    qreal    				font_width_;

    enum
    {
        Highlighting_None,
        Highlighting_Data,
        Highlighting_Ascii
    }                       highlighting_;

    AddressSize             address_size_;
};