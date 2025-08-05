/**
 *
 * @file      SingleSimulationAppData.h
 * @brief     Single Component App Construct a Simulation App. We Call It Single Simulation App.
 *            In This Class Defined Single Simulation App Data. It With ComponentAppData  And
 *            SimulationAppData Feature.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-12 18:42
 *
 */

#pragma once
#include "DataCenterAPI.h"
#include "SimulationAppData.h"
#include "ComponentData.h"
#include "ComponentAppData.h"
#include <QGraphicsItem>
#include <QFileInfo>

namespace Data
{
    /**
     * @brief     Single Simulation App Data Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-12 18:44
     */
    class DATA_CENTER_API SingleSimulationAppData : public ComponentAppData, public SimulationAppData
    {
    public:
        /**
         * @brief     Constructor
         * @return    SingleSimulationAppData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:45
         */
        explicit SingleSimulationAppData() { _simulationAppType = Simulation_App_Single_Component_App; }

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:45
         */
        ~SingleSimulationAppData() = default;

        /**
         * @brief     Is Current Single Simulation App Data Is a Valid Data
         * @return    bool . is valid
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:45
         */
        virtual bool isValidSimulationAppData() { return isValidComponentAppData(); }

        /**
         * @brief     Write Out Simulation App Template. While As Single Simulation App. No Need To Implement
         * @param     filePath[i]. Simulation App Template File Path
         * @return    bool . write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:46
         */
        virtual bool writeOutAppDescribeFile(const QString & filePath) { Q_UNUSED(filePath); return false; }

        /**
         * @brief     copy from other
         * @param     other[i]. copied from
         * @return    bool . is ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:47
         */
        virtual bool copy(Core::FITKAbstractDataObject * other) override { return ComponentAppData::copy(other); }

    };

    /**
     * @brief     Single Simulation App Data Manger
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:15
     */
    class DATA_CENTER_API SingleSimulationAppDataManger : public Core::FITKAbstractDataManager<SingleSimulationAppData>
    {
    public:
        /**
         * @brief     default constructor
         * @return    SingleSimulationAppDataManger object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:16
         */
        explicit SingleSimulationAppDataManger() = default;

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:16
         */
        virtual ~SingleSimulationAppDataManger() = default;

        /**
         * @brief     while graphics item removed . remove reference single simulation app data
         * @param     item[i]. removed graphics item
         * @return    bool . is removed ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:19
         */
        bool removeByGraphicsItem(QGraphicsItem * item);

        /**
         * @brief     get single app data by graphics object
         * @param     obj[i] . graphics object
         * @return    Data::SingleSimulationAppData * . single app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:20
         */
        SingleSimulationAppData * getSingleAppDataByGraphicsObject(QGraphicsItem * obj);

        /**
         * @brief     while delete multi graphics item and line. update single app data
         * @param     remains[i] . still remain graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:21
         */
        void dataUpdateByRemoveItems(QList<QGraphicsItem *> remains);
    };
}
