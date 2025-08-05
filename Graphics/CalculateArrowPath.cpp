#include "CalculateArrowPath.h"

namespace Graphics
{

    CalculateArrowPath::CalculateArrowPath()
    {

    }

    CalculateArrowPath::~CalculateArrowPath()
    {

    }

    QList<QPoint> CalculateArrowPath::arrowPath(QPoint vertex, QSize zone, Direction direction /*= Right*/)
    {
        QPoint pt1, pt2, pt3;

        if (direction == Right)
        {
            pt1 = QPoint(vertex.x() - zone.width(), vertex.y() - zone.height() / 2);
            pt2 = QPoint(vertex.x() - zone.width() / 2, vertex.y());
            pt3 = QPoint(vertex.x() - zone.width(), vertex.y() + zone.height() / 2);
        }
        else if (direction == Left)
        {
            pt1 = QPoint(vertex.x() + zone.width(), vertex.y() - zone.height() / 2);
            pt2 = QPoint(vertex.x() + zone.width() / 2, vertex.y());
            pt3 = QPoint(vertex.x() + zone.width(), vertex.y() + zone.height() / 2);
        }
        else if (direction == Up)
        {
            pt1 = QPoint(vertex.x() + zone.width() / 2, vertex.y() - zone.height());
            pt2 = QPoint(vertex.x(), vertex.y() - zone.height() / 2);
            pt3 = QPoint(vertex.x() - zone.width() / 2, vertex.y() - zone.height());
        }
        else if (direction == Down)
        {
            pt1 = QPoint(vertex.x() - zone.width() / 2, vertex.y() + zone.height());
            pt2 = QPoint(vertex.x(), vertex.y() + zone.height() / 2);
            pt3 = QPoint(vertex.x() + zone.width() / 2, vertex.y() + zone.height());
        }

        QPainterPath path;
        QList<QPoint> pts{ vertex,pt1,pt2,pt3,vertex };
        return pts;
    }

}