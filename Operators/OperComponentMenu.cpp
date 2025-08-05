#include "OperComponentMenu.h"
#include "DataCenter/ComponentAppData.h"
#include "ComponentAppStateHelper.h"
#include "DataCenter/FrameAppData.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"

namespace EventOper
{

    OperComponentMenu::OperComponentMenu()
    {

    }

    OperComponentMenu::~OperComponentMenu()
    {

    }

    bool OperComponentMenu::triggered()
    {
        /// prepares
        clearArgs();
        if (_items.size() != 1)
        {
            return false;
        }

        Data::ComponentAppData * cpt = dynamic_cast<Data::ComponentAppData *> (_items.first());
        if (!cpt)
        {
            return false;
        }

        
    }
}