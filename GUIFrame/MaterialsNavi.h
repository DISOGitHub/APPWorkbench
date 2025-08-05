/**
 *
 * @file      MaterialsNavi.h
 * @brief     Workbench Inner Material Component Navigation
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 19:51
 *
 */
#pragma once
#include <QWidget>

namespace GUI
{
    /**
     * @brief     Workbench Inner Material Component Navigation
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 20:14
     */
    class MaterialsNavi : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flags
         * @return    MaterialsNavi object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:14
         */
        explicit MaterialsNavi(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:15
         */
        ~MaterialsNavi();

    protected:
        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:15
         */
        virtual void paintEvent(QPaintEvent * event) override;

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:15
         */
        void initUi();
    };
}