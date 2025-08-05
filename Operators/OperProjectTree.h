/**
 *
 * @file      OperProjectTree.h
 * @brief     Project Tree Operator. Load Open Save Delete Project
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-23 20:11
 *
 */
#pragma once
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/TreeEventOperator.h"
#include "OperatorsGUIAPI.h"

namespace EventOper
{
    enum ProjectTreeItem
    {
        Item_Template = 0,
        Item_Template_Instance,
        Item_History,
        Item_History_Instance,
    };

    /**
     * @brief     project tree operator
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-23 20:38
     */
    class OperProjectTree : public TreeEventOperator
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @return    OperProjectTree object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 20:38
         */
        OperProjectTree();

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 20:38
         */
        ~OperProjectTree();

        /**
         * @brief     update tree
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 20:39
         */
        virtual void updateTree() override;

        /**
         * @brief     tree item button double click
         * @param     item[i] . tree item button double clicked
         * @param     column[i] . tree item column button double clicked
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 12:42
         */
        virtual void buttonDoubleClicked(QTreeWidgetItem * item, int column) override;

        /**
         * @brief     right button menu
         * @param     item[i] . tree widget item menu
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 12:42
         */
        virtual void rightButtonMenu(QTreeWidgetItem * item) override;

    private:
        /**
         * @brief     load simulation app templates
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 20:41
         */
        void loadTemplates();

        /**
         * @brief     load projects
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-23 20:41
         */
        void loadProejcts();

    private:
        /**
         * @brief     app template tree item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-23 20:39
         */
        QTreeWidgetItem * _appTemplate{};

        /**
         * @brief     project tree item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-23 20:39
         */
        QTreeWidgetItem * _project{};
    };
    Register2FITKOperatorRepo(ProjectTreeEvent, OperProjectTree);
}