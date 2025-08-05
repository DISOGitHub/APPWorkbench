/**
 *
 * @file      OperFileAction.h
 * @brief     Toolbar Project File And Description File Operator Action Triggered
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 9:03
 *
 */

#pragma once
#include "OperatorsInterface/MultiEventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"

namespace EventOper
{
    /**
     * @brief     Toolbar Project File And Description File Operator Action Triggered
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 9:06
     */
    class OperFileAction : public MultiEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperFileAction object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:06
         */
        OperFileAction();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:07
         */
        ~OperFileAction();

    protected:
        /**
         * @brief     prepare file action arguments
         * @return    bool . is prepare ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:12
         */
        virtual bool prepareArgs() override;

        /**
         * @brief     open project or open app template action triggered
         * @param     type[i]. 0 as open app template. 1 as open project
         * @return    bool . is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 10:43
         */
        bool gotoProjectPage(int type);

        /**
         * @brief     save project
         * @return    bool . is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:15
         */
        bool saveProject();

        /**
         * @brief     save application template
         * @return    bool . is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:16
         */
        bool saveAppTemplate();
    };
    Register2FITKOperatorRepo(OpenProject, OperFileAction);
    Register2FITKOperatorRepo(OpenAppTemplate, OperFileAction);
    Register2FITKOperatorRepo(SaveProject, OperFileAction);
    Register2FITKOperatorRepo(SaveAppTemplate, OperFileAction);
}