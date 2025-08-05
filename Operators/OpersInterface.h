/**
 *
 * @file      OpersGUIInterface.h
 * @brief     Use to load dynamic link library. No business.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 15:04
 *
 */

#pragma once
#include "OperatorsGUIAPI.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

namespace EventOper
{
    class OPERATOR_GUI_API OperatorsInterface : public AppFrame::FITKComponentInterface
    {
    public:
        explicit OperatorsInterface() = default;
        virtual ~OperatorsInterface() = default;

        /**
         * @brief:    initialize . no business
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 15:06
         */
        void init() override;

        /**
         * @brief:    Get component name. no business
         * @return:   QString
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 15:07
         */
        virtual QString getComponentName() override;

    };
}