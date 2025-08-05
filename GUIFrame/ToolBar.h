/**
 *
 * @file      ToolBar.h
 * @brief     A Look Like ToolBar For Windows ' ToolBar Position
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 19:16
 *
 */
#pragma once
#include <QWidget>
#include <QHBoxLayout>

namespace GUI
{
    class IconButton;
    /**
     * @brief     a look like tool bar inherit from qwidget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 19:16
     */
    class ToolBar : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i] . parent widget
         * @param     f[i] . widget flag
         * @return    ToolBar object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:17
         */
        explicit ToolBar(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:18
         */
        ~ToolBar();


        /**
         * @brief     add icon button like tool bar add action
         * @param     icon[i]. icon button icon
         * @param     toolTip[i]. icon button 's tooltip
         * @param     triggeredName[i]. icon button triggered name
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:18
         */
        void addAction(const QString & icon, const QString & toolTip, const QString & triggeredName);

        /**
         * @brief     add separator like tool bar
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:19
         */
        void addSeparator();

        /**
         * @brief     get icon buttons
         * @return    QList<IconButton *> . icon buttons
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:19
         */
        QList<IconButton *> iconButtons();

    protected:

        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:20
         */
        void initUi();

        /**
         * @brief     update user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:20
         */
        void updateUi();

        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:20
         */
        virtual void paintEvent(QPaintEvent *event) override;

        /**
         * @brief     icon buttons
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:21
         */
        QList<IconButton *> _buttons;

        /**
         * @brief     tool bar 's layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:21
         */
        QHBoxLayout * _lay{};
    };
}