/**
 *
 * @file      ProjectIO.h
 * @brief     Class To IO Workbench Project File
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-21 16:10
 *
 */
#pragma once
#include <QString>

namespace Data
{
    class SimulationAppData;
}

namespace GUI
{
    /**
     * @brief     Class To IO Workbench Project File
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-21 16:11
     */
    class ProjectIO
    {
    public:
        /**
         * @brief     constructor
         * @param     data[i]. simulation app data
         * @return    ProjectIO object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:11
         */
        ProjectIO(Data::SimulationAppData * data = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:12
         */
        ~ProjectIO();

        /**
         * @brief     set simulation app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 16:20
         */
        void setSimulationAppData(Data::SimulationAppData * data);

        /**
         * @brief     read workbench project file
         * @param     filePath[i] . workbench project file
         * @return    Data::SimulationAppData * . read out simulation app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:15
         */
        Data::SimulationAppData * read(const QString & filePath);

        /**
         * @brief     write workbench project file
         * @param     filePath[i] . workbench project file
         * @return    bool . is write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:16
         */
        virtual bool write(const QString & filePath);

    protected:

        /**
         * @brief     is set in simulation app data valid
         * @param     data[i]. simulation app data set in
         * @return    bool . is valid
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:28
         */
        bool isValid(Data::SimulationAppData * data);

        /**
         * @brief     ensure directory exists.
         * @param     path[i] . directory
         * @return    bool . is execute ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:45
         */
        bool ensureDirectoryExists(const QString & path);

        /**
         * @brief     simulation app data sett in
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 16:20
         */
        Data::SimulationAppData * _data{};
    };
}
