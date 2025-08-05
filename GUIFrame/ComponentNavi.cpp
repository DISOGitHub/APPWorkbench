#include "ComponentNavi.h"
#include "GUIWidget/DrawerWidget.h"
#include "GUIWidget/ComponentItem.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "DataCenter/FrameAppData.h"
#include "DataCenter/ComponentData.h"

namespace GUI
{
    ComponentNavi::ComponentNavi(QWidget *parent, Qt::WindowFlags f)
        : DrawerPanel(parent, f)
    {
        initUi();
    }

    ComponentNavi::~ComponentNavi()
    {
    }

    void ComponentNavi::initUi()
    {
        /// load default panel
        auto geometryPanel = addDrawerItem(tr("Geometry"));
        auto meshPanel = addDrawerItem(tr("Mesh"));
        auto solverPanel = addDrawerItem(tr("Solver"));
        auto postPanel = addDrawerItem(tr("Post"));
        auto toolPanel = addDrawerItem(tr("Tools"));

        /// load components
        auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        auto cptDataMgr = appData->getComponentDataManger();
        if (!cptDataMgr) { return; }

        auto cptNum = cptDataMgr->getDataCount();
        for (int index = 0; index < cptNum; ++index)
        {
            Data::ComponentData * cpt = cptDataMgr->getDataByIndex(index);

            if (cpt->type() == "Geometry")
                geometryPanel->addComponentItem(new GUI::ComponentItem(cpt->svg(), cpt->getDataObjectName(), geometryPanel));
            else if (cpt->type() == "Mesh")
                meshPanel->addComponentItem(new GUI::ComponentItem(cpt->svg(), cpt->getDataObjectName(), meshPanel));
            else if (cpt->type() == "Solver")
                solverPanel->addComponentItem(new GUI::ComponentItem(cpt->svg(), cpt->getDataObjectName(), solverPanel));
            else if (cpt->type() == "Post")
                postPanel->addComponentItem(new GUI::ComponentItem(cpt->svg(), cpt->getDataObjectName(), postPanel));
            else if (cpt->type() == "Tool")
                toolPanel->addComponentItem(new GUI::ComponentItem(cpt->svg(), cpt->getDataObjectName(), toolPanel));
        }

        /// update user interface
        geometryPanel->updateUi();
        meshPanel->updateUi();
        solverPanel->updateUi();
        postPanel->updateUi();
        toolPanel->updateUi();
        updateUi();
    }

}
