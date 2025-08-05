/**
 *
 * @file      ComponentFactory.cpp
 * @brief     The factory of component to load dynamic link library. no business.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 15:57
 *
 */
#pragma once
#include "FITK_Kernel/FITKAppFramework/FITKComponentFactory.h"

 /**
  * @brief     component factory
  * @author    maguiwa(maguiwa520@163.com)
  * @date      2024-8-29 16:01
  */
class ComponentFactory : public AppFrame::FITKComponentFactory
{
public:

    /**
     * @brief:    default constructor
     * @return:   component factory object
     * @author:   maguiwa (maguiwa520@163.com)
     * @date      2024-8-29 16:03
     */
    ComponentFactory() = default;

    /**
     * @brief:    default destructor
     * @author:   maguiwa (maguiwa520@163.com)
     * @date      2024-8-29 16:04
     */
    ~ComponentFactory() = default;

    /**
     * @brief:    To load dynamic link library by call function.
     * @return:   QList<AppFrame::FITKComponentInterface *> registered components list
     * @author:   maguiwa (maguiwa520@163.com)
     * @date      2024-8-29 16:01
     */
    QList<AppFrame::FITKComponentInterface *> createComponents() override;
};
