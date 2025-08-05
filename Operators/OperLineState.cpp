#include "OperLineState.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

#include "Graphics/GraphicsItem.h"
#include "Graphics/NotifyItem.h"
#include "Graphics/LineItem.h"

#include "DataCenter/FrameAppData.h"
#include "DataCenter/LineData.h"
#include "DataCenter/LogData.h"
#include "DataCenter/ChannelDegenerate.h"
#include "DataCenter/ComponentAppData.h"
#include "DataCenter/MultiSimulationAppData.h"
#include "DataCenter/SingleSimulationAppData.h"

#include <QSet>

namespace EventOper
{

    OperLineState::OperLineState()
    {

    }

    OperLineState::~OperLineState()
    {

    }

    bool OperLineState::triggered()
    {
        /// prepare arguments
        if (!prepareArgs()) { return false; }

        /// check line 's discipline
        if (!checkLineDisciplineMatch()) {
            return false;
        }

        /// check line 's channel
        if (!checkLineChannel()) {
            return false;
        }

        /// check to item 's input duplicate
        if (!checkToItemDuplicateInputs()) {
            return false;
        }
        return true;
    }

    bool OperLineState::prepareArgs()
    {
        /// get check from to graphics item
        if (_items.isEmpty() || _items.size() != 2) { return false; }
        _from = dynamic_cast<Graphics::GraphicsItem *> (_items[0]);
        _to = dynamic_cast<Graphics::GraphicsItem *> (_items[1]);
        if (!_from || !_to) { return false; }

        /// get relation graphics item data
        Data::FrameAppData * appData = FITKAPP->getGlobalData()->getData<Data::FrameAppData>(FRAME_APP_DATA_ID);
        if (!appData) { return false; }
        Data::ComponentAppDataManger * cptAppDataMgr = appData->getComponentAppDataManger();
        if (!cptAppDataMgr) { return false; }
        _fromData = cptAppDataMgr->componentAppDataByGraphicsObject(_from);
        _toData = cptAppDataMgr->componentAppDataByGraphicsObject(_to);
        _sglAppDataMgr = appData->getSingleSimulationAppDataManger();
        _mulAppDataMgr = appData->getMultiSimulationAppDataManger();

        return (_fromData && _toData && _sglAppDataMgr && _mulAppDataMgr);
    }

    bool OperLineState::checkLineDisciplineMatch()
    {
        if (!_fromData || !_toData) { return false; }
        QStringList cpt1Disciplines = _fromData->disciplines();
        QStringList cpt2Disciplines = _toData->disciplines();

        /// special treatment with general disciplines component app
        if (cpt1Disciplines.size() == 1 && cpt1Disciplines.first() == "general")
            return true;
        if (cpt2Disciplines.size() == 1 && cpt2Disciplines.first() == "general")
            return true;

        QSet<QString> cpt1(cpt1Disciplines.begin(), cpt1Disciplines.end()), cpt2(cpt2Disciplines.begin(), cpt2Disciplines.end());

        if (cpt1.intersects(cpt2))
            return true;

        _msg = QString("Line 's Between %1 %2 And %3 %4 's Discipline Do Not Match.").
            arg(_fromData->getDataObjectName()).
            arg(ADDR(_from)).
            arg(_toData->getDataObjectName()).
            arg(ADDR(_to));
        LOGW(_msg);
        return false;
    }

    bool OperLineState::checkLineChannel()
    {
        if (!_fromData || !_toData) { return false; }
        QStringList outputChannelNames = _fromData->outputChannelNames();
        QStringList inputChannelNames = _toData->inputChannelNames();
        for (QString outputChannelName : outputChannelNames)
        {
            Data::Channel * outputChannel = _fromData->outputChannel(outputChannelName);
            for (QString inputChannelName : inputChannelNames)
            {
                Data::Channel * inputChannel = _toData->inputChannel(inputChannelName);
                Data::ChannelDegenerate checker;
                Data::Channel * degenerateChannel = checker.degenerate(outputChannel, inputChannel);
                if (degenerateChannel)
                {
                    delete degenerateChannel;
                    degenerateChannel = nullptr;
                    return true;
                }
            }
        }
        _msg = QString("Line 's Between %1 %2 And %3 %4 's Channel Not Match.").
            arg(_fromData->getDataObjectName()).
            arg(ADDR(_from)).
            arg(_toData->getDataObjectName()).
            arg(ADDR(_to));
        LOGW(_msg);
        return false;
    }

    bool OperLineState::checkToItemDuplicateInputs()
    {
        if (_sglAppDataMgr->getSingleAppDataByGraphicsObject(_to))
        {
            /// to item is a single simulation app. 
            return true;
        }
        Data::MultiSimulationAppData * multi = _mulAppDataMgr->getMultiAppDataByGraphicsObject(_to);
        if (!multi) { return false; }

        /// to item is in a multi simulation app.
        QList<Data::ComponentAppData *> cpts = multi->getPreviousLinkedComponentApps(_toData);
        if (cpts.isEmpty())
        {
            /// to item is a multi simulation app 's in degree 0 item
            return true;
        }
        else
        {
            /// check if to item has files type input channel
            QStringList inputChannelNames = _toData->filesTypeInputChannelNames();
            if (!inputChannelNames.isEmpty())
            {
                /// if has fit. can line. not interest repeat
                return true;
            }
        }
        _msg = QString("%1 %2 's Input Channel Already Fit.").
            arg(_toData->getDataObjectName()).
            arg(ADDR(_to));
        LOGW(_msg);
        return false;
    }
}