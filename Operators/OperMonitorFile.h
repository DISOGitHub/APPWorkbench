/**
 *
 * @file      OperMonitorFile.h
 * @brief     While Multi Simulation App Run. While Mid Component App Run. It Need Part Or All Previous Component
 *            App 's Output As Input. While User Use Run Previous Component App Or Use Component App Item 's Right
 *            Button Menu To Run Previous Component App. Linked Next Component Input File Or Files May Changed.
 *            Workbench Need Notify User. So We Use This Class To Monitor All Transfered Files
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 19:09
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/MultiEventOperator.h"
#include <QFileSystemWatcher>

 /// forward declare
namespace Data
{
    class TransferData;
    class TransferDataManger;
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
}

class QGraphicsObject;
namespace EventOper
{
    /**
     * @brief     Monitor File Operator Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 19:21
     */
    class OperMonitorFile : public MultiEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperMonitorFile object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 19:21
         */
        explicit OperMonitorFile();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 19:22
         */
        ~OperMonitorFile();

        /**
         * @brief     prepare arguments
         * @return    bool . is prepare ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 19:22
         */
        virtual bool prepareArgs() override;

    public slots:
        /**
         * @brief     file changed
         * @param     filePath[i]. changed file path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-26 11:36
         */
        void fileChanged(const QString & filePath);

        /**
         * @brief     folder changed
         * @param     folderPath[i]. changed folder path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 9:03
         */
        void folderChanged(const QString folderPath);

        /**
         * @brief     notify graphics items 's input changed
         * @param     objs[i]. graphics items
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 9:10
         */
        void notifyInputChanged(QList<QGraphicsObject * > objs);

    protected:

        /**
         * @brief     add transfer data
         * @return    bool . is add ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 19:22
         */
        bool addTransfer();

        /**
         * @brief     remove transfer data
         * @return    bool . is remove ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 19:23
         */
        bool removeTransfer();

        /**
         * @brief     transfer data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 19:23
         */
        Data::TransferData * _tranferData{};

        /**
         * @brief     system file watcher
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:52
         */
        QFileSystemWatcher _watcher;

        /**
         * @brief     transfer data manager
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 10:54
         */
        Data::TransferDataManger * _transferDataMgr{};

        /**
         * @brief     single simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-29 9:16
         */
        Data::SingleSimulationAppDataManger * _sglDataMgr{};

        /**
         * @brief     multi simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-29 9:16
         */
        Data::MultiSimulationAppDataManger * _mulDataMgr{};
    };

    Register2FITKOperatorRepo(AddTransfer, OperMonitorFile);
    Register2FITKOperatorRepo(RemoveTransfer, OperMonitorFile);
}