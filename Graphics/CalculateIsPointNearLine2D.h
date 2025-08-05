/**
 *
 * @file      CalculateIsPointNearLine2D.h
 * @brief     Calculate Point Distance Two Point Construct Line Distance. If Distance Less Than Tolerence . Near true returns
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 14:19
 *
 */
#pragma once
#include <QPoint>

namespace Graphics
{
    /**
     * @brief     Is Point Near Line Calculate Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 14:20
     */
    class CalculateIsPointNearLine2D
    {
    public:
        /**
         * @brief     Constructor
         * @return    CalculateIsPointNearLine2D Object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:21
         */
        CalculateIsPointNearLine2D();

        /**
         * @brief     Destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:21
         */
        ~CalculateIsPointNearLine2D();

        /**
         * @brief     Is Point Near Line
         * @param     linePt0[i]. Line 's First Pt
         * @param     linePt1[i]. Line 's Second Pt
         * @param     pt[i]. Pt
         * @param     extension[i]. Whether to Consider line extension
         * @param     tolerence[i]. tolerence Length
         * @return    bool . Is Point Near Line or Not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:21
         */
        bool isNear(QPoint linePt0, QPoint linePt1, QPoint pt, bool extension, double tolerence);
    };
}