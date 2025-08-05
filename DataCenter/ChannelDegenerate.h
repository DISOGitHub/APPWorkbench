/**
 *
 * @file      ChannelDegenerate.h
 * @brief     While Link Two Component App. From Component App And To Component App Need Channel Degenerate
 *            Between From Component App Output Channels and To Component App Input Channels. This File Used
 *            To Channel Degenerate With Channel Output and Channel Input.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 16:04
 *
 */

#pragma once
#include "DataCenterAPI.h"
#include "ComponentData.h"

namespace Data
{
    /**
     * @brief     while line from 's output channel and to 's input channel will degenerate into a line channel
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-12 9:30
     */
    class DATA_CENTER_API ChannelDegenerate
    {
    public:
        /**
         * @brief     default constructor
         * @return    ChannelDegenerate object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:03
         */
        explicit ChannelDegenerate() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 16:03
         */
        ~ChannelDegenerate() = default;

        /**
         * @brief     operator degenerate
         * @param     output[i]. from 's output channel
         * @param     input[]. to 's input channel
         * @return    Data::Channel * . if not fit . return none.else return degenerated channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 9:32
         */
        Channel * degenerate(Channel * output, Channel * input);

        /**
         * @brief     operator degenerate
         * @param     from[i]. from component app
         * @param     to[i]. to component app
         * @return    QList<Channel *> . degenerated channels
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 11:12
         */
        QList<Channel *> degenerate(ComponentData * from, ComponentData * to);

    protected:
        /**
         * @brief     operator degenerate as output channel is folder type and input channel is file type.
         * @param     output[i]. output channel
         * @param     input[i]. input channel
         * @return    Data::Channel * . degenerated channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 9:36
         */
        Channel * degenerateFolder2File(FolderChannel * output, FileChannel * input);

        /**
         * @brief     operator degenerate as output channel is folder type and input channel is folder type.
         * @param     output[i]. output channel
         * @param     input[i]. input channel
         * @return    Data::Channel * . degenerated channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 10:34
         */
        Channel * degenerateFolder2Folder(FolderChannel * output, FolderChannel * input);

        /**
         * @brief     operator degenerate as output channel is file type and input channel is file type.
         * @param     output[i]. output channel
         * @param     input[i]. input channel
         * @return    Data::Channel * . degenerated channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-13 15:29
         */
        Channel * degenerateFile2File(FileChannel * output, FileChannel * input);
    };
}