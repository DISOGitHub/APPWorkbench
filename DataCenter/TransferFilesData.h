/**
 *
 * @file      TransferFilesData.h
 * @brief     Class Defined Transfer Files Info.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-29 11:31
 *
 */

#pragma once
#include "TransferData.h"
#include "DataCenterAPI.h"

namespace Data
{
    /**
     * @brief     Class Defined Transfer Files Info.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-29 15:30
     */
    class DATA_CENTER_API TransferFilesData : public TransferData
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    TransferFilesData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:30
         */
        explicit TransferFilesData();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:30
         */
        virtual ~TransferFilesData();

        /**
         * @brief     get file paths
         * @return    QStringList . file paths
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:30
         */
        QStringList filePaths() const { return _filePaths; }

        /**
         * @brief     set file paths
         * @param     filePaths[i] . file paths
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:31
         */
        void setFilePaths(const QStringList & filePaths) { _filePaths = filePaths; }

    protected:
        /**
         * @brief     transfered files path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 18:39
         */
        QStringList _filePaths;
    };
}