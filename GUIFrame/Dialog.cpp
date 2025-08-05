#include "Dialog.h"
#include "MainWindow.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

namespace GUI
{

    Dialog::Dialog(QWidget *parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QDialog(parent, f)
    {
        if (!parent)
        {
            MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<MainWindow>();
            if (main)
            {
                setWindowIcon(main->windowIcon());
            }
        }
    }

    Dialog::~Dialog()
    {

    }

}