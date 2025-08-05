#include "StyleMenu.h"
#include <QFile>

namespace GUI
{

    StyleMenu::StyleMenu(QWidget *parent /*= nullptr*/)
        : QMenu(parent)
    {
        initUi();
    }

    StyleMenu::StyleMenu(const QString &title, QWidget *parent /*= nullptr*/)
        : QMenu(title, parent)
    {

    }

    StyleMenu::~StyleMenu()
    {

    }

    void StyleMenu::initUi()
    {
        QFile file(":/frames/Menu.qss");
        if (file.open(QIODevice::ReadOnly))
        {
            QString style = file.readAll();
            setStyleSheet(style);
            file.close();
        }
    }

}