#include "IniFileReader.h"
#include <QSettings>

namespace EventHelper
{

    IniFileReader::IniFileReader(const QString & filePath)
        : _filePath(filePath)
    {

    }

    IniFileReader::~IniFileReader()
    {

    }

    void IniFileReader::read()
    {
        QSettings settings(_filePath, QSettings::IniFormat);
        settings.beginGroup("Output_Files");
        int num = settings.value("Output_File_Number").toInt();

        for (int index = 0; index < num; ++index)
        {
            QString pathKey = QString("Output_File%1_Path").arg(index + 1);
            QString nameKey = QString("Output_File%1_Name").arg(index + 1);
            QString typeKey = QString("Output_File%1_Type").arg(index + 1);
            QString descKey = QString("Output_File%1_Desc").arg(index + 1);
            QString suffixKey = QString("Output_File%1_Suffix").arg(index + 1);

            IniFileDesc item;
            item.path = settings.value(pathKey).toString();
            item.name = settings.value(nameKey).toString();
            item.type = settings.value(typeKey).toString();
            item.desc = settings.value(descKey).toString();
            item.suffix = settings.value(suffixKey).toString();

            _outputFiles.append(item);
        }
    }

    IniOutputFiles IniFileReader::getOutputFiles()
    {
        return _outputFiles;
    }

    IniOutputFiles IniFileReader::getFolderTypeOutputFiles()
    {
        IniOutputFiles result;
        for (IniFileDesc desc : _outputFiles)
        {
            if (desc.type == "Folder")
            {
                result.append(desc);
            }
        }
        return result;
    }

    IniOutputFiles IniFileReader::getFileTypeOutputFiles()
    {
        IniOutputFiles result;
        for (IniFileDesc desc : _outputFiles)
        {
            if (desc.type == "File")
            {
                result.append(desc);
            }
        }
        return result;
    }

}