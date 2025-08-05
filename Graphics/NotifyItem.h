/**
 *
 * @file      NotifyItem.h
 * @brief     While Line GraphicsLine. Notify Warning and Errors
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 16:35
 *
 */

#pragma once
#include <QGraphicsObject>
#include "Define.h"

namespace Graphics
{
    class NotifyItemPrivate;
    /**
     * @brief     Notify Line State.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 16:36
     */
    class NotifyItem : public QGraphicsObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. notify item 's parent item
         * @return    NotifyItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:37
         */
        explicit NotifyItem(QGraphicsItem *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:37
         */
        ~NotifyItem();

        /**
         * @brief     Set Notify State and Message
         * @param     state[i]. Notify State
         * @param     msg[i]. Notify Message
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:51
         */
        void setNotifyState(NotifyState state, const QString & msg);

        /**
         * @brief     get bounding rect of notify item
         * @return    QRectF . bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:56
         */
        virtual QRectF boundingRect() const override;

        /**
         * @brief     paint notify item
         * @param     painter[i]. painter
         * @param     option[i]. not used
         * @param     widget[i]. not used
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:57
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief     user left button double clicked
         * @param     event[i]. left button double click event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 16:57
         */
        virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    protected:
        /**
         * @brief     load svg resource
         * @param     svg[i]. svg resource
         * @return    QByteArray . svg resource contents
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 19:22
         */
        QByteArray loadSvgResource(const QString & svg);

    private:
        /**
         * @brief     private part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 16:56
         */
        NotifyItemPrivate * _private{};
    };
}