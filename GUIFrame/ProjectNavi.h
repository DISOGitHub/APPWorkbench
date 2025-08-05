/**
 *
 * @file      ProjectNavi.h
 * @brief     Project Navigation Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 20:12
 *
 */
#pragma once
#include <QTreeWidget>
#include "GUIFrameAPI.h"

namespace GUI
{
    /**
     * @brief     Project Navigation Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 20:12
     */
    class GUI_FRAME_API ProjectNavi : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flag
         * @return    ProjectNavi object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:12
         */
        explicit ProjectNavi(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:13
         */
        ~ProjectNavi();

        /**
         * @brief     get tree widget
         * @return    QTreeWidget * . tree widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:13
         */
        QTreeWidget * treeWidget() { return _tree; }

    protected:
        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:13
         */
        virtual void paintEvent(QPaintEvent * event) override;

    private:
        /**
         * @brief     initialize
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 20:13
         */
        void init();

    private:
        /**
         * @brief     tree widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 20:13
         */
        QTreeWidget * _tree{};

    };
}