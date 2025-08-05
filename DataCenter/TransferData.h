/**
 *
 * @file      TransferData.h
 * @brief     while multi simulation app run. project.ini or open_project.ini set input file that from previous
 *            component. while user run previous component app . may change current component 's input file. then
 *            we need record all files that transfered by workbench. while file changed. notify.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 18:31
 *
 */
#pragma once
#include <QGraphicsItem>
#include "DataCenterAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"

namespace Data
{
    /**
     * @brief     transfer file types
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 18:34
     */
    enum TransferType
    {
        /**
         * @brief     transfer nothing
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:34
         */
        Transfer_None_Type,

        /**
         * @brief     transfer one file
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:34
         */
        Transfer_File_Type,

        /**
         * @brief     transfer files
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:34
         */
        Transfer_Files_Type,

        /**
         * @brief     transfer folder with suffix type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:35
         */
        Transfer_Folder_Type,
    };

    /**
     * @brief     transfer base struct
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 18:35
     */
    class DATA_CENTER_API TransferData : public Core::FITKAbstractDataObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    TransferData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:25
         */
        explicit TransferData();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:25
         */
        virtual ~TransferData();

        /**
         * @brief     get graphics item
         * @return    QGraphicsObject * .graphics item
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:25
         */
        QGraphicsObject * graphicsObject() const { return _item; }

        /**
         * @brief     set graphics item
         * @param     item[i]. graphics item
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:26
         */
        void setGraphicsObject(QGraphicsObject * item) { _item = item; }

        /**
         * @brief     get ini file path
         * @return    QString . ini file path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:26
         */
        QString iniFilePath() const { return _iniFilePath; }

        /**
         * @brief     set ini file path
         * @param     iniFilePath[i]. ini file path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:27
         */
        void setIniFilePath(const QString & iniFilePath) { _iniFilePath = iniFilePath; }

        /**
         * @brief     get transfer type
         * @return    Data::TransferType. transfer type
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:27
         */
        TransferType transferType() const { return _transferType; }

        /**
         * @brief     set transfer type
         * @param     type[i]. transfer type
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:28
         */
        void setTransferType(TransferType type) { _transferType = type; }

    protected:
        /**
         * @brief     bind graphics object
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:36
         */
        QGraphicsObject * _item{};

        /**
         * @brief     bind ini file name / project.ini
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:36
         */
        QString _iniFilePath;

        /**
         * @brief     transfer type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:37
         */
        TransferType _transferType{ Transfer_None_Type };
    };

    class DATA_CENTER_API TransferDataManger : public Core::FITKAbstractDataManager<TransferData>
    {
    public:
        /**
         * @brief     default constructor
         * @return    TransferData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 18:48
         */
        TransferDataManger() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 18:49
         */
        ~TransferDataManger() = default;


    };

}