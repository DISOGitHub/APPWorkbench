/**
 *
 * @file      IniFileWriter.h
 * @brief     tool to write ini file. to run component. solve or open history project
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-30 13:17
 *
 */
#pragma once
#include <QString>
#include <QList>
#include "Define.h"

namespace Data
{
    class SimulationAppInput;
    class SimulationAppOutput;
    class ComponentAppData;
}

namespace EventHelper
{
    /**
     * @brief     class to write ini file for component run. solve or open history project
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-30 13:19
     */
    class IniFileWriter
    {
    public:
        /**
         * @brief     constructor
         * @param     filePath[i]. ini file path
         * @return    IniFileWriter object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:34
         */
        IniFileWriter(const QString & filePath = QString());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:35
         */
        ~IniFileWriter();

        /**
         * @brief     write ini file
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:35
         */
        void write();

        /**
         * @brief     set if open project mode. open project mode write open_project.ini . else write project.ini
         * @param     openProject[i]. open project mode
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:35
         */
        void setOpenProjectMode(bool openProject) { _openProject = openProject; }

        /**
         * @brief     set ini file path
         * @param     filePath[i]. ini file path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:36
         */
        void setFilePath(const QString & filePath) { _filePath = filePath; }

        /**
         * @brief     set ini file contents : output base path value
         * @param     basePath[i]. output base path value
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:37
         */
        void setBasePath(const QString & basePath);

        /**
         * @brief     set input files
         * @param     files[i]. input files info
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:37
         */
        void setInputFiles(IniInputFiles files);

    protected:
        /**
         * @brief     open project mode
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:38
         */
        bool _openProject{ false };

        /**
         * @brief     ini file path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:38
         */
        QString _filePath{};

        /**
         * @brief     ini file contents part: output base path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:38
         */
        QString _outputBasePath{};

        /**
         * @brief     ini file input files info
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 13:38
         */
        IniInputFiles _inputFiles;
    };
}