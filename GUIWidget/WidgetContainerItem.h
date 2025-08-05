/**
 *
 * @file      WidgetContainerItem.h
 * @brief     Widget Container Item . Inherit From QLabel
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-25 11:39
 *
 */
#pragma once
#include <QLabel>

namespace GUI
{
    /**
     * @brief     Widget Container Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 11:39
     */
    class WidgetContainerItem : public QLabel
    {
        Q_OBJECT
    public:
        /**
         * @brief     default constructor
         * @return    WidgetContainerItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:38
         */
        WidgetContainerItem() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 11:38
         */
        ~WidgetContainerItem() = default;

        /**
         * @brief     get item name
         * @return    QString . item name
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 12:59
         */
        QString name() const { return _name; }

        /**
         * @brief     set item name
         * @param     name[i]. item name
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:00
         */
        void setName(const QString & name) { _name = name; }

        /**
         * @brief     get function widget
         * @return    QWidget * . function widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:00
         */
        QWidget * functionWidget() const { return _func; }

        /**
         * @brief     set function widget
         * @param     func[i]. function widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:00
         */
        void setFunctionWidget(QWidget * func) { _func = func; }

        /**
         * @brief     get content widget
         * @return    QWidget * . content widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:01
         */
        QWidget * contentWidget() const { return _content; }

        /**
         * @brief     set content widget
         * @param     content[i]. content widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:01
         */
        void setContentWidget(QWidget * content) { _content = content; }

    protected:

        /**
         * @brief     item name. Duplicate names are not allowed
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 10:48
         */
        QString _name;

        /**
         * @brief     shortcuts functions
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 10:50
         */
        QWidget * _func{};

        /**
         * @brief     Core display area
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-4 10:53
         */
        QWidget * _content{};
    };
}