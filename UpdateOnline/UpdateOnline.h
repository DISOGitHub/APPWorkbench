/**
 *
 * @file      UpdateOnline.h
 * @brief     Frame app 's components update on line entrance
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 10:03
 *
 */

#pragma once
#include "UpdateOnlineAPI.h"
#include <QString>

namespace UpdateOnline
{
    /**
     * @brief     Entrance of update on line function
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-29 10:07
     */
    class UPDATE_ONLINE_API UpdateTool
    {
    public:

        /**
         * @brief:    set the operator to use update component packages on line
         * @param:    const QString & name: the name of the update operator
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:08
         */
        static void setUpdateOperator(const QString & name);

        /**
         * @brief:    Execute update process
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 10:09
         */
        static void updateOperation();

    protected:
        /**
         * @brief     Default use update online operator name
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 11:28
         */
        static QString _defaultOperName;
    };
}