#include "ComponentItem.h"
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QPainter>
#include <QMimeData>
#include <QDrag>
#include <QSvgRenderer>

namespace GUI
{
    ComponentItem::ComponentItem(const QString &svg, const QString &text, QWidget *parent)
        : QWidget(parent)
        , _svg(svg)
        , _text(text)
    {
        calculateText();
        setFixedSize(_minWidth, _minWidth);
    }

    ComponentItem::~ComponentItem()
    {

    }

    void ComponentItem::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        if (width() < _minWidth)
        {
            return;
        }
        int _width = width();

        /// initialize painter
        QPainter painter(this);
        painter.setPen(_iconBorderPen);
        painter.setRenderHint(QPainter::Antialiasing, true);

        /// round rect frame
        int iconWidth = _width - _textBorderWidth * 2 - _fontHeight - _topIconBorderWidth;
        QRect rect((_width - iconWidth) / 2, _topIconBorderWidth, iconWidth, iconWidth);
        painter.drawRoundRect(rect);

        /// render rectangle with svg image
        QSvgRenderer renderer;
        renderer.load(_svg);
        renderer.render(&painter, rect.adjusted(_pixmapBorderWidth + 1, _pixmapBorderWidth, -2 * _pixmapBorderWidth, -2 * _pixmapBorderWidth));

        /// text
        QRect textRect(QPoint((_width - _fontWidth) / 2, _width - _textBorderWidth - _fontHeight), QPoint(_fontWidth + (_width - _fontWidth) / 2, _width - _textBorderWidth));
        painter.drawText(textRect, Qt::AlignHCenter | Qt::AlignVCenter, _showText);
    }

    void ComponentItem::mousePressEvent(QMouseEvent* event)
    {
        QWidget::mousePressEvent(event);
        if (event->button() == Qt::LeftButton)
        {
            QMimeData * data = new QMimeData();
            data->setData("ComponentName", _text.toLocal8Bit());

            QDrag * drag = new QDrag(this);
            drag->setMimeData(data);

            QPixmap pixmap(grab());
            drag->setHotSpot(QPoint(pixmap.width() / 2, pixmap.height() / 2));
            drag->setPixmap(pixmap);

            drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction);
        }
    }

    void ComponentItem::calculateText()
    {
        QFontMetrics metrics(font());
        _fontHeight = metrics.height();
        _fontWidth = metrics.width(_text);

        if (_fontWidth > width())
        {
            int byteNum = _text.size();
            for (int iCnt = byteNum - 1; iCnt > 0; --iCnt)
            {
                QString show = _text.left(iCnt) + "...";
                if (metrics.width(show) < width())
                {
                    _fontWidth = metrics.width(show);
                    _showText = show;
                    break;
                }
            }
        }
        else
            _showText = _text;
    }
}