/**
 *
 * @file      OperFileIO.h
 * @brief     Operator For File 's Read And Write. Simulation Description File. Project File . Component Description File
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-23 15:24
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/FileIOOperator.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"

namespace Data
{
    class ComponentData;
    class ComponentDataManger;
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
    class MultiSimulationAppData;
}
namespace Core
{
    class FITKAbstractDataObject;
}

namespace EventOper
{
    /**
     * @brief     File IO Operator Implement
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-23 15:36
     */
    class OperFileIO : public FileIOOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperFileIO object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:37
         */
        OperFileIO();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:37
         */
        ~OperFileIO();

        /**
         * @brief     read component description file
         * @param     filePath[i]. component description file
         * @return    bool . is read ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:53
         */
        virtual bool readComponentInfo(const QString & filePath) override;

        /**
         * @brief     write app description
         * @param     multi[i]. multi component simulation app
         * @param     filePath[i] . description file path
         * @return    bool . is write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:58
         */
        virtual bool writeAppDescription(Core::FITKAbstractDataObject * multi, const QString & filePath) override;

        /**
         * @brief     read app description
         * @param     filePath[i]. description file path
         * @return    Data::MultiSimulationAppData * . multi component simulation app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:59
         */
        virtual Core::FITKAbstractDataObject * readAppDescription(const QString & filePath) override;

        /**
         * @brief     write project file
         * @param     filePath[i] . project file path
         * @return    bool . is write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 16:00
         */
        virtual bool writeProject(const QString & filePath) override;

        /**
         * @brief     read project file
         * @param     filePath[i] . project file path
         * @return    bool . is read ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 16:00
         */
        virtual bool readProject(const QString & filePath) override;



    protected:

        /**
        * @brief     component data manger
        * @author    maguiwa(maguiwa520@163.com)
        * @date      2024-9-23 18:56
        */
        Data::ComponentDataManger * _cptDataMgr{};

        /**
         * @brief     multi component app construct simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-23 19:00
         */
        Data::MultiSimulationAppDataManger * _mulSimAppDataMgr{};

        /**
         * @brief     single component app construct simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-23 19:01
         */
        Data::SingleSimulationAppDataManger * _sglSimAppDataMgr{};

        /**
         * @brief     ensure directory exists
         * @param     directory[i]. directory
         * @return    bool . is ensure ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 19:50
         */
        bool ensureDirectoryExists(const QString & directory);

    private:
        /**
         * @brief     get rapidjson document by json file path
         * @param     filePath[i]. json file path
         * @return    rapidjson::Document . document object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 17:28
         */
        rapidjson::Document getDocumentByJsonFilePath(const QString & filePath);

        /**
         * @brief     read component 's basic info
         * @param     filePath[i]. component description file path
         * @param     data[o]. component app data
         * @param     doc[i]. rapid json document object
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 17:40
         */
        void readComponentBasicInfo(const QString & filePath, Data::ComponentData * data, rapidjson::Document & doc);

        /**
         * @brief     read component input / output channel info
         * @param     input[i]. is input channel, input channel true , output channel false
         * @param     data[o]. component data
         * @param     node[i]. rapid json value object
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 18:17
         */
        void readComponentChannel(bool input, Data::ComponentData * data, const rapidjson::Value & node);

        /**
         * @brief     read component additional input params
         * @param     data[o]. component data
         * @param     node[i]. rapid json value object
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 18:37
         */
        void readAdditionalInputParams(Data::ComponentData * data, const rapidjson::Value & node);
    };

    Register2FITKOperatorRepo(FileIO, OperFileIO);
}