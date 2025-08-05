/**
 *
 * @file      ComponentAppData.h
 * @brief     As Part Of Simulation App. Component App Has Component Instance Data.
 *            Input Files Info. Output Files Info. Component App Project Path And File
 *            Info. It Can Single Construct SingleSimulationAppData. Also Can Construct
 *            MultiSimulationAppData With LineData.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 20:03
 *
 */
#pragma once
#include "DataCenterAPI.h"
#include "ComponentData.h"
#include "SimulationAppData.h"
#include <QGraphicsObject>
#include <QFileInfo>

namespace Data
{
    /**
     * @brief     Component App Data.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 20:08
     */
    class DATA_CENTER_API ComponentAppData : public ComponentData
    {
    public:
        /**
         * @brief     default constructor
         * @return    ComponentAppData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:09
         */
        explicit ComponentAppData(QGraphicsObject * obj = nullptr);

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:09
         */
        ~ComponentAppData() = default;

        /**
         * @brief     copy component app data
         * @param     other[i]. data copied from
         * @return    bool . copy success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 10:26
         */
        virtual bool copy(Core::FITKAbstractDataObject * other) override;

        /**
         * @brief     determine component instance data prepared ok for solve.
         * @return    bool. prepared ok or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:09
         */
        virtual bool isValidComponentAppData();

        /**
         * @brief     if is valid return false. call this to get errors
         * @return    QStringList . errors
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:26
         */
        QStringList lastErrors() const { return _lastErrors; }

        /**
         * @brief     while component app solved. check whether project path exists project file
         * @return    bool . is project file exist. project file 's hdf5 format component app history project file
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:27
         */
        bool existProject();

        /**
         * @brief     get last time app solved project path
         * @return    QString . project path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:28
         */
        QString projectPath() const { return _simulationProjectPath; }

        /**
         * @brief     get project 's current component app 's output path
         * @return    QString . project 's current component app 's output path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:49
         */
        QString outputPath();

        /**
         * @brief     get project 's current component app 's input path
         * @return    QString. project 's current component app 's input path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:50
         */
        QString inputPath();

        /**
         * @brief     get ini format
         * @return    QString
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 11:26
         */
        QString iniFilePath();

        /**
         * @brief     set last time component app solved project path
         * @param     projectPath[i]. project path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:30
         */
        void setProjectPath(const QString & projectPath) { _simulationProjectPath = projectPath; }

        /**
         * @brief     get last time component app solved project file info
         * @return    QFileInfo . project file info. default hdf5 file
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 20:31
         */
        QFileInfo projectFileInfo() const { return _componentAppProjectFileInfo; }

        /**
         * @brief     bind graphics object
         * @return    QGraphicsObject * . graphics object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:26
         */
        QGraphicsObject * graphicsObject() const { return _graphicsObject; }

        /**
         * @brief     set graphics object
         * @param     obj[i]. graphics object
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:27
         */
        void setGraphicsObject(QGraphicsObject * obj) { _graphicsObject = obj; }

    protected:

        /**
         * @brief     graphics object
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 14:25
         */
        QGraphicsObject * _graphicsObject{};

        /**
         * @brief     component app 's project path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 20:11
         */
        QString _simulationProjectPath;

        /**
         * @brief     component app 's project file info
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 20:13
         */
        QFileInfo _componentAppProjectFileInfo;

        /**
         * @brief     if isValid return false. this store errors.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 20:17
         */
        QStringList _lastErrors;

    };

    class DATA_CENTER_API ComponentAppDataManger : public Core::FITKAbstractDataManager<ComponentAppData>
    {
    public:
        /**
         * @brief     constructor
         * @return    ComponentAppDataManger object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:02
         */
        explicit ComponentAppDataManger() = default;

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:02
         */
        ~ComponentAppDataManger() = default;

        /**
         * @brief     get component app data by graphics object
         * @param     obj[i]. graphics object
         * @return    Data::ComponentAppData *. component app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 15:48
         */
        ComponentAppData * componentAppDataByGraphicsObject(QGraphicsObject * obj);
    };
}
