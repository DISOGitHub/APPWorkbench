#include "GraphicsItem.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/ComponentAppData.h"
#include "DataCenter/ComponentData.h"
#include "DataCenter/LogData.h"

#include "OperatorsInterface/GraphicsObjectEventOperator.h"
#include "OperatorsInterface/ComponentEventOperator.h"

#include "PortItem.h"
#include "GraphicsScene.h"
#include "NameItem.h"

#include <QPainter>
#include <QSvgRenderer>
#include <QMenu>
#include <QGraphicsSceneEvent>
#include "StateItem.h"

namespace Graphics
{
    class ItemPrivater
    {
    public:
        void initItem(GraphicsItem * item, const QString & componentName)
        {
            /**
            /* get component data by component name
            */
            auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
            if (!appData) { return; }
            auto cptDataMgr = appData->getComponentDataManger();
            if (!cptDataMgr) { return; }
            Data::ComponentData * cptData = cptDataMgr->getDataByName(componentName);

            /**
            * create component instance data and copy form component data
            */
            _data = new Data::ComponentAppData(item);
            _data->copy(cptData);

            /**
            /* set component item ' attrs. selectable movable focusable and send geometry change info.
            */
            item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable | QGraphicsItem::ItemSendsGeometryChanges);
            item->setToolTip(_data->description());
            item->setAcceptHoverEvents(true);
            item->setComponentName(componentName);

            /**
            /* sub parts of item
            */
            _nameItem = new NameItem(_data->getDataObjectName(), item);
            _nameItem->setPos(-_nameItem->borderWidth(), _rect.height() + _nameItem->topBorderHeight());
            _portItem = new PortItem(item);
            _portItem->setPos(-_portItem->size() / 2, _rect.width() / 2 - _portItem->size() / 2);
            _statePart = new StateItem(item);
            _statePart->setPos((_rect.width() - _statePart->boundingRect().width()) / 2, -_statePart->boundingRect().height() - 10);

            /**
            * get operator of component event
            */
            _oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::ComponentEventOperator>("SimulationApp");
        }

        /**
         * @brief     the name of the component. unique id to get component info
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:10
         */
        QString _componentName;

        /**
         * @brief     data of the component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:11
         */
        Data::ComponentAppData * _data{};

        /**
         * @brief     bounding rect of the component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:16
         */
        QRectF _rect{ QRectF(0.0,0.0,80,80) };

        /**
         * @brief     distance between icon and frame
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:16
         */
        int _iconBorder{ 10 };

        /**
         * @brief     weather component is selected
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:15
         */
        bool _selected{ false };

        /**
         * @brief     pen to draw frame in normal calculate finished selected component state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:10
         */
        QPen _frameNormalPen{ QPen(QColor(56,56,56),2) };
        QPen _frameCalculatePen{ QPen(QColor(56,156,56),2) };
        QPen _frameFinishedPen{ QPen(QColor(56,56,156),2) };
        QPen _frameSelectedPen{ QPen(QColor(255,56,199),2,Qt::SolidLine) };

        /**
         * @brief     state of component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:10
         */
        ComponentState _componentState{ Component_Normal_State };

        /**
         * @brief     is this graphics item is current item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-10 10:11
         */
        bool _isCurrentComponent{ false };

        /**
         * @brief     name part of component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:09
         */
        NameItem * _nameItem{};

        /**
         * @brief     port part of component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 12:14
         */
        PortItem * _portItem{};

        /**
         * @brief     state part of component
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:41
         */
        StateItem * _statePart{};

        /**
         * @brief     operator of component event
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 17:08
         */
        EventOper::ComponentEventOperator * _oper{};
    };


    GraphicsItem::GraphicsItem(const QString & componentName, QGraphicsItem *parent /*= nullptr*/)
        : QGraphicsObject(parent)
        , _privater(new ItemPrivater())
    {
        _privater->initItem(this, componentName);
    }

    GraphicsItem::~GraphicsItem()
    {
        if (_privater)
        {
            delete _privater;
            _privater = nullptr;
        }
    }

    QString GraphicsItem::componentName() const
    {
        return _privater->_componentName;
    }

    void GraphicsItem::setComponentName(const QString & name)
    {
        _privater->_componentName = name;
        update();
    }

    ComponentState GraphicsItem::componentState() const
    {
        return _privater->_componentState;
    }

    void GraphicsItem::setComponentState(ComponentState state)
    {
        _privater->_componentState = state;
        update();
    }

    void GraphicsItem::setComponentInputState(ComponentInputState inputState)
    {
        _privater->_statePart->setGraphicsItemState(inputState);
    }

    bool GraphicsItem::currentComponentItem() const
    {
        return _privater->_isCurrentComponent;
    }

    void GraphicsItem::setCurrentComponentItem(bool current)
    {
        _privater->_isCurrentComponent = current;
        update();
    }

    void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);

        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);

        /// 1. draw frame
        if (isSelected())
        {
            painter->setPen(_privater->_frameSelectedPen);
        }
        else
        {
            switch (_privater->_componentState)
            {
            case Component_Normal_State:
                painter->setPen(_privater->_frameNormalPen);
                break;
            case Component_Calculate_State:
                painter->setPen(_privater->_frameCalculatePen);
                break;
            case Component_Finished_State:
                painter->setPen(_privater->_frameFinishedPen);
                break;
            }
        }
        painter->drawRoundRect(_privater->_rect);

        /// 2.draw current item
        if (_privater->_isCurrentComponent)
        {
            painter->setBrush(QBrush(QColor(165, 215, 165)));
            painter->drawRoundRect(_privater->_rect);
        }

        /// 3. draw icon
        QSvgRenderer renderer;
        QString svg = _privater->_data->svg();
        renderer.load(svg);
        renderer.render(painter, _privater->_rect.adjusted(_privater->_iconBorder, _privater->_iconBorder, -_privater->_iconBorder, -_privater->_iconBorder));

        painter->restore();
    }

    QRectF GraphicsItem::boundingRect() const
    {
        return _privater->_rect;
    }

    Data::ComponentAppData * GraphicsItem::componentAppData() const
    {
        return _privater->_data;
    }

    Graphics::PortItem * GraphicsItem::portPart() const
    {
        return _privater->_portItem;
    }

    Graphics::NameItem * GraphicsItem::namePart() const
    {
        return _privater->_nameItem;
    }

    void GraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
    {
        QGraphicsObject::mouseDoubleClickEvent(event);
        if (!_privater->_oper) { return; }
        _privater->_oper->doubleClicked(this);
    }

    void GraphicsItem::menuItemClicked()
    {
        if (!_privater->_oper) { return; }
        QAction * action = qobject_cast<QAction *> (sender());
        if (action)
        {
            if (action->text() == tr("Open Project"))
            {
                _privater->_oper->openProject(this);
            }
            else if (action->text() == tr("Run"))
            {
                _privater->_oper->run(this);
            }
        }
    }

    QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant & value)
    {
        /// support item position change
        if ((change == ItemPositionChange || change == ItemPositionHasChanged) && scene())
        {
            GraphicsScene * _scene = qobject_cast<GraphicsScene *>(scene());
            if (_scene)
                _scene->updateLineItem(this);
        }
        return QGraphicsItem::itemChange(change, value);
    }

    void GraphicsItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
    {
        Q_UNUSED(event);

        QMenu menu;
        QAction * action = nullptr;

        bool bOk = _privater->_oper->rightButtonMenu(this);
        if (!bOk) { return; }

        if (_privater->_oper->hasArgs(tr("Open Project")))
        {
            action = menu.addAction(tr("Open Project"));
            connect(action, SIGNAL(triggered()), this, SLOT(menuItemClicked()));
        }
        if (_privater->_oper->hasArgs(tr("Run")))
        {
            action = menu.addAction(tr("Run"));
            connect(action, SIGNAL(triggered()), this, SLOT(menuItemClicked()));
        }

        menu.exec(QCursor::pos());
    }

}
