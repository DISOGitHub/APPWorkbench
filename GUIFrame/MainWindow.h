/**
 *
 * @file      MainWindow.h
 * @brief     Main Window.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-30 16:37
 *
 */

#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QMdiArea>
#include <QToolBar>
#include "GUIFrameAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractGUIObject.h"

namespace Ui {
    class MainWindow;
}

namespace Graphics
{
    class GraphicsView;
    class GraphicsScene;
}

namespace GUI
{
    class ActionEventHandler;
    class NavigationWidget;
    class WidgetContainer;

    class ProjectNavi;
    class ComponentNavi;
    class DescriptionNavi;
    class MaterialsNavi;
    class SettingNavi;

    class DescriptionWidget;
    class SettingWidget;

    class FileWidget;
    class OutputWidget;
    class TerminalWidget;

    class StatusBarWidget;
    class ToolBar;
    class IconButton;

    enum MainPage
    {
        /**
         * @brief     Components Page. Construct Simulation App and Run
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:38
         */
        Main_Page_Components = 0,
        /**
         * @brief     App Template and Project Manage Page
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:39
         */
        Main_Page_App_Template,
        /**
         * @brief     Component App Detail Page.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:39
         */
        Main_Page_Detail,
        /**
         * @brief     Inner Material Page
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:39
         */
        Main_Page_Material,
        /**
         * @brief     Setting Page
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:40
         */
        Main_Page_Setting,
    };

    class GUI_FRAME_API MainWindow : public QMainWindow, public Core::FITKAbstractGUIObject
    {
        Q_OBJECT
    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

        /**
         * @brief     get graphics scene
         * @return    Graphics::GraphicsScene * graphics scene
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:21
         */
        Graphics::GraphicsScene * getGraphicsScene() const { return _scene; }

        /**
         * @brief     get toolbar action
         * @param     actionName[i]. action name
         * @return    QAction * . action object pointer
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 11:08
         */
        IconButton * iconButton(const QString & actionName) const;

        /**
         * @brief     get bottom widget object pointer
         * @return    GUI::WidgetContainer * . bottom widget object pointer
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:32
         */
        WidgetContainer * bottomWidget() const { return _bottom; }

        /**
         * @brief     get output widget object pointer
         * @return    GUI::OutputWidget * . output widget object pointer
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 17:57
         */
        OutputWidget * outputWidget() const { return _output; }

        /**
         * @brief     set current page
         * @param     page[i]. current page
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:42
         */
        void setCurrentPage(MainPage page);

        /**
         * @brief     get current page
         * @return    GUI::MainPage . current page
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 9:42
         */
        MainPage currentPage() const { return _mainPage; }

        /**
         * @brief     get project navigation widget
         * @return    GUI::ProjectNavi * . project navigation widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 10:04
         */
        ProjectNavi * projectNavi() const { return _project; }
    private:


        /**
         * @brief     initialize main window
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:20
         */
        void init();

        /**
         * @brief:    load packaged components
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 16:50
         */
        void loadConfigs();

        /**
         * @brief:    initialize tool bar
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 16:39
         */
        void initToolBar();

        /**
         * @brief:    initialize navigation widget.
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 16:51
         */
        void initNavigationWidget();

        /**
         * @brief     initialize central widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:22
         */
        void initCentralWidget();

        /**
         * @brief     initialize bottom widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:23
         */
        void initBottomWidget();

        /**
         * @brief     set MainWindow layout
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 9:24
         */
        void combineWidgets();

        /**
         * @brief     load preset QSS
         * @param     resource[i]. preset QSS file
         * @return    QString. preset QSS file contents
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 20:00
         */
        QString loadQSS(const QString & resource);

    private:
        /**
         * @brief     recored current page type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:55
         */
        MainPage _mainPage{ Main_Page_Components };

        /**
         * @brief     main window 's tool bar
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:55
         */
        ToolBar * _toolBar{};

        /**
         * @brief     navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:56
         */
        NavigationWidget *_navi{};

        /**
         * @brief     stack widget contains all sub navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:56
         */
        QStackedWidget *_stackNavi{};

        /**
         * @brief     stack widget contains all main widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:58
         */
        QStackedWidget * _stack{};

        /**
         * @brief     bottom part widgets
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:58
         */
        WidgetContainer *_bottom{};

        /**
         * @brief     project navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:58
         */
        ProjectNavi *_project{};

        /**
         * @brief     component navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:59
         */
        ComponentNavi *_component{};

        /**
         * @brief     description navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 9:59
         */
        DescriptionNavi *_describe{};

        /**
         * @brief     material navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:00
         */
        MaterialsNavi *_materials{};

        /**
         * @brief     setting navigation widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:01
         */
        SettingNavi *_setting{};

        /**
         * @brief     area tab widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:01
         */
        QTabWidget *_area{};

        /**
         * @brief     graphics scene
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:01
         */
        Graphics::GraphicsScene *_scene{};

        /**
         * @brief     graphics view
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:01
         */
        Graphics::GraphicsView *_view{};

        /**
         * @brief     bottom output widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:02
         */
        OutputWidget *_output{};

        /**
         * @brief     bottom file widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:02
         */
        FileWidget *_file{};

        /**
         * @brief     bottom terminal widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:02
         */
        TerminalWidget *_terminal{};

        /**
         * @brief     status bar widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:03
         */
        StatusBarWidget *_statusBar{};

        /**
         * @brief     main window ui
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 10:03
         */
        Ui::MainWindow * _ui{};

        Q_DISABLE_COPY(MainWindow)
    };
}