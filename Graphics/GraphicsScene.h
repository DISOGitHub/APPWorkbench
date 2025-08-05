/**
 *
 * @file      GraphicsScene.h
 * @brief     Graphics Scene. Draw Background and Auto Scale
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 16:32
 *
 */
#pragma once
#include "GraphicsAPI.h"
#include "Define.h"
#include <QGraphicsScene>

namespace Graphics
{
    class ScenePrivater;
    class GraphicsItem;
    class GraphicsLineItem;
    /**
     * @brief     Graphics Scene Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 16:33
     */
    class GRAPHICS_API GraphicsScene : public QGraphicsScene
    {
        Q_OBJECT

            Q_PROPERTY(QPen darkPen READ darkPen WRITE setDarkPen)
            Q_PROPERTY(QPen lightPen READ lightPen WRITE setLightPen)
            Q_PROPERTY(SceneInterval sceneInterval READ sceneInterval WRITE setSceneInterval)
            Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid)
    public:
        /**
         * @brief     scene background grid interval
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:33
         */
        struct SceneInterval
        {
            /**
             * @brief     big grid interval
             * @author    maguiwa(maguiwa520@163.com)
             * @date      2024-9-24 16:34
             */
            int bigInterval{ 50 };
            /**
             * @brief     small grid interval
             * @author    maguiwa(maguiwa520@163.com)
             * @date      2024-9-24 16:34
             */
            int smallInterval{ 25 };
        };

        /**
         * @brief     constructor
         * @param     parent[i]. parent object
         * @return    GraphicsScene object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:34
         */
        explicit GraphicsScene(QObject *parent = nullptr);

        /**
         * @brief     constructor
         * @param     sceneRect[i]. scene rect
         * @param     parent[i]. parent object
         * @return    GraphicsScene object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:35
         */
        explicit GraphicsScene(const QRectF &sceneRect, QObject *parent = nullptr);

        /**
         * @brief     constructor
         * @param     x[i]. scene pos x
         * @param     y[i]. scene pos y
         * @param     width[i]. scene width
         * @param     height[i]. scene height
         * @param     parent[i]. parent object
         * @return    GraphicsScene object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:36
         */
        explicit GraphicsScene(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:37
         */
        virtual ~GraphicsScene();

        /**
         * @brief     get big background grid pen
         * @return    QPen . big background grid pen
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:37
         */
        QPen darkPen() const;

        /**
         * @brief     set big background grid pen
         * @param     pen[i] . big background grid pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:38
         */
        void setDarkPen(QPen pen);

        /**
         * @brief     get small background grid pen
         * @return    QPen . small background grid pen
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:38
         */
        QPen lightPen() const;

        /**
         * @brief     set small background grid pen
         * @param     pen[i] . small background grid pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:38
         */
        void setLightPen(QPen pen);

        /**
         * @brief     get if show background grid
         * @return    bool . is show background grid
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:39
         */
        bool showGrid() const;

        /**
         * @brief     set show background grid
         * @param     show[i] . show
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:43
         */
        void setShowGrid(bool show);

        /**
         * @brief     get background grid interval
         * @return    Graphics::GraphicsScene::SceneInterval . background grid interval
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:44
         */
        SceneInterval sceneInterval() const;

        /**
         * @brief     set background grid interval
         * @param     interval[i] . background grid interval
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:44
         */
        void setSceneInterval(SceneInterval interval);

        /**
         * @brief     while item out scene. update scene rect to contains item.
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:45
         */
        void updateSceneRect();

        /**
         * @brief     set canvas mode
         * @param     mode[i] . canvas mode
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:46
         */
        void setCanvasMode(CanvasMode mode);

        /**
         * @brief     get canvas mode
         * @return    CanvasMode . canvas mode
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:46
         */
        CanvasMode canvasMode() const;

        /**
         * @brief     draw background
         * @param     painter[i]. painter
         * @param     rect[i]. draw rect
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:46
         */
        void drawBackground(QPainter *painter, const QRectF &rect) override;

        /**
        * @brief     update current item 's relation lines
        * @param     item[i]. current graphics item
        * @return    void
        * @author    maguiwa (maguiwa520@163.com)
        * @data      2024-9-2 18:39
        */
        virtual void updateLineItem(GraphicsItem * item);

        /**
         * @brief     get current selected component item list
         * @return    QList<GraphicsItem *> . component item list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 13:59
         */
        QList<GraphicsItem *> selectedComponents() const;

    private slots:
        /**
         * @brief     in scene. selection has changed
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:10
         */
        void onSelectionChanged();

    private:
        /**
         * @brief     Graphics Scene Private Part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 16:42
         */
        ScenePrivater * _privater{};
    };
}