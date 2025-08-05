/**
 *
 * @file      CanvasLayoutHelperWidget.h
 * @brief     Widget to help Graphics Items Align and Layout
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 10:58
 *
 */
#pragma once
#include <QWidget>
#include <QToolBar>
#include <QHBoxLayout>

namespace GUI
{
    class MainWindow;
    class IconButton;
}

namespace EventHelper
{
    /**
     * @brief     CanvasLayoutHelperWidget. A Widget to help Graphics Items Align and Layout
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 13:07
     */
    class CanvasLayoutHelperWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. window flags
         * @return    CanvasLayoutHelperWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:55
         */
        explicit CanvasLayoutHelperWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:55
         */
        ~CanvasLayoutHelperWidget();

        /**
         * @brief     set number of selected graphics item
         * @param     itemNum[i]. number of selected graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:56
         */
        void setNumberOfItems(int itemNum);

    protected:
        /**
         * @brief     initialize ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:59
         */
        void initUi();

        /**
         * @brief     update ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 10:54
         */
        void updateUi();

        /**
         * @brief     copy icon button from main window by triggered name
         * @param     triggeredName[i]. triggered name
         * @return    GUI::IconButton * . icon button
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:08
         */
        GUI::IconButton * copyFromMainWindowIconButton(const QString & triggeredName);

    private:
        /**
         * @brief     number of selected items
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 10:57
         */
        int _itemNum{};

        /**
         * @brief     GUI::MainWindow 's pointer
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 11:06
         */
        GUI::MainWindow * _mainWindow{};

        /**
         * @brief     h box layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-19 19:47
         */
        QHBoxLayout * _lay{};
    };
}