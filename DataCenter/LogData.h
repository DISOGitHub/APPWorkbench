/**
 *
 * @file      LogData.h
 * @brief     Log Data Defines And Log Data Manager
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 15:43
 *
 */
#pragma once
#include "DataCenterAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/MultiEventOperator.h"
#include <QGraphicsItem>

namespace Data
{
    enum LogType
    {
        /**
         * @brief     Normal Log
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:44
         */
        Log_Normal,
        /**
         * @brief     Warning Log
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:45
         */
        Log_Warning,
        /**
         * @brief     Error Log
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:45
         */
        Log_Error,
    };

    class DATA_CENTER_API LogData : public Core::FITKAbstractDataObject
    {
    public:
        explicit LogData(const QString & msg, LogType type = Log_Normal);
        ~LogData() = default;

        /**
         * @brief     convert log to QString format text
         * @return    QString . QString format log text
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:53
         */
        QString log2String();

        /**
         * @brief     get log type
         * @return    Data::LogType
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:49
         */
        LogType logType() const { return _type; }

        /**
         * @brief     set log type
         * @param     type[i]. log type
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:50
         */
        void setLogType(LogType type) { _type = type; }

        /**
         * @brief     get log message
         * @return    QString . log message
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:50
         */
        QString logMessage() const { return _msg; }

        /**
         * @brief     set log message
         * @param     msg[i]. log message
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:50
         */
        void setLogMessage(const QString & msg) { _msg = msg; }

    protected:
        /**
         * @brief     Log Message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:47
         */
        QString _msg;

        /**
         * @brief     Log Type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:47
         */
        LogType _type{ Log_Normal };
    };

    class DATA_CENTER_API LogDataManger : public Core::FITKAbstractDataManager<LogData>
    {
    public:
        explicit LogDataManger() = default;
        virtual ~LogDataManger() = default;

    };
}

#pragma once
#include "DataCenter/LogData.h"

#define LOG(msg) \
    { \
        auto oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::MultiEventOperator>("Log"); \
        if (oper) { \
        oper->setEventSign("Log"); \
        oper->setArgs("msg", Data::LogData(msg).log2String());  \
        oper->triggered(); \
        } \
    }

#define LOGW(msg) \
    { \
        auto oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::MultiEventOperator>("Log"); \
        if (oper) { \
        oper->setEventSign("Log"); \
        oper->setArgs("msg", Data::LogData(msg,Data::Log_Warning).log2String());  \
        oper->triggered(); \
        } \
    }

#define LOGE(msg) \
    { \
        auto oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::MultiEventOperator>("Log"); \
        if (oper) { \
        oper->setEventSign("Log"); \
        oper->setArgs("msg", Data::LogData(msg,Data::Log_Error).log2String());  \
        oper->triggered(); \
        } \
    }

#define ADDR(ptr) QString::number(reinterpret_cast<uintptr_t>(ptr), 16).toUpper()