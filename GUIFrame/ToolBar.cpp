#include "ToolBar.h"
#include "GUIWidget/IconButton.h"
#include <QPainter>

namespace GUI
{

    ToolBar::ToolBar(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QWidget(parent, f)
    {
        initUi();
    }

    ToolBar::~ToolBar()
    {

    }

    void ToolBar::addAction(const QString & icon, const QString & toolTip, const QString & triggeredName)
    {
        IconButton * btn = new IconButton(QIcon(icon), QIcon(icon), toolTip, this, QSize(24, 24));
        btn->setTriggeredName(triggeredName);
        _buttons.append(btn);
        updateUi();
    }

    void ToolBar::addSeparator()
    {
        IconButton * btn = new IconButton(QIcon(""), QIcon(""), "", this, QSize(32, 32));
        _buttons.append(btn);
        updateUi();
    }

    QList<IconButton *> ToolBar::iconButtons()
    {
        return _buttons;
    }

    void ToolBar::initUi()
    {
        _lay = new QHBoxLayout();
        setLayout(_lay);
        _lay->setSpacing(2);
        _lay->setContentsMargins(5, 1, 1, 1);
    }

    void ToolBar::updateUi()
    {
        while (_lay->count() != 0)
        {
            _lay->takeAt(0);
        }

        for (IconButton * btn : _buttons)
        {
            _lay->addWidget(btn);
        }
        _lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    }

    void ToolBar::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        painter.setPen(QPen(QColor(229, 229, 229), 1));
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

}