/**
 *
 * @file      TerminalWidget.h
 * @brief     Terminal Command Widget. Reserved For Python And Other Commands
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 19:21
 *
 */
#pragma once
#include <QPlainTextEdit>

namespace GUI
{
    /**
     * @brief     Terminal Command Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 19:22
     */
    class TerminalWidget : public QTextEdit
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @return    TerminalWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:22
         */
        explicit TerminalWidget(QWidget *parent = nullptr);

        /**
         * @brief     constructor
         * @param     text[i]. terminal widget command text
         * @param     parent[i]. parent widget
         * @return    TerminalWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:23
         */
        explicit TerminalWidget(const QString &text, QWidget *parent = nullptr);

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:23
         */
        virtual ~TerminalWidget();
    };
}