/**
 *
 * @file      OperCanvasItemsLayout.h
 * @brief     Handle Canvas Item Layout Actions Triggered.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 13:22
 *
 */
#pragma once
#include "OperatorsInterface/MultiEventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"

namespace Graphics
{
    class GraphicsItem;
}

namespace EventOper
{
    /**
     * @brief     handle main window 's canvas item layout actions
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 15:36
     */
    class OperCanvasItemsLayout : public MultiEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperCanvasItemsLayout object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:37
         */
        explicit OperCanvasItemsLayout();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:37
         */
        virtual ~OperCanvasItemsLayout();

    protected:

        /**
         * @brief     prepare layout action 's function
         * @return    bool . prepare success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:38
         */
        virtual bool prepareArgs() override;

        /**
         * @brief     items align left event
         * @return    bool . execute success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:38
         */
        bool alignLeft();

        /**
         * @brief     items align right event
         * @return    bool . execute success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:39
         */
        bool alignRight();

        /**
         * @brief     items align top event
         * @return    bool . execute success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:39
         */
        bool alignTop();

        /**
         * @brief     items align bottom event
         * @return    bool . execute success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:39
         */
        bool alignBottom();

        /**
         * @brief     horizontal layout
         * @return    bool . layout success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:40
         */
        bool hLayout();

        /**
         * @brief     vertical layout
         * @return    bool . layout success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:41
         */
        bool vLayout();

    private:
        /**
         * @brief     get current scene selected GraphicsItem  list
         * @return    QList<Graphics::GraphicsItem *> . GraphicsItem  list
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 15:41
         */
        QList<Graphics::GraphicsItem *> getSelectedComponents();
    };

    Register2FITKOperatorRepo(Align_Left, OperCanvasItemsLayout);
    Register2FITKOperatorRepo(Align_Top, OperCanvasItemsLayout);
    Register2FITKOperatorRepo(Align_Right, OperCanvasItemsLayout);
    Register2FITKOperatorRepo(Align_Bottom, OperCanvasItemsLayout);
    Register2FITKOperatorRepo(H_Lay, OperCanvasItemsLayout);
    Register2FITKOperatorRepo(V_Lay, OperCanvasItemsLayout);
}