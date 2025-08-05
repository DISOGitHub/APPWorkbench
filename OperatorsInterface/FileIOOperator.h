/**
 *
 * @file      FileIOOperator.h
 * @brief     Operator For File 's Read And Write Interface. Simulation Description File. Project File . Component Description File
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-23 16:55
 *
 */

#pragma once
#include "FITK_Kernel/FITKCore/FITKAbstractOperator.h"
#include "OperatorsInterfaceAPI.h"

 /**
  * @brief     forward declare
  * @author    maguiwa(maguiwa520@163.com)
  * @date      2024-9-23 17:10
  */
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
    class OPERATORS_INTERFACE_API FileIOOperator : public Core::FITKAbstractOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperFileIO object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:37
         */
        FileIOOperator();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:37
         */
        ~FileIOOperator();

        /**
         * @brief     read component description file
         * @param     filePath[i]. component description file
         * @return    bool . is read ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:53
         */
        virtual bool readComponentInfo(const QString & filePath);

        /**
         * @brief     write app description
         * @param     multi[i]. multi component simulation app
         * @param     filePath[i] . description file path
         * @return    bool . is write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:58
         */
        virtual bool writeAppDescription(Core::FITKAbstractDataObject * multi, const QString & filePath);

        /**
         * @brief     read app description
         * @param     filePath[i]. description file path
         * @return    Data::MultiSimulationAppData * . multi component simulation app data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 15:59
         */
        virtual Core::FITKAbstractDataObject * readAppDescription(const QString & filePath);

        /**
         * @brief     write project file
         * @param     filePath[i] . project file path
         * @return    bool . is write ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 16:00
         */
        virtual bool writeProject(const QString & filePath);

        /**
         * @brief     read project file
         * @param     filePath[i] . project file path
         * @return    bool . is read ok
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 16:00
         */
        virtual bool readProject(const QString & filePath);
    };
}