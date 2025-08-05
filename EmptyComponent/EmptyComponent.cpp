#include "EmptyComponent.h"
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QDebug>
#include <QMessageBox>

EmptyComponent::EmptyComponent(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
    :QWidget(parent, f)
{
    initUi();
}

EmptyComponent::~EmptyComponent()
{

}

void EmptyComponent::setInput(const QString & input)
{
    _inputIni = QDir::cleanPath(input);
    qDebug() << _inputIni;
    //QMessageBox::warning(this, _inputIni, _inputIni);
    QFile file(input);
    if (!file.exists()) { return; }
    QSettings settings(_inputIni, QSettings::IniFormat);
    QFileInfo info(_inputIni);
    QString appName = info.dir().dirName();
    setWindowTitle(appName);

    _basePath = settings.value("Basic_Information/Output_Base_Path").toString();
    qDebug() << _basePath;
    //QMessageBox::warning(this, _basePath, _basePath);
    int num = settings.value("Output_Files/Output_File_Number").toInt();
    for (int index = 0; index < num; ++index)
    {
        QString descKey = QString("Output_Files/Output_File%1_Desc").arg(index + 1);
        QString desc = settings.value(descKey).toString();
        _types.append(desc);
    }
}

void EmptyComponent::initUi()
{
    setFixedSize(QSize(800, 480));

}

void EmptyComponent::closeEvent(QCloseEvent *event)
{
    /// write ini and files
    int num = _types.size();
    QSettings settings(_inputIni, QSettings::IniFormat);

    for (int iCnt = 0; iCnt < num; ++iCnt)
    {
        QString keyPath = QString("Output_Files/Output_File%1_Path").arg(iCnt + 1);
        QString keyName = QString("Output_Files/Output_File%1_Name").arg(iCnt + 1);
        settings.setValue(keyPath, QDir(_basePath).cleanPath(_basePath));
        settings.setValue(keyName, "empty." + _types[iCnt]);

        QString fileName = _basePath + "/" + "empty." + _types[iCnt];
        qDebug() << fileName;
        //QMessageBox::warning(this, fileName, fileName);

        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QFile file(_basePath + "/" + "empty.hdf5");
    file.open(QIODevice::WriteOnly);
    file.close();

    QWidget::closeEvent(event);
}
