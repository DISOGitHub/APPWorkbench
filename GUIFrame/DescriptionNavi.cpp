#include "DescriptionNavi.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/ComponentAppData.h"

#include "GUIWidget/DrawerWidget.h"
#include <QPainter>

namespace GUI
{
    DescriptionNavi::DescriptionNavi(QWidget *parent, Qt::WindowFlags f)
        : DrawerPanel(parent, f)
    {
        initUi();
    }

    DescriptionNavi::~DescriptionNavi()
    {
    }

    void DescriptionNavi::initUi()
    {
        /// load default panel
        auto localCptApps = addDrawerItem(tr("Local Component Apps"));
        auto remoteCptApps = addDrawerItem(tr("Remote Component Apps"));

        /// load local component descriptions
        auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        auto cptDataMgr = appData->getComponentDataManger();
        if (!cptDataMgr) { return; }

        auto cptNum = cptDataMgr->getDataCount();
        for (int index = 0; index < cptNum; ++index)
        {
            Data::ComponentData * cpt = cptDataMgr->getDataByIndex(index);
            GUI::DescriptionItem * item = new GUI::DescriptionItem();
            QString majors;
            for (QString major : cpt->disciplines())
            {
                majors += major;
                majors += ".";
            }

            item->setDescription(cpt->getDataObjectName(), cpt->type(), cpt->author(), cpt->company(), majors);
            item->setSvg(cpt->svg());
            localCptApps->addDescriptionItem(item);
        }
        updateUi();
    }

}