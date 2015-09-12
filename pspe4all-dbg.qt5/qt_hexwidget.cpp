/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#include "qt_hexwidget.h"

#include <QApplication>
#include <QBuffer>
#include <QClipboard>
#include <QDebug>
#include <QFontDialog>
#include <QMenu>
#include <QMouseEvent>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QScrollBar>
#include <QSignalMapper>
#include <QTextStream>
#include <QtGlobal>

#include <cctype>
#include <climits>
#include <memory>
#include <cmath>
#include <inttypes.h>

namespace
{
    struct show_separator_tag {};

    template <size_t N>
    struct address_format {};

    template <>
    struct address_format<4>
    {

        template <class T>
        static QString format_address(T address, const show_separator_tag&)
        {
            static char buffer[10];
            const quint16 hi = (address >> 16) & 0xffff;
            const quint16 lo = (address & 0xffff);

            qsnprintf(buffer, sizeof(buffer), "%04X:%04X", hi, lo);
            return QString::fromLocal8Bit(buffer);
        }

        template <class T>
        static QString format_address(T address)
        {
            static char buffer[9];
            const quint16 hi = (address >> 16) & 0xffff;
            const quint16 lo = (address & 0xffff);

            qsnprintf(buffer, sizeof(buffer), "%04X%04X", hi, lo);
            return QString::fromLocal8Bit(buffer);
        }
    };

    template <>
    struct address_format<8>
    {

        template <class T>
        static QString format_address(T address, const show_separator_tag&)
        {
            static char buffer[19];
            const quint32 hi = (address >> 32) & 0xffffffff;
            const quint32 lo = (address & 0xffffffff);

            qsnprintf(buffer, sizeof(buffer), "%08X:%08X", hi, lo);
            return QString::fromLocal8Bit(buffer);
        }

        template <class T>
        static QString format_address(T address)
        {
            static char buffer[18];
            const quint32 hi = (address >> 32) & 0xffffffff;
            const quint32 lo = (address & 0xffffffff);

            qsnprintf(buffer, sizeof(buffer), "%08X%08X", hi, lo);
            return QString::fromLocal8Bit(buffer);
        }
    };

    bool is_printable(unsigned char ch)
    {

        if (ch < 0x80)
        {
            return std::isprint(ch) || std::isspace(ch);
        }
        else
        {
            return (ch & 0xff) >= 0xa0;
        }
    }

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

qt_HexWidget::qt_HexWidget(QWidget *parent)
    : QAbstractScrollArea(parent)
    , internal_buffer_(0)
    , address_color_(Qt::red)
    , even_word_(Qt::blue)
    , non_printable_text_(Qt::red)
    , data_(0)
    , address_offset_(0)
    , origin_(0)
    , cold_zone_end_(0)
    , show_address_(true)
    , show_ascii_(true)
    , show_comments_(true)
    , show_hex_(true)
    , show_address_separator_(true)
    , show_line1_(true)
    , show_line2_(true)
    , show_line3_(true)
    , unprintable_char_('.')
    , font_height_(0)
    , row_width_(16)
    , word_width_(1)
    , selection_end_(-1)
    , selection_start_(-1)
    , font_width_(0)
    , highlighting_(Highlighting_None)
{
    setFont(QFont("Monospace", 8));

    address_size_ = Address32;

    setShowAddressSeparator(false);

    setFocusPolicy(Qt::StrongFocus);
}

qt_HexWidget::~qt_HexWidget()
{
    delete internal_buffer_;
}

void qt_HexWidget::setShowAddressSeparator(bool value)
{
    show_address_separator_ = value;
    updateScrollbars();
}

QString qt_HexWidget::formatAddress(address_t address)
{
    if (address_size_ == Address32)
    {
        if (show_address_separator_) return address_format<4>::format_address(address, show_separator_tag());
        else                         return address_format<4>::format_address(address);
    }
    else
    {
        if (show_address_separator_) return address_format<8>::format_address(address, show_separator_tag());
        else                         return address_format<8>::format_address(address);
    }
}

void qt_HexWidget::repaint()
{
    viewport()->repaint();
}

qint64 qt_HexWidget::dataSize() const
{
    return data_.size();
}

void qt_HexWidget::setFont(const QFont &f)
{
    const QFontMetricsF fm(f);
    font_width_ = fm.width('X');
    font_height_ = fm.height();

    updateScrollbars();

    QAbstractScrollArea::setFont(f);
}

QMenu *qt_HexWidget::createStandardContextMenu()
{
    QMenu *const menu = new QMenu(this);

    menu->addAction(tr("Select &Font"), this, SLOT(onMenuSelectFont()));
    menu->addSeparator();
    addMenuToggleAction(menu, tr("Show A&ddress"), show_address_, this, SLOT(setShowAddress(bool)));
    addMenuToggleAction(menu, tr("Show &Hex"), show_hex_, this, SLOT(setShowHexDump(bool)));
    addMenuToggleAction(menu, tr("Show &Ascii"), show_ascii_, this, SLOT(setShowAsciiDump(bool)));
    addMenuToggleAction(menu, tr("Show &Comments"), show_comments_, this, SLOT(setShowComments(bool)));

    QSignalMapper *wordWidthMapper = new QSignalMapper(menu);

    QMenu *const wordMenu = new QMenu(tr("Set Word Width"), menu);
    QAction *const a1 = addMenuToggleAction(wordMenu, tr("1 Byte"), word_width_ == 1, wordWidthMapper, SLOT(map()));
    QAction *const a2 = addMenuToggleAction(wordMenu, tr("2 Bytes"), word_width_ == 2, wordWidthMapper, SLOT(map()));
    QAction *const a3 = addMenuToggleAction(wordMenu, tr("4 Bytes"), word_width_ == 4, wordWidthMapper, SLOT(map()));
    QAction *const a4 = addMenuToggleAction(wordMenu, tr("8 Bytes"), word_width_ == 8, wordWidthMapper, SLOT(map()));

    wordWidthMapper->setMapping(a1, 1);
    wordWidthMapper->setMapping(a2, 2);
    wordWidthMapper->setMapping(a3, 4);
    wordWidthMapper->setMapping(a4, 8);

    connect(wordWidthMapper, SIGNAL(mapped(int)), SLOT(setWordWidth(int)));

    QSignalMapper *rowWidthMapper = new QSignalMapper(menu);

    QMenu *const rowMenu = new QMenu(tr("Set Row Width"), menu);
    QAction *const a5 = addMenuToggleAction(rowMenu, tr("1 Word"), row_width_ == 1, rowWidthMapper, SLOT(map()));
    QAction *const a6 = addMenuToggleAction(rowMenu, tr("2 Words"), row_width_ == 2, rowWidthMapper, SLOT(map()));
    QAction *const a7 = addMenuToggleAction(rowMenu, tr("4 Words"), row_width_ == 4, rowWidthMapper, SLOT(map()));
    QAction *const a8 = addMenuToggleAction(rowMenu, tr("8 Words"), row_width_ == 8, rowWidthMapper, SLOT(map()));
    QAction *const a9 = addMenuToggleAction(rowMenu, tr("16 Words"), row_width_ == 16, rowWidthMapper, SLOT(map()));

    rowWidthMapper->setMapping(a5, 1);
    rowWidthMapper->setMapping(a6, 2);
    rowWidthMapper->setMapping(a7, 4);
    rowWidthMapper->setMapping(a8, 8);
    rowWidthMapper->setMapping(a9, 16);

    connect(rowWidthMapper, SIGNAL(mapped(int)), SLOT(setRowWidth(int)));

    menu->addSeparator();
    menu->addMenu(wordMenu);
    menu->addMenu(rowMenu);

    menu->addSeparator();
    menu->addAction(tr("&Copy Selection To Clipboard"), this, SLOT(onMenuCopy()));

    return menu;
}

void qt_HexWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *const menu = createStandardContextMenu();
    menu->exec(event->globalPos());
    delete menu;
}

void qt_HexWidget::onMenuCopy()
{
    if (hasSelectedText())
    {
        QString s;
        QTextStream ss(&s);

        const int chars_per_row = bytesPerRow();
        qint64 offset = static_cast<quint64>(verticalScrollBar()->value()) * chars_per_row;

        if (origin_ != 0)
        {
            if (offset > 0)
            {
                offset += origin_;
                offset -= chars_per_row;
            }
        }

        const qint64 end = qMax(selection_start_, selection_end_);
        const qint64 start = qMin(selection_start_, selection_end_);
        const qint64 data_size = dataSize();

        while (offset < end)
        {
            if ((offset + chars_per_row) > start)
            {
                const QByteArray row_data = data_.mid(offset, chars_per_row);

                if (!row_data.isEmpty())
                {
                    if (show_address_)
                    {
                        const address_t address_rva = address_offset_ + offset;
                        const QString addressBuffer = formatAddress(address_rva);
                        ss << addressBuffer << '|';
                    }

                    if (show_hex_)
                    {
                        drawHexDumpToBuffer(ss, offset, data_size, row_data);
                        ss << "|";
                    }

                    if (show_ascii_)
                    {
                        drawAsciiDumpToBuffer(ss, offset, data_size, row_data);
                        ss << "|";
                    }

                    if (show_comments_ && comment_server_)
                    {
                        drawCommentsToBuffer(ss, offset, data_size);
                    }
                }

                ss << "\n";
            }
            offset += chars_per_row;
        }

        QApplication::clipboard()->setText(s);
        QApplication::clipboard()->setText(s, QClipboard::Selection);
    }
}

void qt_HexWidget::onMenuSelectFont()
{
    setFont(QFontDialog::getFont(0, font(), this, QString(), QFontDialog::MonospacedFonts));
}

void qt_HexWidget::clear()
{
    data_.clear();
    repaint();
}

bool qt_HexWidget::hasSelectedText() const
{
    return !(selection_start_ == -1 || selection_end_ == -1);
}

bool qt_HexWidget::isInViewableArea(qint64 index) const
{
    const qint64 firstViewableWord = static_cast<quint64>(verticalScrollBar()->value()) * row_width_;
    const qint64 viewableLines = viewport()->height() / font_height_;
    const qint64 viewableWords = viewableLines * row_width_;
    const qint64 lastViewableWord = firstViewableWord + viewableWords;

    return index >= firstViewableWord && index < lastViewableWord;
}

void qt_HexWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier)
    {
        switch (event->key())
        {
        case Qt::Key_A:
            selectAll();
            repaint();
            break;
        case Qt::Key_Home:
            scrollTo(0);
            break;
        case Qt::Key_End:
            scrollTo(dataSize() - bytesPerRow());
            break;
        case Qt::Key_Down:

            do
            {
                qint64 offset = static_cast<quint64>(verticalScrollBar()->value()) * bytesPerRow();

                if (origin_ != 0)
                {
                    if (offset > 0)
                    {
                        offset += origin_;
                        offset -= bytesPerRow();
                    }
                }

                if (offset + 1 < dataSize())
                {
                    scrollTo(offset + 1);
                }
            }
            while (0);

            return;
        case Qt::Key_Up:
            do
            {
                qint64 offset = static_cast<quint64>(verticalScrollBar()->value()) * bytesPerRow();

                if (origin_ != 0)
                {
                    if (offset > 0)
                    {
                        offset += origin_;
                        offset -= bytesPerRow();
                    }
                }

                if (offset > 0)
                {
                    scrollTo(offset - 1);
                }
            }
            while (0);

            return;
        }
    }

    QAbstractScrollArea::keyPressEvent(event);
}

int qt_HexWidget::line3() const
{
    if (show_ascii_)
    {
        const int elements = bytesPerRow();
        return asciiDumpLeft() + (elements * font_width_) + (font_width_ / 2);
    }
    else
    {
        return line2();
    }
}

int qt_HexWidget::line2() const
{
    if (show_hex_)
    {
        const int elements = row_width_ * (charsPerWord() + 1) - 1;
        return hexDumpLeft() + (elements * font_width_) + (font_width_ / 2);
    }
    else
    {
        return line1();
    }
}

int qt_HexWidget::line1() const
{
    if (show_address_)
    {
        const int elements = addressLen();
        return (elements * font_width_) + (font_width_ / 2);
    }
    else
    {
        return 0;
    }
}

int qt_HexWidget::hexDumpLeft() const
{
    return line1() + (font_width_ / 2);
}

int qt_HexWidget::asciiDumpLeft() const
{
    return line2() + (font_width_ / 2);
}

int qt_HexWidget::commentLeft() const
{
    return line3() + (font_width_ / 2);
}

unsigned int qt_HexWidget::charsPerWord() const
{
    return word_width_ * 2;
}

unsigned int qt_HexWidget::addressLen() const
{
    const unsigned int addressLength = (address_size_ * CHAR_BIT) / 4;
    return addressLength + (show_address_separator_ ? 1 : 0);
}

void qt_HexWidget::updateScrollbars()
{
    const qint64 sz = dataSize();
    const int bpr = bytesPerRow();

    qint64 maxval = sz / bpr + ((sz % bpr) ? 1 : 0) - viewport()->height() / font_height_;

    verticalScrollBar()->setMaximum(qMax((qint64)0, maxval));
    horizontalScrollBar()->setMaximum(qMax(0, static_cast<int>((line3() - viewport()->width()) / font_width_)));
}

void qt_HexWidget::scrollTo(address_t offset)
{
    const int bpr = bytesPerRow();
    origin_ = offset % bpr;
    address_t address = offset / bpr;

    updateScrollbars();

    if (origin_ != 0)
    {
        ++address;
    }

    verticalScrollBar()->setValue(address);
    repaint();
}

void qt_HexWidget::setShowAddress(bool show)
{
    show_address_ = show;
    updateScrollbars();
    repaint();
}

void qt_HexWidget::setShowHexDump(bool show)
{
    show_hex_ = show;
    updateScrollbars();
    repaint();
}

void qt_HexWidget::setShowComments(bool show)
{
    show_comments_ = show;
    updateScrollbars();
    repaint();
}

void qt_HexWidget::setShowAsciiDump(bool show)
{
    show_ascii_ = show;
    updateScrollbars();
    repaint();
}

void qt_HexWidget::setRowWidth(int rowWidth)
{
    Q_ASSERT(rowWidth >= 0);
    row_width_ = rowWidth;
    updateScrollbars();
    repaint();
}

void qt_HexWidget::setWordWidth(int wordWidth)
{
    Q_ASSERT(wordWidth >= 0);
    word_width_ = wordWidth;
    updateScrollbars();
    repaint();
}

unsigned int qt_HexWidget::bytesPerRow() const
{
    return row_width_ * word_width_;
}

qint64 qt_HexWidget::pixelToWord(int x, int y) const
{
    qint64 word = -1;

    switch (highlighting_)
    {
    case Highlighting_Data:
        x = qBound(line1(), x, static_cast<int>(line2() + font_width_));

        x -= line1();

        x = x / font_width_ + (fmod(x, font_width_) >= font_width_ / 2 ? 1 : 0);
        y /= font_height_;

        x /= (charsPerWord() + 1);
        break;
    case Highlighting_Ascii:
        x = qBound(asciiDumpLeft(), x, line3());

        x -= asciiDumpLeft();

        x /= font_width_;
        y /= font_height_;

        x /= word_width_;
        break;
    default:
        Q_ASSERT(0);
        break;
    }

    quint64 start_offset = static_cast<quint64>(verticalScrollBar()->value()) * bytesPerRow();

    if (origin_ != 0)
    {
        if (start_offset > 0)
        {
            start_offset += origin_;
            start_offset -= bytesPerRow();
        }
    }

    start_offset /= static_cast<unsigned int>(word_width_);

    if ((origin_ % word_width_) != 0)
    {
        start_offset += 1;
    }

    word = ((y * row_width_) + x) + start_offset;

    return word;
}

void qt_HexWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        const int x = event->x() + horizontalScrollBar()->value() * font_width_;
        const int y = event->y();
        if (x >= line1() && x < line2())
        {

            highlighting_ = Highlighting_Data;

            const qint64 offset = pixelToWord(x, y);
            qint64 byte_offset = offset * word_width_;
            if (origin_)
            {
                if (origin_ % word_width_)
                {
                    byte_offset -= word_width_ - (origin_ % word_width_);
                }
            }

            selection_start_ = byte_offset;
            selection_end_ = selection_start_ + word_width_;
            repaint();
        }
        else if (x < line1())
        {
            highlighting_ = Highlighting_Data;

            const qint64 offset = pixelToWord(line1(), y);
            qint64 byte_offset = offset * word_width_;
            if (origin_)
            {
                if (origin_ % word_width_)
                {
                    byte_offset -= word_width_ - (origin_ % word_width_);
                }
            }

            const unsigned chars_per_row = bytesPerRow();

            selection_start_ = byte_offset;
            selection_end_ = byte_offset + chars_per_row;
            repaint();
        }
    }
}

void qt_HexWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        const int x = event->x() + horizontalScrollBar()->value() * font_width_;
        const int y = event->y();

        if (x < line2())
        {
            highlighting_ = Highlighting_Data;
        }
        else if (x >= line2())
        {
            highlighting_ = Highlighting_Ascii;
        }

        const qint64 offset = pixelToWord(x, y);
        qint64 byte_offset = offset * word_width_;
        if (origin_)
        {
            if (origin_ % word_width_)
            {
                byte_offset -= word_width_ - (origin_ % word_width_);
            }
        }

        if (offset < dataSize())
        {
            selection_start_ = selection_end_ = byte_offset;
        }
        else
        {
            selection_start_ = selection_end_ = -1;
        }
        repaint();
    }
}

void qt_HexWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (highlighting_ != Highlighting_None)
    {
        const int x = event->x() + horizontalScrollBar()->value() * font_width_;
        const int y = event->y();

        const qint64 offset = pixelToWord(x, y);

        if (selection_start_ != -1)
        {
            if (offset == -1)
            {
                selection_end_ = (row_width_ - selection_start_) + selection_start_;
            }
            else
            {
                qint64 byte_offset = (offset * word_width_);

                if (origin_)
                {
                    if (origin_ % word_width_)
                    {
                        byte_offset -= word_width_ - (origin_ % word_width_);
                    }

                }
                selection_end_ = byte_offset;
            }

            if (selection_end_ < 0)
            {
                selection_end_ = 0;
            }

            if (!isInViewableArea(selection_end_))
            {
                // TODO: scroll to an appropriate location
            }

        }
        repaint();
    }
}

void qt_HexWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        highlighting_ = Highlighting_None;
    }
}

void qt_HexWidget::setData(const QByteArray &d)
{
    data_ = d;
    if (data_.size() > Q_INT64_C(0xffffffff))
    {
        address_size_ = Address64;
    }

    deselect();
    updateScrollbars();
    repaint();
}

void qt_HexWidget::resizeEvent(QResizeEvent *)
{
    updateScrollbars();
}

void qt_HexWidget::setAddressOffset(address_t offset)
{
    address_offset_ = offset;
}

bool qt_HexWidget::isSelected(qint64 index) const
{
    bool ret = false;
    if (index < static_cast<qint64>(dataSize()))
    {
        if (selection_start_ != selection_end_)
        {
            if (selection_start_ < selection_end_)
            {
                ret = (index >= selection_start_ && index < selection_end_);
            }
            else
            {
                ret = (index >= selection_end_ && index < selection_start_);
            }
        }
    }
    return ret;
}

void qt_HexWidget::drawComments(QPainter &painter, quint64 offset, unsigned int row, quint64 size) const
{
    Q_UNUSED(size);

    painter.setPen(QPen(palette().text().color()));

    const address_t address = address_offset_ + offset;
    const QString comment = comment_server_->comment(address, word_width_);

    painter.drawText(commentLeft(), row, comment.length() * font_width_, font_height_, Qt::AlignTop, comment);
}

void qt_HexWidget::drawAsciiDumpToBuffer(QTextStream &stream, quint64 offset, quint64 size, const QByteArray &row_data) const
{
    const unsigned chars_per_row = bytesPerRow();
    for (unsigned i = 0; i < chars_per_row; ++i)
    {
        const quint64 index = offset + i;
        if (index < size)
        {
            if (isSelected(index))
            {
                const unsigned char ch = row_data[i];
                const bool printable = is_printable(ch) && ch != '\f' && ch != '\t' && ch != '\r' && ch != '\n' && ch < 0x80;
                const char byteBuffer(printable ? ch : unprintable_char_);
                stream << byteBuffer;
            }
            else
            {
                stream << ' ';
            }
        }
        else
        {
            break;
        }
    }
}

void qt_HexWidget::drawCommentsToBuffer(QTextStream &stream, quint64 offset, quint64 size) const
{
    Q_UNUSED(size);
    const address_t address = address_offset_ + offset;
    const QString comment = comment_server_->comment(address, word_width_);
    stream << comment;
}

QString qt_HexWidget::formatBytes(const QByteArray &row_data, int index) const
{
    union
    {
        quint64 q;
        quint32 d;
        quint16 w;
        quint8  b;
    } value = { 0 };

    char byte_buffer[32];

    switch (word_width_)
    {
    case 1:
        value.b |= (row_data[index + 0] & 0xff);
        qsnprintf(byte_buffer, sizeof(byte_buffer), "%02X", value.b);
        break;
    case 2:
        value.w |= (row_data[index + 0] & 0xff);
        value.w |= (row_data[index + 1] & 0xff) << 8;
        qsnprintf(byte_buffer, sizeof(byte_buffer), "%04X", value.w);
        break;
    case 4:
        value.d |= (row_data[index + 0] & 0xff);
        value.d |= (row_data[index + 1] & 0xff) << 8;
        value.d |= (row_data[index + 2] & 0xff) << 16;
        value.d |= (row_data[index + 3] & 0xff) << 24;
        qsnprintf(byte_buffer, sizeof(byte_buffer), "%08X", value.d);
        break;
    case 8:
        value.q |= static_cast<quint64>(row_data[index + 0] & 0xff);
        value.q |= static_cast<quint64>(row_data[index + 1] & 0xff) << 8;
        value.q |= static_cast<quint64>(row_data[index + 2] & 0xff) << 16;
        value.q |= static_cast<quint64>(row_data[index + 3] & 0xff) << 24;
        value.q |= static_cast<quint64>(row_data[index + 4] & 0xff) << 32;
        value.q |= static_cast<quint64>(row_data[index + 5] & 0xff) << 40;
        value.q |= static_cast<quint64>(row_data[index + 6] & 0xff) << 48;
        value.q |= static_cast<quint64>(row_data[index + 7] & 0xff) << 56;
        qsnprintf(byte_buffer, sizeof(byte_buffer), "%016llX", value.q);
        break;
    }

    return byte_buffer;
}

void qt_HexWidget::drawHexDumpToBuffer(QTextStream &stream, quint64 offset, quint64 size, const QByteArray &row_data) const
{

    Q_UNUSED(size);

    for (int i = 0; i < row_width_; ++i)
    {

        const quint64 index = offset + (i * word_width_);

        if (index + word_width_ <= size)
        {
            const QString byteBuffer = formatBytes(row_data, i * word_width_);

            if (isSelected(index))
            {
                stream << byteBuffer;
            }
            else
            {
                stream << QString(byteBuffer.length(), ' ');
            }

            if (i != (row_width_ - 1))
            {
                stream << ' ';
            }
        }
        else
        {
            break;
        }
    }
}

void qt_HexWidget::drawHexDump(QPainter &painter, quint64 offset, unsigned int row, quint64 size, int *word_count, const QByteArray &row_data) const
{
    const int hex_dump_left = hexDumpLeft();

    for (int i = 0; i < row_width_; ++i)
    {
        const quint64 index = offset + (i * word_width_);

        if (index + word_width_ <= size)
        {
            const QString byteBuffer = formatBytes(row_data, i * word_width_);

            const qreal drawLeft = hex_dump_left + (i * (charsPerWord() + 1) * font_width_);
            const qreal drawWidth = charsPerWord() * font_width_;

            if (isSelected(index))
            {
                painter.fillRect(QRectF(drawLeft, row, drawWidth, font_height_), palette().highlight());

                if (i != (row_width_ - 1))
                {
                    if (isSelected(index + 1))
                    {
                        painter.fillRect(QRectF(drawLeft + drawWidth, row, font_width_, font_height_), palette().highlight());
                    }
                }

                painter.setPen(QPen(palette().highlightedText().color()));
            }
            else
            {
                painter.setPen(QPen((*word_count & 1) ? even_word_ : palette().text().color()));
            }

            if (cold_zone_end_ > address_offset_ && offset < cold_zone_end_ - address_offset_)
            {
                painter.setPen(QPen(Qt::gray));
            }

            painter.drawText(drawLeft, row, byteBuffer.length() * font_width_, font_height_, Qt::AlignTop, byteBuffer);

            ++(*word_count);
        }
        else
        {
            break;
        }
    }
}

void qt_HexWidget::drawAsciiDump(QPainter &painter, quint64 offset, unsigned int row, quint64 size, const QByteArray &row_data) const
{
    const int ascii_dump_left = asciiDumpLeft();

    const unsigned chars_per_row = bytesPerRow();
    for (unsigned i = 0; i < chars_per_row; ++i)
    {
        const quint64 index = offset + i;

        if (index < size)
        {
            const char ch = row_data[i];
            const qreal drawLeft = ascii_dump_left + i * font_width_;
            const bool printable = is_printable(ch);

            // drawing a selected character
            if (isSelected(index))
            {
                painter.fillRect(QRectF(drawLeft, row, font_width_, font_height_), palette().highlight());
                painter.setPen(QPen(palette().highlightedText().color()));
            }
            else
            {
                painter.setPen(QPen(printable ? palette().text().color() : non_printable_text_));
            }

            if (cold_zone_end_ > address_offset_ && offset < cold_zone_end_ - address_offset_)
            {
                painter.setPen(QPen(Qt::gray));
            }

            const QString byteBuffer(printable ? ch : unprintable_char_);

            painter.drawText(drawLeft, row, font_width_, font_height_, Qt::AlignTop, byteBuffer);
        }
        else
        {
            break;
        }
    }
}

void qt_HexWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    painter.translate(-horizontalScrollBar()->value() * font_width_, 0);

    int word_count = 0;

    unsigned int row = 0;

    const int chars_per_row = bytesPerRow();

    quint64 offset = static_cast<quint64>(verticalScrollBar()->value()) * chars_per_row;

    if (origin_ != 0)
    {
        if (offset > 0)
        {
            offset += origin_;
            offset -= chars_per_row;
        }
        else
        {
            origin_ = 0;
            updateScrollbars();
        }
    }

    const quint64 data_size = static_cast<quint64>(dataSize());
    const unsigned int widget_height = static_cast<unsigned int>(height());

    while (row + font_height_ < widget_height && offset < data_size)
    {
        const QByteArray row_data = data_.mid(offset, chars_per_row);

        if (!row_data.isEmpty())
        {
            if (show_address_)
            {
                const address_t address_rva = address_offset_ + offset;
                const QString addressBuffer = formatAddress(address_rva);
                painter.setPen(QPen(address_color_));

                if (cold_zone_end_ > address_offset_ && offset < cold_zone_end_ - address_offset_)
                {
                    painter.setPen(QPen(Qt::gray));
                }

                painter.drawText(0, row, addressBuffer.length() * font_width_, font_height_, Qt::AlignTop, addressBuffer);
            }

            if (show_hex_)
            {
                drawHexDump(painter, offset, row, data_size, &word_count, row_data);
            }

            if (show_ascii_)
            {
                drawAsciiDump(painter, offset, row, data_size, row_data);
            }

            if (show_comments_ && comment_server_)
            {
                drawComments(painter, offset, row, data_size);
            }
        }

        offset += chars_per_row;
        row += font_height_;
    }

    painter.setPen(QPen(palette().shadow().color()));

    if (show_address_ && show_line1_)
    {
        const int line1_x = line1();
        painter.drawLine(line1_x, 0, line1_x, widget_height);
    }

    if (show_hex_ && show_line2_)
    {
        const int line2_x = line2();
        painter.drawLine(line2_x, 0, line2_x, widget_height);
    }

    if (show_ascii_ && show_line3_)
    {
        const int line3_x = line3();
        painter.drawLine(line3_x, 0, line3_x, widget_height);
    }
}

void qt_HexWidget::selectAll()
{
    selection_start_ = 0;
    selection_end_ = dataSize();
}

void qt_HexWidget::deselect()
{
    selection_start_ = -1;
    selection_end_ = -1;
}

QByteArray qt_HexWidget::allBytes() const
{
    return data_;
}

QByteArray qt_HexWidget::selectedBytes() const
{
    if (hasSelectedText())
    {
        const qint64 s = qMin(selection_start_, selection_end_);
        const qint64 e = qMax(selection_start_, selection_end_);

        return data_.mid(s, e - s);
    }

    return QByteArray();
}

qt_HexWidget::address_t qt_HexWidget::selectedBytesAddress() const
{
    const address_t select_base = qMin(selection_start_, selection_end_);
    return select_base + address_offset_;
}

quint64 qt_HexWidget::selectedBytesSize() const
{

    quint64 ret;
    if (selection_end_ > selection_start_)
    {
        ret = selection_end_ - selection_start_;
    }
    else
    {
        ret = selection_start_ - selection_end_;
    }

    return ret;
}

qt_HexWidget::address_t qt_HexWidget::addressOffset() const
{
    return address_offset_;
}

void qt_HexWidget::setCommentServer(const CommentProviderPointer &p)
{
    comment_server_ = p;
}

qt_HexWidget::CommentProviderPointer qt_HexWidget::commentServer() const
{
    return comment_server_;
}

bool qt_HexWidget::showHexDump() const
{
    return show_hex_;
}

bool qt_HexWidget::showAddress() const
{
    return show_address_;
}

bool qt_HexWidget::showAsciiDump() const
{
    return show_ascii_;
}

bool qt_HexWidget::showComments() const
{
    return show_comments_;
}

int qt_HexWidget::wordWidth() const
{
    return word_width_;
}

int qt_HexWidget::rowWidth() const
{
    return row_width_;
}

qt_HexWidget::address_t qt_HexWidget::firstVisibleAddress() const
{
    // current actual offset (in bytes)
    const int chars_per_row = bytesPerRow();
    quint64 offset = static_cast<quint64>(verticalScrollBar()->value()) * chars_per_row;

    if (origin_ != 0)
    {
        if (offset > 0)
        {
            offset += origin_;
            offset -= chars_per_row;
        }
    }

    return offset + addressOffset();
}

void qt_HexWidget::setAddressSize(AddressSize address_size)
{
    address_size_ = address_size;
    repaint();
}

qt_HexWidget::AddressSize qt_HexWidget::addressSize() const
{
    return address_size_;
}

void qt_HexWidget::setColdZoneEnd(address_t offset)
{
    cold_zone_end_ = offset;
}