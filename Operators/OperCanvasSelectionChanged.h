/**
 *
 * @file      OperCanvasSelectionChanged.h
 * @brief     Canvas Selection Changed. Use CanvasLayoutHelperWidget to position GraphicsItem
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 10:35
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/EventOperator.h"
#include "CanvasLayoutHelperWidget.h"

namespace EventOper
{
    /**
     * @brief     Canvas Selection Items Changed Operator
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 10:36
     */
    class OperCanvasSelectionChanged : public EventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperCanvasSelectionChanged object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:36
         */
        OperCanvasSelectionChanged();

        /**
         * @brief
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:37
         */
        ~OperCanvasSelectionChanged();


        /**
         * @brief     canvas selection changed event triggered.
         * @return    bool . execute success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:37
         */
        virtual bool triggered() override;

    private:
        /**
         * @brief     canvas layout helper widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 11:16
         */
        EventHelper::CanvasLayoutHelperWidget * _helper{};
    };
    Register2FITKOperatorRepo(CanvasSelectionChanged, OperCanvasSelectionChanged);
}