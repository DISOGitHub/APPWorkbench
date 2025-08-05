/**
 *
 * @file      MultiSimulationAppData.h
 * @brief     Multi Component App Construct Multi Simulation App. Manage Multi Simulation App Data
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 8:26
 *
 */
#pragma once
#include "DataCenterAPI.h"
#include "SimulationAppData.h"
#include "ComponentData.h"
#include "ComponentAppData.h"
#include "QGraphicsItem"
#include "LineData.h"

namespace Data
{
    /**
     * @brief     Manage Multi Simulation App Data
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-4 8:32
     */
    class DATA_CENTER_API MultiSimulationAppData : public Core::FITKAbstractDataObject, public SimulationAppData
    {
        friend class MultiSimulationAppDataManger;
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    MultiSimulationAppData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 8:32
         */
        explicit MultiSimulationAppData() { _simulationAppType = Simulation_App_Multi_Component_App; }

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 8:32
         */
        ~MultiSimulationAppData() = default;

        /**
         * @brief     whether Component App Data and Line Data is Valid
         * @return    bool . is a Valid Simulation App Data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 8:37
         */
        virtual bool isValidSimulationAppData() override;

        /**
         * @brief     write out template file by this
         * @param     filePath[i]. Write Simulation Template
         * @return    bool .
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 8:38
         */
        virtual bool writeOutAppDescribeFile(const QString & AppName) override;

        /**
         * @brief     add component app data to multi simulation app data
         * @param     data[i]. component app data
         * @return    bool . if already has this component app data or this app component data in other multi simulation app data
         *            return false. else return true
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 8:33
         */
        bool addComponentAppData(ComponentAppData * data);

        /**
         * @brief     remove component app data
         * @param     item[i]. graphics item object pointer
         * @return    bool . if exists return true. else return false
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 8:51
         */
        bool removeComponentAppData(QGraphicsItem * item);

        /**
         * @brief     add line data
         * @param     data[i]. line data
         * @return    bool . execute success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:07
         */
        bool addLineData(LineData * data);

        /**
         * @brief     remove line data
         * @param     item[i]. line item
         * @return    bool . execute success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:06
         */
        bool removeLineData(QGraphicsItem * item);

        /**
         * @brief     combine two multi simulation app data. warning : user need to remove app data .
         * @param     app[i]. another multi simulation app data
         * @return    bool . combine success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 8:52
         */
        bool combine(MultiSimulationAppData * app);

        /**
         * @brief     get line data
         * @return    QList<LineData *>. line datas
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 15:55
         */
        QList<LineData *> lineDatas() const { return _lineDatas; }

        /**
         * @brief     set project path
         * @param     projectPath[i]. project path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 13:38
         */
        void setProjectPath(const QString & projectPath);

        /**
         * @brief     get project path
         * @return    QString . project path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 13:38
         */
        QString projectPath() const { return _projectPath; }

        /**
         * @brief     get multi component app construct App 's first component data
         * @return    Data::ComponentAppData * . first component 's data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 16:30
         */
        ComponentAppData * getFirstComponentAppData();

        /**
         * @brief     while run. it 's used to control the simulation process
         * @return    Data::ComponentAppData * . current component data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 16:31
         */
        ComponentAppData * getCurrentComponentAppData();

        /**
         * @brief     set current component app data.
         * @return    bool . if success return true. else data is not valid in this app
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 16:33
         */
        bool setCurrentComponentAppData(ComponentAppData * data);

        /**
         * @brief     get all component app in degree. if in degree is zero. it 's the next. next may have multi. just return first one
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 9:11
         */
        ComponentAppData * getNextSolveComponentApp();

        /**
         * @brief     get component app in degree
         * @param     cpt[i]. component app
         * @return    int . in degree
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 9:29
         */
        int getComponentAppInDegree(ComponentAppData * cpt);

        /**
         * @brief
         * @param     cpt[]
         * @return    QList<ComponentAppData *>
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:25
         */
        QList<ComponentAppData *> getPreviousLinkedComponentApps(ComponentAppData * cpt);

        /**
         * @brief     get cpt component app linked next component apps
         * @return    QList<ComponentAppData *> . cpt component app linked next component apps
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 9:17
         */
        QList<ComponentAppData *> getNextLinkedComponentApps(ComponentAppData * cpt);

        /**
         * @brief     get component app data by graphics item
         * @param     item[i]. graphics item
         * @return    Data::ComponentAppData *. component app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 9:22
         */
        ComponentAppData * getComponentAppDataByGraphicsObject(QGraphicsItem * item);

        /**
         * @brief     get all component app data.
         * @return    QList<ComponentAppData *> . all component app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 13:41
         */
        QList<ComponentAppData *> componentAppDatas() const { return _componentAppDatas; }

        /**
         * @brief     is graphics item is reference with component app data or line data inside
         * @param     item[i] . graphics item
         * @return    bool . reference result
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 12:55
         */
        bool isReferenceGraphicItem(QGraphicsItem * item);

        /**
         * @brief     get multi component app data by graphics item list
         * @param     items[i]. graphics item list
         * @return    QList<Data::ComponentAppData *> .multi component app data list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:21
         */
        QList<Data::ComponentAppData *> referenceComponentAppData(QList<QGraphicsItem *> items);

        /**
         * @brief     get multi line data by graphics item list
         * @param     items[i]. graphics item list
         * @return    QList<Data::LineData *> . multi line data list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:22
         */
        QList<Data::LineData *> referenceLineData(QList<QGraphicsItem *> items);

        /**
         * @brief     get multi DAG end component app data list
         * @return    QList<Data::ComponentAppData *> .multi DAG end component app data list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:23
         */
        QList<Data::ComponentAppData *> endComponentAppData();

        /**
         * @brief     get multi DAG begin component app data list
         * @return    QT_NAMESPACE::QList<Data::ComponentAppData *> .multi DAG begin component app data list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:24
         */
        QList<Data::ComponentAppData *> beginComponentAppData();

    protected:
        /**
         * @brief     components app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 8:25
         */
        QList<ComponentAppData *> _componentAppDatas;

        /**
         * @brief     while run this multi simulation app. record current step pos
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 16:28
         */
        ComponentAppData * _currentAppData{};

        /**
         * @brief     components transfer data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 8:26
         */
        QList<LineData *> _lineDatas;

        /**
         * @brief     multi simulation app 's project path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-9 13:37
         */
        QString _projectPath;

    };

    /**
     * @brief     Multi Simulation App Data Manger
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 9:22
     */
    class DATA_CENTER_API MultiSimulationAppDataManger : public Core::FITKAbstractDataManager<MultiSimulationAppData>
    {
        friend class MultiSimulationAppData;
    public:

        /**
         * @brief     default constructor
         * @return    MultiSimulationAppDataManger Object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:33
         */
        explicit MultiSimulationAppDataManger() = default;


        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:34
         */
        virtual ~MultiSimulationAppDataManger() = default;

        /**
         * @brief     get multi app data by graphics item
         * @param     item[i]. graphics item
         * @return    Data::MultiSimulationAppData * . multi app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 9:35
         */
        MultiSimulationAppData * getMultiAppDataByGraphicsObject(QGraphicsItem * item);

        /**
         * @brief     get component app data by graphics item
         * @param     item[i]. graphics item
         * @return    Data::ComponentAppData * . componet app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:50
         */
        ComponentAppData * getComponentAppDataByGraphicsObject(QGraphicsItem * item);

        /**
         * @brief     update multi simulation app data by remove item and line
         * @param     removes[i]. graphics objects will removes
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 11:41
         */
        QList<ComponentAppData *> dataUpdateByRemoveItems(QList<QGraphicsItem *> removes);

        /**
         * @brief     is current graphics item( cpt ) 's port linked
         * @param     item[i]. graphics item( cpt )
         * @param     inputPort[i].true as input port, false as output port
         * @return    bool . is port linked
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:25
         */
        bool isPortLinked(QGraphicsItem * item, bool inputPort);

    private:
        /**
         * @brief     recombine multi simulation app data
         * @param     beg[i]. one of multi simulation app 's in degree 0 item
         * @param     begs[i]. all simulation app 's in degree 0 items
         * @param     cpts[i]. all remain component app data
         * @param     lines[i]. all remain line data
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:26
         */
        void recombineMultiSimulationAppData(Data::ComponentAppData * beg, QList<Data::ComponentAppData *> & begs, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines);

        /**
         * @brief     forward spread
         * @param     data[i]. multi simulation app data
         * @param     currents[i]. current component app data
         * @param     cpts[i]. all remain component app data
         * @param     lines[i]. all remain component app data
         * @return    QList<Data::ComponentAppData *> . forward remains current components. end
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:29
         */
        QList<Data::ComponentAppData *> forwardSpread(MultiSimulationAppData * data, QList<Data::ComponentAppData *> currents, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines);

        /**
         * @brief     reverse spread
         * @param     data[i]. multi simulation app data
         * @param     beg[i]. one of multi simulation app 's in degree 0 item
         * @param     currents[i]. current component app data
         * @param     cpts[i]. all remain component app data
         * @param     lines[i]. all remain component app data
         * @return    QList<Data::ComponentAppData *> . reverse remains current components. beg
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:31
         */
        QList<Data::ComponentAppData *> reverseSpread(MultiSimulationAppData * data, QList<Data::ComponentAppData *> & begs, QList<Data::ComponentAppData *> currents, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines);
    };
}