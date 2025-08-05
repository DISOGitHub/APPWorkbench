/**
 *
 * @file      FileWidget.h
 * @brief     While Linked Component App Transfer File . This Widget Display It
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 18:37
 *
 */
#pragma once
#include <QPlainTextEdit>
#include <QTableWidget>

namespace GUI
{
    /**
     * @brief     Component App 's  Transfer File Widget
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 18:38
     */
    class FileWidget : public QWidget
    {
        Q_OBJECT
            Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen)
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. window flag
         * @return    ProblemWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 20:18
         */
        explicit FileWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 20:18
         */
        virtual ~FileWidget();

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


    protected:
        /**
         * @brief     initialize ui
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 20:14
         */
        void initUi();


    protected:
        /**
         * @brief     border pen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 20:14
         */
        QPen _borderPen{ QPen(QColor(229,229,229),1) };

        /**
         * @brief     table widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-5 20:21
         */
        QTableWidget * _table{};
    };
}