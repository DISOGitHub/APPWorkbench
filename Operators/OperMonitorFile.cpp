#include "OperMonitorFile.h"
#include "DataCenter/TransferData.h"
#include "DataCenter/FrameAppData.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include <QDir>
#include "DataCenter/MultiSimulationAppData.h"
#include "Graphics/GraphicsItem.h"
#include "Graphics/StateItem.h"
#include "DataCenter/TransferFileData.h"
#include "DataCenter/TransferFilesData.h"
#include "DataCenter/TransferFolderData.h"

namespace EventOper
{

    OperMonitorFile::OperMonitorFile()
    {
        connect(&_watcher, SIGNAL(fileChanged(QString)), this, SLOT(fileChanged(QString)));
        connect(&_watcher, SIGNAL(folderChanged(QString)), this, SLOT(folderChanged(QString)));
    }

    OperMonitorFile::~OperMonitorFile()
    {

    }

    bool OperMonitorFile::prepareArgs()
    {
        /// state check
        if (hasArgs("TransferData"))
        {
            _tranferData = argValuePtr<Data::TransferData>("TransferData");
        }

        if (!_tranferData)
        {
            return false;
        }

        /// prepare functions
        _signEventHandler.insert("AddTransfer", [this]()-> bool { return this->addTransfer(); });
        _signEventHandler.insert("RemoveTransfer", [this]()-> bool { return this->removeTransfer(); });

        /// prepare data
        Data::FrameAppData * app = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!app) { return false; }
        _transferDataMgr = app->transferData();
        _sglDataMgr = app->getSingleSimulationAppDataManger();
        _mulDataMgr = app->getMultiSimulationAppDataManger();

        return true;
    }

    void OperMonitorFile::fileChanged(const QString & filePath)
    {
        int num = _transferDataMgr->getDataCount();
        QList<QGraphicsObject *> inputChangedItems;

        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::TransferData * trans = _transferDataMgr->getDataByIndex(iCnt);
            if (trans->transferType() == Data::Transfer_File_Type)
            {
                Data::TransferFileData * file = (Data::TransferFileData *)(trans);
                if (file->filePath() == filePath)
                    inputChangedItems.append(trans->graphicsObject());
            }
            else if (trans->transferType() == Data::Transfer_Files_Type)
            {
                Data::TransferFilesData * files = (Data::TransferFilesData *)(trans);
                if (files->filePaths().contains(filePath))
                    inputChangedItems.append(trans->graphicsObject());
            }
        }
        notifyInputChanged(inputChangedItems);
    }

    void OperMonitorFile::folderChanged(const QString folderPath)
    {
        int num = _transferDataMgr->getDataCount();
        QList<QGraphicsObject *> inputChangedItems;

        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::TransferData * trans = _transferDataMgr->getDataByIndex(iCnt);
            if (trans->transferType() == Data::Transfer_Folder_Type)
            {
                Data::TransferFolderData * folder = (Data::TransferFolderData *)(trans);
                if (folder->folderPath() == folderPath)
                    inputChangedItems.append(trans->graphicsObject());
            }
        }
        notifyInputChanged(inputChangedItems);
    }

    void OperMonitorFile::notifyInputChanged(QList<QGraphicsObject * > objs)
    {
        for (QGraphicsObject * obj : objs)
        {
            Graphics::GraphicsItem * item = qobject_cast<Graphics::GraphicsItem *>(obj);
            if (item)
            {
                item->setComponentInputState(Graphics::State_Input_Changed);
            }
        }
    }

    bool OperMonitorFile::addTransfer()
    {
        if (_tranferData->transferType() == Data::Transfer_None_Type) { return true; }
        _transferDataMgr->appendDataObj(_tranferData);


        if (Data::Transfer_File_Type == _tranferData->transferType())
        {
            Data::TransferFileData * file = (Data::TransferFileData *)(_tranferData);
            _watcher.addPath(file->filePath());
        }
        else if (Data::Transfer_Files_Type == _tranferData->transferType())
        {
            Data::TransferFilesData * files = (Data::TransferFilesData *)(_tranferData);
            _watcher.addPaths(files->filePaths());
        }
        else if (Data::Transfer_Folder_Type == _tranferData->transferType())
        {
            Data::TransferFolderData * folder = (Data::TransferFolderData *)(_tranferData);
            QDir dir(folder->folderPath());

            /// construct filter
            QStringList filters;
            for (QString type : folder->types())
            {
                filters.append("*." + type);
            }

            /// add watch files
            QStringList filePaths = folder->filePaths();
            for (QFileInfo info : dir.entryInfoList(filters, QDir::Files | QDir::NoDotAndDotDot))
            {
                filePaths.append(info.fileName());
                _watcher.addPath(info.filePath());
            }
            folder->setFilePaths(filePaths);
        }
        return false;
    }

    bool OperMonitorFile::removeTransfer()
    {

        return false;
    }

}