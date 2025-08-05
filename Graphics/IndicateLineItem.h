/**
 *
 * @file      IndicateLineItem.h
 * @brief     Indicate Line Item. To Show Line Shape Before Set To Output
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 14:48
 *
 */
#pragma once
#include <QGraphicsObject>

namespace Graphics
{
    class GraphicsItem;
    class IndicateLineItemPrivate;
    /**
     * @brief     Indicate Line Graphics Item. Part of Graphics Item
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-31 14:51
     */
    class IndicateLineItem : public QGraphicsObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     QGraphicsItem * . parent poninter
         * @return    IndicateLineItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:51
         */
        explicit IndicateLineItem(QGraphicsItem *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:52
         */
        ~IndicateLineItem();

        /**
         * @brief     get indicate line item Dynamic bounding rect
         * @return    QRectF . bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:56
         */
        QRectF boundingRect() const override;

        /**
         * @brief     paint indicate line item
         * @param     QPainter * painter. painter
         * @param     const QStyleOptionGraphicsItem * option. not used
         * @param     QWidget * widget. not used
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:57
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief     set indicate line from graphics item.
         * @param     GraphicsItem * item. indicate line from graphics item.
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 15:01
         */
        void setFromGraphicsItem(GraphicsItem * item);

        /**
         * @brief     get indicate line from graphics item
         * @return    Graphics::GraphicsItem *
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 11:40
         */
        GraphicsItem * fromGraphicsItem() const;

        /**
         * @brief     set cursor position in scene coordinate
         * @param     QPointF pos. cursor position in item coordinate
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 15:02
         */
        void setCursorPos(QPointF pos);

    private:
        /**
         * @brief     private part pointer
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 14:54
         */
        IndicateLineItemPrivate * _private{};

    };
}