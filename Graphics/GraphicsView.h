/**
 *
 * @file      GraphicsView.h
 * @brief     Graphics View . Handle Mouse Event Under Select Mode and Line Mode
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-31 9:38
 *
 */

#pragma once
#include "GraphicsAPI.h"
#include "Define.h"
#include <QGraphicsView>

namespace Graphics
{
    class ViewPrivater;
    class PortItem;
    class LineItem;
    class GraphicsItem;
    class GRAPHICS_API GraphicsView : public QGraphicsView
    {
        Q_OBJECT
            Q_PROPERTY(State state READ state WRITE setState)
            Q_PROPERTY(int sensitiveDistance READ sensitiveDistance WRITE setSensitiveDistance)
            friend class GraphicItem;
    public:
        /**
         * @brief     constructor
         * @param     QWidget * parent
         * @return    GraphicsView object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:39
         */
        explicit GraphicsView(QWidget *parent = nullptr);

        /**
         * @brief     constructor
         * @param     QGraphicsScene * scene Graphics Scene pointer
         * @param     QWidget * parent Parent Widget
         * @return    GraphicsView object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:39
         */
        explicit GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:40
         */
        ~GraphicsView();

        /**
         * @brief     get graphics view state
         * @return    State . graphics view state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:30
         */
        State state() const;

        /**
         * @brief     set graphics view state
         * @param     state[i] . graphics view state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:31
         */
        void setState(const State & state);

        /**
         * @brief     get graphic item parts sensitive distance
         * @return    int . sensitive distance
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:38
         */
        int sensitiveDistance() const;

        /**
         * @brief     set graphic item parts sensitive distance
         * @param     int distance . sensitive distance
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:38
         */
        void setSensitiveDistance(int distance);

    protected:

        /**
         * @brief     drag item enter graphics view. accept component item with component name
         * @param     event[i]. drag enter event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:31
         */
        void dragEnterEvent(QDragEnterEvent *event) override;

        /**
         * @brief     drag item move in graphics view
         * @param     event[i]. drag move event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:32
         */
        void dragMoveEvent(QDragMoveEvent *event) override;

        /**
         * @brief     user mouse up while drag item inside
         * @param     event[i] . drop event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:33
         */
        void dropEvent(QDropEvent *event) override;

        /**
         * @brief     Mouse Move Event. Line Mode and Select Mode need Process Event
         * @param     QMouseEvent * event. mouse move event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:52
         */
        void mouseMoveEvent(QMouseEvent *event) override;

        /**
         * @brief     Mouse Press Event. Line Mode and Select Mode need Process Event
         * @param     QMouseEvent * event. mouse press event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:54
         */
        void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief     mouse release event
         * @param     event[i]. mouse release event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:34
         */
        void mouseReleaseEvent(QMouseEvent *event) override;

        /**
         * @brief     keyboard button press event. while select items and press del button. delete items
         * @param     event[i]. keyboard button press event.
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:34
         */
        void keyPressEvent(QKeyEvent *event) override;


    private:
        /**
         * @brief     in line mode. before select input port. mouse move
         * @param     QPointF mousePoint. mouse point position
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 12:56
         */
        void mouseMoveNearByInputPort(QPointF mousePoint);

        /**
         * @brief     in line mode. before select output output. mouse move
         * @param     QPointF mousePoint. mouse point position
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 12:57
         */
        void mouseMoveNearByOutputPort(QPointF mousePoint);

        /**
         * @brief     update port state.
         * @param     PortItem * port. port pointer
         * @param     PortType type. port type
         * @param     QRectF portRect. port sensitive rect.
         * @param     QPointF mousePoint. mouse point.
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:24
         */
        void updatePortState(PortItem * port, PortType type, QRectF portRect, QPointF mousePoint);

        /**
         * @brief     in line mode . user press mouse left button to select input port
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:30
         */
        void mousePressSelectInputPort();

        /**
         * @brief     in line mode . user press mouse left button to select output port
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:31
         */
        void mousePressSelectOutputPort();

        /**
         * @brief     in line mode . user press mouse right button to cancel draw line
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 14:31
         */
        void mousePressCancelLine();

        /**
         * @brief     update data based on user 's line operation
         * @param     line[i]. line operation created line item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:55
         */
        void dataUpdateByAddLine(LineItem * line);

        /**
         * @brief     data update by user remove one or more item line object
         * @param     objs[i]. objects removed
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 9:00
         */
        void dataUpdateByRemoveItems(QList<QGraphicsItem *> objs);

        /**
        * @brief     load preset QSS
        * @param     resource[i]. preset QSS file
        * @return    QString. preset QSS file contents
        * @author    maguiwa (maguiwa520@163.com)
        * @data      2024-9-4 20:00
        */
        QString loadQSS(const QString & resource);

        /**
         * @brief     whether has line with from and to graphics item
         * @param     from[i]. from graphics item
         * @param     to[i]. to graphics item
         * @return    bool . true if contains. else false
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 14:39
         */
        bool containsLine(GraphicsItem * from, GraphicsItem * to);

        /**
         * @brief     add line
         * @param     from[i]. line 's from graphics item
         * @param     to[i]. line 's to graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 14:57
         */
        LineItem * addLine(GraphicsItem * from, GraphicsItem * to);

    private:
        /**
         * @brief     private part
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 14:11
         */
        ViewPrivater * _private{};
    };
}