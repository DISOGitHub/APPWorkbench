#pragma once
#include <QString>
#include <QList>

/**
 * @brief     ini format file description
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 13:28
 */
struct IniFileDesc
{
    /**
     * @brief     file path
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:29
     */
    QString path;
    /**
     * @brief     file name
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:29
     */
    QString name;
    /**
     * @brief     file description
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:29
     */
    QString desc;
    /**
     * @brief     file type
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:29
     */
    QString type;
    /**
     * @brief     file suffix
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:30
     */
    QString suffix;
};

/// alias
using IniInputFiles = QList<IniFileDesc>;
using IniOutputFiles = QList<IniFileDesc>;

