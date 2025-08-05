/**
 *
 * @file      CalculateNotifyPoint.h
 * @brief     Calculate Line 's Notify Point. On Polyline Center
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-5 17:08
 *
 */
#pragma once
#include <QPoint>
#include <QList>

namespace Graphics
{
    /**
     * @brief     Calculate Line 's Notify Point. On Polyline Center
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 17:11
     */
    class CalculateNotifyPoint
    {
    public:

        /**
         * @brief     constructor
         * @return    CalculateNotifyPoint object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 17:11
         */
        CalculateNotifyPoint();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 17:11
         */
        ~CalculateNotifyPoint();

        /**
         * @brief     calculate notify point
         * @param     featurePts[i] . based feature points
         * @return    QPoint . notify point
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 17:11
         */
        QPoint notifyPoint(QList<QPoint> featurePts);
    };
}