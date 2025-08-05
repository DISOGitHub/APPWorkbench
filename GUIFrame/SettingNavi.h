/**
 *
 * @file      SettingNavi.h
 * @brief     Setting Navigation Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 20:07
 *
 */
#pragma once
#include <QWidget>

namespace GUI
{
    /**
     * @brief     Setting Navigation Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 20:07
     */
    class SettingNavi : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flags
         * @return    SettingNavi object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:07
         */
        explicit SettingNavi(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:08
         */
        ~SettingNavi();

    protected:
        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:08
         */
        virtual void paintEvent(QPaintEvent * event) override;

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:08
         */
        void initUi();
    };
}