#include "LineItem.h"
#include "CalculateFeaturePoints.h"
#include "CalculateIsPointNearLine2D.h"
#include "CalculateArrowPath.h"
#include "GraphicsScene.h"

#include "GraphicsItem.h"
#include "PortItem.h"
#include "NameItem.h"
#include "ArrowItem.h"
#include "NotifyItem.h"
#include "DataCenter/LineData.h"

#include <QPainter>
#include <QPainterPath>
#include <cmath>
#include "CalculateNotifyPoint.h"

namespace Graphics
{
    class LineItemPrivate
    {
    public:
        LineItemPrivate(LineItem * line)
            : _line(line)
        {
            _arrowPart = new ArrowItem(_line);
            _arrowPart->setArrowSize(_arrowSize);
            _notifyPart = new NotifyItem(_line);
            _notifyPart->setVisible(false);
        }

        /**
         * @brief     line graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:23
         */
        LineItem * _line{};

        /**
         * @brief     from graphics item of line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:16
         */
        GraphicsItem * _fromItem{};

        /**
         * @brief     to graphics item of line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:16
         */
        GraphicsItem * _toItem{};

        /**
         * @brief     line graphics item 's normal pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:18
         */
        QPen _penNormal{ QPen(QColor(25,56,199),2,Qt::SolidLine) };

        /**
         * @brief     line graphics item 's selected pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:22
         */
        QPen _penSelected{ QPen(QColor(255,56,199),2,Qt::SolidLine) };

        /**
         * @brief     line graphics item 's feature points. in item coordinate
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:20
         */
        QList<QPoint> _featurePoints;

        /**
         * @brief     bounding rect of graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:34
         */
        QRect _boundingRect;

        /**
         * @brief     the length of the first segment to turning point
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 17:21
         */
        int _turningPointLength{ 40 };

        /**
         * @brief     Tolerance distance of line item . used for select line item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 14:28
         */
        int _toleranceDistance{ 10 };

        /**
         * @brief     arrow size of line item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:05
         */
        QSize _arrowSize{ QSize(18,12) };

        /**
         * @brief     line type of line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 15:17
         */
        LineType _lineType;

        /**
         * @brief     arrow part of line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 16:20
         */
        ArrowItem * _arrowPart{};

        /**
         * @brief     line data state notify message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 18:31
         */
        QString _notify;

        /**
         * @brief     notify part of line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 17:03
         */
        NotifyItem * _notifyPart{};

        /**
         * @brief     update graphics item 's feature points
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:33
         */
        void updateFeaturePoints()
        {
            /// calculate feature points and line type
            CalculateFeaturePoints calculator(_fromItem->portPart()->outputPortPos(), _toItem->portPart()->inputPortPos());
            calculator.setGraphicsItemTopHeight(_fromItem->boundingRect().height() / 2);
            calculator.setGraphicsItemBottomHeight(_fromItem->boundingRect().height() / 2 + _fromItem->namePart()->topBorderHeight() + _fromItem->namePart()->boundingRect().height());
            calculator.setGraphicsItemWidth(_fromItem->boundingRect().height() / 2);
            calculator.setArrowSize(_arrowSize);
            calculator.setTurningPointLength(_turningPointLength);
            _featurePoints = calculator.featurePoints();
            _lineType = calculator.getLineType();
        }

        /**
         * @brief     update notify point
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 18:24
         */
        void updateNotifyPoint()
        {
            /// calculate notify point
            CalculateNotifyPoint calculator;
            QPoint pt = calculator.notifyPoint(_featurePoints);
            _notifyPart->setPos(pt + QPoint(-_notifyPart->boundingRect().width() / 2, -_notifyPart->boundingRect().height() / 2));
        }

        /**
         * @brief     update line item 's bounding box
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 15:09
         */
        void updateBoundingBox()
        {
            if (_featurePoints.isEmpty()) { return; }
            int xmin = _featurePoints.first().x(), xmax = xmin, ymin = _featurePoints.first().y(), ymax = ymin;

            for (QPoint pt : _featurePoints)
            {
                xmin = std::min(pt.x(), xmin);
                xmax = std::max(pt.x(), xmax);
                ymin = std::min(pt.y(), ymin);
                ymax = std::max(pt.y(), ymax);
            }

            _boundingRect = QRect(xmin, ymin, xmax - xmin, ymax - ymin);
        }

        void updateArrow()
        {
            _arrowPart->setPos(_featurePoints.last() + QPoint(-_arrowSize.width(), -_arrowSize.height() / 2));
        }
    };


    LineItem::LineItem(QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
        , _private(new LineItemPrivate(this))
    {
        setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        setAcceptHoverEvents(true);
        setToolTip(tr("This a Line"));
    }

    LineItem::~LineItem()
    {
        if (_private)
        {
            delete _private;
            _private = nullptr;
        }
    }

    void LineItem::setFromGraphicsItem(GraphicsItem * item)
    {
        _private->_fromItem = item;
        updateLine();
    }

    Graphics::GraphicsItem * LineItem::fromGraphicsItem() const
    {
        return _private->_fromItem;
    }

    void LineItem::setToGraphicsItem(GraphicsItem * item)
    {
        _private->_toItem = item;
        updateLine();
    }

    Graphics::GraphicsItem * LineItem::toGraphicsItem() const
    {
        return _private->_toItem;
    }

    bool LineItem::selectTest(QPointF pos)
    {
        /// in item coordinate. do select test
        QPoint clickedPos = (pos - this->pos()).toPoint();
        int lineNum = _private->_featurePoints.size() - 1;

        CalculateIsPointNearLine2D calculator;
        for (int iLine = 0; iLine < lineNum; ++iLine)
        {
            QPoint pt0 = _private->_featurePoints[iLine];
            QPoint pt1 = _private->_featurePoints[iLine + 1];

            bool isNear = calculator.isNear(pt0, pt1, clickedPos, false, _private->_toleranceDistance);
            if (isNear)
            {
                setSelected(true);
                return true;
            }
        }
        setSelected(false);
        return false;
    }

    QPainterPath LineItem::shape() const
    {
        QPainterPath path;
        int lineNum = _private->_featurePoints.size() - 1;
        for (int iLine = 0; iLine < lineNum; ++iLine)
        {
            QPoint pt0 = _private->_featurePoints[iLine];
            QPoint pt1 = _private->_featurePoints[iLine + 1];

            if (pt0.x() == pt1.x())
            {
                int y = std::min(pt0.y(), pt1.y());
                path.addRect(pt0.x() - _private->_toleranceDistance, y, _private->_toleranceDistance * 2, fabs(pt1.y() - pt0.y()));
            }
            else if (pt0.y() == pt1.y())
            {
                int x = std::min(pt0.x(), pt1.x());
                path.addRect(x, pt0.y() - _private->_toleranceDistance, fabs(pt1.x() - pt0.x()), _private->_toleranceDistance * 2);
            }
        }
        return path;
    }

    QPen LineItem::pen() const
    {
        return _private->_penNormal;
    }

    void LineItem::setPen(QPen pen)
    {
        _private->_penNormal = pen;
        update();
    }

    QRectF LineItem::boundingRect() const
    {
        return _private->_boundingRect.adjusted(0, -_private->_toleranceDistance, 0, _private->_toleranceDistance);
    }

    void LineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        /// has no item to draw in line item. all visualization implemented in children objects
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        GraphicsScene * sc = qobject_cast<GraphicsScene*>(scene());
        if (sc && isSelected())
        {
            if (sc->canvasMode() == Select_Mode)
            {
                /// need select part to change
            }
            else if (sc->canvasMode() == Line_Mode)
            {
                painter->setPen(_private->_penSelected);
                _private->_arrowPart->setPen(_private->_penSelected);
                _private->_arrowPart->setBrush(QBrush(_private->_penSelected.color()));
            }
        }
        else
        {
            painter->setPen(_private->_penNormal);
            _private->_arrowPart->setPen(_private->_penNormal);
            _private->_arrowPart->setBrush(QBrush(_private->_penNormal.color()));
        }

        QPoint orignPt = this->pos().toPoint();

        int ptNum = _private->_featurePoints.size();
        for (int iCnt = 1; iCnt < _private->_featurePoints.size(); ++iCnt)
        {
            /// line part from pt and to point . in scene coordinate
            QPoint fromPt = _private->_featurePoints[iCnt - 1] + orignPt;
            QPoint toPt = _private->_featurePoints[iCnt] + orignPt;

            painter->drawLine(fromPt, toPt);
        }

        painter->restore();
    }

    int LineItem::toleranceDistance() const
    {
        return _private->_toleranceDistance;
    }

    void LineItem::setToleranceDistance(int distance)
    {
        _private->_toleranceDistance = distance;
    }

    void LineItem::updateLine()
    {
        if (_private->_fromItem &&
            _private->_toItem)
        {
            _private->updateFeaturePoints();
            _private->updateNotifyPoint();
            prepareGeometryChange();
            _private->updateBoundingBox();
            _private->updateArrow();
        }
    }
}
