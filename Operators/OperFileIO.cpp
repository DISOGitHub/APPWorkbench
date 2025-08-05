#include "OperFileIO.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "DataCenter/FrameAppData.h"
#include "DataCenter/ComponentData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/SingleSimulationAppData.h"
#include "DataCenter/LogData.h"

#include <QDir>
#include <fstream>
#include <iostream>

#define Q2J(member,doc) rapidjson::Value(member.toStdString().c_str(), doc.GetAllocator())

namespace EventOper
{
    OperFileIO::OperFileIO()
    {
        auto appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return; }
        _cptDataMgr = appData->getComponentDataManger();
        _sglSimAppDataMgr = appData->getSingleSimulationAppDataManger();
        _mulSimAppDataMgr = appData->getMultiSimulationAppDataManger();
    }

    OperFileIO::~OperFileIO()
    {

    }

    bool OperFileIO::readComponentInfo(const QString & filePath)
    {
        QDir dir(filePath);
        if (!dir.exists())
        {
            return false;
        }

        for (QFileInfo info : dir.entryInfoList(QStringList{ "*.json" }, QDir::Files))
        {
            rapidjson::Document doc = getDocumentByJsonFilePath(info.absoluteFilePath());
            if (doc.HasParseError())
            {
                continue;
            }
            Data::ComponentData * data = new Data::ComponentData();

            /// read basic info
            readComponentBasicInfo(filePath, data, doc);

            /// read inputs info
            const rapidjson::Value & inputs = doc["input"];
            for (rapidjson::SizeType index = 0; index < inputs.Size(); ++index)
            {
                readComponentChannel(true, data, inputs[index]);
            }

            /// read outputs info
            const rapidjson::Value & outputs = doc["output"];
            for (rapidjson::SizeType index = 0; index < outputs.Size(); ++index)
            {
                readComponentChannel(false, data, outputs[index]);
            }

            /// read additional input params information
            const rapidjson::Value & params = doc["additionalInputParams"];
            for (rapidjson::SizeType index = 0; index < params.Size(); ++index)
            {
                readAdditionalInputParams(data, params[index]);
            }

            _cptDataMgr->appendDataObj(data);
        }
    }

    bool OperFileIO::writeAppDescription(Core::FITKAbstractDataObject * multi, const QString & filePath)
    {
        /// check
        Data::MultiSimulationAppData * data = qobject_cast<Data::MultiSimulationAppData *> (multi);
        if (!data || !data->isValidSimulationAppData())
        {
            return false;
        }

        /// prepare
        QFileInfo info(filePath);

        /// create document
        rapidjson::Document doc;
        doc.SetObject();
        doc.AddMember("name", Q2J(info.fileName(), doc), doc.GetAllocator());

        /// create component app part
        rapidjson::Value components(rapidjson::kArrayType);
        for (Data::ComponentAppData * cpt : data->componentAppDatas())
        {
            rapidjson::Value compoent(rapidjson::kObjectType);
            compoent.AddMember("name", Q2J(cpt->getDataObjectName(), doc), doc.GetAllocator());
            compoent.AddMember("id", Q2J(ADDR(cpt->graphicsObject()), doc), doc.GetAllocator());
            compoent.AddMember("desc", Q2J(cpt->description(), doc), doc.GetAllocator());
            compoent.AddMember("path", Q2J(cpt->path(), doc), doc.GetAllocator());
            components.PushBack(compoent, doc.GetAllocator());
        }
        doc.AddMember("components", components, doc.GetAllocator());

        /// create line part
        rapidjson::Value lines(rapidjson::kArrayType);
        for (Data::LineData * lineData : data->lineDatas())
        {
            rapidjson::Value line(rapidjson::kObjectType);
            line.AddMember("from", Q2J(ADDR(lineData->fromGraphicsObject()), doc), doc.GetAllocator());
            line.AddMember("to", Q2J(ADDR(lineData->toGraphicsObject()), doc), doc.GetAllocator());
        }
        doc.AddMember("lines", lines, doc.GetAllocator());

        /// to buffer
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);

        /// to file
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(buffer.GetString());
            file.close();
        }

        LOG(QString("%1 App Describe File Saved.").arg(info.baseName()));
        return true;
    }

    Core::FITKAbstractDataObject * OperFileIO::readAppDescription(const QString & filePath)
    {
        QDir dir(filePath);
        if (!dir.exists())
        {
            return nullptr;
        }

        rapidjson::Document doc = getDocumentByJsonFilePath(filePath);
        if (doc.HasParseError())
        {
            return nullptr;
        }
        Data::MultiSimulationAppData * data = new Data::MultiSimulationAppData();


    }

    bool OperFileIO::writeProject(const QString & filePath)
    {
        return false;
    }

    bool OperFileIO::readProject(const QString & filePath)
    {
        return false;
    }

    bool OperFileIO::ensureDirectoryExists(const QString & directory)
    {
        QDir dir(directory);
        if (dir.exists())
        {
            return true;
        }
        return dir.mkpath(directory);
    }

    rapidjson::Document OperFileIO::getDocumentByJsonFilePath(const QString & filePath)
    {
        rapidjson::Document document;
        std::ifstream ifs(filePath.toStdString().c_str());
        if (!ifs.is_open()) { return document; }
        rapidjson::IStreamWrapper isw(ifs);
        document.ParseStream(isw);
        return document;
    }

    void OperFileIO::readComponentBasicInfo(const QString & filePath, Data::ComponentData * data, rapidjson::Document & doc)
    {
        if (!data)
        {
            return;
        }

        data->setDataObjectName(doc["name"].GetString());
        QString svg = filePath + "/svg/" + doc["svg"].GetString();
        data->setSvg(svg);
        data->setVersion(doc["version"].GetString());
        data->setDescription(doc["desc"].GetString());
        QString path = filePath + "/../../Apps/" + doc["path"].GetString();
        data->setPath(path);
        data->setType(doc["type"].GetString());
        data->setAuthor(doc["author"].GetString());
        data->setCompany(doc["company"].GetString());
        QStringList disciplines = QString(doc["disciplines"].GetString()).split(",", QString::SkipEmptyParts);
        data->setDisciplines(disciplines);
        data->setWithGUI(doc["withGUI"].GetBool());
    }

    void OperFileIO::readComponentChannel(bool input, Data::ComponentData * data, const rapidjson::Value & node)
    {
        QString channelName = node["channelName"].GetString();
        Data::Channel * base = nullptr;
        if (channelName == "None")
        {
            base = new Data::Channel();
            base->channelName = channelName;
            base->channelType = Data::Channel_None_Type;
            if (input)
                data->addInputChannel(base);
            else
                data->addOutputChannel(base);
            return;
        }

        QString channelType = node["channelType"].GetString();
        if (channelType == "File")
        {
            Data::FileChannel * channel = new Data::FileChannel();
            channel->channelName = channelName;
            channel->channelType = Data::Channel_File_Type;
            channel->fileType = node["fileType"].GetString();
            channel->channelDesc = node["channelDesc"].GetString();
            base = channel;
        }
        else if (channelType == "Files")
        {
            Data::FilesChannel * channel = new Data::FilesChannel();
            channel->channelName = channelName;
            channel->channelType = Data::Channel_File_Type;
            QString fileTypes = node["fileType"].GetString();
            channel->fileTypes = fileTypes.split(",", QString::SkipEmptyParts);
            channel->channelDesc = node["channelDesc"].GetString();
            base = channel;
        }
        else if (channelType == "Folder")
        {
            Data::FolderChannel * channel = new Data::FolderChannel();
            channel->channelName = channelName;
            channel->channelType = Data::Channel_Folder_Type;
            QString supports = node["supports"].GetString();
            channel->supports = supports.split(",", QString::SkipEmptyParts);
            channel->channelDesc = node["channelDesc"].GetString();
            base = channel;
        }
        if (input)
            data->addInputChannel(base);
        else
            data->addOutputChannel(base);
    }

    void OperFileIO::readAdditionalInputParams(Data::ComponentData * data, const rapidjson::Value & node)
    {
        Data::AdditionalInputParam info;
        info.argv = node["argv"].GetString();
        info.desc = node["desc"].GetString();
        info.defaultUse = node["defaultUse"].GetBool();
        info.userSet = node["userSet"].GetBool();
        data->addAdditionalInputParam(info);
    }

}
