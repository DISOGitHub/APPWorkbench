/**
 *
 * @file      CalculateArrowPath.h
 * @brief     Calculate Arrow Image Path.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 14:42
 *
 */
#pragma 
#include <QRect>
#include <QPoint>
#include <QPainterPath>
#include "Define.h"

namespace Graphics
{
    /**
     * @brief     Class to calculate arrow path
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:43
     */
    class CalculateArrowPath
    {
    public:
        /**
         * @brief     constructor
         * @return    CalculateArrowPath object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:43
         */
        CalculateArrowPath();


        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:43
         */
        ~CalculateArrowPath();

        /**
         * @brief     calculate arrow path.
         * @param     vertex[i]. the vertex of arrow
         * @param     zone[i]. the rect of arrow
         * @param     direction[i]. the direction of arrow
         * @return    QList<QPoint> . arrow path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:44
         */
        QList<QPoint> arrowPath(QPoint vertext, QSize zone, Direction direction = Right);
    };
}

