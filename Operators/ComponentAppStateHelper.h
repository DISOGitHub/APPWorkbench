/**
 *
 * @file      ComponentAppStateHelper.h
 * @brief     To Help Component App :
 *                  1.Is This Component App Can Solve.
 *                  2.If Can Solve. Prepare Component App 's Inputs
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-7 10:01
 *
 */

#pragma once
#include <QString>
#include <QMap>
#include <QList>
#include "Define.h"
#include "DataCenter/ComponentData.h"

namespace Data
{
    class SimulationAppData;
    class MultiSimulationAppData;
    class SingleSimulationAppData;
    class ComponentAppData;
    class LineDataManger;
}

namespace EventOper
{
    class MultiEventOperator;
}

namespace EventHelper
{
    /**
     * @brief     To Help Component App State
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-7 10:11
     */
    enum EnumCanSolveState
    {
        /**
         * @brief     input param error
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 10:36
         */
        Input_Param_Error,

        /**
         * @brief     check if current multi data is valid. return false
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-9 13:23
         */
        Component_Input_Error,

        /**
         * @brief     previous component not solved
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 10:37
         */
        Previous_Component_Not_Solved,

        /**
         * @brief     in ini mode
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 14:49
         */
        Can_Not_Solve,

        /**
         * @brief     all input have. but some input has multi fit files
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 15:01
         */
        Can_Solve_With_Multi,

        /**
         *
         * @file      ComponentAppStateHelper.h
         * @brief     prepare is ok
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 11:23
         *
         */
        Can_Solve,

        /**
         * @brief     current component app is a natural in degree 0 component app
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-9 13:25
         */
        Natural_Can_Solve,

        /**
         * @brief     current single simulation app 's component app not with none input channel
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 15:56
         */
        Can_Not_Be_Single_Simulation,
    };

    struct ComponentCanSolveState
    {
        /**
         * @brief     Enum State
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 13:35
         */
        EnumCanSolveState enumState;

        /**
         * @brief     if can not solve. state is Previous_Component_Not_Solved . then this is the not solved previous component app
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 13:35
         */
        Data::ComponentAppData * relatedCpt{};

        /**
         * @brief
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 16:52
         */
        IniInputFiles inputs;
    };


    /**
     * @brief     Component App State Helper
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-7 10:06
     */
    class ComponentAppStateHelper
    {
    public:
        /**
         * @brief     constructor
         * @param     app[i]. simulation app data
         * @param     cpt[i]. component app data in this multi simulation app
         * @return    ComponentAppStateHelper object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:06
         */
        ComponentAppStateHelper(Data::SimulationAppData * app, Data::ComponentAppData * cpt);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:07
         */
        ~ComponentAppStateHelper();

        /**
         * @brief     if component set in can solve. if can solve auto prepare cpt 's input
         * @return    bool . can or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 10:08
         */
        ComponentCanSolveState isComponentCanSolve();

        /**
         * @brief     prepare open project ini file
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:27
         */
        void prepareOpenProjectIni();

        /**
         * @brief     component app run
         * @param     run[i]. true as run with project.ini, false as run with open_project.ini
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 20:36
         */
        void componentAppRun(bool run = true);

    protected:
        /**
        * @brief     Update Component App Graphics Object State While Component Run
        * @param     current[i]. component app data
        * @return    void
        * @author    maguiwa (maguiwa520@163.com)
        * @data      2024-9-9 20:44
        */
        void updateComponentAppGraphicsObjectState(Data::ComponentAppData * current);

        /**
         * @brief     is component app can solve in multi simulation app
         * @param     multi[i]. multi simulation app data
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 14:44
         */
        ComponentCanSolveState isComponentCanSolveInMultiSimulationApp(Data::MultiSimulationAppData * multi);

        /**
         * @brief     ensure multi simulation app project path exists
         * @param     multi[i]. multi simulation app data
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 15:19
         */
        void ensureMultiSimulationAppProjectPathExists(Data::MultiSimulationAppData * multi);

        /**
         * @brief     ensure single simulation app project path exists
         * @param     single[i]. single simulation app data
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 15:19
         */
        void ensureSingleSimulationAppProjectPathExists(Data::SingleSimulationAppData * single);

        /**
         * @brief     is component app can solve in single simulation app
         * @param     single[i]. single simulation app data
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 14:44
         */
        ComponentCanSolveState isComponentCanSolveInSingleSimulationApp(Data::SingleSimulationAppData * single);

        /**
         * @brief     is component can solve in ini way.
         * @param     previous[i]. previous component app ' s data
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 11:19
         */
        ComponentCanSolveState isComponentCanSolveInner(QList<Data::ComponentAppData * > previous);

        /**
         * @brief     get folder type channels in channels
         * @param     channels[i]. input channels
         * @return    QList<Data::Channel *> .folder type channels in channels
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 13:50
         */
        QList<Data::Channel *> folderTypeChannels(QList<Data::Channel *> channels);

        /**
         * @brief     get file type channels in channels
         * @param     channels[i]. input channels
         * @return    QList<Data::Channel *>  .file type channels in channels
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 13:52
         */
        QList<Data::Channel *> fileTypeChannels(QList<Data::Channel *> channels);

        /**
         * @brief     get files type channels in channels
         * @param     channels[i]. input channels
         * @return    QList<Data::Channel *>   .files type channels in channels
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 13:53
         */
        QList<Data::Channel *> filesTypeChannels(QList<Data::Channel *> channels);

        /**
         * @brief     by folder type channel . judge if current component app can solve
         * @param     from[i]. only one from component app.
         * @param     channels[i]. degenerate folder channel between previous and current component app
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:11
         */
        ComponentCanSolveState isMeetFolderTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels);

        /**
         * @brief     by file type channel . judge if current component app can solve
         * @param     from[i]. only one from component app
         * @param     channels[i] degenerate file type channel between previous and current component app
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:14
         */
        ComponentCanSolveState isMeetFileTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels);

        /**
         * @brief     by files type channel . judge if current component app can solve
         * @param     from[i]. only one from component app
         * @param     channels[i]. degenerate files type channel between previous and current component app
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:17
         */
        ComponentCanSolveState isMeetFilesTypeChannels(Data::ComponentAppData * from, QList<Data::Channel *> channels);

        /**
         * @brief     multi from component app files type . judge if current component app can solve
         * @param     previous[i]. multi from component app
         * @return    EventHelper::ComponentCanSolveState . can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:19
         */
        ComponentCanSolveState multiMeetFilesTypeChannels(QList<Data::ComponentAppData * > previous);

        /**
         * @brief     read component app 's ini type file. get output info
         * @param     cpt[i]. component app
         * @param     fileType[i]. true means get file type output info. false means folder type output info
         * @return    IniOutputFiles . read out output infos
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:20
         */
        IniOutputFiles getComponentAppIniOutputFiles(Data::ComponentAppData * cpt, bool fileType);

        /**
         * @brief     before run. write ini format input file
         * @param     cpt[i]. current component app data
         * @param     inputFiles[i]. ini input files
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:22
         */
        void setComponentAppIniInputFiles(Data::ComponentAppData * cpt, IniInputFiles inputFiles);

        /**
         * @brief     while get input files number . then know can solve state.
         * @param     inputFiles[i]. input files info
         * @return    EventHelper::ComponentCanSolveState. can solve state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:23
         */
        ComponentCanSolveState stateWithInputCondition(IniInputFiles inputFiles);

        /**
         * @brief     judge if ini file exist and with valid input
         * @param     iniFilePath[i]. ini file path
         * @return    bool . exist and with valid input or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 15:07
         */
        bool isIniFileExistAndWithValidInput(const QString & iniFilePath);

        /**
         * @brief     multi simulation app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 10:15
         */
        Data::SimulationAppData * _app{};

        /**
         * @brief     component app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 10:16
         */
        Data::ComponentAppData * _cpt{};

        /**
         * @brief     line data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 13:45
         */
        Data::LineDataManger * _lineDataMgr{};

        /**
         * @brief     file monitor
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-29 10:29
         */
        EventOper::MultiEventOperator * _fileMonitorAdd{};
    };
}