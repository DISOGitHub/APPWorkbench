#include "GraphicsView.h"
#include "GraphicsItem.h"
#include "GraphicsScene.h"

#include "PortItem.h"
#include "IndicateLineItem.h"
#include "LineItem.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/LogData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/ChannelDegenerate.h"
#include "DataCenter/SingleSimulationAppData.h"

#include "OperatorsInterface/GraphicsObjectEventOperator.h"

#include <QScrollBar>
#include <QKeyEvent>
#include <QMimeData>
#include <QGraphicsSceneMouseEvent>

namespace Graphics
{

    class ViewPrivater
    {
    public:
        void initView(GraphicsView * view)
        {
            view->setDragMode(QGraphicsView::RubberBandDrag);
            view->setAcceptDrops(true);
            view->setCursor(Qt::ArrowCursor);

            /// initialize data manger
            auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
            if (!appData) { return; }
            _cptAppDataMgr = appData->getComponentAppDataManger();
            _sglSimAppDataMgr = appData->getSingleSimulationAppDataManger();
            _mulSimAppDataMgr = appData->getMultiSimulationAppDataManger();
            _lineDataMgr = appData->getLineDataManger();

        }

        /**
         * @brief     canvas state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:04
         */
        State _state;

        /**
         * @brief     while draw alignment line. use to know if left button down and select graphics item move
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:07
         */
        bool _leftButtonDownAndSelectedItem{ false };

        /**
         * @brief     while draw alignment line. if < _tolerationDistance. draw alignment line
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:08
         */
        int _tolerationDistance{ 8 };

        /**
         * @brief     first selected item. used for alignment
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:14
         */
        GraphicsItem * _firstSelectedItem{};

        /**
         * @brief     view port ratio
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:14
         */
        double _viewportRatio{ 1.0 };

        /**
         * @brief     component app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:15
         */
        Data::ComponentAppDataManger * _cptAppDataMgr{};

        /**
         * @brief     single simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:15
         */
        Data::SingleSimulationAppDataManger * _sglSimAppDataMgr{};

        /**
         * @brief     line data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:16
         */
        Data::LineDataManger * _lineDataMgr{};

        /**
         * @brief     multi simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 17:16
         */
        Data::MultiSimulationAppDataManger * _mulSimAppDataMgr{};

        /**
         * @brief     nearby judgment distance
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-31 13:09
         */
        int _sensitiveDistance{ 5 };

        /**
         * @brief     indicate line item . only one exists
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 10:44
         */
        IndicateLineItem * _line{};
    };

    GraphicsView::GraphicsView(QWidget *parent /*= nullptr*/)
        : QGraphicsView(parent)
        , _private(new ViewPrivater())
    {
        _private->initView(this);
        setStyleSheet(loadQSS(":/frames/GraphicsView.qss"));
    }

    GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent /*= nullptr*/)
        : QGraphicsView(scene, parent)
        , _private(new ViewPrivater())
    {
        _private->initView(this);
        setStyleSheet(loadQSS(":/frames/GraphicsView.qss"));
    }

    GraphicsView::~GraphicsView()
    {
        if (_private)
        {
            delete _private;
            _private = nullptr;
        }
    }

    State GraphicsView::state() const
    {
        return _private->_state;
    }

    void GraphicsView::setState(const State & state)
    {
        _private->_state = state;
    }

    int GraphicsView::sensitiveDistance() const
    {
        return _private->_sensitiveDistance;
    }

    void GraphicsView::setSensitiveDistance(int distance)
    {
        _private->_sensitiveDistance = distance;
        /// because sensitive distance used with mouse move. no need to update
    }

    void GraphicsView::dragEnterEvent(QDragEnterEvent *event)
    {
        QGraphicsView::dragEnterEvent(event);
        const QMimeData * mime = event->mimeData();
        QString byte = QString(mime->data("ComponentName"));
        if (!byte.isEmpty())
            event->accept();
        else
            event->ignore();
    }

    void GraphicsView::dragMoveEvent(QDragMoveEvent *event)
    {
        Q_UNUSED(event);
    }

    void GraphicsView::dropEvent(QDropEvent *event)
    {
        /// get component name
        const QMimeData * mime = event->mimeData();
        QString componentName = QString(mime->data("ComponentName"));

        /// add component item on canvas
        GraphicsItem * item = new GraphicsItem(componentName);
        QRectF rect = item->boundingRect();
        item->setPos(mapToScene(event->pos()) - QPointF(rect.width() / 2, rect.height() / 2));
        item->setZValue(1);
        scene()->addItem(item);
        auto items = scene()->items();

        /// add single simulation app data
        _private->_cptAppDataMgr->appendDataObj(item->componentAppData());
        Data::SingleSimulationAppData * singleApp = new Data::SingleSimulationAppData();
        singleApp->copy(item->componentAppData());
        _private->_sglSimAppDataMgr->appendDataObj(singleApp);

        /// add log
        QString log = QString("Add Component App %1 %2 at %3,%4").
            arg(componentName).
            arg(ADDR(item)).
            arg(item->pos().x()).
            arg(item->pos().y());
        LOG(log);
    }

    void GraphicsView::mouseMoveEvent(QMouseEvent *event)
    {
        QGraphicsView::mouseMoveEvent(event);
        QPointF eventScenePoint = mapToScene(event->pos());

        if (_private->_state.mode == Select_Mode)
        {
        }
        else if (_private->_state.mode == Line_Mode)
        {
            /// if line state is initialize state. while mouse move. state is changed to need select from node state.
            if (_private->_state.lineState == Line_Initial_State ||
                _private->_state.lineState == Line_Need_Select_From_State)
            {
                /// while mouse nearby. graphics item output port part show
                mouseMoveNearByOutputPort(eventScenePoint);
            }
            else if (_private->_state.lineState == Line_Need_Select_To_State)
            {
                /// while mouse nearby. graphics item input port part show
                mouseMoveNearByInputPort(eventScenePoint);

                /// update indicate line item cursor position. in item coordinate
                if (_private->_line)
                    _private->_line->setCursorPos(eventScenePoint - _private->_line->pos());
            }
        }
    }

    void GraphicsView::mousePressEvent(QMouseEvent *event)
    {
        QList<QGraphicsItem *> all = items();
        QGraphicsView::mousePressEvent(event);
        if (Qt::LeftButton == event->button())
        {
            if (Line_Mode == _private->_state.mode)
            {
                if (Line_Initial_State == _private->_state.lineState ||
                    Line_Need_Select_From_State == _private->_state.lineState)
                {
                    /// in line mode. select output port as line 's begin
                    mousePressSelectOutputPort();
                }
                else if (Line_Need_Select_To_State == _private->_state.lineState)
                {
                    /// in line mode. select output port as line 's end
                    mousePressSelectInputPort();
                }
            }
            else if (Select_Mode == _private->_state.mode)
            {

            }
        }
        else if (Qt::RightButton == event->button())
        {
            if (Line_Mode == _private->_state.mode)
            {
                /// if has indicate line. cancel line
                mousePressCancelLine();
            }
        }
    }

    void GraphicsView::mouseReleaseEvent(QMouseEvent *event)
    {
        QGraphicsView::mouseReleaseEvent(event);
    }

    void GraphicsView::keyPressEvent(QKeyEvent *event)
    {
        if (event->key() == Qt::Key_Delete)
        {
            auto items = scene()->selectedItems();
            dataUpdateByRemoveItems(items);
            int iNum = items.size();
            for (int iCnt = 0; iCnt < iNum; ++iCnt)
            {
                auto item = items[iCnt];
                scene()->removeItem(item);
                delete item;
                item = nullptr;
            }
        }
        QGraphicsView::keyPressEvent(event);
    }

    void GraphicsView::mouseMoveNearByInputPort(QPointF mousePoint)
    {
        QList<QGraphicsItem *> all = items();
        for (QGraphicsItem * one : all)
        {
            /// get item port part
            GraphicsItem * item = dynamic_cast<GraphicsItem *>(one);
            if (!item) { continue; }
            PortItem * port = item->portPart();
            if (!port) { continue; }

            /// is mouse nearby item input port. manage input port state
            QPointF portPoint = port->scenePos();
            QRectF inputPortRect(
                portPoint.x() - _private->_sensitiveDistance,
                portPoint.y() - _private->_sensitiveDistance,
                port->size() + _private->_sensitiveDistance * 2,
                port->size() + _private->_sensitiveDistance * 2);

            updatePortState(port, Port_Type_Input, inputPortRect, mousePoint);
        }
    }

    void GraphicsView::mouseMoveNearByOutputPort(QPointF mousePoint)
    {
        QList<QGraphicsItem *> all = items();
        for (QGraphicsItem * one : all)
        {
            /// get item port part
            GraphicsItem * item = dynamic_cast<GraphicsItem *>(one);
            if (!item) { continue; }
            PortItem * port = item->portPart();
            if (!port) { continue; }

            /// is mouse nearby item output port. manage input port state
            QPointF portPoint = port->scenePos();
            QRectF outputPortRect(
                portPoint.x() + item->boundingRect().width() - _private->_sensitiveDistance,
                portPoint.y() - _private->_sensitiveDistance,
                port->size() + _private->_sensitiveDistance * 2,
                port->size() + _private->_sensitiveDistance * 2);

            updatePortState(port, Port_Type_Output, outputPortRect, mousePoint);
        }
    }

    void GraphicsView::updatePortState(PortItem * port, PortType type, QRectF portRect, QPointF mousePoint)
    {
        GraphicsItem * item = dynamic_cast<GraphicsItem *>(port->parentItem());
        if (!item) { return; }
        bool linked = _private->_mulSimAppDataMgr->isPortLinked(item, type == Port_Type_Input ? true : false);

        /// mouse move nearby port
        if (portRect.contains(mousePoint))
        {
            if (!linked)
                port->setPortState(type, Port_State_Nearby);
            else
                port->setPortState(type, Port_State_Selected_Nearby);
        }
        /// mouse move away port
        else
        {
            if (!linked)
                port->setPortState(type, Port_State_Normal);
            else
                port->setPortState(type, Port_State_Selected);
        }
        port->update();
    }

    void GraphicsView::mousePressSelectInputPort()
    {
        QList<QGraphicsItem *> all = items();
        for (QGraphicsItem * one : all)
        {
            /// get all port type graphics item
            PortItem * port = dynamic_cast<PortItem*> (one);
            if (!port) { continue; }

            /// if press nearby input port
            if (Port_State_Nearby != port->portState(Port_Type_Input) &&
                Port_State_Selected_Nearby != port->portState(Port_Type_Input))
            {
                continue;
            }

            /// check line self
            GraphicsItem * from = _private->_line->fromGraphicsItem();
            GraphicsItem * to = dynamic_cast<GraphicsItem *>(port->parentItem());
            if (!to) { continue; }
            if (from == to)
            {
                LOGW("Can Not Line By Self.");
                return;
            }

            /// check if already has line between this two components
            if (containsLine(from, to))
            {
                /// cancel line
                to->portPart()->setPortState(Port_Type_Input, to->portPart()->portState(Port_Type_Input) == Port_State_Nearby ? Port_State_Normal : Port_State_Selected);
                mousePressCancelLine();

                /// log warning
                QString msg = QString("Already Has Line Between %1 %2 And %3 %4. Can 't Line.").
                    arg(from->componentName()).
                    arg(ADDR(from)).
                    arg(to->componentName()).
                    arg(ADDR(to));
                LOGW(msg);
                return;
            }

            /// has pressed mouse left button nearby input port. remove indicate line item
            to->portPart()->setPortState(Port_Type_Input, to->portPart()->portState(Port_Type_Input) == Port_State_Nearby ? Port_State_Normal : Port_State_Selected);
            mousePressCancelLine();

            /// if from to component can line
            EventOper::GraphicsObjectEventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::GraphicsObjectEventOperator>("LineState");
            if (!oper) { return; }
            QList<QGraphicsObject *> objs{ from,to };
            oper->setGraphicsObject(objs);
            bool bOk = oper->triggered();
            if (!bOk) { return; }

            /// add line item
            LineItem * line = addLine(from, to);

            /// data operation
            dataUpdateByAddLine(line);

            /// log
            QString log = QString("Line From Component App %1 %2 %3 To %4")
                .arg(line->fromGraphicsItem()->componentName())
                .arg(ADDR(line->fromGraphicsItem()))
                .arg(line->toGraphicsItem()->componentName())
                .arg(ADDR(line->toGraphicsItem()));
            LOG(log);
            return;
        }
    }

    void GraphicsView::mousePressSelectOutputPort()
    {
        QList<QGraphicsItem *> all = items();
        for (QGraphicsItem * one : all)
        {
            PortItem * port = dynamic_cast<PortItem*> (one);
            if (!port) { continue; }

            /// whether press nearby output port
            if (Port_State_Nearby == port->portState(Port_Type_Output) ||
                Port_State_Selected_Nearby == port->portState(Port_Type_Output))
            {
                /// has pressed mouse left button nearby output port
                _private->_state.lineState = Line_Need_Select_To_State;
                if (!_private->_line)
                    _private->_line = new IndicateLineItem();
                _private->_line->setFromGraphicsItem(qobject_cast<GraphicsItem*>(port->parentObject()));
                _private->_line->setPos(port->outputPortPos());
                scene()->addItem(_private->_line);
                break;
            }
        }
    }

    void GraphicsView::mousePressCancelLine()
    {
        if (_private->_line &&
            scene()->items().contains(_private->_line))
        {
            GraphicsItem * item = _private->_line->fromGraphicsItem();
            if (!item) { return; }
            item->portPart()->setPortState(Port_Type_Output, Port_State_Normal);
            _private->_state.lineState = Line_Need_Select_From_State;
            scene()->removeItem(_private->_line);
            delete _private->_line;
            _private->_line = nullptr;
        }
    }

    void GraphicsView::dataUpdateByAddLine(LineItem * line)
    {
        /// create line data
        Data::LineData * lineData = new Data::LineData(line, line->fromGraphicsItem(), line->toGraphicsItem());
        _private->_lineDataMgr->appendDataObj(lineData);
        Data::ChannelDegenerate tool;
        QList<Data::Channel *> channels = tool.degenerate(line->fromGraphicsItem()->componentAppData(), line->toGraphicsItem()->componentAppData());
        for (Data::Channel * channel : channels) {
            lineData->addDegeneratedChannel(channel);
        }

        /// get data as single simulation app data. is null , it 's a multi simulation app data
        Data::SingleSimulationAppData * from = _private->_sglSimAppDataMgr->getSingleAppDataByGraphicsObject(line->fromGraphicsItem());
        Data::SingleSimulationAppData * to = _private->_sglSimAppDataMgr->getSingleAppDataByGraphicsObject(line->toGraphicsItem());
        /// remove single simulation app data. update multi simulation app data.
        if (from)
        {
            /// from item is a single simulation app
            if (to)
            {
                /// to item is a single simulation app. construct multi simulation app data. remove two single simulation app data.
                Data::MultiSimulationAppData * multi = new Data::MultiSimulationAppData();
                Data::ComponentAppData * cpt1 = new Data::ComponentAppData();
                cpt1->copy(from);
                Data::ComponentAppData * cpt2 = new Data::ComponentAppData();
                cpt2->copy(to);

                multi->addComponentAppData(cpt1);
                multi->addComponentAppData(cpt2);
                multi->addLineData(lineData);
                _private->_mulSimAppDataMgr->appendDataObj(multi);

                _private->_sglSimAppDataMgr->removeDataObj(from);
                _private->_sglSimAppDataMgr->removeDataObj(to);
            }
            else
            {
                /// to item is a multi simulation app. add line data and from component app date to to multi simulation app data. 
                Data::MultiSimulationAppData * multi = _private->_mulSimAppDataMgr->getMultiAppDataByGraphicsObject(line->toGraphicsItem());
                Data::ComponentAppData * cpt1 = new Data::ComponentAppData();
                cpt1->copy(from);

                multi->addComponentAppData(cpt1);
                multi->addLineData(lineData);

                _private->_sglSimAppDataMgr->removeDataObj(from);
            }
        }
        else
        {
            /// from item is a multi simulation app.
            if (to)
            {
                /// to item is a single simulation app. add line data and to component app date to from multi simulation app data. 
                Data::MultiSimulationAppData * multi = _private->_mulSimAppDataMgr->getMultiAppDataByGraphicsObject(line->fromGraphicsItem());
                Data::ComponentAppData * cpt2 = new Data::ComponentAppData();
                cpt2->copy(to);

                multi->addComponentAppData(cpt2);
                multi->addLineData(lineData);

                _private->_sglSimAppDataMgr->removeDataObj(to);
            }
            else
            {
                /// to item is a multi simulation app . combine two multi simulation app data
                Data::MultiSimulationAppData * multi1 = _private->_mulSimAppDataMgr->getMultiAppDataByGraphicsObject(line->fromGraphicsItem());
                Data::MultiSimulationAppData * multi2 = _private->_mulSimAppDataMgr->getMultiAppDataByGraphicsObject(line->toGraphicsItem());
                multi1->combine(multi2);
                multi1->addLineData(lineData);
                _private->_mulSimAppDataMgr->removeDataObj(multi2);
            }
        }
    }

    void GraphicsView::dataUpdateByRemoveItems(QList<QGraphicsItem *> objs)
    {
        /// dynamic update simulation app data
        QList<Data::ComponentAppData *> singles = _private->_mulSimAppDataMgr->dataUpdateByRemoveItems(objs);
        _private->_sglSimAppDataMgr->dataUpdateByRemoveItems(objs);
        for (Data::ComponentAppData * single : singles)
        {
            Data::SingleSimulationAppData * app = new Data::SingleSimulationAppData();
            app->copy(single);
            _private->_sglSimAppDataMgr->appendDataObj(app);
        }

        /// remove direct removed item and line
        for (QGraphicsItem * obj : objs)
        {
            GraphicsItem * item = dynamic_cast<GraphicsItem *>(obj);
            if (item)
            {
                Data::ComponentAppData * data = _private->_cptAppDataMgr->componentAppDataByGraphicsObject(item);
                if (!data) { continue; }
                _private->_cptAppDataMgr->removeDataObj(data);
            }
            else
            {
                LineItem * line = dynamic_cast<LineItem *>(obj);
                if (!line) { continue; }
                _private->_lineDataMgr->removeLineDataByGraphicsItem(line);
            }
        }

        /// remove no from or no to item line
        QList<QGraphicsItem *> all = scene()->items();
        for (QGraphicsItem * removed : objs)
            all.removeOne(removed);
        _private->_lineDataMgr->removeInvalidData(all);
    }

    QString GraphicsView::loadQSS(const QString & resource)
    {
        QString qss;
        QFile file(resource);
        if (file.open(QIODevice::ReadOnly))
        {
            qss = file.readAll();
            file.close();
        }
        return qss;
    }

    bool GraphicsView::containsLine(GraphicsItem * from, GraphicsItem * to)
    {
        int num = _private->_lineDataMgr->getDataCount();

        for (int index = 0; index < num; ++index)
        {
            Data::LineData * lineData = _private->_lineDataMgr->getDataByIndex(index);
            LineItem * line = dynamic_cast<LineItem *> (lineData->graphicsObject());
            if (!line) { continue; }
            if (line->fromGraphicsItem() == from &&
                line->toGraphicsItem() == to)
            {
                return true;
            }
        }
        return false;
    }

    LineItem * GraphicsView::addLine(GraphicsItem * from, GraphicsItem * to)
    {
        LineItem * line = new LineItem();
        line->setFromGraphicsItem(from);
        line->setToGraphicsItem(to);
        from->portPart()->setPortState(Port_Type_Output, Port_State_Selected);
        to->portPart()->setPortState(Port_Type_Input, Port_State_Selected);
        line->setZValue(0);
        scene()->addItem(line);
        return line;
    }

}