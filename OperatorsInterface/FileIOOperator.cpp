#include "FileIOOperator.h"

namespace EventOper
{

    FileIOOperator::FileIOOperator()
    {

    }

    FileIOOperator::~FileIOOperator()
    {

    }

    bool FileIOOperator::readComponentInfo(const QString & filePath)
    {
        Q_UNUSED(filePath)
            return false;
    }

    bool FileIOOperator::writeAppDescription(Core::FITKAbstractDataObject * multi, const QString & filePath)
    {
        Q_UNUSED(multi)
            Q_UNUSED(filePath)
            return false;
    }

    Core::FITKAbstractDataObject * FileIOOperator::readAppDescription(const QString & filePath)
    {
        Q_UNUSED(filePath)
            return nullptr;
    }

    bool FileIOOperator::writeProject(const QString & filePath)
    {
        Q_UNUSED(filePath)
            return false;
    }

    bool FileIOOperator::readProject(const QString & filePath)
    {
        Q_UNUSED(filePath)
            return false;
    }

}