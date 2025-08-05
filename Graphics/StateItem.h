/**
 * @brief     Component App Item 's Graphics Item 's State Part
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-26 10:14
 */

#pragma once
#include <QGraphicsObject>

namespace Graphics
{
    /**
     * @brief     Graphics Item State
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-26 10:19
     */
    enum ComponentInputState
    {
        /**
         * @brief     Normal State. Nothing Display
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:18
         */
        State_Normal = 0,

        /**
         * @brief     Input Changed State. Display State
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:18
         */
        State_Input_Changed = 1,
    };

    /**
     * @brief     Graphics Item State Item Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-26 10:21
     */
    class StateItem : public QGraphicsObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. graphics item
         * @return    StateItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:22
         */
        explicit StateItem(QGraphicsItem *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:22
         */
        ~StateItem();

        /**
         * @brief     set graphics item state
         * @param     state[i]. graphics item state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:24
         */
        void setGraphicsItemState(ComponentInputState state);

        /**
         * @brief     get graphics item state
         * @return    Graphics::GraphicsItemState
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:24
         */
        ComponentInputState graphicsItemState() const { return _state; }

        /**
         * @brief     get graphics item 's bounding rect
         * @return    QRectF . graphics item 's bounding rect
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:24
         */
        virtual QRectF boundingRect() const override;

        /**
         * @brief     state item paint
         * @param     painter[i]. painter
         * @param     option[i]. no used
         * @param     widget[i]. no used
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:25
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

    protected:

        /**
         * @brief     load svg format image to draw
         * @param     rc[i]. resource
         * @return    QByteArray . resource byte array
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 10:34
         */
        QByteArray loadSvgResource(const QString & rc);

        /**
         * @brief     Graphics Item State
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:20
         */
        ComponentInputState _state{ State_Normal };

        /**
         * @brief     State_Input_Changed used svg file byte array
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:36
         */
        QByteArray _inputChangedResource;
    };
}