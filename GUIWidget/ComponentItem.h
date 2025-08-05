/**
 *
 * @file      ComponentItem.h
 * @brief     Show Component Item Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 9:33
 *
 */
#pragma once
#include "GUIWidgetAPI.h"
#include <QPen>
#include <QWidget>

class QPushButton;
class QLabel;
namespace GUI
{
    class ComponentItem;
    /**
     * @brief     Show Component Item Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 9:33
     */
    class GUI_WIDGET_API ComponentItem : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     svg[i]. svg image
         * @param     text[i]. component item name
         * @param     parent[i]. parent widget
         * @return
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:33
         */
        ComponentItem(const QString &svg, const QString &text, QWidget *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:34
         */
        ~ComponentItem();

        /**
         * @brief     get min width
         * @return    int . min width
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:34
         */
        int getMinWidth() const { return _minWidth; }

    protected:

        /**
         * @brief     paint event
         * @param     event[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:35
         */
        virtual void paintEvent(QPaintEvent *event) override;

        /**
         * @brief     mouse press event. begin drag
         * @param     event[i]. mouse press event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:35
         */
        virtual void mousePressEvent(QMouseEvent* event) override;

    private:
        /**
         * @brief     if component item text too long. short it
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 9:36
         */
        void calculateText();

        /**
         * @brief     component item text
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:36
         */
        QString _text;

        /**
         * @brief     component item show text
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:37
         */
        QString _showText;

        /**
         * @brief     component item svg image file path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:37
         */
        QString _svg;

        /**
         * @brief     widget min width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:38
         */
        int _minWidth{ 80 };

        /**
         * @brief     font height
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:38
         */
        int _fontHeight;

        /**
         * @brief     font width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:38
         */
        int _fontWidth;

        /**
         * @brief     text border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:39
         */
        int _textBorderWidth{ 5 };

        /**
         * @brief     top icon border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:39
         */
        int _topIconBorderWidth{ 8 };

        /**
         * @brief     pixmap border width
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:39
         */
        int _pixmapBorderWidth{ 2 };

        /**
         * @brief     icon border pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:40
         */
        QPen _iconBorderPen{ QPen(QColor(56,56,156),2) };
    };
}