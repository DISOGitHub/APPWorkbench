#include "OperSimulationAppRun.h"
#include "DataCenter/SingleSimulationAppData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/LogData.h"
#include "DataCenter/FrameAppData.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "ComponentAppStateHelper.h"
#include "ComponentCoreDriver.h"

#include <QDir>
#include <QDateTime>
#include "IniFileWriter.h"
#include "Graphics/GraphicsItem.h"

namespace EventOper
{

    OperSimulationAppRun::~OperSimulationAppRun()
    {

    }

    bool OperSimulationAppRun::prepareArgs()
    {
        _signEventHandler.insert("Previous", [this]() ->bool { return this->runPreviousComponentApp(); });
        _signEventHandler.insert("Current", [this]() ->bool { return this->runCurrentComponentApp(); });
        _signEventHandler.insert("Next", [this]() ->bool { return this->runNextComponentApp(); });

        Data::FrameAppData * appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return false; }
        _sglAppDataMgr = appData->getSingleSimulationAppDataManger();
        _mulAppDataMgr = appData->getMultiSimulationAppDataManger();
        return true;
    }

    bool OperSimulationAppRun::runPreviousComponentApp()
    {
        /// check params
        if (!_sglAppDataMgr || !_mulAppDataMgr) { return false; }

        /// to find canvas 's simulation app num. include single simulation app and multi simulation app
        int singleAppNum = _sglAppDataMgr->getDataCount();
        int multiAppNum = _mulAppDataMgr->getDataCount();
        if (singleAppNum + multiAppNum > 1) {
            /// there is multi simulation app in canvas. current can not run . after need let user to select run 
            LOGW("Canvas Has Multi Simulation App. Please Make Sure Canvas Has Only One Simulation App");
            return false;
        }

        if (singleAppNum == 1)
        {
            /// run single simulation app
            LOGW("Single Simulation App Does Not Has Previous Component App.");
            return true;
        }
        else if (multiAppNum == 1)
        {
            /// run multi simulation app
            Data::MultiSimulationAppData * data = _mulAppDataMgr->getDataByIndex(0);
            if (!data) { return false; }

            /// get current component app data
            Data::ComponentAppData * cptData = data->getCurrentComponentAppData();
            if (!cptData) { return false; }
            terminateCurrentComponentApp(cptData);

            /// get previous component app data
            QList<Data::ComponentAppData *> previous = data->getPreviousLinkedComponentApps(cptData);
            if (previous.isEmpty())
            {
                LOGW("Current Component App In Degree Is 0. Has No Previous Component App.");
                return false;
            }

            Data::ComponentAppData * pre = nullptr;
            if (previous.size() == 1)
                pre = previous.first();

            /// if previous component app can run
            EventHelper::ComponentAppStateHelper helper(data, pre);
            EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();

            if (state.enumState == EventHelper::Can_Solve)
            {
                /// current component app can solve . solve
                LOG(QString("Run Previous Component App %1 %2.").arg(pre->getDataObjectName()).arg(ADDR(pre->graphicsObject())));
                data->setCurrentComponentAppData(pre);
                helper.componentAppRun();
                return true;
            }
            else if (state.enumState == EventHelper::Can_Solve_With_Multi)
            {
                /// before current component app run. user need select current component app input file.
            }
        }
        return false;
    }

    bool OperSimulationAppRun::runCurrentComponentApp()
    {
        /// check params
        if (!_sglAppDataMgr || !_mulAppDataMgr) { return false; }

        /// to find canvas 's simulation app num. include single simulation app and multi simulation app
        int singleAppNum = _sglAppDataMgr->getDataCount();
        int multiAppNum = _mulAppDataMgr->getDataCount();

        if (singleAppNum + multiAppNum > 1) {
            /// there is multi simulation app in canvas. current can not run . after need let user to select run 
            LOGW("Canvas Has Multi Simulation App. Please Make Sure Canvas Has Only One Simulation App");
            return false;
        }

        if (singleAppNum == 1)
        {
            /// run single simulation app
            Data::SingleSimulationAppData * data = _sglAppDataMgr->getDataByIndex(0);
            if (!data) { return false; }

            /// if current component app can run
            EventHelper::ComponentAppStateHelper helper(data, data);
            EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();

            if (EventHelper::Natural_Can_Solve == state.enumState ||
                EventHelper::Can_Solve == state.enumState)
            {
                LOG(QString("Run Single Simulation App 's Component App %1 %2.").arg(data->getDataObjectName()).arg(ADDR(data->graphicsObject())));
                helper.componentAppRun(data);
                return true;
            }
            else if (EventHelper::Can_Not_Be_Single_Simulation == state.enumState)
            {
                LOG(QString("Single Simulation App 's Component App %1 %2. Can Construct Single Simulation App").arg(data->getDataObjectName()).arg(ADDR(data->graphicsObject())));
                return false;
            }
            return false;
        }
        else if (multiAppNum == 1)
        {
            /// run multi simulation app
            Data::MultiSimulationAppData * data = _mulAppDataMgr->getDataByIndex(0);
            if (!data) { return false; }

            /// get current component app data
            Data::ComponentAppData * cpt = data->getCurrentComponentAppData();
            if (!cpt) { return false; }

            /// if current component app can run
            EventHelper::ComponentAppStateHelper helper(data, cpt);
            EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();

            if (EventHelper::Natural_Can_Solve == state.enumState ||
                EventHelper::Can_Solve == state.enumState)
            {
                LOG(QString("Run Current Component App %1 %2.").arg(cpt->getDataObjectName()).arg(ADDR(cpt->graphicsObject())));
                helper.componentAppRun();
                return true;
            }
            else if (state.enumState == EventHelper::Can_Solve_With_Multi)
            {
                /// before current component app run. user need select current component app input file.
            }
            else if (state.enumState == EventHelper::Component_Input_Error)
            {
                /// 
                LOGW("");
            }
        }
        return false;
    }

    bool OperSimulationAppRun::runNextComponentApp()
    {
        /// check params
        if (!_sglAppDataMgr || !_mulAppDataMgr) { return false; }

        /// to find canvas 's simulation app num. include single simulation app and multi simulation app
        int singleAppNum = _sglAppDataMgr->getDataCount();
        int multiAppNum = _mulAppDataMgr->getDataCount();
        if (singleAppNum + multiAppNum > 1) {
            /// there is multi simulation app in canvas. current can not run . after need let user to select run 
            LOG("Canvas Has Multi Simulation App. Please Make Sure Canvas Has Only One Simulation App");
            return false;
        }

        if (singleAppNum == 1)
        {
            /// run single simulation app
            LOGW("Single Simulation App Does Not Has Next Component App.");
            return true;
        }
        else if (multiAppNum == 1)
        {
            /// run multi simulation app
            Data::MultiSimulationAppData * data = _mulAppDataMgr->getDataByIndex(0);
            if (!data) { return false; }

            /// get current component app data
            Data::ComponentAppData * cptData = data->getCurrentComponentAppData();
            if (!cptData) { return false; }
            if (!cptData->existProject())
            {
                LOGW("Current Component App Not Run Finished. Please Run Current Component App First.");
                return false;
            }
            terminateCurrentComponentApp(cptData);

            /// get next component app data
            Data::ComponentAppData * nextCptData = data->getNextSolveComponentApp();
            if (!nextCptData) { return false; }

            /// if next component app can run
            EventHelper::ComponentAppStateHelper helper(data, nextCptData);
            EventHelper::ComponentCanSolveState state = helper.isComponentCanSolve();

            if (state.enumState == EventHelper::Can_Solve)
            {
                /// next component app can solve . set next component app as current and solve
                data->setCurrentComponentAppData(nextCptData);
                LOG(QString("Run Next Component App %1 %2.").arg(nextCptData->getDataObjectName()).arg(ADDR(nextCptData->graphicsObject())));
                helper.componentAppRun(nextCptData);
                return true;
            }
            else if (state.enumState == EventHelper::Can_Solve_With_Multi)
            {
                /// before current component app run. user need select current component app input file.
            }
        }

        return false;
    }

    /*   void OperSimulationAppRun::componentAppRun(Data::ComponentAppData * cpt)
       {
           auto mgr = EventHelper::ComponentCoreDriverManger::instance();
           auto driver = mgr->getDriver(cpt->graphicsObject());
           driver->clearArgs();
           driver->setCoreAppPath(cpt->path());
           driver->setIniFilePath(cpt->iniFilePath() + "/project.ini");

           for (QString paramName : cpt->additionalInputParamNames())
           {
               Data::AdditionalInputParam param = cpt->additionalInputParam(paramName);
               if (param.defaultUse && !param.userSet)
               {
                   driver->addArg(param.argv);
               }
           }
           driver->start();
           updateComponentAppGraphicsObjectState(cpt);
       }*/

    void OperSimulationAppRun::terminateCurrentComponentApp(Data::ComponentAppData * current)
    {
        auto mgr = EventHelper::ComponentCoreDriverManger::instance();
        auto driver = mgr->getDriver(current->graphicsObject());
        driver->terminate();
    }

    /*   void OperSimulationAppRun::updateComponentAppGraphicsObjectState(Data::ComponentAppData * current)
       {
           /// update current run  component app 's state
           QGraphicsItem * item = current->graphicsObject();
           if (!item) { return; }
           Graphics::GraphicsItem * real = dynamic_cast<Graphics::GraphicsItem *>(item);
           if (!real) { return; }
           real->setComponentState(Component_Calculate_State);

           Data::MultiSimulationAppData * multi = _mulAppDataMgr->getMultiAppDataByGraphicsObject(current->graphicsObject());
           if (multi)
           {
               for (Data::ComponentAppData * cptData : multi->componentAppDatas())
               {
                   if (cptData != current)
                   {
                       Graphics::GraphicsItem * other = dynamic_cast<Graphics::GraphicsItem *>(cptData->graphicsObject());
                       if (!other) { return; }
                       other->setCurrentComponentItem(false);
                       other->update();
                   }
               }
           }
           real->setCurrentComponentItem(true);
           real->update();
       }*/
}
