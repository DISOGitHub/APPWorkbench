#include "ComponentCoreDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/ComponentAppData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/SingleSimulationAppData.h"

#include "Graphics/GraphicsItem.h"

#include <QFileInfo>
#include <QSettings>
#include <QDebug>
#include <QTemporaryFile>

namespace EventHelper
{

    ComponentCoreDriver::ComponentCoreDriver(QGraphicsItem * item)
        : _process(new QProcess())
    {
        initialize(item);
    }

    ComponentCoreDriver::~ComponentCoreDriver()
    {
        if (_process)
        {
            if (_process->state() == QProcess::NotRunning)
            {
                _process->close();
            }
            else
            {
                _process->terminate();
                _process->close();
            }
            delete _process;
            _process = nullptr;
        }

    }

    void ComponentCoreDriver::setCoreAppPath(const QString & coreAppPath)
    {
        _corePath = coreAppPath;
    }

    void ComponentCoreDriver::setIniFilePath(const QString & iniFilePath)
    {
        _iniFilePath = iniFilePath;
    }

    bool ComponentCoreDriver::isRunning()
    {
        return _process->state() == QProcess::Running;
    }

    void ComponentCoreDriver::addArg(const QString & arg)
    {
        _args.append(arg);
    }

    void ComponentCoreDriver::clearArgs()
    {
        _args.clear();
    }

    void ComponentCoreDriver::start()
    {
        QFileInfo info(_corePath);
        if (!info.exists()) { return; }

        /// working directory
        QString checkEnv = info.absolutePath();
        _process->setWorkingDirectory(checkEnv);

        if (QSysInfo::productType() == "linux" ||
            QSysInfo::productType() == "ubuntu")
        {
            /// environments bashrc
            QProcessEnvironment env;
            loadBashRCEnvironmentVariables(env);

            /// environments support component app path and gl version
            QString ldLibraryEnv = env.value("LD_LIBRARY_PATH");
            QFileInfo info(_corePath);
            ldLibraryEnv = info.path() + ":" + ldLibraryEnv;
            env.insert("LD_LIBRARY_PATH", ldLibraryEnv);
            env.insert("MESA_GL_VERSION_OVERRIDE", "4.5");
            env.insert("MESA_GLLSL_VERSION_OVERRIDE", "450");

            _process->setProcessEnvironment(env);
        }
        else if (QSysInfo::productType() == "windows")
        {

            /// environments
            QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
            _process->setProcessEnvironment(env);
        }

        /// args
        QStringList useArgs;
        useArgs << "-FITKWB" << _iniFilePath << _args;

        _process->start(_corePath, useArgs);
    }

    void ComponentCoreDriver::setWithGUI(bool with)
    {
        _withGUI = with;
        /// start
        if (!_withGUI)
        {
            connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()));
            connect(_process, SIGNAL(readyReadStandardError()), this, SLOT(readStandardError()));
        }
        connect(_process, SIGNAL(finished(int)), this, SLOT(componentFinished(int)));
    }

    void ComponentCoreDriver::terminate()
    {
        if (_process->state() == QProcess::Running) {
            _process->terminate();
            if (!_process->waitForFinished(3000)) {
                _process->kill();
            }
        }
    }

    void ComponentCoreDriver::readStandardOutput()
    {
        qDebug() << "Normal:" << _process->readAllStandardOutput();
    }

    void ComponentCoreDriver::readStandardError()
    {
        qDebug() << "Error:" << _process->readAllStandardError();
    }

    void ComponentCoreDriver::componentFinished(int exitCode)
    {
        Q_UNUSED(exitCode);
        if (!_item || !_cptAppData) { return; }
        if (_cptAppData->existProject())
            _item->setComponentState(Component_Finished_State);
        else
            _item->setComponentState(Component_Normal_State);
        _item->update();
    }

    void ComponentCoreDriver::initialize(QGraphicsItem * item)
    {
        _item = dynamic_cast<Graphics::GraphicsItem *>(item);
        if (!_item) { return; }
        Data::FrameAppData * appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        Data::SingleSimulationAppDataManger * sglAppDataMgr = appData->getSingleSimulationAppDataManger();
        Data::MultiSimulationAppDataManger * mulAppDataMgr = appData->getMultiSimulationAppDataManger();
        if (!sglAppDataMgr || !mulAppDataMgr) { return; }
        _cptAppData = sglAppDataMgr->getSingleAppDataByGraphicsObject(_item);
        if (!_cptAppData)
            _cptAppData = mulAppDataMgr->getComponentAppDataByGraphicsObject(_item);
        setWithGUI(_cptAppData->withGUI());
    }

    void ComponentCoreDriver::loadBashRCEnvironmentVariables(QProcessEnvironment &env)
    {
        QTemporaryFile tempScriptFile;
        if (!tempScriptFile.open()) {
            qDebug() << "Failed to open temporary file";
            return;
        }

        const QString tempScriptPath = tempScriptFile.fileName();
        tempScriptFile.close();

        QFile scriptFile(tempScriptPath);
        if (!scriptFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to open temporary script file for writing";
            return;
        }

        QTextStream out(&scriptFile);
        out << "#!/bin/bash\n"
            << "source ~/.bashrc\n"
            << "env";

        scriptFile.close();

        QProcess chmodProc;
        chmodProc.start("chmod", { "777", tempScriptPath });
        if (!chmodProc.waitForFinished())
        {
            qDebug() << "Failed to set executable permissions on temporary script";
            return;
        }

        QProcess bashProcess;
        bashProcess.start("bash", { "-i","-l",tempScriptPath });
        if (!bashProcess.waitForStarted())
        {
            qDebug() << "Failed to start the bash process";
            return;
        }
        if (!bashProcess.waitForFinished(5000))
        {
            qDebug() << "Process failed to finish or timed out";
            return;
        }

        QByteArray output = bashProcess.readAllStandardOutput();
        QByteArray error = bashProcess.readAllStandardError();
        if (output.isEmpty())
            return;

        const QStringList lines = QString::fromUtf8(output).split('\n');
        for (const QString &line : lines) {
            int separator = line.indexOf('=');
            if (separator != -1 && separator != line.length() - 1) {
                QString name = line.left(separator);
                QString value = line.mid(separator + 1);
                env.insert(name, value);
            }
        }
    }

    EventHelper::ComponentCoreDriverManger * EventHelper::ComponentCoreDriverManger::_instance = nullptr;

    ComponentCoreDriverManger * ComponentCoreDriverManger::instance()
    {
        if (!_instance)
        {
            _instance = new ComponentCoreDriverManger();
        }
        return _instance;
    }

    ComponentCoreDriver * ComponentCoreDriverManger::getDriver(QGraphicsItem * obj)
    {
        if (_drivers.contains(obj))
            return _drivers[obj];
        else
        {

            ComponentCoreDriver * driver = new ComponentCoreDriver(obj);
            _drivers.insert(obj, driver);
            return driver;
        }
    }

    void ComponentCoreDriverManger::removeDriver(QGraphicsItem * obj)
    {
        if (_drivers.contains(obj))
        {
            ComponentCoreDriver * core = _drivers[obj];
            core->terminate();
            delete core;
            core = nullptr;
        }
    }

    ComponentCoreDriverManger::~ComponentCoreDriverManger()
    {
        while (!_drivers.isEmpty())
        {
            removeDriver(_drivers.firstKey());
        }
    }

}
