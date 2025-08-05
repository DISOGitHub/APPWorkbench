/**
 *
 * @file      ScaleMenu.h
 * @brief     Bottom Widget Scale Menu To Scale Canvas
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-21 15:02
 *
 */

#pragma once
#include <QMenu>
#include "GUIWidgetAPI.h"

namespace GUI
{
    /**
     * @brief     Scale Menu
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 20:09
     */
    class GUI_WIDGET_API StyleMenu : public QMenu
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @return    ScaleMenu object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:10
         */
        explicit StyleMenu(QWidget *parent = nullptr);

        /**
         * @brief     constructor
         * @param     title[i]. title
         * @param     parent[i]. parent widget
         * @return    ScaleMenu object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:10
         */
        explicit StyleMenu(const QString &title, QWidget *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:11
         */
        ~StyleMenu();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:11
         */
        void initUi();
    };
}