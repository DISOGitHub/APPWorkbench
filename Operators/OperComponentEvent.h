/**
 *
 * @file      OperComponentEvent.h
 * @brief     Support User Use Component App 's  Right Button Menu To Solve or Open Project
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 19:57
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/ComponentEventOperator.h"
#include "QGraphicsItem"

namespace Data
{
    class ComponentAppData;
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
    class SimulationAppData;
}

namespace EventOper
{
    /**
     * @brief     Operator For User Component App 's Right Button Menu Clicked
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 19:59
     */
    class OperComponentEvent : public ComponentEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperComponentEvent object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:00
         */
        OperComponentEvent();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:01
         */
        ~OperComponentEvent();

        /**
         * @brief     User Double Clicked Component App Item
         * @param     item[i]. Component App Item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:01
         */
        virtual void doubleClicked(QGraphicsObject * item) override;

        /**
         * @brief     User Use Right Button Menu 's Open Project . Or Double Clicked While Exists Project
         * @param     item[i]. graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:02
         */
        virtual void openProject(QGraphicsObject * item) override;

        /**
         * @brief     User Use Right Button Menu 's Run Project . Or Double Clicked While Not Exists Project
         * @param     item[i]. graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:03
         */
        virtual void run(QGraphicsObject * item) override;

        /**
         * @brief     Get Right Button Menu Item
         * @param     item[i]. Graphics Item
         * @return    bool . is get ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:04
         */
        virtual bool rightButtonMenu(QGraphicsObject * item) override;

    protected:
        void prepareData(QGraphicsItem * item);

        /**
         * @brief     Single Simulation App Data Manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 20:04
         */
        Data::SingleSimulationAppDataManger * _sglSimAppDataMgr{};

        /**
         * @brief     Multi Simulation App Data Manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 20:05
         */
        Data::MultiSimulationAppDataManger * _mulSimAppDataMgr{};

        Data::SimulationAppData * _app{};
        Data::ComponentAppData * _cpt{};
    };
    Register2FITKOperatorRepo(SimulationApp, OperComponentEvent);
}