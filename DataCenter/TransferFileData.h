/**
 *
 * @file      TransferFileData.h
 * @brief     Class Defined Transfer File Info.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-29 11:25
 *
 */

#pragma once
#include "TransferData.h"
#include "DataCenterAPI.h"

namespace Data
{
    /**
     * @brief     Class Defined Transfer File Info.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-29 15:28
     */
    class DATA_CENTER_API TransferFileData : public TransferData
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    TransferFileData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:29
         */
        explicit TransferFileData();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:29
         */
        virtual ~TransferFileData();

        /**
         * @brief     get file path
         * @return    QString . file path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:29
         */
        QString filePath() const { return _filePath; }

        /**
         * @brief     set file path
         * @param     filePath[i]. file path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-29 15:29
         */
        void setFilePath(const QString & filePath) { _filePath = filePath; }

    protected:
        /**
        * @brief     transfered file path
        * @author    maguiwa(maguiwa520@163.com)
        * @date      2024-9-25 18:38
        */
        QString _filePath;

    };
}