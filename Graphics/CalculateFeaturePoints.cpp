#include "CalculateFeaturePoints.h"
#include <cmath>

namespace Graphics
{

    CalculateFeaturePoints::CalculateFeaturePoints(QPoint from, QPoint to)
        : _from(from)
        , _to(to)
    {

    }

    CalculateFeaturePoints::~CalculateFeaturePoints()
    {

    }

    LineType CalculateFeaturePoints::lineType()
    {
        int disX = _to.x() - _from.x();
        if (disX > 0)
        {
            if (disX > _turningPointLength * 2)
                return Line_ZTurning_Type;
            else if (disX > _arrowSize.width() * 4)
                return Line_ZCenter_Type;
        }
        int disY = fabs(_to.y() - _from.y());
        if (disY > _itemBottomHeight + _itemTopHeight + _turningPointLength * 2)
            return Line_STurning_Type;
        else if (disY > _itemBottomHeight + _itemTopHeight + _arrowSize.height() * 2)
            return Line_SCenter_Type;
        else
            return Line_OClock_Type;
    }

    QList<QPoint> CalculateFeaturePoints::featurePoints()
    {
        _lineType = lineType();
        switch (_lineType)
        {
        case Line_ZTurning_Type:
            return zTurningFeaturePoints();
        case Line_ZCenter_Type:
            return zCenterFeaturePoints();
        case Line_STurning_Type:
            return sTurningFeaturePoints();
        case Line_SCenter_Type:
            return sCenterFeaturePoints();
        case Line_OClock_Type:
            return oClockFeaturePoints();
        default:
            break;
        }
    }

    LineType CalculateFeaturePoints::getLineType() const
    {
        return _lineType;
    }

    QList<QPoint> CalculateFeaturePoints::zTurningFeaturePoints()
    {
        QList<QPoint> pts;
        pts.append(_from);
        pts.append(QPoint(_from.x() + _turningPointLength, _from.y()));
        pts.append(QPoint(_from.x() + _turningPointLength, _to.y()));
        pts.append(_to);
        return pts;
    }

    QList<QPoint> CalculateFeaturePoints::zCenterFeaturePoints()
    {
        QList<QPoint> pts;
        auto xPos = (_from.x() + _to.x()) / 2;
        pts.append(_from);
        pts.append(QPoint(xPos, _from.y()));
        pts.append(QPoint(xPos, _to.y()));
        pts.append(_to);
        return pts;
    }

    QList<QPoint> CalculateFeaturePoints::sTurningFeaturePoints()
    {
        QList<QPoint> pts;
        pts.append(_from);
        pts.append(QPoint(_from.x() + _turningPointLength, _from.y()));
        if (_from.y() > _to.y())
        {
            pts.append(QPoint(_from.x() + _turningPointLength, _from.y() - _itemTopHeight - _turningPointLength));
            pts.append(QPoint(_to.x() - _turningPointLength, _from.y() - _itemTopHeight - _turningPointLength));
        }
        else
        {
            /// need update to consider name item
            pts.append(QPoint(_from.x() + _turningPointLength, _from.y() + _itemBottomHeight + _turningPointLength));
            pts.append(QPoint(_to.x() - _turningPointLength, _from.y() + _itemBottomHeight + _turningPointLength));
        }
        pts.append(QPoint(_to.x() - _turningPointLength, _to.y()));
        pts.append(_to);
        return pts;
    }

    QList<QPoint> CalculateFeaturePoints::sCenterFeaturePoints()
    {
        QList<QPoint> pts;
        pts.append(_from);
        pts.append(QPoint(_from.x() + _turningPointLength, _from.y()));

        int distanceY = fabs(_from.y() - _to.y());

        if (_from.y() > _to.y())
        {
            int centerY = _to.y() + _itemBottomHeight + (distanceY - _itemTopHeight - _itemBottomHeight) / 2;
            pts.append(QPoint(_from.x() + _turningPointLength, centerY));
            pts.append(QPoint(_to.x() - _turningPointLength, centerY));
        }
        else
        {
            int centerY = _from.y() + _itemBottomHeight + (distanceY - _itemTopHeight - _itemBottomHeight) / 2;
            pts.append(QPoint(_from.x() + _turningPointLength, centerY));
            pts.append(QPoint(_to.x() - _turningPointLength, centerY));
        }
        pts.append(QPoint(_to.x() - _turningPointLength, _to.y()));
        pts.append(_to);
        return pts;
    }

    QList<QPoint> CalculateFeaturePoints::oClockFeaturePoints()
    {
        QList<QPoint> pts;
        QPoint pt1, pt2, pt3, pt4;
        if (_from.y() > _to.y())
        {
            if (_from.y() > _to.y())
            {
                /**
                *  FromItem at ToItem 's Bottom Right . no need to consider ToItem 's right part
                *  just consider FromItem 's right part
                */
                pt1 = QPoint(_from.x() + _turningPointLength, _from.y());
                pt2 = QPoint(pt1.x(), _from.y() + _itemBottomHeight + _turningPointLength);
                pt3 = QPoint(_to.x() - _turningPointLength, pt2.y());
                pt4 = QPoint(pt3.x(), _to.y());
            }
            else
            {
                /**
                *  FromItem at ToItem 's Bottom Left . no need to consider FromItem 's right part
                *  just consider ToItem 's right part
                */
                pt1 = QPoint(_from.x() + _turningPointLength, _from.y());
                pt2 = QPoint(pt1.x(), _from.y() + _itemBottomHeight + _turningPointLength);
                pt3 = QPoint(_from.x() - _turningPointLength, pt2.y());
                pt4 = QPoint(pt3.x(), _to.y());
            }
        }
        else
        {
            if (_from.x() > _to.x())
            {
                /**
                *  FromItem at ToItem 's Top Right . no need to consider ToItem 's right part
                *  just consider FromItem 's right part.
                */
                pt1 = QPoint(_from.x() + _turningPointLength, _from.y());
                pt2 = QPoint(pt1.x(), _to.y() + _itemBottomHeight + _turningPointLength);
                pt3 = QPoint(_to.x() - _turningPointLength, pt2.y());
                pt4 = QPoint(pt3.x(), _to.y());
            }
            else
            {
                /**
                *  FromItem at ToItem 's Top Left . no need to consider FromItem 's right part
                *  just consider ToItem 's right part.
                */
                pt1 = QPoint(_to.x() + _itemWidth + _turningPointLength, _from.y());
                pt2 = QPoint(pt1.x(), _to.y() + _itemBottomHeight + _turningPointLength);
                pt3 = QPoint(_to.x() - _turningPointLength, pt2.y());
                pt4 = QPoint(pt3.x(), _to.y());
            }
        }
        pts.append(_from);
        pts.append(pt1);
        pts.append(pt2);
        pts.append(pt3);
        pts.append(pt4);
        pts.append(_to);
        return pts;
    }
}