#include "NameItem.h"
#include "GraphicsItem.h"
#include <QFont>
#include <QFontMetrics>
#include <QPainter>
#include "DataCenter/LogData.h"

namespace Graphics
{
    class NameItemPrivater
    {
    public:

        NameItemPrivater(NameItem * item, const QString & name)
            : _item(item)
            , _name(name)
        {
            GraphicsItem * parent = dynamic_cast<GraphicsItem *> (_item->parentItem());
            if (!parent) { return; }
            QFontMetrics metrics(_font);
            int fontHeight = metrics.height() + 4;
            _boundingRect = QRectF(0, 0, parent->boundingRect().width() + _borderWidth * 2, fontHeight);
            adjustName();
        }

        /**
         * @brief     if name part too large . omit tail
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:23
         */
        void adjustName()
        {
            QFontMetrics metrics(_font);
            /// calculate name item show text
            int fontWidth = metrics.width(_name);
            if (fontWidth > _boundingRect.width())
            {
                int num = _name.size();
                for (int iCnt = num - 1; iCnt > 0; --iCnt)
                {
                    _showName = _name.left(iCnt) + "...";
                    if (metrics.width(_showName) < _boundingRect.width())
                    {
                        break;
                    }
                }
            }
            else
                _showName = _name;
        }

        /**
         * @brief     name item pointer
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:54
         */
        NameItem * _item{};

        /**
         * @brief     name item 's full name
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 16:00
         */
        QString _name;

        /**
         * @brief     name item show name
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:54
         */
        QString _showName;

        /**
         * @brief     name item bounding rect
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:54
         */
        QRectF _boundingRect;

        /**
         * @brief     name item use font
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:54
         */
        QFont _font;

        /**
         * @brief     name item top border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:55
         */
        int _topBorderWidth{ 5 };

        /**
         * @brief     name item border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:55
         */
        int _borderWidth{ 10 };


    };

    NameItem::NameItem(const QString & name, QGraphicsItem * parent /*= nullptr*/)
        : QGraphicsObject(parent)
        , _privater(new NameItemPrivater(this, name))
    {

    }

    NameItem::~NameItem()
    {

    }

    int NameItem::borderWidth()
    {
        return _privater->_borderWidth;
    }

    int NameItem::topBorderHeight()
    {
        return _privater->_topBorderWidth;
    }

    int NameItem::bottomOffset()
    {
        GraphicsItem * parent = dynamic_cast<GraphicsItem*>(parentItem());
        if (!parent) { return 0; }
        return parent->boundingRect().height() / 2 + _privater->_topBorderWidth + boundingRect().height();
    }

    void NameItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option)
            Q_UNUSED(widget)
            painter->save();

        /// draw name text
        painter->drawText(_privater->_boundingRect, _privater->_showName, Qt::AlignHCenter | Qt::AlignVCenter);

        painter->restore();
    }

    QRectF NameItem::boundingRect() const
    {
        return _privater->_boundingRect;
    }

}