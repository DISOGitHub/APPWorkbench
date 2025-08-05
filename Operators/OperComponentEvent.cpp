#include "OperComponentEvent.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/SingleSimulationAppData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/ComponentAppData.h"
#include "DataCenter/LogData.h"

#include "ComponentAppStateHelper.h"

#include <QProcess>

namespace EventOper
{
    OperComponentEvent::OperComponentEvent()
    {
        auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        _sglSimAppDataMgr = appData->getSingleSimulationAppDataManger();
        _mulSimAppDataMgr = appData->getMultiSimulationAppDataManger();
    }

    OperComponentEvent::~OperComponentEvent()
    {

    }

    void OperComponentEvent::doubleClicked(QGraphicsObject * item)
    {
        prepareData(item);
        if (_cpt &&
            !_cpt->projectPath().isEmpty() &&
            _cpt->existProject())
        {
            openProject(item);
        }
        else
        {
            run(item);
        }
    }

    void OperComponentEvent::openProject(QGraphicsObject * item)
    {
        prepareData(item);
        EventHelper::ComponentAppStateHelper helper(_app, _cpt);
        helper.prepareOpenProjectIni();
        helper.componentAppRun(false);
    }

    void OperComponentEvent::run(QGraphicsObject * item)
    {
        prepareData(item);
        EventHelper::ComponentAppStateHelper helper(_app, _cpt);
        EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();
        if (EventHelper::Can_Solve == state.enumState ||
            EventHelper::Natural_Can_Solve == state.enumState)
        {
            helper.componentAppRun(true);
        }
        else if (EventHelper::Can_Solve_With_Multi == state.enumState)
        {

        }
    }

    bool OperComponentEvent::rightButtonMenu(QGraphicsObject * item)
    {
        prepareData(item);
        clearArgs();

        /// if already exist project
        if (_cpt->existProject())
        {
            setArgs(tr("Open Project"), true);
            setArgs(tr("Run"), true);
            return true;
        }
        else
        {
            /// is component app can solve
            EventHelper::ComponentAppStateHelper helper(_app, _cpt);
            EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();

            if (EventHelper::Can_Solve == state.enumState ||
                EventHelper::Natural_Can_Solve == state.enumState ||
                EventHelper::Can_Solve_With_Multi == state.enumState)
            {
                setArgs(tr("Run"), true);
                return true;
            }
        }
        return false;
    }

    void OperComponentEvent::prepareData(QGraphicsItem * item)
    {
        Data::SingleSimulationAppData * singleAppData = _sglSimAppDataMgr->getSingleAppDataByGraphicsObject(item);
        if (singleAppData)
        {
            _app = singleAppData;
            _cpt = singleAppData;
        }
        else
        {
            Data::MultiSimulationAppData * multiAppData = _mulSimAppDataMgr->getMultiAppDataByGraphicsObject(item);
            if (multiAppData)
            {
                _app = multiAppData;
                _cpt = multiAppData->getComponentAppDataByGraphicsObject(item);
            }
        }
    }
}