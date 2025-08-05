#include "ComponentAppStateHelper.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/SingleSimulationAppData.h"
#include "DataCenter/MultiSimulationAppData.h"

#include "IniFileReader.h"
#include "IniFileWriter.h"
#include "ComponentCoreDriver.h"
#include "Graphics/GraphicsItem.h"
#include "Graphics/StateItem.h"

#include <QSettings>
#include <QSet>
#include <QDateTime>
#include "DataCenter/TransferData.h"
#include "OperatorsInterface/MultiEventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp"
#include "DataCenter/TransferFileData.h"
#include "DataCenter/TransferFolderData.h"
#include "DataCenter/TransferFilesData.h"


namespace EventHelper
{

    ComponentAppStateHelper::ComponentAppStateHelper(Data::SimulationAppData * app, Data::ComponentAppData * cpt)
        : _app(app)
        , _cpt(cpt)
    {
        Data::FrameAppData * appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        _lineDataMgr = appData->getLineDataManger();
        _fileMonitorAdd = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::MultiEventOperator>("AddTransfer");
    }

    ComponentAppStateHelper::~ComponentAppStateHelper()
    {

    }

    ComponentCanSolveState ComponentAppStateHelper::isComponentCanSolve()
    {
        if (Data::Simulation_App_Multi_Component_App == _app->simulationAppType())
        {
            Data::MultiSimulationAppData * multi = dynamic_cast<Data::MultiSimulationAppData *> (_app);
            if (multi)
            {
                return isComponentCanSolveInMultiSimulationApp(multi);
            }
        }
        else if (Data::Simulation_App_Single_Component_App == _app->simulationAppType())
        {
            Data::SingleSimulationAppData * single = dynamic_cast<Data::SingleSimulationAppData *> (_app);
            if (single)
            {
                return isComponentCanSolveInSingleSimulationApp(single);
            }
        }
    }

    void ComponentAppStateHelper::prepareOpenProjectIni()
    {
        QString openProjectIni = _cpt->iniFilePath() + "/open_project.ini";
        QFile file(openProjectIni);
        if (file.exists())
        {
            return;
        }

        IniFileWriter writer(openProjectIni);
        writer.setFilePath(openProjectIni);
        writer.setBasePath(_cpt->outputPath());
        writer.setOpenProjectMode(true);

        IniInputFiles inputFiles;
        IniFileDesc desc;
        desc.name = _cpt->projectFileInfo().fileName();
        desc.desc = "project file";
        desc.path = _cpt->projectFileInfo().path();
        desc.type = "File";
        desc.suffix = _cpt->projectFileInfo().suffix();
        inputFiles.append(desc);

        writer.setInputFiles(inputFiles);
        writer.write();
        return;
    }

    void ComponentAppStateHelper::componentAppRun(bool run /*= true*/)
    {
        auto mgr = EventHelper::ComponentCoreDriverManger::instance();
        auto driver = mgr->getDriver(_cpt->graphicsObject());
        driver->clearArgs();
        driver->setCoreAppPath(_cpt->path());

        if (run)
        {
            driver->setIniFilePath(_cpt->iniFilePath() + "/project.ini");
            /// only run can change component app 's input state
            Graphics::GraphicsItem * item = qobject_cast<Graphics::GraphicsItem *>(_cpt->graphicsObject());
            if (item)
                item->setComponentInputState(Graphics::State_Normal);
        }
        else
            driver->setIniFilePath(_cpt->iniFilePath() + "/open_project.ini");

        for (QString paramName : _cpt->additionalInputParamNames())
        {
            Data::AdditionalInputParam param = _cpt->additionalInputParam(paramName);
            if (param.defaultUse && !param.userSet)
            {
                driver->addArg(param.argv);
            }
        }
        driver->start();

        /// multi simulation app need set current component app
        if (Data::Simulation_App_Multi_Component_App == _app->simulationAppType())
        {
            Data::MultiSimulationAppData * multi = dynamic_cast<Data::MultiSimulationAppData *> (_app);
            multi->setCurrentComponentAppData(_cpt);
        }

        /// update component app graphics object state
        updateComponentAppGraphicsObjectState(_cpt);
    }

    void ComponentAppStateHelper::updateComponentAppGraphicsObjectState(Data::ComponentAppData * current)
    {
        /// update current run  component app 's state
        QGraphicsItem * item = current->graphicsObject();
        if (!item) { return; }
        Graphics::GraphicsItem * real = dynamic_cast<Graphics::GraphicsItem *>(item);
        if (!real) { return; }
        real->setComponentState(Component_Calculate_State);

        if (Data::Simulation_App_Multi_Component_App == _app->simulationAppType())
        {
            Data::MultiSimulationAppData * multi = dynamic_cast<Data::MultiSimulationAppData *>(_app);
            if (!multi) { return; }
            for (Data::ComponentAppData * cptData : multi->componentAppDatas())
            {
                if (cptData == current) { continue; }
                Graphics::GraphicsItem * other = dynamic_cast<Graphics::GraphicsItem *>(cptData->graphicsObject());
                if (!other) { return; }
                other->setCurrentComponentItem(false);
                other->update();
            }
        }

        real->setCurrentComponentItem(true);
        real->update();
    }

    EventHelper::ComponentCanSolveState ComponentAppStateHelper::isComponentCanSolveInMultiSimulationApp(Data::MultiSimulationAppData * multi)
    {
        /// check component state
        ComponentCanSolveState state;
        if (!_cpt || !multi)
        {
            state.enumState = Input_Param_Error;
            return state;
        }

        /// check is valid simulation app data
        if (!multi->isValidSimulationAppData())
        {
            state.enumState = Component_Input_Error;
            return state;
        }

        /// if cpt 's ini file already exist and set input ok. return true.
        if (!_cpt->projectPath().isEmpty() &&
            isIniFileExistAndWithValidInput(_cpt->iniFilePath() + "/project.ini"))
        {
            state.enumState = Can_Solve;
            return state;
        }

        QList<Data::ComponentAppData *> apps = multi->getPreviousLinkedComponentApps(_cpt);
        /// if cpt is the first level(one of components that in degree number equals to 0 . natural can solve)
        if (apps.isEmpty() && _cpt->inputChannel("None")) {
            ensureMultiSimulationAppProjectPathExists(multi);
            setComponentAppIniInputFiles(_cpt, IniInputFiles());
            state.enumState = Natural_Can_Solve;
            return state;
        }

        /// check all previous component has solved. exists project.
        for (Data::ComponentAppData * app : apps)
        {
            if (!app->existProject())
            {
                /// not exists . need solve previous first
                state.enumState = Previous_Component_Not_Solved;
                state.relatedCpt = app;
                return state;
            }
        }

        /// get all previous component 's ini info. use ini info to fit input
        return isComponentCanSolveInner(apps);
    }

    void ComponentAppStateHelper::ensureMultiSimulationAppProjectPathExists(Data::MultiSimulationAppData * multi)
    {
        QString projectPath = multi->projectPath();
        if (projectPath.isEmpty())
        {
            /// first time run in degree value 0 component app item. create all project file path
            QString basePath = QDir::cleanPath(qApp->applicationDirPath() + "/../Projects");
            QString folder = basePath + "/" + "project_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
            QDir dir;
            dir.mkdir(folder);
            if (!dir.exists(folder))
            {
                return;
            }
            multi->setProjectPath(folder);

            /// create component app project path
            for (Data::ComponentAppData * cpt : multi->componentAppDatas())
            {
                cpt->setProjectPath(folder);
                dir.mkdir(cpt->iniFilePath());
                dir.mkdir(cpt->inputPath());
                dir.mkdir(cpt->outputPath());
            }
        }
        else
        {
            /// already exist project path . may dynamic add or remove component app item. dynamic check and ensure reference file path
            for (Data::ComponentAppData * cpt : multi->componentAppDatas())
            {
                if (cpt->projectPath().isEmpty())
                {
                    cpt->setProjectPath(multi->projectPath());
                    QDir dir;
                    dir.mkdir(cpt->iniFilePath());
                    dir.mkdir(cpt->inputPath());
                    dir.mkdir(cpt->outputPath());
                }
            }
        }

    }

    void ComponentAppStateHelper::ensureSingleSimulationAppProjectPathExists(Data::SingleSimulationAppData * single)
    {
        QString projectPath = single->projectPath();
        if (projectPath.isEmpty())
        {
            /// first time run in degree value 0 component app item. create component project file path
            QString basePath = QDir::cleanPath(qApp->applicationDirPath() + "/../Projects");
            QString folder = basePath + "/" + "project_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss");
            QDir dir;
            dir.mkdir(folder);
            if (!dir.exists(folder))
            {
                return;
            }
            single->setProjectPath(folder);
            dir.mkdir(single->iniFilePath());
            dir.mkdir(single->inputPath());
            dir.mkdir(single->outputPath());
        }
    }

    EventHelper::ComponentCanSolveState ComponentAppStateHelper::isComponentCanSolveInSingleSimulationApp(Data::SingleSimulationAppData * single)
    {
        /// check component state
        ComponentCanSolveState state;
        if (!single)
        {
            state.enumState = Input_Param_Error;
            return state;
        }

        /// check is valid simulation app data
        if (!single->isValidSimulationAppData())
        {
            state.enumState = Component_Input_Error;
            return state;
        }

        /// if cpt 's ini file already exist and set input ok. return true.
        if (!_cpt->projectPath().isEmpty() &&
            isIniFileExistAndWithValidInput(_cpt->iniFilePath() + "/project.ini"))
        {
            state.enumState = Can_Solve;
            return state;
        }

        /// if cpt can natural run
        if (_cpt->inputChannel("None"))
        {
            ensureSingleSimulationAppProjectPathExists(single);
            setComponentAppIniInputFiles(_cpt, IniInputFiles());
            state.enumState = Natural_Can_Solve;
            return state;
        }

        state.enumState = Can_Not_Be_Single_Simulation;
        return state;
    }

    EventHelper::ComponentCanSolveState ComponentAppStateHelper::isComponentCanSolveInner(QList<Data::ComponentAppData * > previous)
    {
        EventHelper::ComponentCanSolveState state;
        if (previous.size() == 1)
        {
            /// get line 's degenerated channels
            QGraphicsObject * from = previous.first()->graphicsObject();
            QGraphicsObject * to = _cpt->graphicsObject();
            Data::LineData * line = _lineDataMgr->getLineDataByFromToGraphicsItem(from, to);
            if (!line) { return state; }
            QList<Data::Channel *> channels = line->degeneratedChannels();

            /// folder type first check
            QList<Data::Channel *> folderChannels = folderTypeChannels(channels);
            state = isMeetFolderTypeChannels(previous.first(), folderChannels);
            if (state.enumState == Can_Solve || state.enumState == Can_Solve_With_Multi)
            {
                return state;
            }

            /// file type channel check
            QList<Data::Channel *> fileChannels = fileTypeChannels(channels);
            state = isMeetFileTypeChannels(previous.first(), fileChannels);
            if (state.enumState == Can_Solve || state.enumState == Can_Solve_With_Multi)
            {
                return state;
            }

            /// files type channel check
            QList<Data::Channel *> filesChannels = filesTypeChannels(channels);
            state = isMeetFilesTypeChannels(previous.first(), filesChannels);
            if (state.enumState == Can_Solve || state.enumState == Can_Solve_With_Multi)
            {
                return state;
            }
        }
        else
        {
            /// multi line . direct into filePath.
            return multiMeetFilesTypeChannels(previous);
        }
        return state;
    }

    QList<Data::Channel *> ComponentAppStateHelper::folderTypeChannels(QList<Data::Channel *> channels)
    {
        QList<Data::Channel *> result;
        for (Data::Channel * channel : channels)
        {
            if (channel->channelType == Data::Channel_Folder_Type)
            {
                result.append(channel);
            }
        }
        return result;
    }

    QList<Data::Channel *> ComponentAppStateHelper::fileTypeChannels(QList<Data::Channel *> channels)
    {
        QList<Data::Channel *> result;
        for (Data::Channel * channel : channels)
        {
            if (channel->channelType == Data::Channel_File_Type)
            {
                result.append(channel);
            }
        }
        return result;
    }

    QList<Data::Channel *> ComponentAppStateHelper::filesTypeChannels(QList<Data::Channel *> channels)
    {
        QList<Data::Channel *> result;
        for (Data::Channel * channel : channels)
        {
            if (channel->channelType == Data::Channel_Files_Type)
            {
                result.append(channel);
            }
        }
        return result;
    }

    ComponentCanSolveState ComponentAppStateHelper::isMeetFolderTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels)
    {
        /// construct global data
        ComponentCanSolveState state;
        IniOutputFiles outputFiles = getComponentAppIniOutputFiles(from, false);
        IniInputFiles inputFiles;

        if (!outputFiles.isEmpty()) {
            /// fit by ini file
            IniInputFiles inputFiles;
            for (Data::Channel * channel : channels)
            {
                Data::FolderChannel * folderChannel = (Data::FolderChannel *) channel;
                for (IniFileDesc desc : outputFiles)
                {
                    /// folder type channel means only fit one. then fit
                    if (folderChannel->supports.contains(desc.suffix))
                    {
                        inputFiles.append(desc);
                    }
                }
            }
            if (inputFiles.size() >= 1)
                return stateWithInputCondition(inputFiles);
        }

        /// fit by folder
        for (Data::Channel * channel : channels)
        {
            Data::FolderChannel * folderChannel = (Data::FolderChannel *) channel;

            QDir dir(from->outputPath());
            QSet <QString> types;
            for (QFileInfo info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
            {
                types.insert(info.suffix());
            }

            QSet<QString> supports(folderChannel->supports.begin(), folderChannel->supports.end());
            if (supports.intersects(types))
            {
                QSet<QString> meets = supports.intersect(types);

                IniFileDesc desc;
                desc.path = from->outputPath();
                for (QString type : meets) {
                    desc.suffix += type;
                    desc.suffix += ",";
                }
                /// remove last comma
                desc.suffix = desc.suffix.left(desc.suffix.size() - 1);
                desc.type = "Folder";
                inputFiles.append(desc);
            }
        }
        return stateWithInputCondition(inputFiles);
    }

    ComponentCanSolveState ComponentAppStateHelper::isMeetFileTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels)
    {
        /// construct global data
        ComponentCanSolveState state;
        IniOutputFiles outputFiles = getComponentAppIniOutputFiles(from, true);
        IniInputFiles inputFiles;

        if (!outputFiles.isEmpty()) {
            /// fit by ini file    
            for (Data::Channel * channel : channels)
            {
                Data::FileChannel * fileChannel = (Data::FileChannel *)channel;
                for (IniFileDesc desc : outputFiles)
                {
                    if (desc.suffix == fileChannel->fileType)
                    {
                        inputFiles.append(desc);
                    }
                }
            }
            if (inputFiles.size() >= 1)
                return stateWithInputCondition(inputFiles);
        }

        /// fit in folder
        for (Data::Channel * channel : channels)
        {
            Data::FileChannel * fileChannel = (Data::FileChannel *) channel;
            QDir dir(from->outputPath());
            for (QFileInfo info : dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
            {
                if (info.suffix() == fileChannel->fileType)
                {
                    IniFileDesc desc;
                    desc.name = info.fileName();
                    desc.path = info.filePath();
                    desc.suffix = info.suffix();
                    desc.type = "File";
                    inputFiles.append(desc);
                }
            }
        }
        return stateWithInputCondition(inputFiles);
    }

    ComponentCanSolveState ComponentAppStateHelper::isMeetFilesTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels)
    {
        /// construct global data
        ComponentCanSolveState state;
        IniOutputFiles outputFiles = getComponentAppIniOutputFiles(from, true);
        IniInputFiles inputFiles;

        /// fit by ini file
        if (!outputFiles.isEmpty()) {

            if (!inputFiles.isEmpty())
                return stateWithInputCondition(inputFiles);
        }

        /// fit in folder
        return stateWithInputCondition(inputFiles);
    }

    ComponentCanSolveState ComponentAppStateHelper::multiMeetFilesTypeChannels(QList<Data::ComponentAppData * > previous)
    {
        ComponentCanSolveState state;
        return state;
    }

    IniOutputFiles ComponentAppStateHelper::getComponentAppIniOutputFiles(Data::ComponentAppData * cpt, bool fileType)
    {
        QString projectIni = cpt->iniFilePath() + "/project.ini";
        IniFileReader reader(projectIni);
        reader.read();
        IniOutputFiles outputFiles;
        if (fileType)
            outputFiles = reader.getFileTypeOutputFiles();
        else
            outputFiles = reader.getFolderTypeOutputFiles();
        return outputFiles;
    }

    void ComponentAppStateHelper::setComponentAppIniInputFiles(Data::ComponentAppData * cpt, IniInputFiles inputFiles)
    {
        /// write input file
        QString projectIni = cpt->iniFilePath() + "/project.ini";
        IniFileWriter writer(projectIni);
        writer.setBasePath(cpt->outputPath());
        writer.setInputFiles(inputFiles);
        writer.write();

        /// add notify
        Data::TransferData * trans = nullptr;
        if (inputFiles.size() == 1)
        {
            IniFileDesc desc = inputFiles.first();
            if (desc.type == "File")
            {
                Data::TransferFileData * file = new Data::TransferFileData();
                file->setFilePath(desc.path);
                file->setIniFilePath(projectIni);
                file->setGraphicsObject(_cpt->graphicsObject());
                trans = file;
            }
            else if (desc.type == "Folder")
            {
                Data::TransferFolderData * folder = new Data::TransferFolderData();
                folder->setFolderPath(desc.path);
                folder->setIniFilePath(projectIni);
                folder->setGraphicsObject(_cpt->graphicsObject());
                folder->setTypes(desc.suffix.split(",", QString::SkipEmptyParts));
                trans = folder;
            }
        }
        else if (inputFiles.size() > 1)
        {
            Data::TransferFilesData * files = new Data::TransferFilesData();
            files->setIniFilePath(projectIni);
            files->setGraphicsObject(_cpt->graphicsObject());

            QStringList filePaths;
            for (IniFileDesc file : inputFiles)
            {
                filePaths.append(file.path);
            }
            files->setFilePaths(filePaths);
            trans = files;
        }
        _fileMonitorAdd->setArgs("TransferData", QVariant::fromValue<Core::FITKAbstractDataObject*>(trans));
        _fileMonitorAdd->triggered();
    }

    EventHelper::ComponentCanSolveState ComponentAppStateHelper::stateWithInputCondition(IniInputFiles inputFiles)
    {
        ComponentCanSolveState state;
        if (inputFiles.size() == 0)
        {
            state.enumState = Can_Not_Solve;
            return state;
        }
        if (inputFiles.size() == 1)
        {
            setComponentAppIniInputFiles(_cpt, inputFiles);
            state.enumState = Can_Solve;
            return state;
        }
        else if (inputFiles.size() >= 2)
        {
            state.enumState = Can_Solve_With_Multi;
            state.inputs = inputFiles;
            return state;
        }
        return state;
    }

    bool ComponentAppStateHelper::isIniFileExistAndWithValidInput(const QString & iniFilePath)
    {
        QFile file(iniFilePath);
        if (file.exists())
        {
            bool valid = true;
            QSettings setting(_cpt->iniFilePath() + "/project.ini", QSettings::IniFormat);
            int inputFileNum = setting.value("Input_Files/Input_File_Number").toInt();
            for (int index = 0; index < inputFileNum; ++index)
            {
                QString pathKey = QString("Input_Files/Input_File%1_Path").arg(index + 1);
                QString nameKey = QString("Input_Files/Input_File%1_Name").arg(index + 1);

                QString path = setting.value(pathKey).toString();
                QString name = setting.value(nameKey).toString();

                QString filePath = path + "/" + name;

                /// is this input is valid
                if (!file.exists(filePath))
                {
                    return false;
                }
            }
            if (valid) {
                /// valid input ini
                return true;
            }
        }
        return false;
    }
}
