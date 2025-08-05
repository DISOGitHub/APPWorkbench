#include "ComboBox.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QApplication>
#include <qnamespace.h>

namespace GUI
{
    ComboBox::ComboBox(QWidget *parent)
        : QWidget(parent)
    {
        initUi();
    }

    ComboBox::ComboBox(QStringList items, QWidget *parent)
        : QWidget(parent)
    {
        initUi();
        addItems(items);
    }

    ComboBox::~ComboBox()
    {
    }

    void ComboBox::addItem(QIcon icon, const QString &text)
    {
        auto action = _menu->addAction(icon, text);
        connect(action, SIGNAL(triggered()), this, SLOT(actionTriggered()));
    }

    void ComboBox::addItems(const QStringList &items)
    {
        if (!_menu) { return; }
        for (auto itemName : items)
        {
            auto action = _menu->addAction(itemName);
            connect(action, SIGNAL(triggered()), this, SLOT(actionTriggered()));
        }
    }

    void ComboBox::addSeparator()
    {
        _menu->addSeparator();
    }

    void ComboBox::registerMenu(QMenu * menu)
    {
        _menu = menu;
        connect(_menu, &QMenu::aboutToHide, this, [this]() {
            _clickedInSide = false;
            update();
        });
    }

    void ComboBox::clear()
    {
        _menu->clear();
    }

    void ComboBox::actionTriggered()
    {
        QAction * action = qobject_cast<QAction*>(sender());
        if (action)
        {
            emit itemClicked(action->text());
        }
    }

    void ComboBox::enterEvent(QEvent *event)
    {
        QWidget::enterEvent(event);
        update();
    }

    void ComboBox::leaveEvent(QEvent *event)
    {
        QWidget::leaveEvent(event);
        update();
    }

    void ComboBox::focusInEvent(QFocusEvent *event)
    {
        QWidget::focusInEvent(event);
        update();
    }

    void ComboBox::focusOutEvent(QFocusEvent *event)
    {
        QWidget::focusOutEvent(event);
        update();
    }

    void ComboBox::mousePressEvent(QMouseEvent *event)
    {
        if (!_menu) { return; }
        _clickedInSide = true;
        update();

        QWidget::mousePressEvent(event);
        QWidget * parent = parentWidget();
        QPoint pos = this->pos();
        while (parent && parent->isWindow())
        {
            pos += parent->pos();
            parent = parent->parentWidget();
        }
        if (parent)
        {
            pos = parent->mapToGlobal(pos);
        }
        pos += QPoint(0, -_menu->sizeHint().height());
        _menu->exec(pos);
    }

    void ComboBox::mouseReleaseEvent(QMouseEvent *event)
    {
        QWidget::mouseReleaseEvent(event);
        update();
    }

    void ComboBox::paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        QPalette palette = this->palette();
        painter.setPen(Qt::NoPen);

        if (hasFocus()) {
            /// focus
            painter.setBrush(palette.color(QPalette::Highlight));
        }
        else if (underMouse()) {
            /// hover
            painter.setBrush(palette.color(QPalette::Midlight));
        }
        else if (QApplication::mouseButtons() & Qt::LeftButton && _clickedInSide) {
            /// pressed
            painter.setBrush(palette.color(QPalette::Dark));
        }
        else {
            /// normal
            painter.setBrush(palette.color(QPalette::Window));
            _clickedInSide = false;
        }
        painter.drawRect(rect());
    }

    void ComboBox::initUi()
    {
        setFixedWidth(60);
        auto lay = new QHBoxLayout();
        lay->setSpacing(0);
        lay->setContentsMargins(0, 0, 0, 0);
        setLayout(lay);

        _content = new QLabel(this);
        QLabel * icon = new QLabel(this);
        icon->setPixmap(QPixmap(":/frames/colpand.png").scaled(QSize(16, 16), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        lay->addWidget(_content);
        lay->addWidget(icon);
        lay->setStretch(0, 1);
        lay->setStretch(1, 0);
        _content->setText("100%");

        setAutoFillBackground(true);
    }
}
