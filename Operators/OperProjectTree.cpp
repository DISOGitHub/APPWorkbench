#include "OperProjectTree.h"
#include <QApplication>
#include <QDir>

namespace EventOper
{
    OperProjectTree::OperProjectTree()
    {
    }

    OperProjectTree::~OperProjectTree()
    {
    }

    void OperProjectTree::updateTree()
    {
        if (!_treeWidget)
            return;

        _treeWidget->clear();

        _appTemplate = new QTreeWidgetItem(QStringList({ tr("App Template") }), Item_Template);
        _project = new QTreeWidgetItem(QStringList({ tr("Projects") }), Item_History);

        _treeWidget->addTopLevelItem(_appTemplate);
        _treeWidget->addTopLevelItem(_project);

        loadProejcts();
        loadTemplates();

        _treeWidget->expandAll();
    }

    void OperProjectTree::buttonDoubleClicked(QTreeWidgetItem * item, int column)
    {

    }

    void OperProjectTree::rightButtonMenu(QTreeWidgetItem * item)
    {

    }

    void OperProjectTree::loadTemplates()
    {
        QString templatePath = QDir::cleanPath(qApp->applicationDirPath() + "/../AppTemplate/");
        QDir dir(templatePath);
        for (QFileInfo info : dir.entryInfoList(QStringList{ "*.json" }, QDir::Files))
        {
            QTreeWidgetItem * item = new QTreeWidgetItem(_appTemplate, Item_Template_Instance);
            item->setText(0, info.baseName());
        }
    }

    void OperProjectTree::loadProejcts()
    {
        QString projectPath = QDir::cleanPath(qApp->applicationDirPath() + "/../Projects/");
        QDir dir(projectPath);
        for (QFileInfo info : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            QTreeWidgetItem * item = new QTreeWidgetItem(_project, Item_History_Instance);
            item->setText(0, info.fileName());
        }
    }

}