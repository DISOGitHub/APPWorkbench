/**
 *
 * @file      NavigationWidget.h
 * @brief     Navigation Widget. Fist Level Navigation
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 10:48
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QWidget>
#include <QList>
#include <QVBoxLayout>

namespace GUI
{
    class IconButton;
    /**
     * @brief     Navigation Widget. Fist Level Navigation
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 10:49
     */
    class GUI_WIDGET_API NavigationWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flag
         * @return    NavigationWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:49
         */
        explicit NavigationWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:49
         */
        ~NavigationWidget();

        /**
         * @brief     add icon button as a selectable navigation item
         * @param     button[i]. icon button
         * @param     top[i]. add to the top
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:50
         */
        void addIconButton(IconButton * button, bool top = true);

        /**
         * @brief     set current index
         * @param     index[i]. current index
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:51
         */
        void setCurrentIndex(int index);

        /**
         * @brief     get current index
         * @return    int. current index
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:52
         */
        int currentIndex();

        /**
         * @brief     get icon button count
         * @return    int . icon button count
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:56
         */
        int count();

    Q_SIGNALS:
        /**
         * @brief     while user clicked icon button navigation item. emit item_clicked singal
         * @param     index[i]. item index
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:56
         */
        void item_clicked(int index);

    protected slots:
        /**
         * @brief     while state change .update
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:57
         */
        void stateChanged();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:57
         */
        void initUI();

        /**
         * @brief     current navigation item index
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:58
         */
        int _index{ -1 };

        /**
         * @brief     icon button list. navigation selectable items
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:58
         */
        QList<IconButton *> _buttons;

        /**
         * @brief     top part layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:59
         */
        QVBoxLayout * _topLay{};

        /**
         * @brief     bottom part layout
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:59
         */
        QVBoxLayout * _bottomLay{};

        /**
         * @brief     current triggered icon button
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:59
         */
        IconButton * _current{};
    };
}
