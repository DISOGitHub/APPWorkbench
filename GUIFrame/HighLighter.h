/**
 *
 * @file      HighLighter.h
 * @brief     Text Highlighter For Output Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-4 15:21
 *
 */
#pragma once
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

namespace GUI
{
    /**
     * @brief     HighLighter Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-4 15:23
     */
    class HighLighter : public QSyntaxHighlighter
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent object pointer
         * @return    HighLighter object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:25
         */
        explicit HighLighter(QObject *parent = nullptr);

        /**
         * @brief     constructor
         * @param     parent[i]. parent text document object pointer
         * @return    HighLighter object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:25
         */
        explicit HighLighter(QTextDocument *parent);

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:26
         */
        ~HighLighter() = default;

    protected:
        /**
         * @brief     highlight text block
         * @param     text[i]. text
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:26
         */
        void highlightBlock(const QString &text) override;

    private:
        /**
         * @brief     initialize
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-4 15:31
         */
        void init();

    private:
        /**
         * @brief     time text format
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:27
         */
        QTextCharFormat _timeFormat;

        /**
         * @brief     normal text format
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:33
         */
        QTextCharFormat _normalFormat;

        /**
         * @brief     warning text format
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:27
         */
        QTextCharFormat _warningFormat;

        /**
         * @brief     error text format
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 15:28
         */
        QTextCharFormat _errorFormat;
    };
}

