#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "DataCenter/FrameAppData.h"

#include "GUIWidget/NavigationWidget.h"
#include "GUIWidget/WidgetContainer.h"
#include "GUIWidget/IconButton.h"

#include "ProjectNavi.h"
#include "ComponentNavi.h"
#include "DescriptionNavi.h"
#include "MaterialsNavi.h"
#include "SettingNavi.h"

#include "Graphics/GraphicsScene.h"
#include "Graphics/GraphicsView.h"

#include "OutputWidget.h"
#include "FileWidget.h"
#include "TerminalWidget.h"

#include "StatusBarWidget.h"

#include <QString>
#include <QMenu>
#include <QToolBar>

#include <QSplitter>
#include <QGridLayout>
#include "ActionEventHandler.h"
#include "DataCenter/LogData.h"
#include "ToolBar.h"
#include "OperatorsInterface/FileIOOperator.h"

namespace GUI
{
    MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), _ui(new Ui::MainWindow())
    {
        _ui->setupUi(this);
        init();
    }

    MainWindow::~MainWindow()
    {
    }

    IconButton * MainWindow::iconButton(const QString & triggeredName) const
    {
        for (IconButton * btn : _toolBar->iconButtons())
        {
            if (btn->triggeredName() == triggeredName)
            {
                return btn;
            }
        }
        return nullptr;
    }

    void MainWindow::setCurrentPage(MainPage page)
    {
        _mainPage = page;
        _navi->setCurrentIndex(page);
        emit _navi->item_clicked((int)(page));
    }

    void MainWindow::init()
    {
        setWindowTitle(tr("FastCAE Platform"));
        setWindowIcon(QIcon(":/frames/title.png"));

        loadConfigs();

        initToolBar();
        initNavigationWidget();
        initCentralWidget();
        initBottomWidget();
        combineWidgets();

        setCurrentPage(Main_Page_Components);
        _output->addLog(Data::LogData("Workbench App Start.").log2String());
    }

    void MainWindow::loadConfigs()
    {

        QString cptCfgPath;
        if (QSysInfo::productType() == "windows")
            cptCfgPath = QApplication::applicationDirPath() + "/../AppComponents/Windows/";
        else if (QSysInfo::productType() == "linux" ||
            QSysInfo::productType() == "ubuntu")
            cptCfgPath = QApplication::applicationDirPath() + "/../AppComponents/Linux/";


        EventOper::FileIOOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::FileIOOperator>("FileIO");
        if (!oper) { return; }
        oper->readComponentInfo(cptCfgPath);
    }

    void MainWindow::initToolBar()
    {
        _toolBar = new ToolBar(this);
        _toolBar->addAction(":/frames/open_app_template.png", tr("Create Project From Simulation App Template."), tr("OpenAppTemplate"));
        _toolBar->addAction(":/frames/save_app_template.png", tr("Save Current Simulation App As A Template."), tr("SaveAppTemplate"));
        _toolBar->addAction(":/frames/open_project.png", tr("Open Exists Project."), tr("OpenProject"));
        _toolBar->addAction(":/frames/save_project.png", tr("Save Current Project."), tr("SaveProject"));
        _toolBar->addSeparator();

        _toolBar->addAction(":/frames/select_mode.png", tr("Switch Canvas To Select Mode."), tr("Selected"));
        _toolBar->addAction(":/frames/line_mode.png", tr("Switch Canvas To Line Mode."), tr("Line"));
        _toolBar->addSeparator();

        _toolBar->addAction(":/frames/previous.png", tr("Run Previous Component App."), tr("Previous"));
        _toolBar->addAction(":/frames/current.png", tr("Run Current Component App."), tr("Current"));
        _toolBar->addAction(":/frames/next.png", tr("Run Next Component App."), tr("Next"));
        _toolBar->addSeparator();

        _toolBar->addAction(":/frames/align_left.png", tr("Select Items Align Left."), tr("Align_Left"));
        _toolBar->addAction(":/frames/align_top.png", tr("Select Items Align Top."), tr("Align_Top"));
        _toolBar->addAction(":/frames/align_right.png", tr("Select Items Align Right."), tr("Align_Right"));
        _toolBar->addAction(":/frames/align_bottom.png", tr("Select Items Align Bottom."), tr("Align_Bottom"));
        _toolBar->addSeparator();
        _toolBar->addAction(":/frames/h_lay.png", tr("Select Items Horizontal Layout."), tr("H_Lay"));
        _toolBar->addAction(":/frames/v_lay.png", tr("Select Items Vertical Layout"), tr("V_Lay"));
        _toolBar->addSeparator();

        _toolBar->addAction(":/frames/fit.png", "Fit Screen", tr("Fit"));
        _toolBar->addAction(":/frames/scale.png", "Zoom In", tr("Enlarge"));
        _toolBar->addAction(":/frames/zoom.png", "Zoom Out", tr("Reduce"));

        ActionEventsHandler::getInstance()->handleIconButtons(_toolBar->iconButtons());
    }

    void MainWindow::initNavigationWidget()
    {
        _navi = new NavigationWidget(this);
        _navi->addIconButton(new IconButton(QIcon(":/frames/components.png"), QIcon(":/frames/components_clicked.png"), tr("Components"), this, QSize(36, 36)));
        _navi->addIconButton(new IconButton(QIcon(":/frames/projects.png"), QIcon(":/frames/projects_clicked.png"), tr("Projects"), this, QSize(36, 36)));
        _navi->addIconButton(new IconButton(QIcon(":/frames/package.png"), QIcon(":/frames/package_clicked.png"), tr("Component App Description"), this, QSize(36, 36)));
        _navi->addIconButton(new IconButton(QIcon(":/frames/materials.png"), QIcon(":/frames/materials_clicked.png"), tr("Materials"), this, QSize(36, 36)));
        _navi->addIconButton(new IconButton(QIcon(":/frames/setting.png"), QIcon(":/frames/setting_clicked.png"), tr("Settings"), this, QSize(36, 36)), false);

        _stackNavi = new QStackedWidget(this);
        _component = new ComponentNavi(this);
        _project = new ProjectNavi(this);
        _describe = new DescriptionNavi(this);
        _materials = new MaterialsNavi(this);
        _setting = new SettingNavi(this);

        _stackNavi->addWidget(_component);
        _stackNavi->addWidget(_project);
        _stackNavi->addWidget(_describe);
        _stackNavi->addWidget(_materials);
        _stackNavi->addWidget(_setting);

        _stackNavi->setCurrentIndex(0);
        _stackNavi->setMaximumWidth(400);
        connect(_navi, SIGNAL(item_clicked(int)), _stackNavi, SLOT(setCurrentIndex(int)));
    }

    void MainWindow::initCentralWidget()
    {
        _area = new QTabWidget(this);
        _area->setStyleSheet(loadQSS(":/frames/AreaTab.qss"));

        _scene = new Graphics::GraphicsScene(_area);
        _view = new Graphics::GraphicsView(_scene, _area);
        _area->addTab(_view, tr("Simulation Canvas"));
    }

    void MainWindow::initBottomWidget()
    {
        _bottom = new WidgetContainer(this);

        _output = new OutputWidget(_bottom);
        _file = new FileWidget(_bottom);
        _terminal = new TerminalWidget(_bottom);

        _bottom->addWidget(tr(" OUTPUT "), nullptr, _output);
        _bottom->addWidget(tr(" FILE "), nullptr, _file);
        _bottom->addWidget(tr(" TERMINAL "), nullptr, _terminal);

        _statusBar = new StatusBarWidget(this);
    }

    void MainWindow::combineWidgets()
    {
        QHBoxLayout *lay = new QHBoxLayout();
        _ui->centralwidget->setLayout(lay);
        lay->setSpacing(0);
        lay->setContentsMargins(0, 0, 0, 0);

        QSplitter *spliterV = new QSplitter(Qt::Vertical);
        spliterV->addWidget(_area);
        spliterV->addWidget(_bottom);
        spliterV->setSizes(QList<int>{200, 100});
        spliterV->setHandleWidth(0);

        QSplitter *spliterH = new QSplitter(Qt::Horizontal);
        spliterH->addWidget(_stackNavi);
        spliterH->addWidget(spliterV);
        spliterH->setSizes(QList<int>{100, 400});
        spliterH->setHandleWidth(0);

        QVBoxLayout *mainLay = new QVBoxLayout();
        mainLay->addWidget(_toolBar);
        mainLay->addWidget(spliterH);
        mainLay->addWidget(_statusBar);
        mainLay->setStretch(0, 0);
        mainLay->setStretch(1, 1);
        mainLay->setStretch(2, 0);

        lay->addWidget(_navi);
        lay->addLayout(mainLay);
        lay->setStretch(0, 0);
        lay->setStretch(1, 1);
    }

    QString MainWindow::loadQSS(const QString & resource)
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

}
