#include "ComponentAppData.h"
#include <QDir>

namespace Data
{

    ComponentAppData::ComponentAppData(QGraphicsObject * obj /*= nullptr*/)
    {
        if (obj)
        {
            setGraphicsObject(obj);
        }
    }

    bool ComponentAppData::copy(Core::FITKAbstractDataObject * other)
    {
        ComponentData * cpt = dynamic_cast<ComponentData *>(other);
        ComponentAppData * cptApp = dynamic_cast<ComponentAppData *>(other);
        if (!cpt && !cptApp)
            return false;
        else if (cpt && !cptApp)
            return ComponentData::copy(cpt);

        ComponentData::copy(cpt);
        _graphicsObject = cptApp->_graphicsObject;
        _simulationProjectPath = cptApp->_simulationProjectPath;
        _componentAppProjectFileInfo = cptApp->_componentAppProjectFileInfo;
        _lastErrors = cptApp->_lastErrors;
        return true;
    }

    bool ComponentAppData::isValidComponentAppData()
    {
        return true;
    }

    bool ComponentAppData::existProject()
    {
        QString outputPath = _simulationProjectPath + "/" + getDataObjectName() + "/output";
        QDir dir(outputPath);
        if (!dir.exists()) { return false; }

        for (auto info : dir.entryInfoList(QStringList{ "*.hdf5" }, QDir::Files))
        {
            _componentAppProjectFileInfo = info;
            return true;
        }
        return false;
    }

    QString ComponentAppData::outputPath()
    {
        return QDir::cleanPath(_simulationProjectPath + "/" + getDataObjectName() + "/output/");
    }

    QString ComponentAppData::inputPath()
    {
        return QDir::cleanPath(_simulationProjectPath + "/" + getDataObjectName() + "/input/");
    }

    QString ComponentAppData::iniFilePath()
    {
        return QDir::cleanPath(_simulationProjectPath + "/" + getDataObjectName() + "/");
    }

    Data::ComponentAppData * ComponentAppDataManger::componentAppDataByGraphicsObject(QGraphicsObject * obj)
    {
        int num = getDataCount();
        for (int index = 0; index < num; ++index)
        {
            Data::ComponentAppData * cptAppData = getDataByIndex(index);
            if (cptAppData->graphicsObject() == obj)
            {
                return cptAppData;
            }
        }
        return nullptr;
    }

}