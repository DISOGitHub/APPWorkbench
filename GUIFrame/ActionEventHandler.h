/**
 *
 * @file      ActionEventHandler.h
 * @brief     Toolbar IconButton Triggered Handler
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 17:28
 *
 */
#pragma once
#include <QObject>
#include <QAction>
#include <QMutex>
#include "GUIFrameAPI.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"

namespace GUI
{
    class IconButton;
    /**
     *
     * @file      ActionEventHandler.h
     * @brief     Toolbar IconButton Triggered Handler
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 17:28
     *
     */
    class GUI_FRAME_API ActionEventsHandler : public QObject
    {
        Q_OBJECT
            DeclSingleton(ActionEventsHandler)
    public:
        /**
         * @brief     handle icon button list
         * @param     actions[i] .icon button list
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:28
         */
        void handleIconButtons(QList<IconButton *> actions);

        /**
         * @brief     handle icon button
         * @param     action[i] . icon button
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:29
         */
        void handleIconButton(IconButton * action);

    protected:
        /**
         * @brief     initialize function required by macro . no implement
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:33
         */
        void initialize() {}

        /**
         * @brief     finalize function required by macro . no implement
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:35
         */
        void finalize() {}

    private slots:

        /**
         * @brief     icon button clicked slot
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:35
         */
        void buttonClicked();
    };
}