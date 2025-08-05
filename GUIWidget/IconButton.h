/**
 *
 * @file      IconButton.h
 * @brief     Icon Button . A Button Just With Icon. Has Select And Normal State.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 10:29
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QPushButton>

namespace GUI
{
    /**
     * @brief     Icon Button Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 10:30
     */
    class GUI_WIDGET_API IconButton : public QPushButton
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     icon0[i]. normal state icon
         * @param     icon1[i]. select state icon
         * @param     tip[i]. icon button 's tool tip
         * @param     parent[i]. parent widget
         * @param     size[i]. icon size
         * @return    IconButton object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:30
         */
        IconButton(const QIcon& icon0, const QIcon& icon1, const QString & tip, QWidget *parent = nullptr, QSize size = QSize(24, 24));

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:30
         */
        ~IconButton() override;

        /**
         * @brief     to normal state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:35
         */
        void toNormal();

        /**
         * @brief     to select state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:35
         */
        void toSelected();

        /**
         * @brief     while set select. while mouse leave. still show selected until icon button group other select.
         * @param     selected[i]. icon button select state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:36
         */
        void setSelected(bool selected) { _selected = selected; }

        /**
         * @brief     to disable state.
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:38
         */
        void toDisabled();

        /**
         * @brief     get triggered name. while icon button clicked. used for operator
         * @return    QString . triggered name
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:38
         */
        QString triggeredName() const { return _triggeredName; }

        /**
         * @brief     set triggered name. while icon button clicked. used for operator
         * @param     name[i]. triggered name
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:40
         */
        void setTriggeredName(const QString & name) { _triggeredName = name; }

        /**
         * @brief     get normal state icon
         * @return    QIcon . normal state icon
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:41
         */
        QIcon icon0() { return _icon0; }

        /**
         * @brief     get select state icon
         * @return    QIcon . select state icon
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:41
         */
        QIcon icon1() { return _icon1; }

        /**
         * @brief     get icon button tool tip
         * @return    QString . icon button tool tip
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:42
         */
        QString toolTip() { return _tip; }

        /**
         * @brief     get icon button icon size
         * @return    QSize . icon button icon size
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:43
         */
        QSize iconSize() { return _size; }

    protected:

        /**
         * @brief     while mouse enter . show like select state
         * @param     event[i]. mouse enter event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:43
         */
        virtual void enterEvent(QEvent *event) override;

        /**
         * @brief     while mouse leave . show like normal state( while not set selected )
         * @param     event[i]. mouse leave event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 10:43
         */
        virtual void leaveEvent(QEvent *event) override;

    private:
        /**
         * @brief     normal state icon
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:45
         */
        QIcon _icon0;

        /**
         * @brief     select state icon
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:45
         */
        QIcon _icon1;

        /**
         * @brief     icon button 's tool tip
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:45
         */
        QString _tip;

        /**
         * @brief     icon button 's size
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:45
         */
        QSize _size;

        /**
         * @brief     icon button 's triggered name
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:46
         */
        QString _triggeredName;

        /**
         * @brief     if icon button set selected
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:46
         */
        bool _selected{ false };
    };
}
