#include "ComponentData.h"
#include <QSet>

namespace Data
{

    bool AdditionalInputParam::operator==(const AdditionalInputParam & additional)
    {
        if (argv == additional.argv)
        {
            return true;
        }
        return false;
    }

    QStringList ComponentData::fileTypeInputChannelNames()
    {
        QStringList names;
        for (Channel * channel : _inputChannel.values())
        {
            if (channel->channelType == Channel_File_Type)
                names.append(channel->channelName);
        }
        return names;
    }

    QStringList ComponentData::filesTypeInputChannelNames()
    {
        QStringList names;
        for (Channel * channel : _inputChannel.values())
        {
            if (channel->channelType == Channel_Files_Type)
                names.append(channel->channelName);
        }
        return names;
    }

    QStringList ComponentData::folderTypeInputChannelNames()
    {
        QStringList names;
        for (Channel * channel : _inputChannel.values())
        {
            if (channel->channelType == Channel_Folder_Type)
                names.append(channel->channelName);
        }
        return names;
    }

    void ComponentData::addAdditionalInputParam(const AdditionalInputParam & param)
    {
        _additionalParams.insert(param.argv, param);
    }

    bool ComponentData::copy(FITKAbstractDataObject* obj)
    {
        ComponentData * cpt = dynamic_cast<ComponentData *>(obj);
        if (!cpt) { return false; }
        FITKAbstractNDataObject::copy(obj);

        /// basic info
        _author = cpt->author();
        _company = cpt->company();
        _desc = cpt->description();
        _disciplines = cpt->disciplines();
        _svg = cpt->svg();
        _version = cpt->version();
        _path = cpt->path();
        _licenseType = cpt->licenseType();
        _withGui = cpt->withGUI();

        /// input info
        QStringList inputChannelNames = cpt->inputChannelNames();
        for (QString inputChannelName : inputChannelNames)
        {
            Channel * channel = cpt->inputChannel(inputChannelName);
            Channel * copied = copyChannel(channel);
            addInputChannel(copied);
        }

        /// output info
        QStringList ouputChannelNames = cpt->outputChannelNames();
        for (QString outputChannelName : ouputChannelNames)
        {
            Channel * channel = cpt->outputChannel(outputChannelName);
            Channel * copied = copyChannel(channel);
            addOutputChannel(copied);
        }

        /// additional info
        QStringList additionalNames = cpt->additionalInputParamNames();
        for (QString additionalName : additionalNames)
        {
            addAdditionalInputParam(cpt->additionalInputParam(additionalName));
        }
        return true;
    }

    Data::Channel * ComponentData::copyChannel(Channel * channel)
    {
        Channel * copied = nullptr;
        if (channel->channelType == Channel_File_Type)
        {
            copied = new FileChannel();
            copied->copy(channel);
        }
        else if (channel->channelType == Channel_Files_Type)
        {
            copied = new FilesChannel();
            copied->copy(channel);
        }
        else if (channel->channelType == Channel_Folder_Type)
        {
            copied = new FolderChannel();
            copied->copy(channel);
        }
        else if (channel->channelType == Channel_None_Type)
        {
            copied = new Channel();
            copied->copy(channel);
        }
        return copied;
    }
}