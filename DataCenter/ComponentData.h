/**
 *
 * @file      ComponentData.h
 * @brief     File To Define Component. With Basic Info. Input Info .Output Info . Default Mode Info.
 *            While Add Use Input Mode . Use Output Mode . It Changes To Component Instance
 *            Upon Component Instance.  While Add User Set Input File . Project Infos . It Changes To Component App Data
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-5 11:37
 *
 */

#pragma once
#include "DataCenterAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include <QDir>

namespace Data
{
    class ComponentData;
    /**
     * @brief     component app 's input/output channel type
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-11 12:52
     */
    enum ChannelType
    {
        /**
         * @brief     none type channel. means no input or output
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 8:56
         */
        Channel_None_Type,
        /**
         * @brief     file type channel
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 12:53
         */
        Channel_File_Type,
        /**
         * @brief     files type channel
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 8:55
         */
        Channel_Files_Type,
        /**
         * @brief     folder type channel
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 12:53
         */
        Channel_Folder_Type,
    };

    /**
     * @brief     channel
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-12 8:57
     */
    struct DATA_CENTER_API Channel
    {
        QString channelName;
        ChannelType channelType;
        virtual void copy(Channel * other)
        {
            channelName = other->channelName;
            channelType = other->channelType;
        }
    };

    /**
     * @brief     component app 's input/output channel
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-11 12:53
     */
    struct DATA_CENTER_API FileChannel : public Channel
    {
        /**
         * @brief     channel file type.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 12:55
         */
        QString fileType;

        /**
         * @brief     channel description
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 12:57
         */
        QString channelDesc;

        virtual void copy(Channel * other) override
        {
            FileChannel * real = dynamic_cast<FileChannel*>(other);
            Channel::copy(other);
            fileType = real->fileType;
            channelDesc = real->channelDesc;
        }
    };

    struct DATA_CENTER_API FilesChannel : public Channel
    {
        /**
         * @brief     channel file types. must input file types. type can appear multiple times
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 9:09
         */
        QStringList fileTypes;

        /**
         * @brief     channel description
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 9:09
         */
        QString channelDesc;

        void copy(Channel * other)
        {
            FilesChannel * real = dynamic_cast<FilesChannel*>(other);
            Channel::copy(other);
            fileTypes = real->fileTypes;
            channelDesc = real->channelDesc;
        }
    };

    struct DATA_CENTER_API FolderChannel : public Channel
    {
        /**
         * @brief     folder channel may support file types
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 9:10
         */
        QStringList supports;

        /**
        * @brief     channel description
        * @author    maguiwa(maguiwa520@163.com)
        * @date      2024-9-12 9:09
        */
        QString channelDesc;

        void copy(Channel * other)
        {
            FolderChannel * real = dynamic_cast<FolderChannel*>(other);
            Channel::copy(other);
            supports = real->supports;
            channelDesc = real->channelDesc;
        }
    };

    /**
     * @brief     component app run additional input param description
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 12:56
     */
    struct DATA_CENTER_API AdditionalInputParam
    {
        /**
         * @brief     cmd argv
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 12:57
         */
        QString argv;
        /**
         * @brief     additional input param description
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 12:57
         */
        QString desc;
        /**
         * @brief     is this param default to use
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 12:57
         */
        bool defaultUse{ true };
        /**
         * @brief     is this param can set by user
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 12:58
         */
        bool userSet{ false };
        /**
         * @brief     is same with another AdditionalInputParam
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 12:58
         */
        bool operator==(const AdditionalInputParam & additional);
    };

    /**
     * @brief     component data. component description data. not instance
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 12:58
     */
    class DATA_CENTER_API ComponentData : public Core::FITKAbstractNDataObject
    {
    public:

        /**
         * @brief     default constructor
         * @return    ComponentData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 12:59
         */
        explicit ComponentData() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 12:59
         */
        ~ComponentData() = default;

        /**
         * @brief     get component app 's svg. path is : App/../AppComponents/Windows/svg
         * @return    QString . svg file path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:00
         */
        QString svg() const { return _svg; }

        /**
         * @brief     set component 's svg
         * @param     svg[i]. svg file path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:02
         */
        void setSvg(const QString & svg) { _svg = svg; }

        /**
         * @brief     get component app version
         * @return    QString. component app version
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:03
         */
        QString version() const { return _version; }

        /**
         * @brief     set component app version
         * @param     version[i]. component app version
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:03
         */
        void setVersion(const QString & version) { _version = version; }

        /**
         * @brief     get component app description
         * @return    QString . component app description
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:04
         */
        QString description() const { return _desc; }

        /**
         * @brief     set component app description
         * @param     desc[i]. component app description
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:04
         */
        void setDescription(const QString & desc) { _desc = desc; }

        /**
         * @brief     get component app path
         * @return    QString . component app path
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:05
         */
        QString path() const { return _path; }

        /**
         * @brief     set component app path
         * @param     path[i]. component app path
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:05
         */
        void setPath(const QString & path) { _path = QDir::cleanPath(path); }

        /**
         * @brief     get component app type. built-in type. Geometry Mesh Solver Post Tool
         * @return    QString . component app type
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:06
         */
        QString type() const { return _type; }

        /**
         * @brief     set component app type.
         * @param     type[i] . component app type
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:07
         */
        void setType(const QString & type) { _type = type; }

        /**
         * @brief     set component 's disiplines
         * @param     disiplines[i].  component 's disiplines
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:42
         */
        void setDisciplines(const QStringList & disiplines) { _disciplines = disiplines; }

        /**
         * @brief     get component 's disiplines
         * @return    QStringList .  component 's disiplines
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:42
         */
        QStringList disciplines() const { return _disciplines; }

        /**
         * @brief     set component 's author
         * @param     author[i]. component 's author
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:43
         */
        void setAuthor(const QString & author) { _author = author; }

        /**
         * @brief     get component 's author
         * @return    QString . component 's author
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:44
         */
        QString author() const { return _author; }

        /**
         * @brief     set component 's company
         * @param     company[i]. component 's company
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:45
         */
        void setCompany(const QString & company) { _company = company; }

        /**
         * @brief     get component 's company
         * @return    QString . component 's company
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:45
         */
        QString company() const { return _company; }

        /**
         * @brief     get license type.
         * @return    QString . license type.
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:47
         */
        QString licenseType() const { return _licenseType; }

        /**
         * @brief     set license type.
         * @param     lincenType[i]. license type
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 12:47
         */
        void setLicenseType(const QString & lincenType) { _licenseType = lincenType; }

        /**
        * @brief     get if component app run with gui
        * @return    bool . with gui or not
        * @author    maguiwa (maguiwa520@163.com)
        * @data      2024-9-10 8:33
        */
        bool withGUI() const { return _withGui; }

        /**
         * @brief     set component app run with gui
         * @param     with[i]. with or not
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 8:34
         */
        void setWithGUI(bool with) { _withGui = with; }

        /**
         * @brief     add input channel
         * @param     inputChannel[i]. input channel
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 13:11
         */
        void addInputChannel(Channel * inputChannel) { _inputChannel.insert(inputChannel->channelName, inputChannel); }

        /**
         * @brief     get input channel by name
         * @param     name[i].input channel name
         * @return    Data::Channel . input channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:09
         */
        Channel * inputChannel(const QString & name) { return _inputChannel.contains(name) ? _inputChannel[name] : nullptr; }

        /**
         * @brief     get input channel names
         * @return    QStringList . input channel names
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:10
         */
        QStringList inputChannelNames() const { return _inputChannel.keys(); }

        /**
         * @brief     get file type input channel names. as folder type input first check first
         * @return    QStringList . file type input channel names
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 20:03
         */
        QStringList fileTypeInputChannelNames();

        /**
         * @brief     get files type input channel names
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 13:05
         */
        QStringList filesTypeInputChannelNames();

        /**
         * @brief     get folder type input channel names . as folder type input first check first
         * @return    QStringList . folder type input channel names
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 20:04
         */
        QStringList folderTypeInputChannelNames();

        /**
         * @brief     add output channel
         * @param     outputChannel[i]. output channel
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 13:13
         */
        void addOutputChannel(Channel * outputChannel) { _outputChannel.insert(outputChannel->channelName, outputChannel); }

        /**
         * @brief     get output channel by name
         * @param     name[i]. output channel name
         * @return    Data::Channel . output channel
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:13
         */
        Channel * outputChannel(const QString & name) { return _outputChannel.contains(name) ? _outputChannel[name] : nullptr; }

        /**
         * @brief     get output channel names
         * @return    QStringList . output channel names
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:14
         */
        QStringList outputChannelNames() const { return _outputChannel.keys(); }

        /**
         * @brief     add additional input param
         * @param     param[i]. additional input param
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:35
         */
        void addAdditionalInputParam(const AdditionalInputParam & param);

        /**
         * @brief     get additional input param by additional input param name
         * @param     paramName[i]. additional input param name
         * @return    Data::AdditionalInputParam . additional input param
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:36
         */
        AdditionalInputParam additionalInputParam(const QString & paramName) { return _additionalParams.contains(paramName) ? _additionalParams[paramName] : AdditionalInputParam(); }

        /**
         * @brief     get additional input param names
         * @return    QStringList .  additional input param names
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:37
         */
        QStringList additionalInputParamNames() const { return _additionalParams.keys(); }

        /**
         * @brief     copy date
         * @param     obj[i]. copy from
         * @return    bool .copy result
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 14:02
         */
        virtual bool copy(FITKAbstractDataObject* obj) override;

    protected:

        /**
         * @brief     copy channel
         * @param     from[i]. copy channel from
         * @return    Data::Channel * . copied
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 10:11
         */
        Channel * copyChannel(Channel * from);

        /**
         * @brief     component app 's svg file
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:38
         */
        QString _svg{};

        /**
         * @brief     component app 's version
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:38
         */
        QString _version{};

        /**
         * @brief     component app 's description
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:38
         */
        QString _desc{};

        /**
         * @brief     component app 's path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:39
         */
        QString _path{};

        /**
         * @brief     component app 's type  Geometry Mesh Solver Post Tool
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:39
         */
        QString _type{};

        /**
         * @brief     component app 's disciplines
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 11:31
         */
        QStringList _disciplines{};

        /**
         * @brief     component app 's author.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 11:32
         */
        QString _author{};

        /**
         * @brief     component app 's company.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 11:32
         */
        QString _company{};

        /**
         * @brief     component app 's license type.
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-6 11:33
         */
        QString _licenseType{};

        /**
         * @brief     input channels of component app
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 13:02
         */
        QMap<QString, Channel *> _inputChannel;

        /**
         * @brief     output channels of component app
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 13:03
         */
        QMap<QString, Channel *> _outputChannel;

        /**
         * @brief     component app ' additional params
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 13:41
         */
        QMap<QString, AdditionalInputParam> _additionalParams;

        /**
         * @brief     if component app run with GUI
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-10 8:32
         */
        bool _withGui{ true };
    };

    /**
     * @brief     Component Data Manger
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 13:42
     */
    class DATA_CENTER_API ComponentDataManger : public Core::FITKAbstractDataManager<ComponentData>
    {
    public:
        /**
         * @brief     default constructor
         * @return    ComponentDataManger object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:42
         */
        explicit ComponentDataManger() = default;
        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 13:42
         */
        virtual ~ComponentDataManger() = default;
    };
}