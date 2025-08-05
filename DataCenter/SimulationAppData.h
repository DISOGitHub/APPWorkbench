/**
 *
 * @file      SimulationAppData.h
 * @brief     Simulation App Data Abstract Class Define
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-21 15:59
 *
 */

#pragma once
#include "DataCenterAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"

namespace Data
{
    enum SimulationAppType
    {
        /**
         * @brief     Unset Simulation App Type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 15:59
         */
        Simulation_App_Unset,
        /**
         * @brief     Multi Component Construct App Type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 15:59
         */
        Simulation_App_Multi_Component_App,
        /**
         * @brief     Single Component Construct App Type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 16:00
         */
        Simulation_App_Single_Component_App,
    };

    /**
     * @brief     Simulation App Data Base Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:15
     */
    class DATA_CENTER_API SimulationAppData
    {
    public:

        /**
         * @brief     default constructor
         * @return    SimulationAppData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:00
         */
        explicit SimulationAppData() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:01
         */
        virtual ~SimulationAppData() = default;

        /**
         * @brief     is current simulation app data is a valid data.
         * @return    bool . is valid data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:01
         */
        virtual bool isValidSimulationAppData() = 0;

        /**
         * @brief     write out simulation app describe template file
         * @param     filePath[i] . simulation app describe template file path
         * @return    bool . is write out ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:02
         */
        virtual bool writeOutAppDescribeFile(const QString & filePath) = 0;

        /**
         * @brief     get current simulation app data type
         * @return    Data::SimulationAppType . simulation app data type
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-21 16:03
         */
        SimulationAppType simulationAppType() const { return _simulationAppType; }

    protected:
        /**
         * @brief     simulation app type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-21 15:55
         */
        SimulationAppType _simulationAppType{ Simulation_App_Unset };
    };
}