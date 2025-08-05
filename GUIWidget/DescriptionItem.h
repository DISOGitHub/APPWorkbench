/**
 *
 * @file      DescriptionItem.h
 * @brief     Description Item Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-6 13:01
 *
 */
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPen>
#include "GUIWidgetAPI.h"

namespace GUI
{
    /**
     * @brief     Description Item Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-25 9:41
     */
    class GUI_WIDGET_API DescriptionItem : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. window flag
         * @return    DescriptionItem object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:08
         */
        explicit DescriptionItem(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:08
         */
        ~DescriptionItem();

        /**
         * @brief     set svg file
         * @param     svg[i]. svg file
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:47
         */
        void setSvg(const QString & svg);

        /**
         * @brief     set description items
         * @param     name[i] . description name
         * @param     type[i] . description type
         * @param     author[i] . description author
         * @param     company[i] . description company
         * @param     majors[i] . description majors
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:47
         */
        void setDescription(const QString & name, const QString & type, const QString & author, const QString & company, const QString & majors);

    protected:
        /**
         * @brief
         * @param     event[]
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:08
         */
        virtual void paintEvent(QPaintEvent *event) override;
        /**
         * @brief
         * @param     event[]
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:08
         */
        virtual void mousePressEvent(QMouseEvent* event) override;

        /**
         * @brief
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:08
         */
        void updateUi();

        /**
         * @brief     component item name
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:42
         */
        QString _name;

        /**
         * @brief     component item type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:42
         */
        QString _type;

        /**
         * @brief     component app author
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:42
         */
        QString _author;

        /**
         * @brief     component app 's company
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 9:43
         */
        QString _company;

        /**
         * @brief     component app 's field
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:00
         */
        QString _majors;

        /**
         * @brief     component app 's svg image
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:01
         */
        QString _svg;

        /**
         * @brief     show name label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:02
         */
        QLabel * _nameLabel{};

        /**
         * @brief     show type label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:02
         */
        QLabel * _typeLabel{};

        /**
         * @brief     show author label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:02
         */
        QLabel * _authorLabel{};

        /**
         * @brief     show company label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:02
         */
        QLabel * _companyLabel{};

        /**
         * @brief     show disciplines label
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:03
         */
        QLabel * _disciplinesLabel{};

        /**
         * @brief     icon border pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:03
         */
        QPen _iconBorderPen{ QPen(QColor(56,56,156),2) };

        /**
         * @brief     frame pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-25 10:04
         */
        QPen _framePen{ QPen(QColor(226,226,226),1) };

    private:
        /**
         * @brief     initialize Ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 13:49
         */
        void initUi();
    };
}