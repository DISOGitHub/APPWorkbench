#include "StateItem.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QFile>

namespace Graphics
{

    StateItem::StateItem(QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
    {
        _inputChangedResource = loadSvgResource(":/frames/input_changed.svg");
    }

    StateItem::~StateItem()
    {

    }

    void StateItem::setGraphicsItemState(ComponentInputState state)
    {
        if (_state != state)
        {
            _state = state;
            update();
        }
    }

    QRectF StateItem::boundingRect() const
    {
        return QRectF(0, 0, 32, 32);
    }

    void StateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->save();

        if (State_Normal == _state)
        {

        }
        else if (State_Input_Changed == _state)
        {
            QSvgRenderer renderer;
            renderer.load(_inputChangedResource);
            renderer.render(painter, boundingRect());
        }

        painter->restore();
    }

    QByteArray StateItem::loadSvgResource(const QString & rc)
    {
        QFile file(rc);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray svg = file.readAll();
            file.close();
            return svg;
        }
    }
}