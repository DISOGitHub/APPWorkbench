#include "ProjectIO.h"
#include "DataCenter/SimulationAppData.h"
#include "DataCenter/FrameAppData.h"
#include "DataCenter/SingleSimulationAppData.h"
#include "DataCenter/MultiSimulationAppData.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include <QFileInfo>

namespace GUI
{
    ProjectIO::ProjectIO(Data::SimulationAppData * data /*= nullptr*/)
    {
        if (!data)
        {
            setSimulationAppData(data);
        }
    }

    ProjectIO::~ProjectIO()
    {

    }


    void ProjectIO::setSimulationAppData(Data::SimulationAppData * data)
    {
        if (!isValid(data)) { return; }
        _data = data;
    }

    Data::SimulationAppData * ProjectIO::read(const QString & filePath)
    {
        Data::SimulationAppData * result = nullptr;
        return result;
    }

    bool ProjectIO::write(const QString & filePath)
    {
        QFileInfo info(filePath);
        if (!ensureDirectoryExists(info.absolutePath()))
        {
            return false;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly))
        {
            return false;
        }



        return false;
    }


    bool ProjectIO::isValid(Data::SimulationAppData * data)
    {
        if (!data) { return false; }
        Data::FrameAppData * workbenchData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!workbenchData) { return false; }
        if (data->simulationAppType() == Data::Simulation_App_Single_Component_App)
        {
            Data::SingleSimulationAppDataManger * sglMgr = workbenchData->getSingleSimulationAppDataManger();
            if (!sglMgr) { return false; }
            Data::SingleSimulationAppData * sgl = dynamic_cast<Data::SingleSimulationAppData *> (data);
            if (!sgl) { return false; }
            if (sglMgr->isContains(sgl)) { return false; }
            return true;
        }
        else if (data->simulationAppType() == Data::Simulation_App_Multi_Component_App)
        {
            Data::MultiSimulationAppData * mul = dynamic_cast<Data::MultiSimulationAppData *> (data);
            if (!mul) { return false; }
            Data::MultiSimulationAppDataManger * mulMgr = workbenchData->getMultiSimulationAppDataManger();
            if (!mulMgr) { return false; }
            if (!mulMgr->isContains(mul)) { return false; }
            return true;
        }
        return false;
    }


    bool ProjectIO::ensureDirectoryExists(const QString & path)
    {
        QDir dir(path);
        if (dir.exists())
        {
            return true;
        }
        return dir.mkpath(path);
    }

}
