/**
 *
 * @file      NameItem.h
 * @brief     Graphics Item 's Name Part
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-2 16:04
 *
 */

#pragma once
#include <QGraphicsObject>

namespace Graphics
{
    class NameItemPrivater;
    /**
     * @brief     Draw Graphics Item 's Name Part Item
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-2 16:04
     */
    class NameItem : public QGraphicsObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     name[i]. item 's name
         * @param     parent[i]. item 's parent. graphics item
         * @return    NameItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:04
         */
        explicit NameItem(const QString & name, QGraphicsItem * parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:05
         */
        ~NameItem();

        /**
         * @brief     get border width of name item
         * @return    int . border width
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:05
         */
        int borderWidth();

        /**
         * @brief     get top border width of name item
         * @return    int . top border width
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:09
         */
        int topBorderHeight();

        /**
         * @brief     get name item bottom 's position to the graphics item center
         * @return    int . bottom offset
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:06
         */
        int bottomOffset();

        /**
         * @brief     to paint name item
         * @param     painter[i]. painter
         * @param     option[i]. unused
         * @param     widget[]. unused
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:07
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief     get name item 's bounding rect
         * @return    QRectF . bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 16:07
         */
        virtual QRectF boundingRect() const override;

    private:
        /**
         * @brief     private part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 16:08
         */
        NameItemPrivater * _privater{};
    };
}