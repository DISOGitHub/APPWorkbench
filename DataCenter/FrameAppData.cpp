#include "FrameAppData.h"
#include "ComponentData.h"
#include "ComponentAppData.h"
#include "SingleSimulationAppData.h"
#include "MultiSimulationAppData.h"
#include "TransferData.h"

namespace Data
{

    FrameAppData::FrameAppData()
    {
        _componentDataMgr = new ComponentDataManger;
        _componentAppDataMgr = new ComponentAppDataManger;
        _singleSimulationAppDataMgr = new SingleSimulationAppDataManger;
        _multiSimulationAppDataMgr = new MultiSimulationAppDataManger;
        _lineDataMgr = new LineDataManger;
        _transferData = new TransferDataManger();
    }

    FrameAppData::~FrameAppData()
    {
        if (_componentDataMgr)
        {
            delete _componentDataMgr;
            _componentDataMgr = nullptr;
        }
        if (_componentAppDataMgr)
        {
            delete _componentAppDataMgr;
            _componentAppDataMgr = nullptr;
        }
        if (_singleSimulationAppDataMgr)
        {
            delete _singleSimulationAppDataMgr;
            _singleSimulationAppDataMgr = nullptr;
        }
        if (_multiSimulationAppDataMgr)
        {
            delete _multiSimulationAppDataMgr;
            _multiSimulationAppDataMgr = nullptr;
        }
        if (_lineDataMgr)
        {
            delete _lineDataMgr;
            _lineDataMgr = nullptr;
        }
    }

    Data::ComponentDataManger * FrameAppData::getComponentDataManger()
    {
        return _componentDataMgr;
    }

    Data::ComponentAppDataManger * FrameAppData::getComponentAppDataManger()
    {
        return _componentAppDataMgr;
    }

    Data::SingleSimulationAppDataManger * FrameAppData::getSingleSimulationAppDataManger()
    {
        return _singleSimulationAppDataMgr;
    }

    Data::MultiSimulationAppDataManger * FrameAppData::getMultiSimulationAppDataManger()
    {
        return _multiSimulationAppDataMgr;
    }

    Data::LineDataManger * FrameAppData::getLineDataManger()
    {
        return _lineDataMgr;
    }

}