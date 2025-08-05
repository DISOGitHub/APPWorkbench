/**
 *
 * @file      ComponentFactory.cpp
 * @brief     The factory of component to load dynamic link library. no business.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-29 15:57
 *
 */

#include "ComponentFactory.h"
#include "Operators/OpersInterface.h"

QList<AppFrame::FITKComponentInterface *> ComponentFactory::createComponents()
{
    QList<AppFrame::FITKComponentInterface *> componentList;
    componentList << new EventOper::OperatorsInterface;
    return componentList;
}
