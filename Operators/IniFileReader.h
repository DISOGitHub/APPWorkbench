/**
 *
 * @file      IniFileReader.h
 * @brief     tool to read ini file. to help prepare next component ini file
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-12 14:41
 *
 */
#pragma once
#include <QString>
#include <QList>
#include "Define.h"

namespace EventHelper
{
    /**
     * @brief     class to read ini file to help prepare next component ini file
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-12 14:42
     */
    class IniFileReader
    {
    public:
        /**
         * @brief     constructor
         * @param     filePath[i]. ini file path
         * @return    IniFileReader object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:30
         */
        IniFileReader(const QString & filePath);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:30
         */
        ~IniFileReader();

        /**
         * @brief     read ini file
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:30
         */
        void read();

        /**
         * @brief     get read out output files
         * @return    IniOutputFiles
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:31
         */
        IniOutputFiles getOutputFiles();

        /**
         * @brief     get read out folder info in output files
         * @return    IniOutputFiles . read out files info
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:31
         */
        IniOutputFiles getFolderTypeOutputFiles();

        /**
         * @brief     get read out file info in output files
         * @return    IniOutputFiles . read out files info
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:31
         */
        IniOutputFiles getFileTypeOutputFiles();

    protected:
        /**
         * @brief     ini file path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:32
         */
        QString _filePath;

        /**
         * @brief     read out ini file output files info
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:33
         */
        IniOutputFiles _outputFiles;
    };
}