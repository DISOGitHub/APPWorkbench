/**
 *
 * @file      SettingWidget.h
 * @brief     Setting Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 20:03
 *
 */
#pragma once
#include <QWidget>

namespace GUI
{
    /**
     * @brief     setting widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 20:04
     */
    class SettingWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flags
         * @return    SettingWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:05
         */
        explicit SettingWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:06
         */
        ~SettingWidget();
    };
}