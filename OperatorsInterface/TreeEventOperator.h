/**
 *
 * @file      TreeEventOperator.h
 * @brief     Tree Widget Event Operator Interface
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 10:59
 *
 */

#pragma once

#include "FITK_Kernel/FITKCore/FITKAbstractOperator.h"
#include "OperatorsInterfaceAPI.h"

#include <QHash>
#include <QString>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QMenu>

namespace EventOper
{
    /**
     * @brief     Tree Widget Event Triggered Interface Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 11:00
     */
    class OPERATORS_INTERFACE_API TreeEventOperator : public Core::FITKAbstractOperator
    {
        Q_OBJECT

    public:
        /**
         * @brief     constructor
         * @return    TreeEventOperator object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:00
         */
        explicit TreeEventOperator();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:01
         */
        virtual ~TreeEventOperator() = 0;

        /**
         * @brief     set tree widget
         * @param     tree[i].tree widget
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:01
         */
        void setTreeWidget(QTreeWidget * tree);

        /**
         * @brief     get tree widget
         * @return    QTreeWidget * .tree widget
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:01
         */
        QTreeWidget * getTreeWidget() const;

        /**
         * @brief     update tree
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:01
         */
        virtual void updateTree();

    public slots:
        /**
         * @brief     tree item mouse double clicked. (left / right)
         * @param     item[i]. tree widget item
         * @param     column[i]. clicked tree widget item column
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:30
         */
        virtual void buttonDoubleClicked(QTreeWidgetItem * item, int column);

        /**
         * @brief     tree right button menu
         * @param     item[i]. tree widget item
         * @param     pt[i]. cursor position
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 11:02
         */
        void rightButtonMenu(QPoint pt);

        /**
         * @brief     right button menu
         * @param     item[i] . tree widget item menu
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 12:36
         */
        virtual void rightButtonMenu(QTreeWidgetItem * item);

    protected:
        /**
         * @brief     tree widget
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 11:03
         */
        QTreeWidget * _treeWidget{};
    };

}