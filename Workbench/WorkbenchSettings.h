#pragma once
#include "FITK_Kernel/FITKAppFramework/FITKAppSettings.h"

class WorkbenchSettings : public AppFrame::FITKAppSettings
{
public:

    explicit WorkbenchSettings() = default;
    virtual ~WorkbenchSettings() = default;
    void read() override;
};

