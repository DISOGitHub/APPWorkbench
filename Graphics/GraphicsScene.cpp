#include "GraphicsScene.h"
#include "GraphicsView.h"

#include <QGraphicsItem>
#include <cmath>
#include "LineItem.h"
#include "OperatorsInterface/EventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "GraphicsItem.h"

namespace Graphics
{
    class ScenePrivater
    {
    public:
        /**
         * @brief     background big background grid pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:47
         */
        QPen _darkPen{ QPen(QBrush(QColor(230,230,230)),1,Qt::DashDotLine) };
        /**
         * @brief     background small background grid pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:48
         */
        QPen _lightPen{ QPen(QBrush(QColor(245,245,245)),1,Qt::DashLine) };
        /**
         * @brief     if show background grid
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:48
         */
        bool _showGrid{ true };
        /**
         * @brief     graphics background grid interval
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:49
         */
        GraphicsScene::SceneInterval _interval;
        /**
         * @brief     canvas mode
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:49
         */
        CanvasMode _canvasMode{ Select_Mode };
        /**
         * @brief     while change scene rect. factor size.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:49
         */
        QSize _sceneSizeFactor{ QSize(1000,1000) };
        /**
         * @brief     graphics scene original size
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:50
         */
        QSize _sceneOrignSize{ QSize(2000,2000) };
    };

    GraphicsScene::GraphicsScene(QObject *parent /*= nullptr*/)
        : QGraphicsScene(parent)
        , _privater(new ScenePrivater)
    {
        setSceneRect(0, 0, _privater->_sceneOrignSize.width(), _privater->_sceneOrignSize.height());
        connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
    }

    GraphicsScene::GraphicsScene(const QRectF &sceneRect, QObject *parent /*= nullptr*/)
        : QGraphicsScene(sceneRect, parent)
        , _privater(new ScenePrivater)
    {
        setSceneRect(0, 0, _privater->_sceneOrignSize.width(), _privater->_sceneOrignSize.height());
        connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
    }

    GraphicsScene::GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent /*= nullptr*/)
        : QGraphicsScene(x, y, width, height, parent)
        , _privater(new ScenePrivater)
    {
        setSceneRect(0, 0, _privater->_sceneOrignSize.width(), _privater->_sceneOrignSize.height());
        connect(this, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));
    }

    GraphicsScene::~GraphicsScene()
    {
        if (_privater)
        {
            delete _privater;
            _privater = nullptr;
        }
    }

    QPen GraphicsScene::darkPen() const
    {
        return _privater->_darkPen;
    }

    void GraphicsScene::setDarkPen(QPen pen)
    {
        _privater->_darkPen = pen;
        update();
    }

    QPen GraphicsScene::lightPen() const
    {
        return _privater->_lightPen;
    }

    void GraphicsScene::setLightPen(QPen pen)
    {
        _privater->_lightPen = pen;
        update();
    }

    bool GraphicsScene::showGrid() const
    {
        return _privater->_showGrid;
    }

    void GraphicsScene::setShowGrid(bool show)
    {
        _privater->_showGrid = show;
        update();
    }

    Graphics::GraphicsScene::SceneInterval GraphicsScene::sceneInterval() const
    {
        return _privater->_interval;
    }

    void GraphicsScene::setSceneInterval(SceneInterval interval)
    {
        _privater->_interval = interval;
    }

    void GraphicsScene::updateSceneRect()
    {
        int leftOut = 0, rightOut = 0, topOut = 0, bottomOut = 0;
        for (auto item : items())
        {
            if (item->parentItem()) { continue; }

            auto topLeft = item->pos().toPoint() + item->boundingRect().topLeft().toPoint();
            auto bottomRight = item->pos().toPoint() + item->boundingRect().bottomRight().toPoint();

            if (topLeft.x() < 0)
                leftOut = std::max(leftOut, -topLeft.x());
            if (bottomRight.x() > _privater->_sceneOrignSize.width())
                rightOut = std::max(rightOut, bottomRight.x() - _privater->_sceneOrignSize.width());
            if (topLeft.y() < 0)
                topOut = std::max(topOut, -topLeft.y());
            if (bottomRight.y() > _privater->_sceneOrignSize.height())
                bottomOut = std::max(bottomOut, bottomRight.y() - _privater->_sceneOrignSize.height());
        }
        int upNum = 0, downNum = 0, leftNum = 0, rightNum = 0;
        topOut != 0 ? upNum = topOut / _privater->_sceneSizeFactor.height() + 1 : 0;
        bottomOut != 0 ? downNum = bottomOut / _privater->_sceneSizeFactor.height() + 1 : 0;
        leftOut != 0 ? leftNum = leftOut / _privater->_sceneSizeFactor.width() + 1 : 0;
        rightOut != 0 ? rightNum = rightOut / _privater->_sceneSizeFactor.width() + 1 : 0;

        auto rect = QRectF(QPointF(-leftNum * _privater->_sceneSizeFactor.width(),
            -upNum * _privater->_sceneSizeFactor.height()),
            QPointF(rightNum * _privater->_sceneSizeFactor.width() + _privater->_sceneOrignSize.width(),
                bottomOut * _privater->_sceneSizeFactor.height() + _privater->_sceneOrignSize.height()));

        setSceneRect(rect);
    }

    void GraphicsScene::setCanvasMode(CanvasMode mode)
    {
        _privater->_canvasMode = mode;
        for (auto item : items())
            item->setSelected(false);

        State state;
        state.mode = mode;

        if (mode == Line_Mode)
            state.lineState = Line_Initial_State;
        else if (mode == Select_Mode)
            state.selectState = Select_Initial_State;

        for (auto view : views())
        {
            GraphicsView * real = dynamic_cast<GraphicsView*>(view);
            if (real)
            {
                real->setState(state);
                real->update();
            }
        }
    }

    CanvasMode GraphicsScene::canvasMode() const
    {
        return _privater->_canvasMode;
    }

    void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
    {
        if (!_privater->_showGrid)
        {
            return QGraphicsScene::drawBackground(painter, rect);
        }
        Q_UNUSED(rect);
        auto sceneRect = this->sceneRect();
        int width = sceneRect.width();
        int height = sceneRect.height();

        int xNum = width / _privater->_interval.bigInterval;
        int yNum = height / _privater->_interval.bigInterval;
        int subNum = ceil(_privater->_interval.bigInterval / (double)_privater->_interval.smallInterval) - 1;

        painter->setPen(_privater->_darkPen);
        for (int iCnt = 0; iCnt <= xNum; ++iCnt)
        {
            int xPos = sceneRect.x() + iCnt * _privater->_interval.bigInterval;
            painter->drawLine(QPoint(xPos, sceneRect.y()), QPoint(xPos, height));
        }

        for (int iCnt = 0; iCnt <= yNum; ++iCnt)
        {
            int yPos = sceneRect.y() + iCnt * _privater->_interval.bigInterval;
            painter->drawLine(QPoint(sceneRect.x(), yPos), QPoint(width, yPos));
        }

        painter->setPen(_privater->_lightPen);
        for (int iCnt = 0; iCnt < xNum; ++iCnt)
        {
            int xPos = sceneRect.x() + iCnt * _privater->_interval.bigInterval;
            for (int iSub = 0; iSub < subNum; ++iSub)
            {
                int xSubPos = xPos + _privater->_interval.smallInterval *(iSub + 1);
                painter->drawLine(QPoint(xSubPos, sceneRect.y()), QPoint(xSubPos, height));
            }
        }
        for (int iCnt = 0; iCnt <= yNum; ++iCnt)
        {
            int yPos = sceneRect.y() + iCnt * _privater->_interval.bigInterval;
            for (int iSub = 0; iSub < subNum; ++iSub)
            {
                int ySubPos = yPos + _privater->_interval.smallInterval *(iSub + 1);
                painter->drawLine(QPoint(sceneRect.x(), ySubPos), QPoint(width, ySubPos));
            }
        }
        QGraphicsScene::drawBackground(painter, rect);
    }

    void GraphicsScene::updateLineItem(GraphicsItem * item)
    {
        for (auto one : items())
        {
            LineItem * line = dynamic_cast<LineItem *>(one);
            if (!line) { continue; }

            if (line->fromGraphicsItem() == item)
                line->setFromGraphicsItem(item);
            else if (line->toGraphicsItem() == item)
                line->setToGraphicsItem(item);
        }
    }

    QList<GraphicsItem *> GraphicsScene::selectedComponents() const
    {
        QList<GraphicsItem *> results;
        for (auto one : selectedItems())
        {
            GraphicsItem * item = dynamic_cast<GraphicsItem *>(one);
            if (item)
                results.append(item);
        }
        return results;
    }

    void GraphicsScene::onSelectionChanged()
    {
        EventOper::EventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::EventOperator>("CanvasSelectionChanged");
        if (oper)
            oper->triggered();
    }

}