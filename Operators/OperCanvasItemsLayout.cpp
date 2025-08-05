#include "OperCanvasItemsLayout.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "GUIFrame/MainWindow.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsItem.h"
#include <cmath>

namespace EventOper
{

    OperCanvasItemsLayout::OperCanvasItemsLayout()
    {

    }

    OperCanvasItemsLayout::~OperCanvasItemsLayout()
    {

    }

    bool OperCanvasItemsLayout::prepareArgs()
    {
        _signEventHandler.insert("Align_Left", [this]()->bool { return this->alignLeft(); });
        _signEventHandler.insert("Align_Top", [this]()->bool { return this->alignTop(); });
        _signEventHandler.insert("Align_Right", [this]()->bool { return this->alignRight(); });
        _signEventHandler.insert("Align_Bottom", [this]()->bool { return this->alignBottom(); });
        _signEventHandler.insert("H_Lay", [this]()->bool { return this->hLayout(); });
        _signEventHandler.insert("V_Lay", [this]()->bool { return this->vLayout(); });
        return true;
    }

    bool OperCanvasItemsLayout::alignLeft()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 2) { return false; }

        /// get left pos
        int left = items.first()->pos().toPoint().x();
        for (auto item : items)
            left = std::min(left, item->pos().toPoint().x());

        for (auto item : items)
            item->setPos(left, item->pos().y());
        return true;
    }

    bool OperCanvasItemsLayout::alignRight()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 2) { return false; }

        /// get right pos
        int right = items.first()->pos().toPoint().x();
        for (auto item : items)
            right = std::max(right, item->pos().toPoint().x());

        for (auto item : items)
            item->setPos(right, item->pos().y());
        return true;
    }

    bool OperCanvasItemsLayout::alignTop()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 2) { return false; }

        /// get top pos
        int top = items.first()->pos().toPoint().y();
        for (auto item : items)
            top = std::min(top, item->pos().toPoint().y());

        for (auto item : items)
            item->setPos(item->pos().x(), top);
        return true;
    }

    bool OperCanvasItemsLayout::alignBottom()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 2) { return false; }

        /// get bottom pos
        int bottom = items.first()->pos().toPoint().y();
        for (auto item : items)
            bottom = std::max(bottom, item->pos().toPoint().y());

        for (auto item : items)
            item->setPos(item->pos().x(), bottom);
        return true;
    }

    bool OperCanvasItemsLayout::hLayout()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 3) { return false; }

        /// get top and bottom of components
        int left = items.first()->pos().toPoint().y(), right = left;
        for (auto item : items)
        {
            left = std::min(left, item->pos().toPoint().x());
            right = std::max(right, item->pos().toPoint().x());
        }

        /// horizontal layout items
        QMap <int, Graphics::GraphicsItem * > layoutItems;
        int iNum = items.size();
        int iDiv = (right - left) / (iNum - 1);

        for (int iCnt = 0; iCnt < iNum; ++iCnt)
        {
            /// get nearest item and lay it
            int xPos = left + iCnt * iDiv;
            Graphics::GraphicsItem * nearest = nullptr;
            int distance = right - left;

            for (auto item : items)
            {
                if (layoutItems.values().contains(item))
                    continue;
                if (fabs(item->pos().x() - xPos) < distance)
                {
                    distance = fabs(item->pos().x() - xPos);
                    nearest = item;
                }
            }
            if (!nearest) { continue; }
            nearest->setPos(xPos, nearest->pos().y());
            layoutItems.insert(iCnt, nearest);
        }
    }

    bool OperCanvasItemsLayout::vLayout()
    {
        /// get selected components
        QList<Graphics::GraphicsItem *> items = getSelectedComponents();
        if (items.size() < 3) { return false; }

        /// get top and bottom of components
        int bottom = items.first()->pos().toPoint().y(), top = bottom;
        for (auto item : items)
        {
            top = std::min(top, item->pos().toPoint().y());
            bottom = std::max(bottom, item->pos().toPoint().y());
        }

        /// vertical layout items
        QMap <int, Graphics::GraphicsItem * > layoutItems;
        int iNum = items.size();
        int iDiv = (bottom - top) / (iNum - 1);

        for (int iCnt = 0; iCnt < iNum; ++iCnt)
        {
            /// get nearest item and lay it
            int yPos = top + iCnt * iDiv;
            Graphics::GraphicsItem * nearest = nullptr;
            int distance = bottom - top;

            for (auto item : items)
            {
                if (layoutItems.values().contains(item))
                    continue;
                if (item->pos().y() - yPos < distance)
                {
                    distance = item->pos().y() - yPos;
                    nearest = item;
                }
            }
            if (!nearest) { continue; }
            nearest->setPos(nearest->pos().x(), yPos);
            layoutItems.insert(iCnt, nearest);
        }
    }

    QList<Graphics::GraphicsItem *> OperCanvasItemsLayout::getSelectedComponents()
    {
        QList<Graphics::GraphicsItem *> items;
        GUI::MainWindow * main = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        if (!main) { return items; }
        Graphics::GraphicsScene * scene = main->getGraphicsScene();
        if (!scene) { return items; }
        items = scene->selectedComponents();
        return items;
    }

}