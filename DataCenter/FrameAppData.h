/**
 *
 * @file      FrameAppData.h
 * @brief     This Application 's All Data. Store In Other Data Part With < FRAME_APP_DATA_ID 1000 >
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-12 18:23
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "DataCenterAPI.h"

#define FRAME_APP_DATA_ID               1001

namespace Data
{
    class ComponentDataManger;
    class ComponentAppDataManger;
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
    class LineDataManger;
    class TransferDataManger;
    /**
     * @brief     Application 's Data
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-12 18:24
     */
    class DATA_CENTER_API FrameAppData : public Core::FITKAbstractDataObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    FrameAppData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:26
         */
        explicit FrameAppData();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:26
         */
        virtual ~FrameAppData();

        /**
         * @brief     get component data manger. component data number equals to json description file.
         * @return    Data::ComponentDataManger * .component data manger.
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:27
         */
        ComponentDataManger * getComponentDataManger();

        /**
         * @brief     get component app data manger. component app data is component data instance with project and other data.
         * @return    Data::ComponentAppDataManger * .component app data manger
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:27
         */
        ComponentAppDataManger * getComponentAppDataManger();

        /**
         * @brief     get single simulation app data manger . while single component app construct a simulation app . then we
         *            call it single simulation app.
         * @return    Data::SingleSimulationAppDataManger * .  single simulation app data manger
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:29
         */
        SingleSimulationAppDataManger * getSingleSimulationAppDataManger();

        /**
         * @brief     get multi simulation app data manger. while multi component app construct a simulation app . then we call
         *            it multi simulation app.
         * @return    Data::MultiSimulationAppDataManger * . multi simulation app data manger
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:31
         */
        MultiSimulationAppDataManger * getMultiSimulationAppDataManger();

        /**
         * @brief     get line data manger. line with degenerated channel info.
         * @return    Data::LineDataManger * .line data manger
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 18:32
         */
        LineDataManger * getLineDataManger();

        /**
         * @brief     get transfer data
         * @return    Data::TransferData * . transfer data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 11:00
         */
        TransferDataManger * transferData() { return _transferData; }

    protected:
        /**
         * @brief     component data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 18:34
         */
        ComponentDataManger * _componentDataMgr{};

        /**
         * @brief     component app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 18:34
         */
        ComponentAppDataManger * _componentAppDataMgr{};

        /**
         * @brief     single simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 18:34
         */
        SingleSimulationAppDataManger * _singleSimulationAppDataMgr{};

        /**
         * @brief     multi simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 18:35
         */
        MultiSimulationAppDataManger * _multiSimulationAppDataMgr{};

        /**
         * @brief     line data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 18:35
         */
        LineDataManger * _lineDataMgr{};

        /**
         * @brief     transfer data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 19:36
         */
        TransferDataManger * _transferData{};
    };
}