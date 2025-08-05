/**
 *
 * @file      DrawerPanel.h
 * @brief     Drawer Panel Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 10:23
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
    class PressButton;
    class DrawerWidget;
    /**
     * @brief     Drawer Panel Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 10:24
     */
    class GUI_WIDGET_API DrawerPanel : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flag
         * @return    DrawerPanel object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:24
         */
        explicit DrawerPanel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:24
         */
        ~DrawerPanel();

        /**
         * @brief     panel add drawer item
         * @param     itemName[i]. drawer item name
         * @return    GUI::DrawerWidget * . drawer item widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:25
         */
        DrawerWidget * addDrawerItem(const QString & itemName);

    protected slots:
        /**
         * @brief     update user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:25
         */
        void updateUi();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:25
         */
        void initUI();

        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:26
         */
        virtual void paintEvent(QPaintEvent* event) override;

        /**
         * @brief     drawer item names
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:26
         */
        QList<QString> _names;

        /**
         * @brief     drawer widget titles
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:27
         */
        QList<PressButton *> _titles;

        /**
         * @brief     drawer widgets
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:27
         */
        QList<DrawerWidget *> _panels;

        /**
         * @brief     panel 's layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:28
         */
        QVBoxLayout * _lay{};
    };
}