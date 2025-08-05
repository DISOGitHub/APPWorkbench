/**
 *
 * @file      OperLineState.h
 * @brief     Check Line 's State. Need Set Transfered File. Check To Graphics Input Not Duplicate
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 18:26
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/GraphicsObjectEventOperator.h"

namespace Graphics
{
    class GraphicsItem;
    class LineItem;
}
namespace Data
{
    class ComponentAppData;
    class SingleSimulationAppDataManger;
    class MultiSimulationAppDataManger;
}

namespace EventOper
{
    /**
     * @brief     Line State Operator. To Update Line 's State
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 18:31
     */
    class OperLineState : public GraphicsObjectEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperLineState object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:33
         */
        OperLineState();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:33
         */
        ~OperLineState();

        /**
         * @brief     Need to update Line State
         * @return    bool . Update Line State Success or Not
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:34
         */
        virtual bool triggered() override;

    protected:

        /**
         * @brief     prepare args about operation
         * @return    bool . prepare result
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 15:52
         */
        bool prepareArgs();

        /**
         * @brief     check line 's from and to component item 's discipline attribute
         * @return    bool . is match discipline attribute
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 10:51
         */
        bool checkLineDisciplineMatch();

        /**
         * @brief     check 's from and to component item 's channel.
         * @return    bool . is channel fit
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-11 16:07
         */
        bool checkLineChannel();

        /**
         * @brief     check whether to item 's input duplicate
         * @param     info[o]. checked info
         * @return    bool . true means not duplicate
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 19:25
         */
        bool checkToItemDuplicateInputs();

    protected:
        /**
         * @brief     line from graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 11:09
         */
        Graphics::GraphicsItem * _from{};

        /**
         * @brief     line to graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 15:42
         */
        Graphics::GraphicsItem * _to{};

        /**
         * @brief     line from graphics item 's component app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 11:09
         */
        Data::ComponentAppData * _fromData{};

        /**
         * @brief     line to graphics item 's component app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 15:46
         */
        Data::ComponentAppData * _toData{};

        /**
         * @brief     single simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 12:46
         */
        Data::SingleSimulationAppDataManger * _sglAppDataMgr{};

        /**
         * @brief     multi simulation app data manger
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 12:46
         */
        Data::MultiSimulationAppDataManger * _mulAppDataMgr{};

        /**
         * @brief     line message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-11 15:56
         */
        QString _msg;
    };
    Register2FITKOperatorRepo(LineState, OperLineState);
}