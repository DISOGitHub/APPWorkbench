#include "IniFileWriter.h"
#include "DataCenter/FrameAppData.h"
#include <QSettings>
#include <QFileInfo>

namespace EventHelper
{
    IniFileWriter::IniFileWriter(const QString & filePath)
        : _filePath(filePath)
    {

    }

    IniFileWriter::~IniFileWriter()
    {

    }

    void IniFileWriter::write()
    {
        QSettings file(_filePath, QSettings::IniFormat);

        /// basic information part
        file.beginGroup("Basic_Information");
        file.setValue("Output_Base_Path", _outputBasePath);
        if (_openProject)
        {
            file.setValue("Input_Mode", "PROJECT");
        }
        file.endGroup();

        /// input file part
        file.beginGroup("Input_Files");
        int inputNum = _inputFiles.size();
        if (inputNum == 0)
        {
            file.setValue("Input_File_Number", 0);
        }
        else
        {
            file.setValue("Input_File_Number", inputNum);
            for (int index = 0; index < inputNum; ++index)
            {
                IniFileDesc desc = _inputFiles[index];
                file.setValue(QString("Input_File%1_Path").arg(index + 1), desc.path);
                file.setValue(QString("Input_File%1_Name").arg(index + 1), desc.name);
                file.setValue(QString("Input_File%1_Type").arg(index + 1), desc.type);
                file.setValue(QString("Input_File%1_Desc").arg(index + 1), desc.desc);
                file.setValue(QString("Input_File%1_Suffix").arg(index + 1), desc.suffix);
            }
        }
        file.endGroup();

        /// output file part
        file.beginGroup("Output_Files");
        file.endGroup();

        /// restore
        file.sync();
    }

    void IniFileWriter::setBasePath(const QString & basePath)
    {
        _outputBasePath = basePath;
    }

    void IniFileWriter::setInputFiles(IniInputFiles files)
    {
        _inputFiles = files;
    }

}