/**
 *
 * @file      OperSimulationAppRun.h
 * @brief     User User Run Current. Run Next. Run Previous Action To Drive Simulation App Run
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-7 16:39
 *
 */
#include "OperatorsInterface/MultiEventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"

 /**
  * @brief     forward declaration
  * @author    maguiwa(maguiwa520@163.com)
  * @date      2024-9-9 13:33
  */
namespace Data
{
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
    class SingleSimulationAppData;
    class MultiSimulationAppData;
    class ComponentAppData;
}

namespace EventOper
{
    /**
     * @brief     Class To Drive Simulation App Run
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-7 16:45
     */
    class OperSimulationAppRun : public MultiEventOperator
    {
    public:
        /**
         * @brief     constructor
         * @return    OperSimulationAppRun object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 16:46
         */
        explicit OperSimulationAppRun() = default;

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 16:47
         */
        virtual ~OperSimulationAppRun();

    protected:

        /**
         * @brief     prepare event and function pair. subclass implementation
         * @return    bool . success or not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 17:10
         */
        virtual bool prepareArgs();

        /**
         * @brief     run previous component app
         * @return    bool . run success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 17:15
         */
        bool runPreviousComponentApp();

        /**
         * @brief     run current component app
         * @return    bool . run success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 17:15
         */
        bool runCurrentComponentApp();

        /**
         * @brief     run next component app
         * @return    bool . run success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-7 17:16
         */
        bool runNextComponentApp();

        /**
         * @brief     terminate current run component app
         * @param     current[i].  current run component app
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 15:53
         */
        void terminateCurrentComponentApp(Data::ComponentAppData * current);

        ///**
        // * @brief     Update Component App Graphics Object State
        // * @param     current[i]. component app data
        // * @return    void
        // * @author    maguiwa (maguiwa520@163.com)
        // * @data      2024-9-9 20:44
        // */
        //void updateComponentAppGraphicsObjectState(Data::ComponentAppData * current);

    protected:
        /**
         * @brief     single simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 17:30
         */
        Data::SingleSimulationAppDataManger * _sglAppDataMgr{};

        /**
         * @brief     multi simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-7 17:31
         */
        Data::MultiSimulationAppDataManger * _mulAppDataMgr{};
    };

    Register2FITKOperatorRepo(Previous, OperSimulationAppRun);
    Register2FITKOperatorRepo(Current, OperSimulationAppRun);
    Register2FITKOperatorRepo(Next, OperSimulationAppRun);
}