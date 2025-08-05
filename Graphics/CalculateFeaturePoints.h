/**
 * @brief     Input : From Point . To Point . Turning Point Length. Arrow Size.
 *            Output : Line Type . Feature Points
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 9:49
 */

#pragma once
#include <QPoint>
#include <QSize>
#include <QList>
#include "Define.h"

namespace Graphics
{
    /**
     * @brief     class to calculate line type and feature points
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 9:52
     */
    class CalculateFeaturePoints
    {
    public:
        /**
         * @brief     constructor
         * @param     from[i] line 's from point
         * @param     to[i] line 's to point
         * @return    CalculateFeaturePoints object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 9:52
         */
        CalculateFeaturePoints(QPoint from, QPoint to);


        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 9:53
         */
        ~CalculateFeaturePoints();

        /**
         * @brief     set graphics item 's top part height
         * @param     height[i]. top height
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:27
         */
        void setGraphicsItemTopHeight(int height) { _itemTopHeight = height; }

        /**
         * @brief     set graphics item 's bottom part height
         * @param     height[i]. bottom height
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:27
         */
        void setGraphicsItemBottomHeight(int height) { _itemBottomHeight = height; }

        /**
         * @brief     set graphics item 's width
         * @param     width[i]. graphics item 's width
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 17:19
         */
        void setGraphicsItemWidth(int width) { _itemWidth = width; }

        /**
         * @brief     set the line 's arrow size
         * @param     size[i]. line 's arrow size
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:01
         */
        void setArrowSize(QSize size) { _arrowSize = size; }

        /**
         * @brief     get the line 's arrow size
         * @return    QSize . line 's arrow size
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:02
         */
        QSize arrowSize() const { return _arrowSize; }

        /**
         * @brief     set line 's turning point length
         * @param     length[i]. line  's turning point length
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:02
         */
        void setTurningPointLength(int length) { _turningPointLength = length; }

        /**
         * @brief     get line 's turning point length
         * @return    int .line 's turning point length
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:03
         */
        int turningPointLength() const { return _turningPointLength; }

        /**
         * @brief     calculate line 's feature points
         * @return    QList<QPoint>. line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:04
         */
        QList<QPoint> featurePoints();

        /**
         * @brief     get  recent line type
         * @return    LineType . recent line type
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 15:15
         */
        LineType getLineType() const;

    protected:

        /**
         * @brief     calculate line type
         * @return    LineType . line type
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:03
         */
        LineType lineType();

        /**
         * @brief     calculate Line_ZTurning_Type line 's feature points
         * @return    QList<QPoint> . line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:04
         */
        QList<QPoint> zTurningFeaturePoints();

        /**
         * @brief     calculate Line_ZCenter_Type line 's feature points
         * @return    QList<QPoint>  . line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:05
         */
        QList<QPoint> zCenterFeaturePoints();

        /**
         * @brief     calculate Line_STurning_Type line 's feature points
         * @return    QList<QPoint>  . line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:05
         */
        QList<QPoint> sTurningFeaturePoints();

        /**
         * @brief     calculate Line_SCenter_Type line 's feature points
         * @return    QList<QPoint>  . line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:05
         */
        QList<QPoint> sCenterFeaturePoints();

        /**
         * @brief     calculate Line_OClock_Type line 's feature points
         * @return    QList<QPoint>  . line 's feature points
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 10:05
         */
        QList<QPoint> oClockFeaturePoints();

    private:
        /**
         * @brief     line 's from point
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 9:54
         */
        QPoint _from;

        /**
         * @brief     line 's to point
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 9:54
         */
        QPoint _to;

        /**
         * @brief     line 's arrow size
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 9:54
         */
        QSize _arrowSize{ QSize(14,10) };

        /**
         * @brief     graphics item 's top height
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 16:25
         */
        int _itemTopHeight{};

        /**
         * @brief     graphics item 's bottom height
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 16:26
         */
        int _itemBottomHeight{};

        /**
         * @brief     graphics item 's width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 17:09
         */
        int _itemWidth{};

        /**
         * @brief     line 's turning point length
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 9:54
         */
        int _turningPointLength{ 40 };

        /**
         * @brief     current line type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 10:20
         */
        LineType _lineType;
    };
}