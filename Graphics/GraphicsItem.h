/**
 *
 * @file      GraphicsItem.h
 * @brief     component instance item. draw on canvas. support run state . select state and so on
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 17:04
 *
 */

#pragma once
#include "GraphicsAPI.h"
#include <QGraphicsItem>
#include "Define.h"

namespace Data
{
    class ComponentAppData;
}

namespace Graphics
{
    class ItemPrivater;
    class NameItem;
    class PortItem;
    enum ComponentInputState;
    /**
     *
     * @file      GraphicsItem.h
     * @brief     graphics item . draw rectangle and icon inside. other in children items
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-29 17:02
     *
     */
    class GRAPHICS_API GraphicsItem : public QGraphicsObject
    {
        Q_OBJECT

            Q_PROPERTY(QString componentName READ componentName WRITE setComponentName)
            Q_PROPERTY(ComponentState componentState READ componentState WRITE setComponentState)
            friend class GraphicsView;
    public:
        explicit GraphicsItem(const QString & componentName, QGraphicsItem *parent = nullptr);
        virtual ~GraphicsItem();

        /**
         * @brief:    get component name
         * @return:   QString : name
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:55
         */
        QString componentName() const;

        /**
         * @brief:    set component name
         * @param:    const QString & name : name to set
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:56
         */
        void setComponentName(const QString & name);

        /**
         * @brief:    component instance state. normal calculate finished
         * @return:   ComponentState : component state
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:56
         */
        ComponentState componentState() const;

        /**
         * @brief:    set component instance state. normal calculate finished
         * @param:    ComponentState state : component state
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:57
         */
        void setComponentState(ComponentState state);

        /**
         * @brief     set component input state
         * @param     inputState[i]. component input state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 9:27
         */
        void setComponentInputState(ComponentInputState inputState);

        /**
         * @brief     get if this component is current component item
         * @return    bool . is current component item
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 10:13
         */
        bool currentComponentItem() const;

        /**
         * @brief     set if this component is current component item
         * @param     current[i] . is current component item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 10:13
         */
        void setCurrentComponentItem(bool current);

        /**
         * @brief:    paint current component item
         * @param:    QPainter * painter : painter to draw
         * @param:    const QStyleOptionGraphicsItem * option : option . not used
         * @param:    QWidget * widget : widget . not used
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:58
         */
        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = nullptr */) override;

        /**
         * @brief:    bounding rect of graphics item
         * @return:   QRectF : bounding rect
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:59
         */
        virtual QRectF boundingRect() const override;

        /**
         * @brief:    get component instance data
         * @return:   Data::ComponentInstanceData * : component instance data
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 17:00
         */
        Data::ComponentAppData * componentAppData() const;

        /**
         * @brief     Get Port Part Of the Graphic Item
         * @return    Graphics::PortItem * . Port Part
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 13:00
         */
        PortItem * portPart() const;

        /**
         * @brief     Get Name Part Of the Graphics Item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-2 16:18
         */
        NameItem * namePart() const;

    protected:
        /**
         * @brief:    double clicked item. if exist current project then open it, else start calculation
         * @param:    QGraphicsSceneMouseEvent * event : double click event
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:10
         */
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    private slots:

        /**
         * @brief:    user clicked solve menu action.
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:53
         */
        void menuItemClicked();

    private:
        /**
         * @brief     graphics item has changed
         * @param     change[i]. change info
         * @param     value[i]. change value
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-2 18:35
         */
        virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;

        /**
         * @brief:    user define component instance right button menu
         * @param:    QGraphicsSceneContextMenuEvent * event : right button event
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 16:53
         */
        virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    private:
        /**
         * @brief     item to hide graphics item implement
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 16:54
         */
        ItemPrivater *_privater{};
    };
}
