#include "OperFileAction.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/LogData.h"
#include "DataCenter/MultiSimulationAppData.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "GUIFrame/MainWindow.h"
#include "GUIFrame/ProjectNavi.h"
#include "GUIFrame/SaveDialog.h"
#include "OperProjectTree.h"
#include "OperatorsInterface/FileIOOperator.h"

namespace EventOper
{

    OperFileAction::OperFileAction()
    {

    }

    OperFileAction::~OperFileAction()
    {

    }

    bool OperFileAction::prepareArgs()
    {
        _signEventHandler.insert("OpenProject", [this]()->bool { return this->gotoProjectPage(1); });
        _signEventHandler.insert("OpenAppTemplate", [this]()->bool { return this->gotoProjectPage(0); });
        _signEventHandler.insert("SaveProject", [this]()->bool { return this->saveProject(); });
        _signEventHandler.insert("SaveAppTemplate", [this]()->bool { return this->saveAppTemplate(); });
        return true;
    }

    bool OperFileAction::gotoProjectPage(int type)
    {
        GUI::MainWindow * mainWindow = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!mainWindow)
        {
            return false;
        }
        if (mainWindow->currentPage() != GUI::Main_Page_App_Template)
        {
            mainWindow->setCurrentPage(GUI::Main_Page_App_Template);
            LOG(tr("Switch To App Template and Projects Page."));
            return true;
        }
        else
        {
            QTreeWidgetItem * item = mainWindow->projectNavi()->treeWidget()->currentItem();
            if (!item)
            {
                LOGW(tr("Before Open Project Or Create App Please Select Tree Item"));
                return false;
            }
            if (type == 1 && item->type() != Item_History_Instance)
            {
                LOGW(tr("Open Project Need To Select Project Item."));
                return false;
            }
            else if (type == 0 && item->type() != Item_Template_Instance)
            {
                LOGW(tr("Create App Need To Select App Template Item. "));
                return false;
            }
            EventOper::TreeEventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::TreeEventOperator>("ProjectTreeEvent");
            if (!oper)
            {
                return false;
            }
            oper->buttonDoubleClicked(item, 0);
            return true;
        }
    }

    bool OperFileAction::saveProject()
    {
        return false;
    }

    bool OperFileAction::saveAppTemplate()
    {
        Data::FrameAppData * appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData)
        {
            return false;
        }

        Data::MultiSimulationAppDataManger * mulDataMgr = appData->getMultiSimulationAppDataManger();
        if (!mulDataMgr)
        {
            return false;
        }

        int num = mulDataMgr->getDataCount();
        if (num == 1)
        {
            GUI::SaveDialog dlg;
            if (QDialog::Accepted != dlg.exec())
            {
                return false;
            }

            EventOper::FileIOOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::FileIOOperator>("FileIO");
            if (oper)
            {
                Data::MultiSimulationAppData * data = mulDataMgr->getDataByIndex(0);
                QString appTemplatePath = QDir::cleanPath(qApp->applicationDirPath() + "/../AppTemplate") + +"/" + dlg.text() + ".json";
                return oper->writeAppDescription(data, appTemplatePath);
            }
        }
        else
        {
            LOGW(tr("Current Workbench does not supoort multi multi-simulation-template Save!"));
            return false;
        }
    }

}