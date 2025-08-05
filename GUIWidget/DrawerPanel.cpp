#include "DrawerPanel.h"
#include "PressButton.h"
#include "ComponentItem.h"
#include "DrawerWidget.h"

#include <QEvent>
#include <QVBoxLayout>
#include <QStylePainter>
#include <QStyleOption>
#include <QScrollArea>
#include <QGridLayout>
#include <QHBoxLayout>
#include <cmath>


namespace GUI
{

    DrawerPanel::DrawerPanel(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUI();
    }

    DrawerPanel::~DrawerPanel()
    {
    }

    DrawerWidget * DrawerPanel::addDrawerItem(const QString & itemName)
    {
        _names.append(itemName);
        auto title = new PressButton(QIcon(":/frames/colpand.png"), QIcon(":/frames/expand.png"), itemName, Qt::AlignLeft, this);
        title->setBorder(3, true);
        _titles.append(title);
        connect(title, SIGNAL(clicked(bool)), this, SLOT(updateUi()));
        auto panel = new DrawerWidget(this);
        panel->setVisible(false);
        _panels.append(panel);
        return panel;
    }

    void DrawerPanel::initUI()
    {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(248, 248, 248));
        setPalette(palette);
        setAutoFillBackground(true);
        _lay = new QVBoxLayout();
        _lay->setSpacing(0);
        _lay->setContentsMargins(4, 0, 4, 0);
        setLayout(_lay);

    }

    void DrawerPanel::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setPen(QPen(QColor(229, 229, 229), 1));
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void DrawerPanel::updateUi()
    {
        while (_lay->count() != 0)
        {
            _lay->takeAt(0);
        }

        QList<int> factors;
        for (auto title : _titles)
        {
            _lay->addWidget(title);
            factors.append(0);
            auto index = _titles.indexOf(title);
            if (title->isPressed())
            {
                _panels[index]->setVisible(true);
                _lay->addWidget(_panels[index]);
                factors.append(1);
            }
            else
                _panels[index]->setVisible(false);
        }
        if (factors.indexOf(1) == -1)
            _lay->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        else
        {
            for (int iCnt = 0; iCnt < factors.size(); ++iCnt)
            {
                _lay->setStretch(iCnt, factors[iCnt]);
            }
        }

    }
}
