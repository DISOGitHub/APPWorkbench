#pragma once
#include "FITK_Kernel/FITKCore/FITKAbstractOperator.h"
#include "OperatorsInterfaceAPI.h"

namespace EventOper
{
    class OPERATORS_INTERFACE_API EventOperator : public Core::FITKAbstractOperator
    {
        Q_OBJECT

    public:
        /**
         * @brief:    constructor
         * @return:   event operator object
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 8:49
         */
        explicit EventOperator();

        /**
         * @brief:    destructor
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 8:50
         */
        virtual ~EventOperator();

        /**
         * @brief     event has triggered
         * @return    bool . execute success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:28
         */
        virtual bool triggered();


    };

}