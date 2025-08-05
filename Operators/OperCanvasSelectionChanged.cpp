#include "OperCanvasSelectionChanged.h"
#include "GUIFrame/MainWindow.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsItem.h"

namespace EventOper
{

    OperCanvasSelectionChanged::OperCanvasSelectionChanged()
    {
        _helper = new EventHelper::CanvasLayoutHelperWidget();
        _helper->hide();
    }

    OperCanvasSelectionChanged::~OperCanvasSelectionChanged()
    {
        if (_helper)
        {
            delete _helper;
            _helper = nullptr;
        }
    }

    bool OperCanvasSelectionChanged::triggered()
    {
        GUI::MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!main) { return false; }
        Graphics::GraphicsScene * scene = main->getGraphicsScene();
        if (!scene) { return false; }

        /// get selected graphics items
        QList<QGraphicsItem *> qItems = scene->selectedItems();
        QList<Graphics::GraphicsItem *> items;

        for (auto qItem : qItems)
        {
            Graphics::GraphicsItem * item = dynamic_cast<Graphics::GraphicsItem *> (qItem);
            if (item)
                items.append(item);
        }

        if (items.size() <= 1)
        {
            /// hide canvas layout helper widget.
            _helper->hide();
        }
        else
        {
            /// show canvas layout helper widget.
            _helper->move(QCursor::pos());
            _helper->show();
            _helper->setNumberOfItems(items.size());
        }
        return true;
    }

}

