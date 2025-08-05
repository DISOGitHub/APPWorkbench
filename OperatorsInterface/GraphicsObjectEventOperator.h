#pragma once
#include "OperatorsInterfaceAPI.h"
#include "EventOperator.h"
#include <QGraphicsItem>

namespace EventOper
{
    class OPERATORS_INTERFACE_API GraphicsObjectEventOperator : public EventOperator
    {
        Q_OBJECT

    public:
        /**
         * @brief     constructor
         * @return    graphics object event operator object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 19:11
         */
        explicit GraphicsObjectEventOperator();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 19:11
         */
        virtual ~GraphicsObjectEventOperator();

        /**
         * @brief     set event reference graphics objects
         * @param     item[i]. graphics items
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 15:29
         */
        void setGraphicsObject(QList<QGraphicsObject *> items);

    protected:
        /**
         * @brief     graphics object pointer
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 19:14
         */
        QList<QGraphicsObject *> _items{};
    };
}