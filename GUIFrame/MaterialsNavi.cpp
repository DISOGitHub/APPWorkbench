#include "MaterialsNavi.h"
#include <QPainter>

namespace GUI
{
    MaterialsNavi::MaterialsNavi(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUi();
    }

    MaterialsNavi::~MaterialsNavi()
    {
    }

    void MaterialsNavi::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setPen(QPen(QColor(229, 229, 229), 1));
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void MaterialsNavi::initUi()
    {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(248, 248, 248));
        setPalette(palette);
        setAutoFillBackground(true);
    }

}