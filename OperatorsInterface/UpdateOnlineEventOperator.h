/**
 *
 * @file      UpdateOnlineEventOperator.h
 * @brief     Define the interface of the update on line model. No implement.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 10:20
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKAbstractOperator.h"
#include "OperatorsInterfaceAPI.h"

namespace EventOper
{
    /**
     * @brief     Interface of the update online model
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-29 10:21
     */
    class OPERATORS_INTERFACE_API UpdateOnlineEventOperator : public Core::FITKAbstractOperator
    {
        Q_OBJECT

    public:
        explicit UpdateOnlineEventOperator();
        virtual ~UpdateOnlineEventOperator() = 0;

        /**
         * @brief:    Check for updates
         * @param:    QString & dscription: if exists . This is dscription of updates
         * @return:   bool : exist or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:21
         */
        virtual bool checkForUpdates(QString & dscription) = 0;

        /**
         * @brief:    Download updates
         * @return:   bool : download success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:25
         */
        virtual bool downLoadUpdates() = 0;

        /**
         * @brief:    Operate downloads. check and unzip
         * @return:   bool operate success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:30
         */
        virtual bool operateDownloads() = 0;

        /**
         * @brief:    Update local components. replace apps and app component description files
         * @return:   bool update success or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:33
         */
        virtual bool updateComponents() = 0;

        /**
         * @brief:    backup old local components. contains apps and app component description files
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:35
         */
        virtual void backupComponents() = 0;

        /**
         * @brief:    restore backup local component while update components error occur
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:38
         */
        virtual void restoreComponents() = 0;
    };

}