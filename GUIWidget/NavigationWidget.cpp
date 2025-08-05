#include "NavigationWidget.h"
#include "IconButton.h"
#include <QVBoxLayout>

namespace GUI
{
    NavigationWidget::NavigationWidget(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUI();
    }

    NavigationWidget::~NavigationWidget()
    {

    }

    void NavigationWidget::addIconButton(IconButton *button, bool top)
    {
        if (top)
            _topLay->addWidget(button);
        else
            _bottomLay->addWidget(button);
        connect(button, SIGNAL(clicked()), this, SLOT(stateChanged()));
        _buttons.append(button);
    }

    void NavigationWidget::setCurrentIndex(int index)
    {
        if (index < 0 || index > _buttons.size())
        {
            return;
        }
        _index = index;
        int num = _buttons.size();

        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            IconButton * btn = _buttons[iCnt];
            if (index == iCnt)
            {
                btn->toSelected();
                btn->setSelected(true);
                _current = btn;
                emit item_clicked(index);
            }
            else
            {
                btn->toNormal();
                btn->setSelected(false);
            }
        }
    }

    int NavigationWidget::currentIndex()
    {
        return _index;
    }

    int NavigationWidget::count()
    {
        return _buttons.size();
    }

    void NavigationWidget::stateChanged()
    {
        IconButton * btn = qobject_cast<IconButton*>(sender());
        if (!btn)
        {
            return;
        }
        setCurrentIndex(_buttons.indexOf(btn));
    }

    void NavigationWidget::initUI()
    {
        auto lay = new QVBoxLayout();
        setLayout(lay);
        lay->setContentsMargins(5, 5, 5, 5);

        _topLay = new QVBoxLayout();
        _topLay->setSpacing(24);
        _topLay->setContentsMargins(5, 5, 5, 5);
        _bottomLay = new QVBoxLayout();
        _bottomLay->setSpacing(24);
        _bottomLay->setContentsMargins(5, 5, 5, 5);

        lay->addLayout(_topLay);
        lay->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
        lay->addLayout(_bottomLay);

        QPalette palette;
        palette.setColor(QPalette::Background, QColor(248, 248, 248));
        setPalette(palette);
        setAutoFillBackground(true);
    }
}