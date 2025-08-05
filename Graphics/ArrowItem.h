/**
 *
 * @file      ArrowItem.h
 * @brief     Line Item 's Arrow Part. Just Draw Line 's Arrow
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 15:44
 *
 */

#pragma once
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>

namespace Graphics
{
    /**
     * @brief     Arrow Item Class. Line 's Arrow part
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 15:46
     */
    class ArrowItem : public QGraphicsObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. item 's parent item
         * @return    ArrowItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:46
         */
        explicit ArrowItem(QGraphicsItem *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:47
         */
        virtual ~ArrowItem();

        /**
         * @brief     set arrow item 's rect size
         * @param     size[i]. rect size
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:51
         */
        void setArrowSize(QSize size);

        /**
         * @brief     Arrow Item 's bounding rect
         * @return    QRectF . bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:49
         */
        virtual QRectF boundingRect() const override;

        /**
         * @brief     set pen
         * @param     pen[i]. pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 9:43
         */
        void setPen(QPen pen);

        /**
         * @brief     set brush
         * @param     brush[i]. brush
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:01
         */
        void setBrush(QBrush brush);

        /**
         * @brief     paint arrow item
         * @param     painter[i]. painter
         * @param     option[i]. not used
         * @param     widget[i]. not used
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:50
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    protected:
        /**
         * @brief     arrow item 's rect area
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 15:52
         */
        QSize _arrowSize;

        /**
         * @brief     arrow item 's pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:00
         */
        QPen _pen{ QPen(QColor(25,56,199),2) };

        /**
         * @brief     arrow item 's brush
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 15:57
         */
        QBrush _brush{ QBrush(QColor(25,56,199)) };

        /**
         * @brief     arrow path of arrow item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 16:00
         */
        QList<QPoint> _arrowPath{};
    };
}