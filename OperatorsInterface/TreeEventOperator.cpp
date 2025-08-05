#include "TreeEventOperator.h"

namespace EventOper
{
    TreeEventOperator::TreeEventOperator()
    {
    }

    TreeEventOperator::~TreeEventOperator()
    {
    }

    void TreeEventOperator::setTreeWidget(QTreeWidget *tree)
    {
        _treeWidget = tree;
        if (_treeWidget)
        {
            _treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(_treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(buttonDoubleClicked(QTreeWidgetItem *, int)));
            connect(_treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightButtonMenu(QPoint)));
        }
    }

    QTreeWidget *TreeEventOperator::getTreeWidget() const
    {
        return _treeWidget;
    }

    void TreeEventOperator::updateTree()
    {

    }

    void TreeEventOperator::buttonDoubleClicked(QTreeWidgetItem * item, int column)
    {
        Q_UNUSED(item);
        Q_UNUSED(column);
    }

    void TreeEventOperator::rightButtonMenu(QPoint pt)
    {
        QTreeWidgetItem *item = _treeWidget->itemAt(pt);
        if (!item) return;
        rightButtonMenu(item);
    }

    void TreeEventOperator::rightButtonMenu(QTreeWidgetItem * item)
    {
        Q_UNUSED(item);
    }

}