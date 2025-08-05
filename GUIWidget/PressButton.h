/**
 *
 * @file      PressButton.h
 * @brief     Press Button . A Look Like Button. Used As Drawer Widget Title.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 11:00
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QWidget>
#include <QIcon>
#include <QLabel>
#include <QPen>

namespace GUI
{
    /**
     * @brief     Press Button Class With Normal And Pressed State
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 11:02
     */
    class GUI_WIDGET_API PressButton : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     iconNormal[i]. normal state press button
         * @param     iconPressed[i]. pressed state press button
         * @param     text[i]. press button text
         * @param     align[i]. current just support horizontal align left and align right layout
         * @param     parent[i]. parent widget
         * @return    PressButton object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:02
         */
        PressButton(const QIcon &iconNormal, const QIcon &iconPressed, const QString &text, Qt::AlignmentFlag align = Qt::AlignLeft, QWidget *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:05
         */
        ~PressButton();

        /**
         * @brief     set icon size
         * @param     size[i]. icon size
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:05
         */
        void setIconSize(QSize size);

        /**
         * @brief     to control while has border
         * @param     index[i]. way. 0 left . 1 top. 2 right. 3 bottom
         * @param     with[i]. with border or not
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:06
         */
        void setBorder(int index, bool with);

        /**
         * @brief     is press button in pressed state.
         * @return    bool . is in pressed state
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:07
         */
        bool isPressed() const { return _pressed; }

    Q_SIGNALS:
        /**
         * @brief     user clicked press button
         * @param     pressed[i]. is pressed
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:09
         */
        void clicked(bool pressed);

    protected:
        /**
         * @brief     mouse enter event
         * @param     event[i]. mouse enter event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:10
         */
        virtual void enterEvent(QEvent *event) override;

        /**
         * @brief     mouse leave event
         * @param     event[i]. mouse leave event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:10
         */
        virtual void leaveEvent(QEvent *event) override;

        /**
         * @brief     mouse press event
         * @param     event[i]. mouse press event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:10
         */
        virtual void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief     mouse release event
         * @param     event[i]. mouse release event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:11
         */
        virtual void mouseReleaseEvent(QMouseEvent *event) override;

        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:11
         */
        virtual void paintEvent(QPaintEvent * event) override;

        /**
         * @brief     press button icon size
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:12
         */
        QSize _iconSize{ QSize(16, 16) };

        /**
         * @brief     press button pressed state record
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:12
         */
        bool _pressed{ false };

        /**
         * @brief     press button normal state icon
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:13
         */
        QIcon _iconNormal;

        /**
         * @brief     press button pressed state icon
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:13
         */
        QIcon _iconPressed;

        /**
         * @brief     press button text
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:13
         */
        QString _text;

        /**
         * @brief     press button layout align
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:14
         */
        Qt::AlignmentFlag _align{ Qt::AlignLeft };

        /**
         * @brief     show icon label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:14
         */
        QLabel *_iconLabel{};

        /**
         * @brief     press button normal state color
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:17
         */
        QColor _normalColor{ QColor(248,248,248) };

        /**
         * @brief     press button mouse enter color
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:17
         */
        QColor _enterColor{ QColor(226,226,226) };

        /**
         * @brief     press button mouse clicked color
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:18
         */
        QColor _clickedColor{ QColor(160,160,160) };

        /**
         * @brief     press button border pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:23
         */
        QPen _borderPen{ QPen(QColor(226,226,226),1) };

        /**
         * @brief     press button palette
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:23
         */
        QPalette _palette;

        /**
         * @brief     press button with border
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:24
         */
        bool _border[4]{ false };

        /**
         * @brief     press button border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:25
         */
        int _borderWidth{ 1 };

        /**
         * @brief     press button hover state
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 11:27
         */
        bool _hover{ false };

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:27
         */
        void initUi();

        /**
         * @brief     switch press button state
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:27
         */
        void switchState();
    };
}
