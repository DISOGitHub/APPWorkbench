#include <LogData.h>
#include <QDateTime>

#define _LOG_TYPE_STRS_ QStringList{"[info]","[warning]","[error]"}

namespace Data
{

    LogData::LogData(const QString & msg, LogType type /*= Log_Normal*/)
        : _msg(msg)
        , _type(type)
    {

    }

    QString LogData::log2String()
    {
        QString logTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
        QString logType = _LOG_TYPE_STRS_[_type];
        QString log = logTime + " " + logType + " " + _msg;
        return log;
    }

}