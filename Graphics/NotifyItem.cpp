#include "NotifyItem.h"
#include "QSvgRenderer"
#include <QPainter>
#include <QFile>
#include "DataCenter/LogData.h"

namespace Graphics
{
    class NotifyItemPrivate
    {
    public:
        /**
         * @brief     notify state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 17:00
         */
        NotifyState _state{ Notify_Noraml };

        /**
         * @brief     notify message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 17:00
         */
        QString _msg{};
    };

    NotifyItem::NotifyItem(QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
        , _private(new NotifyItemPrivate)
    {

    }

    NotifyItem::~NotifyItem()
    {
        if (_private)
        {
            delete _private;
            _private = nullptr;
        }
    }

    void NotifyItem::setNotifyState(NotifyState state, const QString & msg)
    {
        _private->_state = state;
        _private->_msg = msg;
        update();
    }

    QRectF NotifyItem::boundingRect() const
    {
        return QRectF(0, 0, 32, 32);
    }

    void NotifyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option);
        Q_UNUSED(option);
        painter->save();
        QSvgRenderer renderer;
        renderer.load(loadSvgResource(":/frames/error.svg"));
        renderer.render(painter, QRectF(0, 0, 32, 32));
        painter->restore();
    }

    void NotifyItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {

    }

    QByteArray NotifyItem::loadSvgResource(const QString & svg)
    {
        QFile file(svg);
        if (file.open(QIODevice::ReadOnly))
        {
            return file.readAll();
        }
    }

}