#include "IndicateLineItem.h"
#include "Define.h"
#include "GraphicsItem.h"
#include <QPainter>
#include <QDebug>
#include "CalculateFeaturePoints.h"
#include "NameItem.h"

namespace Graphics
{
    class IndicateLineItemPrivate
    {
    public:
        /**
         * @brief     constructor
         * @param     line[i]. line item
         * @return    IndicateLineItemPrivate object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 13:05
         */
        IndicateLineItemPrivate(IndicateLineItem * line)
            : _line(line)
        {

        }

        IndicateLineItem * _line{};

        /**
         * @brief     Indicate Line Item Bounding Rect
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 15:05
         */
        QRectF _boundingRect{};

        /**
         * @brief     Indicate Line Item From Graphics Item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 15:07
         */
        GraphicsItem * _from{};

        /**
         * @brief     Current Cursor Position
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 15:08
         */
        QPoint _cursorPt{};

        /**
         * @brief     Feature Points
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 17:21
         */
        QList<QPoint> _featurePts{};

        /**
         * @brief     pen indicate line painter used
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 8:42
         */
        QPen _pen{ QPen(QColor(56,56,56),1,Qt::PenStyle::DashLine) };

        /**
         * @brief     in indicate line IndicateLine_ZTurning_Type . turning point distance to from graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 17:23
         */
        int _turningPointLength{ 40 };

        /**
         * @brief     the size of the arrow
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 9:22
         */
        QSize _arrowSize{ QSize(14,10) };

        /**
         * @brief     update feature points
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:34
         */
        void updateFeaturePoints()
        {
            CalculateFeaturePoints calculator(QPoint(0, 0), _cursorPt);
            calculator.setGraphicsItemTopHeight(_from->boundingRect().height() / 2);
            calculator.setGraphicsItemBottomHeight(_from->boundingRect().height() / 2 + _from->namePart()->topBorderHeight() + _from->namePart()->boundingRect().height());
            calculator.setGraphicsItemWidth(_from->boundingRect().height() / 2);
            calculator.setArrowSize(_arrowSize);
            calculator.setTurningPointLength(_turningPointLength);
            _featurePts = calculator.featurePoints();
        }

        /**
         * @brief     update indicate line item bounding box
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 11:33
         */
        void updateBoundingBox()
        {
            if (_featurePts.isEmpty()) { return; }
            int xmin = _featurePts.first().x(), xmax = xmin, ymin = _featurePts.first().y(), ymax = ymin;

            for (auto pt : _featurePts)
            {
                xmin = std::min(pt.x(), xmin);
                xmax = std::max(pt.x(), xmax);
                ymin = std::min(pt.y(), ymin);
                ymax = std::max(pt.y(), ymax);
            }
            QPoint leftTop = QPoint(xmin, ymin);
            QPoint rightBottom = QPoint(xmax, ymax);
            _boundingRect = QRect(leftTop, rightBottom);
            qDebug() << leftTop << rightBottom;
        }
    };

    IndicateLineItem::IndicateLineItem(QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
        , _private(new IndicateLineItemPrivate(this))
    {

    }

    IndicateLineItem::~IndicateLineItem()
    {
        if (_private)
        {
            delete _private;
            _private = nullptr;
        }
    }

    QRectF IndicateLineItem::boundingRect() const
    {
        /// adjust bounding rect
        return _private->_boundingRect.adjusted(-2, -2, 2, 2);
    }

    void IndicateLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->save();
        painter->setPen(_private->_pen);
        int ptNum = _private->_featurePts.size();
        for (int iCnt = 0; iCnt < ptNum - 1; ++iCnt)
        {
            painter->drawLine(_private->_featurePts[iCnt], _private->_featurePts[iCnt + 1]);
        }

        painter->restore();
    }

    void IndicateLineItem::setFromGraphicsItem(GraphicsItem * item)
    {
        _private->_from = item;
        _private->updateFeaturePoints();
    }

    Graphics::GraphicsItem * IndicateLineItem::fromGraphicsItem() const
    {
        return _private->_from;
    }

    void IndicateLineItem::setCursorPos(QPointF pos)
    {
        _private->_cursorPt = pos.toPoint();
        _private->updateFeaturePoints();
        prepareGeometryChange();
        _private->updateBoundingBox();
        update();
    }

}