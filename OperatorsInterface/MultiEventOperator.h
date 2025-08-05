/**
 *
 * @file      MultiEventOperator.h
 * @brief     Multi Event Operator. Used for Merging and Processing Similar Events.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 8:55
 *
 */

#pragma once

#include "OperatorsInterfaceAPI.h"
#include "EventOperator.h"

namespace GUI
{
    class MainWindow;
}

namespace EventOper
{
    /**
     * @brief     multi event operator base class .subclass need to implement prepareArgs function
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-31 8:56
     */
    class OPERATORS_INTERFACE_API MultiEventOperator : public EventOperator
    {
        Q_OBJECT

    public:
        /**
         * @brief     constructor
         * @return    multi event operator object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 8:52
         */
        explicit MultiEventOperator();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 8:53
         */
        virtual ~MultiEventOperator() = 0;


        /**
         * @brief:    get event sign
         * @return:   QString : event sign
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 19:25
         */
        QString getEventSign() const;

        /**
         * @brief:    set event sign
         * @param:    const QString & sign : event sign
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 19:25
         */
        void setEventSign(const QString & sign);

        /**
         * @brief     event has triggered
         * @return    bool : execute success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 19:10
         */
        virtual bool triggered();

    protected:

        /**
         * @brief     prepare event and function pair. subclass implementation
         * @return    bool : prepare success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 19:13
         */
        virtual bool prepareArgs();

    protected:

        /**
         * @brief     name signed event handler.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 19:15
         */
        QMap<QString, std::function<bool()>> _signEventHandler;

        /**
         * @brief     event sign.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 19:23
         */
        QString _eventSign;
    };

}