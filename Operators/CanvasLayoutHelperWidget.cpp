#include "CanvasLayoutHelperWidget.h"

#include <QHBoxLayout>

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "GUIFrame/MainWindow.h"
#include "GUIWidget/IconButton.h"

namespace EventHelper
{

    CanvasLayoutHelperWidget::CanvasLayoutHelperWidget(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QWidget(parent, f)
    {
        initUi();
    }

    CanvasLayoutHelperWidget::~CanvasLayoutHelperWidget()
    {

    }

    void CanvasLayoutHelperWidget::setNumberOfItems(int itemNum)
    {
        _itemNum = itemNum;
        updateUi();
    }

    void CanvasLayoutHelperWidget::initUi()
    {
        _lay = new QHBoxLayout();
        setLayout(_lay);
        _lay->setSpacing(2);
        _lay->setContentsMargins(2, 2, 2, 2);
        _mainWindow = FITKAPP->getGlobalData()->getMainWindowT<GUI::MainWindow>();
        setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    }

    void CanvasLayoutHelperWidget::updateUi()
    {
        while (_lay->count() != 0)
        {
            QLayoutItem * item = _lay->takeAt(0);
            if (item->widget())
            {
                QWidget * widget = item->widget();
                delete widget;
                widget = nullptr;
            }
        }

        if (_itemNum < 2) { return; }

        _lay->addWidget(copyFromMainWindowIconButton(tr("Align_Left")));
        _lay->addWidget(copyFromMainWindowIconButton(tr("Align_Top")));
        _lay->addWidget(copyFromMainWindowIconButton(tr("Align_Right")));
        _lay->addWidget(copyFromMainWindowIconButton(tr("Align_Bottom")));
        setFixedWidth(132);

        if (_itemNum >= 3)
        {
            _lay->addWidget(new GUI::IconButton(QIcon(""), QIcon(""), ""));
            _lay->addWidget(copyFromMainWindowIconButton(tr("H_Lay")));
            _lay->addWidget(copyFromMainWindowIconButton(tr("V_Lay")));
            setFixedWidth(196);
        }
    }

    GUI::IconButton * CanvasLayoutHelperWidget::copyFromMainWindowIconButton(const QString & triggeredName)
    {
        GUI::IconButton * btn = _mainWindow->iconButton(triggeredName);
        GUI::IconButton * copied = new GUI::IconButton(btn->icon0(), btn->icon1(), btn->toolTip(), this, btn->iconSize());
        copied->setTriggeredName(btn->triggeredName());
        connect(copied, SIGNAL(clicked()), btn, SIGNAL(clicked()));
        return copied;
    }

}