#include "ArrowItem.h"
#include <QPainter>
#include "CalculateArrowPath.h"

namespace Graphics
{

    ArrowItem::ArrowItem(QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
    {

    }

    ArrowItem::~ArrowItem()
    {

    }

    void ArrowItem::setArrowSize(QSize size)
    {
        _arrowSize = size;
        CalculateArrowPath calculator;
        _arrowPath = calculator.arrowPath(QPoint(_arrowSize.width(), _arrowSize.height() / 2), _arrowSize, Right);
    }

    QRectF ArrowItem::boundingRect() const
    {
        return QRectF(0, 0, _arrowSize.width(), _arrowSize.height());
    }

    void ArrowItem::setPen(QPen pen)
    {
        _pen = pen;
        update();
    }

    void ArrowItem::setBrush(QBrush brush)
    {
        _brush = brush;
        update();
    }

    void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(_pen);
        painter->setBrush(_brush);
        painter->drawPolygon(_arrowPath.toVector());
        painter->restore();
    }

}