#include "OperCanvasMode.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "GUIFrame/MainWindow.h"
#include "Graphics/Define.h"
#include "Graphics/GraphicsScene.h"

namespace EventOper
{

    OperCanvasMode::OperCanvasMode()
    {

    }

    OperCanvasMode::~OperCanvasMode()
    {

    }

    bool OperCanvasMode::prepareArgs()
    {
        _signEventHandler.insert("Selected", [this]()->bool {return this->setSelectMode(); });
        _signEventHandler.insert("Line", [this]()->bool {return this->setLineMode(); });
        return true;
    }

    bool OperCanvasMode::setSelectMode()
    {
        GUI::MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!main) { return false; }
        Graphics::GraphicsScene * scene = main->getGraphicsScene();
        if (!scene) { return false; }
        scene->setCanvasMode(Select_Mode);
        return true;
    }

    bool OperCanvasMode::setLineMode()
    {
        GUI::MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!main) { return false; }
        Graphics::GraphicsScene * scene = main->getGraphicsScene();
        if (!scene) { return false; }
        scene->setCanvasMode(Line_Mode);
        return true;
    }

}