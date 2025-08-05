/**
 *
 * @file      ComponentNavi.h
 * @brief     Component Navigation Page. User Can Select Component Item And Drag It To Canvas.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 17:36
 *
 */
#pragma once
#include "GUIWidget/DrawerPanel.h"

namespace GUI
{
    /**
     * @brief     Component Navigation Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 17:37
     */
    class ComponentNavi : public DrawerPanel
    {
        Q_OBJECT
    public:
        /**
         * @brief     construct
         * @param     parent[i] . parent widget
         * @param     f[i] . widget flag
         * @return    ComponentNavi object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:37
         */
        explicit ComponentNavi(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:38
         */
        ~ComponentNavi();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 17:38
         */
        void initUi();
    };
}