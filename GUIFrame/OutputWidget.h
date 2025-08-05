
/**
 *
 * @file      OutputWidget.h
 * @brief     Output Widget. Show Messages.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 13:43
 *
 */
#pragma once
#include <QPlainTextEdit>
#include "HighLighter.h"
#include "DataCenter/LogData.h"
#include "GUIFrameAPI.h"

namespace GUI
{
    /**
     * @brief     Output Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-4 13:44
     */
    class GUI_FRAME_API OutputWidget : public QWidget
    {
        Q_OBJECT
            Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen)
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget 's flag
         * @return    OutputWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 16:07
         */
        explicit OutputWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 13:46
         */
        virtual ~OutputWidget();

        /**
         * @brief     get border color of output widget
         * @return    QPen. border pen
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 13:47
         */
        QPen borderPen() const { return _borderPen; }

        /**
         * @brief     set border pen of output widget
         * @param     pen[i]. border pen
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 13:48
         */
        void setBorderPen(QPen pen) { _borderPen = pen, update(); }

        /**
         * @brief     paint event. to draw border
         * @param     e[i]. paint event
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 13:48
         */
        virtual void paintEvent(QPaintEvent *e) override;

        /**
         * @brief     add log info
         * @param     log[i]. QString log info
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 16:18
         */
        void addLog(const QString & log);

        /**
         * @brief     add log info
         * @param     log[i]. log info
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 16:19
         */
        void addLog(Data::LogData log);

    protected:
        /**
         * @brief     border pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 13:46
         */
        QPen _borderPen{ QPen(QColor(229,229,229),1) };

        /**
         * @brief     Text Editor
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 16:08
         */
        QPlainTextEdit * _textEdit{};

        /**
         * @brief     highlighter of text editor
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 16:15
         */
        HighLighter * _highLighter{};

    private:
        /**
         * @brief     initialize ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 16:06
         */
        void initUi();
    };
}