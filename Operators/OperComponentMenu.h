/**
 *
 * @file      OperComponentMenu.h
 * @brief     Get Component App Item 's Right Button Menu. 
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-12 20:11
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/GraphicsObjectEventOperator.h"

namespace Graphics
{
    class GraphicsItem;
}
namespace Data
{
    class ComponentAppData;
    class ComponentAppDataManger;
}

namespace EventOper
{
    class OperComponentMenu : public GraphicsObjectEventOperator
    {
        Q_OBJECT
    public:
        OperComponentMenu();
        ~OperComponentMenu();

        virtual bool triggered() override;

    };
    Register2FITKOPeratorRepo(ComponentMenu, OperComponentMenu);
}