#pragma once

#include "FITK_Kernel/FITKCore/FITKAbstractOperator.h"
#include "OperatorsInterfaceAPI.h"
#include <QGraphicsItem>

namespace EventOper
{
    class OPERATORS_INTERFACE_API ComponentEventOperator : public Core::FITKAbstractOperator
    {
        Q_OBJECT

    public:
        /**
         * @brief:    constructor
         * @return:   component event operator object
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:28
         */
        explicit ComponentEventOperator();

        /**
         * @brief:    destructor
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:28
         */
        virtual ~ComponentEventOperator();

        /**
         * @brief:    user double clicked graphics item instance
         * @param:    QGraphicsObject * item : clicked item
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:24
         */
        virtual void doubleClicked(QGraphicsObject * item) = 0;

        /**
         * @brief:    user clicked graphics item 's open project menu item
         * @param:    QGraphicsObject * item : current graphics item
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:25
         */
        virtual void openProject(QGraphicsObject * item) = 0;

        /**
         * @brief:    user clicked graphics item 's solve project menu item
         * @param:    QGraphicsObject * item : current graphics item
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:26
         */
        virtual void run(QGraphicsObject * item) = 0;

        /**
         * @brief     user right button clicked component item
         * @param     item[i]. component item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 16:17
         */
        virtual bool rightButtonMenu(QGraphicsObject * item) = 0;
    };
}