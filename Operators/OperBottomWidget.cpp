#include "OperBottomWidget.h"
#include "GUIFrame/MainWindow.h"
#include "GUIFrame/OutputWidget.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

namespace EventOper
{

    OperBottomWidget::OperBottomWidget()
    {

    }

    OperBottomWidget::~OperBottomWidget()
    {

    }

    bool OperBottomWidget::prepareArgs()
    {
        _signEventHandler.insert("Log", [this]()->bool { return this->Log(); });
        _signEventHandler.insert("Expand", [this]()->bool { return this->Expand(); });
        _signEventHandler.insert("Retract", [this]()->bool { return this->Retract(); });
        return true;
    }

    bool OperBottomWidget::Log()
    {
        GUI::MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!main) { return false; }
        _output = main->outputWidget();
        if (_output && hasArgs("msg"))
        {
            QString msg;
            if (argValue<QString>("msg", msg))
            {
                _output->addLog(msg);
                return true;
            }
        }
        return false;
    }

    bool OperBottomWidget::Expand()
    {
        return true;
    }

    bool OperBottomWidget::Retract()
    {
        return true;
    }

}