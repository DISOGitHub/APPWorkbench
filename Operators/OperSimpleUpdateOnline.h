/**
 *
 * @file      OperSimpleUpdateOnline.h
 * @brief     simple implement of update on line event operator
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 10:59
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/UpdateOnlineEventOperator.h"

namespace EventOper
{
    /**
     * @brief     Implement of the update online model
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-29 11:02
     */
    class OperSimpleUpdateOnline : public UpdateOnlineEventOperator
    {
        Q_OBJECT
    public:
        OperSimpleUpdateOnline();
        virtual ~OperSimpleUpdateOnline();


        /**
         * @brief:    Check for updates
         * @param:    QString & dscription : if exists . This is dscription of updates
         * @return:   bool : exist or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:04
         */
        virtual bool checkForUpdates(QString & dscription);

        /**
         * @brief:    Download updates
         * @return:   bool : download success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:04
         */
        virtual bool downLoadUpdates();

        /**
         * @brief:    Operate downloads. check and unzip
         * @return:   bool : operate success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:04
         */
        virtual bool operateDownloads();

        /**
         * @brief:    Update local components. replace apps and app component description files
         * @return:   bool : update success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:05
         */
        virtual bool updateComponents();

        /**
         * @brief:    backup old local components. contains apps and app component description files
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:05
         */
        virtual void backupComponents();

        /**
         * @brief:    restore backup local component while update components error occur
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:05
         */
        virtual void restoreComponents();

    };
    Register2FITKOperatorRepo(SimpleUpdateOnline, OperSimpleUpdateOnline);
}