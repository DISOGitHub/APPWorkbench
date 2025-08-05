/**
 *
 * @file      DrawerWidget.h
 * @brief     Drawer Panel Inner Drawer Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 10:18
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QVBoxLayout>
#include <QFrame>
#include "DescriptionItem.h"

namespace GUI
{
    class ComponentItem;
    /**
     * @brief     Drawer Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 10:18
     */
    class GUI_WIDGET_API DrawerWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flag
         * @return    DrawerWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:19
         */
        explicit DrawerWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:19
         */
        ~DrawerWidget();

        /**
         * @brief     add component item into drawer widget. component item and description item can only exists one
         * @param     item[i]. component item added in
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 14:03
         */
        void addComponentItem(ComponentItem * item);

        /**
         * @brief     add description item into drawer widget. component item and description item can only exists one
         * @param     item[i]. description item added in
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 14:06
         */
        void addDescriptionItem(DescriptionItem * item);

        /**
         * @brief     update ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 14:11
         */
        void updateUi();

    protected:
        /**
         * @brief     widget resize event
         * @param     event[i]. resize event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:19
         */
        virtual void resizeEvent(QResizeEvent* event) override;

    private:

        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:20
         */
        void initUi();

        /**
         * @brief     update component user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:20
         */
        void updateComponentUi();

        /**
         * @brief     update description user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:20
         */
        void updateDescriptionUi();

        /**
         * @brief     component item list
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 14:06
         */
        QList<ComponentItem *> _cptItems;

        /**
         * @brief     description item list
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 14:07
         */
        QList<DescriptionItem *> _descItems;

        /**
         * @brief     widget min width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:21
         */
        int _minWidth = 100;

        /**
         * @brief     component border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:21
         */
        int _componentBorderWidth = 18;

        /**
         * @brief     border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:22
         */
        int _border{ 20 };

        /**
         * @brief     spacing width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:22
         */
        int _spacing{ 20 };

        /**
         * @brief     inner widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:23
         */
        QWidget * _inner{};

        /**
         * @brief     inner widget grid layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:23
         */
        QGridLayout * _gridLay{};
    };
}