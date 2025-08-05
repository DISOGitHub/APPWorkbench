/**
 *
 * @file      DescriptionNavi.h
 * @brief     Component Description Navigation Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 18:16
 *
 */
#pragma once
#include "GUIWidget/DrawerPanel.h"

namespace GUI
{
    class IconButton;
    /**
     * @brief     Component Description Navigation Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 18:17
     */
    class DescriptionNavi : public DrawerPanel
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flags
         * @return    DescriptionNavi object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 18:18
         */
        explicit DescriptionNavi(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 18:19
         */
        ~DescriptionNavi();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 18:19
         */
        void initUi();

    };
}