/**
 *
 * @file      OperCanvasMode.h
 * @brief     Operator For Canvas Work Mode. Support Select Graphics Object Mode and Line Mode.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 8:59
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/MultiEventOperator.h"

namespace EventOper
{
    class OperCanvasMode : public MultiEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief:    constructor
         * @return:   operator canvas mode
         * @author:   maguiwa (maguiwa520@163.com)
         * @date:     2024-8-30 20:33
         */
        OperCanvasMode();

        /**
         * @brief:    destructor
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 20:33
         */
        ~OperCanvasMode();

        /**
        * @brief:    prepare event and function pair. implementation
        * @return:   bool : prepare success or not
        * @author:   maguiwa (maguiwa520@163.com)
        * @date:     2024-8-30 20:33
        */
        virtual bool prepareArgs();

    protected:

        /**
         * @brief:    set canvas select mode
         * @return:   bool : success executed or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 20:36
         */
        virtual bool setSelectMode();

        /**
         * @brief:    set canvas line mode
         * @return:   bool : success executed or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 20:37
         */
        virtual bool setLineMode();

    };
    Register2FITKOperatorRepo(Selected, OperCanvasMode);
    Register2FITKOperatorRepo(Line, OperCanvasMode);
}