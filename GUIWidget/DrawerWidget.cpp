#include "DrawerWidget.h"
#include "ComponentItem.h"
#include <QScrollArea>
#include <QFile>
#include <cmath>

namespace GUI
{
    DrawerWidget::DrawerWidget(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUi();
    }

    DrawerWidget::~DrawerWidget()
    {

    }

    void DrawerWidget::addComponentItem(ComponentItem *item)
    {
        _cptItems.append(item);
    }

    void DrawerWidget::addDescriptionItem(DescriptionItem * item)
    {
        int index = _descItems.size();
        _gridLay->addWidget(item, index, 0);
        _descItems.append(item);
    }

    void DrawerWidget::resizeEvent(QResizeEvent *event)
    {
        Q_UNUSED(event);
        updateUi();
    }

    void DrawerWidget::initUi()
    {
        QHBoxLayout * lay = new QHBoxLayout();
        lay->setContentsMargins(0, 0, 0, 0);
        setLayout(lay);

        auto scrollArea = new QScrollArea(this);
        QFile file(":/frames/ScrollArea.qss");
        if (file.open(QIODevice::ReadOnly))
        {
            QString style = file.readAll();
            scrollArea->setStyleSheet(style);
        }

        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameShape(QFrame::NoFrame);
        lay->addWidget(scrollArea);

        auto scrollAreaContents = new QWidget();
        scrollArea->setWidget(scrollAreaContents);

        auto contentLay = new QVBoxLayout(scrollAreaContents);
        _inner = new QWidget(scrollAreaContents);
        contentLay->addWidget(_inner);

        auto innerLay = new QVBoxLayout();
        _gridLay = new QGridLayout();
        _inner->setLayout(innerLay);
        innerLay->addLayout(_gridLay);
        innerLay->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    }

    void DrawerWidget::updateComponentUi()
    {
        /// clear last time lay items
        while (_gridLay->count())
        {
            QLayoutItem * item = _gridLay->takeAt(0);
            QWidget * widget = item->widget();
            if (!widget) { continue; }
            ComponentItem * cpt = qobject_cast<ComponentItem *>(widget);
            if (!cpt && widget)
            {
                delete widget;
                widget = nullptr;
            }
        }

        /// relay items
        _minWidth = _cptItems.first()->getMinWidth();

        int width = _inner->width();
        width = this->width();
        int columnNum = (width - 2 * _border) / (_minWidth + _spacing);
        if (columnNum <= 0) { return; }

        /// sync drawer item column num
        int rowNum = ceil(_cptItems.size() / (columnNum * 1.0));
        for (int iRow = 0; iRow < rowNum; ++iRow)
        {
            for (int iCol = 0; iCol < columnNum; ++iCol)
            {
                int index = iRow * columnNum + iCol;
                if (index >= _cptItems.size())
                {
                    /// add blank widget
                    QWidget * widget = new QWidget();
                    widget->setFixedSize(QSize(80, 80));
                    _gridLay->addWidget(widget, iRow, iCol);
                }
                else
                {
                    _gridLay->addWidget(_cptItems[index], iRow, iCol);
                }
            }
        }
    }

    void DrawerWidget::updateDescriptionUi()
    {

    }

    void DrawerWidget::updateUi()
    {
        if (!_cptItems.isEmpty())
        {
            updateComponentUi();
        }
        else if (_descItems.isEmpty())
        {
            updateDescriptionUi();
        }

    }

}
