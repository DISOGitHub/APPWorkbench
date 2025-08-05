#include "SettingNavi.h"
#include <QPainter>

namespace GUI
{
    SettingNavi::SettingNavi(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUi();
    }

    SettingNavi::~SettingNavi()
    {
    }

    void SettingNavi::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setPen(QPen(QColor(229, 229, 229), 1));
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void SettingNavi::initUi()
    {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(248, 248, 248));
        setPalette(palette);
        setAutoFillBackground(true);
    }

}