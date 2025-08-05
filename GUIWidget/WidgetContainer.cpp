#include "WidgetContainer.h"
#include "IconButton.h"
#include <QPainter>
#include "qevent.h"

namespace GUI
{
    WidgetContainer::WidgetContainer(QWidget* parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUI();
    }

    WidgetContainer::~WidgetContainer()
    {

    }

    int WidgetContainer::addWidget(const QString & name, QWidget * func, QWidget * content)
    {
        if (_currentPage.isEmpty())
            _currentPage = name;

        auto item = new WidgetContainerItem();
        item->setName(name);
        item->setFunctionWidget(func);
        item->setContentWidget(content);
        return addWidget(item);
    }

    int WidgetContainer::addWidget(WidgetContainerItem *item)
    {
        _items.insert(item->name(), item);
        _stackContents->addWidget(item->contentWidget());
        if (!item->functionWidget())
            item->setFunctionWidget(new QWidget());
        _stackShortcuts->addWidget(item->functionWidget());
        item->setText(item->name());
        _leftLay->addWidget(item);
        return _items.size() - 1;
    }

    void WidgetContainer::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);

        QPainter painter(this);
        WidgetContainerItem * _currentItem = _items.value(_currentPage);
        if (!_currentItem) { return; }

        int bottomMarign = _currentItem->parentWidget()->layout()->contentsMargins().bottom();
        int penWidth = 1;
        if (bottomMarign < penWidth) { return; }
        int offset = (bottomMarign - penWidth) / 2;
        int y = _currentItem->pos().y() + _currentItem->height();
        painter.setPen(QPen(QColor(56, 56, 225), penWidth));
        painter.drawLine(QPoint(_currentItem->pos().x(), y), QPoint(_currentItem->x() + _currentItem->width(), y));
    }

    void WidgetContainer::mousePressEvent(QMouseEvent *event)
    {
        QWidget::mousePressEvent(event);
        QPoint pressPos = event->pos();

        for (auto item : _items)
        {
            QRect itemRect = QRect(item->pos(), item->size());
            if (itemRect.contains(pressPos))
            {
                _currentPage = item->name();
                _stackContents->setCurrentWidget(item->contentWidget());
                _stackShortcuts->setCurrentWidget(item->functionWidget());
                update();
                break;
            }
        }
    }

    void WidgetContainer::initUI()
    {
        /// initialize layout
        _title = new QWidget(this);
        _stackContents = new QStackedWidget(this);

        QVBoxLayout * lay = new QVBoxLayout();
        setLayout(lay);

        lay->addWidget(_title);
        lay->addWidget(_stackContents);
        lay->setSpacing(0);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->setStretch(0, 0);
        lay->setStretch(1, 1);

        QHBoxLayout * titleLay = new QHBoxLayout();
        _title->setLayout(titleLay);
        _leftLay = new QHBoxLayout();
        _stackShortcuts = new QStackedWidget(_title);
        titleLay->addLayout(_leftLay);
        titleLay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        titleLay->addWidget(_stackShortcuts);

        /// shared functions
        _expand = new IconButton(QIcon(":/frames/up.png"), QIcon(":/frames/up.png"), tr("Expand Window"), this, QSize(12, 12));
        _close = new IconButton(QIcon(":/frames/close.png"), QIcon(":/frames/close.png"), tr("Close Window"), this, QSize(12, 12));

        titleLay->addWidget(_expand);
        titleLay->addWidget(_close);
    }
}
