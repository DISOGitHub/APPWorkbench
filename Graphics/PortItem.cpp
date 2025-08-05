#include "PortItem.h"
#include <QPainter>

namespace Graphics
{
    class PortItemPrivater
    {
    public:
        PortItemPrivater(PortItem * item)
        {
            /// get graphics item width as base width
            QGraphicsObject * obj = item->parentObject();
            if (obj)
            {
                _baseWidth = obj->boundingRect().width();
            }
        }

        /**
         * @brief     Size Of The Port.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:25
         */
        int _size{ 10 };

        /**
         * @brief     Pen to Draw Port Item Frame
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:27
         */
        QPen _pen{ QPen(QColor(128,128,128),1) };

        /**
         * @brief     Brush to Draw Port Item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:28
         */
        QBrush _brush{ QBrush(QColor(56,56,56)) };

        /**
         * @brief     input port state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:33
         */
        QPair<PortType, PortState> _inputState{ Port_Type_Input,Port_State_Normal };

        /**
         * @brief     output port state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:34
         */
        QPair<PortType, PortState> _outputState{ Port_Type_Output,Port_State_Normal };

        /**
         * @brief     Graphics object width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 11:39
         */
        int _baseWidth{};
    };

    PortItem::PortItem(QGraphicsObject * parent)
        : QGraphicsObject(parent)
        , _private(new PortItemPrivater(this))
    {

    }

    PortItem::~PortItem()
    {
        if (_private)
        {
            delete _private;
            _private = nullptr;
        }
    }

    int PortItem::size() const
    {
        return _private->_size;
    }

    void PortItem::setSize(int size)
    {
        _private->_size = size;
        update();
    }

    QPen PortItem::framePen() const
    {
        return _private->_pen;
    }

    void PortItem::setFramePen(QPen pen)
    {
        _private->_pen = pen;
        update();
    }

    QBrush PortItem::selectedBrush() const
    {
        return _private->_brush;
    }

    void PortItem::setSelectedBrush(QBrush brush)
    {
        _private->_brush = brush;
    }

    void PortItem::setPortState(PortType type, PortState state)
    {
        if (Port_Type_Input == type)
        {
            if (state != _private->_inputState.second)
            {
                _private->_inputState.second = state;
                update();
            }
        }
        else if (Port_Type_Output == type)
        {
            if (state != _private->_outputState.second)
            {
                _private->_outputState.second = state;
                update();
            }
        }
    }

    PortState PortItem::portState(PortType type) const
    {
        if (Port_Type_Input == type)
            return _private->_inputState.second;
        else
            return _private->_outputState.second;
    }

    QRectF PortItem::boundingRect() const
    {
        return QRectF(0, 0, _private->_baseWidth + _private->_size, _private->_size);
    }

    void PortItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option)
            Q_UNUSED(widget)

            painter->save();

        /// construct input output rect
        QRectF inputPortRect(0, 0, _private->_size, _private->_size);
        QRectF outputPortRect(_private->_baseWidth, 0, _private->_size, _private->_size);

        /// draw input and output port
        drawPort(painter, _private->_inputState.second, inputPortRect);
        drawPort(painter, _private->_outputState.second, outputPortRect);

        painter->restore();
    }

    QPoint PortItem::outputPortPos()
    {
        QPoint pt = this->scenePos().toPoint();
        return QPoint(pt.x() + _private->_baseWidth + _private->_size / 2, pt.y() + _private->_size / 2);
    }

    QPoint PortItem::inputPortPos()
    {
        QPoint pt = this->scenePos().toPoint();
        return QPoint(pt.x() + _private->_size / 2, pt.y() + _private->_size / 2);
    }

    void PortItem::drawPort(QPainter *painter, PortState state, QRectF rect)
    {
        if (Port_State_Normal == state ||
            Port_State_Selected == state)
        {
            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::NoBrush);
        }
        else if (Port_State_Nearby == state)
        {
            painter->setPen(_private->_pen);
            painter->setBrush(Qt::NoBrush);
        }
        else if (Port_State_Selected_Nearby == state)
        {
            painter->setPen(_private->_pen);
            painter->setBrush(_private->_brush);
        }
        painter->drawRect(rect);
    }

}