#include "ChannelDegenerate.h"
#include <QSet>

namespace Data
{
    Data::Channel * ChannelDegenerate::degenerate(Channel * output, Channel * input)
    {
        if (output->channelType == Channel_None_Type || input->channelType == Channel_None_Type)
        {
            return nullptr;
        }
        else if (output->channelType == Channel_Folder_Type && input->channelType == Channel_File_Type)
        {
            return degenerateFolder2File((FolderChannel *)output, (FileChannel *)input);
        }
        else if (output->channelType == Channel_Folder_Type && input->channelType == Channel_Folder_Type)
        {
            return degenerateFolder2Folder((FolderChannel *)output, (FolderChannel *)input);
        }
        else if (output->channelType == Channel_File_Type && input->channelType == Channel_File_Type)
        {
            return degenerateFile2File((FileChannel *)output, (FileChannel *)input);
        }
        return nullptr;
        /// need add other type degenerate implementation
    }

    QList<Channel *> ChannelDegenerate::degenerate(ComponentData * from, ComponentData * to)
    {
        QStringList outputChannelNames = from->outputChannelNames();
        QStringList inputChannelNames = to->inputChannelNames();
        QList<Channel *> channels;

        if (outputChannelNames.isEmpty() || inputChannelNames.isEmpty())
        {
            return channels;
        }

        for (QString outputChannelName : outputChannelNames)
        {
            Channel * output = from->outputChannel(outputChannelName);
            for (QString inputChannelName : inputChannelNames)
            {
                Channel * input = to->inputChannel(inputChannelName);
                Channel * degenerated = degenerate(output, input);
                if (degenerated)
                {
                    channels.append(degenerated);
                }
            }
        }
        return channels;
    }

    Data::Channel * ChannelDegenerate::degenerateFolder2File(FolderChannel * output, FileChannel * input)
    {
        if (output->supports.contains(input->fileType))
        {
            Data::FileChannel * channel = new Data::FileChannel();
            channel->copy(input);
            return channel;
        }
        return nullptr;
    }

    Data::Channel * ChannelDegenerate::degenerateFolder2Folder(FolderChannel * output, FolderChannel * input)
    {
        QSet<QString> outputSupports(output->supports.begin(), output->supports.end());
        QSet<QString> inputSupports(input->supports.begin(), input->supports.end());

        QSet<QString> degeneratedTypes = outputSupports.intersect(inputSupports);
        if (degeneratedTypes.isEmpty())
            return nullptr;
        Data::FolderChannel * channel = new Data::FolderChannel();
        channel->channelType = Channel_Folder_Type;
        channel->channelName = output->channelName + "_" + input->channelName;
        channel->channelDesc = "Folder Type Transfer.";
        channel->supports = degeneratedTypes.toList();
        return channel;
    }

    Data::Channel * ChannelDegenerate::degenerateFile2File(FileChannel * output, FileChannel * input)
    {
        if (output->fileType == input->fileType)
        {
            Data::FileChannel * channel = new Data::FileChannel();
            channel->channelType = Channel_File_Type;
            channel->channelName = output->channelName + "_" + input->channelName;
            channel->channelDesc = "File Type Transfer.";
            channel->fileType = output->fileType;
            return channel;
        }
        return nullptr;
    }


}