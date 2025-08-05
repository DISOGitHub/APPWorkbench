/**
 *
 * @file      LineItem.h
 * @brief     Line Item. Describe Relation Between Two Graphics Item
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 13:00
 *
 */
#pragma once
#include "GraphicsAPI.h"
#include <QGraphicsObject>
#include <QPen>
#include <QSize>
#include <QBrush>
#include "DataCenter/LineData.h"

namespace Graphics
{
    class GraphicsItem;
    class NotifyItem;
    class LineItemPrivate;
    /**
     * @brief     Line Item .
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 13:01
     */
    class GRAPHICS_API  LineItem : public QGraphicsObject
    {
        Q_OBJECT
            Q_PROPERTY(QPen pen READ pen WRITE setPen)
            Q_PROPERTY(GraphicsItem * fromGraphicsItem READ fromGraphicsItem() WRITE setFromGraphicsItem)
            Q_PROPERTY(GraphicsItem * toGraphicsItem READ toGraphicsItem WRITE setToGraphicsItem)
            Q_PROPERTY(int toleranceDistance READ toleranceDistance WRITE setToleranceDistance)
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent item. default is nullptr
         * @return    LineItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:01
         */
        explicit LineItem(QGraphicsItem *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:02
         */
        ~LineItem();

        /**
         * @brief     set from graphics item
         * @param     item[i]. from graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:03
         */
        void setFromGraphicsItem(GraphicsItem * item);

        /**
         * @brief     get from graphics item
         * @return    Graphics::GraphicsItem * . from graphics item
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:03
         */
        GraphicsItem * fromGraphicsItem() const;

        /**
         * @brief     set to graphics item
         * @param     item[i]
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:04
         */
        void setToGraphicsItem(GraphicsItem * item);

        /**
         * @brief     get to graphics item
         * @return    Graphics::GraphicsItem * . to graphics item
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:04
         */
        GraphicsItem * toGraphicsItem() const;

        /**
         * @brief     used for test whether user select line by clicked scene pos
         * @param     pos[i] . user clicked scene pos
         * @return    bool . whether selected line
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:04
         */
        virtual bool selectTest(QPointF pos);

        /**
         * @brief     used for line item selection
         * @return    QPainterPath . selection path. if need must expand bounding rect.
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:17
         */
        QPainterPath shape() const override;

        /**
         * @brief     get line 's pen
         * @return    QPen. line 's pen
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:05
         */
        QPen pen() const;

        /**
         * @brief     set line 's pen
         * @param     pen[i]. line 's pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:06
         */
        void setPen(QPen pen);

        /**
         * @brief     line item bounding rect. dynamic by from and to item 's pos
         * @return    QRectF
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:06
         */
        QRectF boundingRect() const override;

        /**
         * @brief     draw line item
         * @param     painter[i]. painter
         * @param     option[i]. not used
         * @param     widget[i]. not used
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:07
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief     Tolerance Distance Of Line. Used For Select Line Item
         * @return    int . Tolerance Distance
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:25
         */
        int toleranceDistance() const;

        /**
         * @brief     Set Tolerance Distance Of Line. Used For Select Line Item
         * @param     distance[i]. Tolerance Distance
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 14:25
         */
        void setToleranceDistance(int distance);

    private:

        /**
         * @brief     while set from or to item. update line
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 13:29
         */
        void updateLine();

    private:
        /**
         * @brief     private part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 13:07
         */
        LineItemPrivate * _private{};

    };
}
