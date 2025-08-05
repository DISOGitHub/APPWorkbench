/**
 *
 * @file      ComboBox.h
 * @brief     A Look Like Combo Box . Inherit From Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 8:58
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QWidget>
#include <QLabel>
#include <QMenu>

namespace GUI
{
    /**
     * @brief     Look Like ComboBox Widget Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 8:59
     */
    class GUI_WIDGET_API ComboBox : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @return    ComboBox object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 8:59
         */
        explicit ComboBox(QWidget * parent = nullptr);

        /**
         * @brief     constructor
         * @param     items[i]. add items
         * @param     parent[i]. parent widget
         * @return    ComboBox object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:00
         */
        explicit ComboBox(QStringList items, QWidget * parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:01
         */
        virtual ~ComboBox();

        /**
         * @brief     add item
         * @param     icon[i]. item icon
         * @param     text[i]. item text
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:01
         */
        void addItem(QIcon icon, const QString & text);

        /**
         * @brief     add items
         * @param     items[i]. items text
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:01
         */
        void addItems(const QStringList & items);

        /**
         * @brief     add separator
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:02
         */
        void addSeparator();

        /**
         * @brief     register menu. used for popup
         * @param     menu[i]. menu registered in
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:02
         */
        void registerMenu(QMenu * menu);

    Q_SIGNALS:
        /**
         * @brief     combo box item clicked
         * @param     itemName[i]. clicked combo box item name
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:03
         */
        void itemClicked(const QString & itemName);

    public slots:

        /**
         * @brief     clear combo box items
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:03
         */
        void clear();


    protected:
        /**
         * @brief     mouse enter event
         * @param     event[i]. mouse enter event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:04
         */
        void enterEvent(QEvent * event) override;

        /**
         * @brief     mouse leave event
         * @param     event[i]. mouse leave event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:04
         */
        void leaveEvent(QEvent * event) override;

        /**
         * @brief     focus in event
         * @param     event[i]. focus in event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:05
         */
        void focusInEvent(QFocusEvent *event) override;

        /**
         * @brief     focus out event
         * @param     event[i]. focus out event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:26
         */
        void focusOutEvent(QFocusEvent *event) override;

        /**
         * @brief     mouse press event
         * @param     event[i]. mouse press event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:28
         */
        void mousePressEvent(QMouseEvent * event) override;

        /**
         * @brief     mouse release event
         * @param     event[i]. mouse release event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:29
         */
        void mouseReleaseEvent(QMouseEvent * event) override;

        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:29
         */
        void paintEvent(QPaintEvent *event) override;

        /**
         * @brief     current item content
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:29
         */
        QLabel * _content{};

        /**
         * @brief     pop up menu
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:30
         */
        QMenu * _menu{};

        /**
         * @brief     style control para to record if clicked inside
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:30
         */
        bool _clickedInSide{ false };

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:31
         */
        void initUi();

    private slots:
        /**
         * @brief     menu item clicked
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:03
         */
        void actionTriggered();
    };
}
