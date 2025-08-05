/**
 *
 * @file      DescriptionWidget.h
 * @brief     Component Description Widget . Load Web Page
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 18:32
 *
 */
#pragma once
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>

namespace GUI
{
    class IconButton;
    /**
     * @brief     Component Description Widget . Load Web Page
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 18:33
     */
    class DescriptionWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i] . parent widget
         * @param     f[i] . window flag
         * @return    DescriptionWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 18:36
         */
        explicit DescriptionWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 18:37
         */
        ~DescriptionWidget();

    };
}
