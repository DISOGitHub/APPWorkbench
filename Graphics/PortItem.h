/**
 *
 * @file      PortItem.h
 * @brief     Graphic Item 's Port Part. In Line Mode. While Mouse Nearby. Part Show and Can Select
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 10:09
 *
 */

#pragma once
#include <QGraphicsObject>
#include <QPen>
#include <QBrush>
#include "Define.h"

namespace Graphics
{
    class PortItemPrivater;
    /**
     * @brief     Graphic Item 's Port Part
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-31 10:11
     */
    class PortItem : public QGraphicsObject
    {
        Q_OBJECT
            Q_PROPERTY(int size READ size WRITE setSize)
            Q_PROPERTY(QPen framePen READ framePen WRITE setFramePen)
            Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
    public:
        /**
         * @brief     Constructor
         * @param     QGraphicsObject * parent Graphic Item
         * @return    PortItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:11
         */
        explicit PortItem(QGraphicsObject * parent);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:12
         */
        virtual ~PortItem();

        /**
         * @brief     get port edge length
         * @return    int. edge length
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:54
         */
        int size() const;

        /**
         * @brief     set port edge length
         * @param     int size. edge length
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:55
         */
        void setSize(int size);

        /**
         * @brief     get port draw frame pen
         * @return    QPen. draw frame pen
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:55
         */
        QPen framePen() const;

        /**
         * @brief     set port draw frame pen
         * @param     QPen pen. draw frame pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:56
         */
        void setFramePen(QPen pen);

        /**
         * @brief     get port fill graphics brush
         * @return    QBrush. fill graphics brush
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:57
         */
        QBrush selectedBrush() const;

        /**
         * @brief     set port fill graphics brush
         * @param     QBrush brush
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:57
         */
        void setSelectedBrush(QBrush brush);

        /**
         * @brief     set port state. to change input or output port state
         * @param     PortType type . port type .
         * @param     PortState state . port state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:40
         */
        void setPortState(PortType type, PortState state);

        /**
         * @brief     get port state
         * @param     PortType type. port type
         * @return    PortState . port state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:41
         */
        PortState portState(PortType type) const;

        /**
         * @brief     get bounding rect of port part
         * @return    QRectF bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:41
         */
        QRectF boundingRect() const override;

        /**
         * @brief
         * @param     QPainter * painter
         * @param     const QStyleOptionGraphicsItem * option
         * @param     QWidget * widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 10:43
         */
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief     get port item output port center point position. in scene coordinate
         * @return    QPoint . output port center point position
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 11:05
         */
        QPoint outputPortPos();

        /**
         * @brief     get port item input port center point position. in scene coordinate
         * @return    QPoint
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 11:06
         */
        QPoint inputPortPos();

    private:
        /**
         * @brief     private part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 10:44
         */
        PortItemPrivater * _private{};

        /**
         * @brief     draw port.
         * @param     QPainter * painter. painter
         * @param     PortState state. port state
         * @param     QRectF rect. rect zone . stand for input or output
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 12:08
         */
        void drawPort(QPainter *painter, PortState state, QRectF rect);
    };
}