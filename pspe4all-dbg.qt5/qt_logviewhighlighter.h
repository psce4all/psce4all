/**
* (c) 2015 psce4all project. All rights reserved.
* Released under GPL v2 license. Read LICENSE for more details.
*/

#pragma once

#include <QSyntaxHighlighter>

class qt_LogViewHighlighter : public QSyntaxHighlighter
{
public:
    explicit qt_LogViewHighlighter(QTextDocument * parent) : QSyntaxHighlighter(parent)
    {
        QLinearGradient foreground(0.0, 0.5, 1.0, 0.5);
        QLinearGradient background(0.0, 0.5, 1.0, 0.5);
        foreground.setCoordinateMode(QGradient::ObjectBoundingMode);
        background.setCoordinateMode(QGradient::ObjectBoundingMode);
        foreground.setColorAt(1.0, QColor::fromRgb(0x00, 0x00, 0x00));
        background.setColorAt(1.0, QColor::fromRgb(0xFF, 0xFF, 0xFF));

        foreground.setColorAt(0.0, QColor::fromRgb(0x5F, 0x0F, 0x3F));
        background.setColorAt(0.0, QColor::fromRgb(0xF9, 0xDC, 0xEF));
        this->fatalcharformat_.setFontFamily("Monospace");
        this->fatalcharformat_.setFontStyleHint(QFont::TypeWriter);
        this->fatalcharformat_.setFontWeight(QFont::Bold);
        this->fatalcharformat_.setForeground(foreground);
        this->fatalcharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x8F, 0x0F, 0x0F));
        background.setColorAt(0.0, QColor::fromRgb(0xFB, 0xD5, 0xD5));
        this->errorcharformat_.setFontFamily("Monospace");
        this->errorcharformat_.setFontStyleHint(QFont::TypeWriter);
        this->errorcharformat_.setFontWeight(QFont::Bold);
        this->errorcharformat_.setForeground(foreground);
        this->errorcharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x8F, 0x8F, 0x0F));
        background.setColorAt(0.0, QColor::fromRgb(0xFB, 0xFB, 0xD5));
        this->warncharformat_.setFontFamily("Monospace");
        this->warncharformat_.setFontStyleHint(QFont::TypeWriter);
        this->warncharformat_.setFontWeight(QFont::Bold);
        this->warncharformat_.setForeground(foreground);
        this->warncharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x8F, 0x0F, 0x8F));
        background.setColorAt(0.0, QColor::fromRgb(0xFB, 0xD5, 0xFB));
        this->infocharformat_.setFontFamily("Monospace");
        this->infocharformat_.setFontStyleHint(QFont::TypeWriter);
        this->infocharformat_.setFontWeight(QFont::Bold);
        this->infocharformat_.setForeground(foreground);
        this->infocharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x0F, 0x61, 0xA9));
        background.setColorAt(0.0, QColor::fromRgb(0xEC, 0xF5, 0xFD));
        this->debugcharformat_.setFontFamily("Monospace");
        this->debugcharformat_.setFontStyleHint(QFont::TypeWriter);
        this->debugcharformat_.setFontWeight(QFont::Bold);
        this->debugcharformat_.setForeground(foreground);
        this->debugcharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x61, 0xA9, 0x0F));
        background.setColorAt(0.0, QColor::fromRgb(0xE9, 0xFB, 0xD5));
        this->tracecharformat_.setFontFamily("Monospace");
        this->tracecharformat_.setFontStyleHint(QFont::TypeWriter);
        this->tracecharformat_.setFontWeight(QFont::Bold);
        this->tracecharformat_.setForeground(foreground);
        this->tracecharformat_.setBackground(background);

        foreground.setColorAt(0.0, QColor::fromRgb(0x0F, 0xA9, 0xA4));
        background.setColorAt(0.0, QColor::fromRgb(0xD5, 0xFB, 0xFA));
        this->forcecharformat_.setFontFamily("Monospace");
        this->forcecharformat_.setFontStyleHint(QFont::TypeWriter);
        this->forcecharformat_.setFontWeight(QFont::Bold);
        this->forcecharformat_.setForeground(foreground);
        this->forcecharformat_.setBackground(background);
    }

private:
    void highlightSpecialLine(QString const & text, QString const & keyword, QTextCharFormat const & charformat)
    {
        if (text.startsWith(keyword))
        {
            this->setFormat(0, 136, charformat);
        }
    }


protected:
    virtual void highlightBlock(QString const & text) override
    {
        if (text.isEmpty())
            return;

        this->highlightSpecialLine(text, "E_FATAL", this->fatalcharformat_);
        this->highlightSpecialLine(text, "E_ERROR", this->errorcharformat_);
        this->highlightSpecialLine(text, "E_WARN ", this->warncharformat_);
        this->highlightSpecialLine(text, "E_INFO ", this->infocharformat_);
        this->highlightSpecialLine(text, "E_DEBUG", this->debugcharformat_);
        this->highlightSpecialLine(text, "E_TRACE", this->tracecharformat_);
        this->highlightSpecialLine(text, "E_FORCE", this->forcecharformat_);
    }

private:
    QTextCharFormat fatalcharformat_;
    QTextCharFormat errorcharformat_;
    QTextCharFormat warncharformat_;
    QTextCharFormat infocharformat_;
    QTextCharFormat debugcharformat_;
    QTextCharFormat tracecharformat_;
    QTextCharFormat forcecharformat_;
};
