/**
 *
 * @file      OperBottomWidget.h
 * @brief     Operator Of Bottom Widget. Log. Expand. Retract.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 17:16
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/MultiEventOperator.h"

namespace GUI
{
    class WidgetContainer;
    class OutputWidget;
}

namespace EventOper
{
    /**
     * @brief     Operator Of Bottom Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-4 17:21
     */
    class OperBottomWidget : public MultiEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperBottomWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:21
         */
        OperBottomWidget();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:21
         */
        ~OperBottomWidget();

        /**
         * @brief     prepare inner functions
         * @return    bool . prepare is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:22
         */
        virtual bool prepareArgs();

    protected:

        /**
         * @brief     add log
         * @return    bool . add log success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:22
         */
        virtual bool Log();

        /**
         * @brief     expand bottom widget
         * @return    bool . expand bottom widget is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:22
         */
        virtual bool Expand();

        /**
         * @brief     retract bottom widget
         * @return    bool . execute is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:23
         */
        virtual bool Retract();

    protected:
        /**
         * @brief     bottom widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 17:33
         */
        GUI::WidgetContainer * _bottom{};

        /**
         * @brief     output widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 17:59
         */
        GUI::OutputWidget * _output{};
    };
    Register2FITKOperatorRepo(Log, OperBottomWidget);
    Register2FITKOperatorRepo(Expand, OperBottomWidget);
    Register2FITKOperatorRepo(Retract, OperBottomWidget);
}