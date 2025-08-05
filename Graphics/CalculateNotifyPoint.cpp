#include "CalculateNotifyPoint.h"
#include <QLine>
#include <cmath>

namespace Graphics
{

    CalculateNotifyPoint::CalculateNotifyPoint()
    {

    }

    CalculateNotifyPoint::~CalculateNotifyPoint()
    {

    }

    QPoint CalculateNotifyPoint::notifyPoint(QList<QPoint> featurePts)
    {
        /// calculate length
        int segmentNum = featurePts.size() - 1;
        int length = 0;
        QList<int> segmentLens;
        for (int iSeg = 0; iSeg < segmentNum; ++iSeg)
        {
            int dx = featurePts[iSeg].x() - featurePts[iSeg + 1].x();
            int dy = featurePts[iSeg].y() - featurePts[iSeg + 1].y();
            int segmentLen = sqrt(dx * dx + dy * dy);
            segmentLens.append(segmentLen);
            length += segmentLen;
        }

        /// calculate notify point
        int half = length / 2;
        int offset = 0;
        int segIndex = 0;
        for (int segmentLen : segmentLens)
        {
            offset += segmentLen;
            if (offset > half)
            {
                break;
            }
            segIndex += 1;
        }

        int segOffset = half;
        for (int iCnt = 0; iCnt < segIndex; ++iCnt)
            segOffset -= segmentLens[iCnt];

        QPoint pt1 = featurePts[segIndex];
        QPoint pt2 = featurePts[segIndex + 1];

        QPoint notify;
        if (pt1.x() == pt2.x())
        {
            notify.setX(pt1.x());
            notify.setY(pt2.y() > pt1.y() ? pt1.y() + segOffset : pt1.y() - segOffset);
        }
        else if (pt1.y() == pt2.y())
        {
            notify.setX(pt2.x() > pt1.x() ? pt1.x() + segOffset : pt1.x() - segOffset);
            notify.setY(pt1.y());
        }
        return notify;
    }

}