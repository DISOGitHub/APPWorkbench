/**
 *
 * @file      WidgetContainer.h
 * @brief     Widget Container Looks Like VS Code 's bottom part
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 9:22
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QString>
#include <QMap>
#include <QHBoxLayout>
#include "WidgetContainerItem.h"

namespace GUI
{
    class IconButton;
    class PressButton;
    /**
     * @brief     Widget Container Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-4 10:54
     */
    class GUI_WIDGET_API WidgetContainer : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget pointer
         * @param     f[i]. window flag
         * @return    WidgetContainer object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:55
         */
        explicit WidgetContainer(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:55
         */
        ~WidgetContainer() override;

        /**
         * @brief     add widget item
         * @param     name[i]. widget item 's name
         * @param     func[i]. widget item 's shortcuts functions widget
         * @param     content[i]. widget item 's core display area
         * @return    int . item index
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:56
         */
        int addWidget(const QString & name = QString(), QWidget * func = nullptr, QWidget * content = nullptr);

        /**
         * @brief     add widget item
         * @param     item[i]. widget item
         * @return    int . item index
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:57
         */
        int addWidget(WidgetContainerItem * item);

    Q_SIGNALS:
        /**
         * @brief     signal expand occur
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 11:21
         */
        void expand();

        /**
         * @brief     signal retract occur
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 11:23
         */
        void retract();

    protected:
        /**
         * @brief     paint event. to paint current item 's select state
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:57
         */
        virtual void paintEvent(QPaintEvent *event) override;

        /**
         * @brief     mouse press event. to select current item
         * @param     event[i]. mouse press event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:58
         */
        virtual void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief     initialize Ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 10:59
         */
        void initUI();

    private:
        /**
         * @brief     widget item map
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 10:59
         */
        QMap<QString, WidgetContainerItem * > _items;

        /**
         * @brief     title widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:00
         */
        QWidget * _title{};

        /**
         * @brief     shortcuts functions stack. in title widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:00
         */
        QStackedWidget * _stackShortcuts{};

        /**
         * @brief     contents stack
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:00
         */
        QStackedWidget * _stackContents{};

        /**
         * @brief     title 's item navigation part layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:01
         */
        QHBoxLayout * _leftLay{};

        /**
         * @brief     shared function close
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:01
         */
        IconButton * _close{};

        /**
         * @brief     shared function expand
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:03
         */
        IconButton * _expand{};

        /**
         * @brief     name of current page
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 11:02
         */
        QString _currentPage{};
    };
}
