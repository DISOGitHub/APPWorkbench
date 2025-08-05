/**
 *
 * @file      TransferFolderData.h
 * @brief     Class Defined Transfer Folder Info.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-29 11:53
 *
 */

#pragma once
#include "TransferData.h"
#include "DataCenterAPI.h"

namespace Data
{
    /**
     * @brief     Class Defined Transfer Folder Info.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-29 15:31
     */
    class DATA_CENTER_API TransferFolderData : public TransferData
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    TransferFolderData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:31
         */
        explicit TransferFolderData();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:31
         */
        virtual ~TransferFolderData();

        /**
         * @brief     get folder path
         * @return    QString . folder path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:32
         */
        QString folderPath() const { return _folderPath; }

        /**
         * @brief     set folder path
         * @param     path[i] . folder path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:32
         */
        void setFolderPath(const QString & path) { _folderPath = path; }

        /**
         * @brief     get transfered file types
         * @return    QStringList . transfered file types
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:32
         */
        QStringList types() const { return _types; }

        /**
         * @brief     set transfered file types
         * @param     types[i] . transfered file types
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:33
         */
        void setTypes(const QStringList & types) { _types = types; }

        /**
         * @brief     get instance transfered file paths
         * @return    QStringList . instance transfered file paths
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:33
         */
        QStringList filePaths() const { return _filePaths; }

        /**
         * @brief     set instance transfered file paths
         * @param     paths[i] . instance transfered file paths
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:34
         */
        void setFilePaths(const QStringList & paths) { _filePaths = paths; }

    protected:
        /**
         * @brief     folder path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:40
         */
        QString _folderPath;

        /**
         * @brief     monitor file type in folder
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:40
         */
        QStringList _types;

        /**
         * @brief     transfer files path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-26 11:32
         */
        QStringList _filePaths;
    };
}