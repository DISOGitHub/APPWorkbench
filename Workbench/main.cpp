#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "MainWindowGenerator.h"
#include "GlobalDataFactory.h"
#include "ComponentFactory.h"
#include "WorkbenchSettings.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#endif // Q_OS_WIN

int main(int argc, char *argv[])
{
    //控制图片缩放质量
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    // 初始化应用框架
    AppFrame::FITKApplication app(argc, argv);

#ifdef Q_OS_LINUX
    qputenv("PYTHONHOME", app.applicationDirPath().toUtf8() + "/../Python37");

    QStringList pythonPaths;
    pythonPaths << app.applicationDirPath() + "/../Python37/bin";
    pythonPaths << app.applicationDirPath() + "/../Python37/lib";
    pythonPaths << app.applicationDirPath() + "/../Python37/lib/python3.7";
    pythonPaths << app.applicationDirPath() + "/../Python37/lib/python3.7/site-packages";
    pythonPaths << app.applicationDirPath() + "/../Python37/lib/python3.7/lib-dynload";
    qputenv("PYTHONPATH", pythonPaths.join(":").toUtf8());
#endif

    // 注册程序的主要组件和设置
    app.regMainWindowGenerator(new MainWindowGenerator); // 注册主窗口生成器
    app.regGlobalDataFactory(new GlobalDataFactory);     // 注册全局数据工厂
    app.regComponentsFactory(new ComponentFactory);      // 注册组件工厂
    app.regAppSettings(new WorkbenchSettings);             // 注册应用结构设置

    return app.exec();
}

