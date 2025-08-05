#include "PressButton.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>

namespace GUI
{
    PressButton::PressButton(const QIcon &iconNormal, const QIcon &iconPressed, const QString &text, Qt::AlignmentFlag align, QWidget *parent)
        : QWidget(parent), _iconNormal(iconNormal), _iconPressed(iconPressed), _text(text), _align(align)
    {
        initUi();
    }

    PressButton::~PressButton()
    {
    }

    void PressButton::setIconSize(QSize size)
    {
        _iconSize = size;
        _iconLabel->setFixedSize(_iconSize);
        if (_pressed)
            _iconLabel->setPixmap(_iconPressed.pixmap(_iconSize));
        else
            _iconLabel->setPixmap(_iconNormal.pixmap(_iconSize));
    }

    void PressButton::setBorder(int index, bool with)
    {
        if (index > 3 || index < 0)
        {
            return;
        }
        _border[index] = with;
        update();
    }

    void PressButton::enterEvent(QEvent *event)
    {
        QWidget::enterEvent(event);
        _hover = true;
        _palette.setColor(QPalette::Window, _enterColor);
        setPalette(_palette);
        update();
    }

    void PressButton::leaveEvent(QEvent *event)
    {
        QWidget::leaveEvent(event);
        _hover = false;
        _palette.setColor(QPalette::Window, _normalColor);
        setPalette(_palette);
        update();
    }

    void PressButton::mousePressEvent(QMouseEvent *event)
    {
        QWidget::mousePressEvent(event);
        switchState();
        _palette.setColor(QPalette::Window, _clickedColor);
        setPalette(_palette);
        update();
        emit clicked(_pressed);
    }

    void PressButton::mouseReleaseEvent(QMouseEvent *event)
    {
        QWidget::mouseReleaseEvent(event);
        if (_hover)
            _palette.setColor(QPalette::Window, _enterColor);
        else
            _palette.setColor(QPalette::Window, _normalColor);
        setPalette(_palette);
        update();
    }

    void PressButton::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setPen(_borderPen);
        if (_border[0])
        {
            painter.drawLine(rect().topLeft(), rect().bottomLeft());
        }
        if (_border[1])
        {
            painter.drawLine(rect().topLeft(), rect().bottomRight());
        }
        if (_border[2])
        {
            painter.drawLine(rect().topRight(), rect().bottomRight());
        }
        if (_border[3])
        {
            painter.drawLine(rect().bottomLeft(), rect().bottomRight());
        }
    }

    void PressButton::initUi()
    {
        auto lay = new QHBoxLayout();
        setLayout(lay);

        _iconLabel = new QLabel(this);
        _iconLabel->setFixedSize(_iconSize);
        _iconLabel->setPixmap(_iconNormal.pixmap(_iconSize));

        QLabel *textLabel = new QLabel(this);
        textLabel->setText(_text);

        if (_align == Qt::AlignLeft)
        {
            lay->addWidget(_iconLabel);
            lay->addWidget(textLabel);
            lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        }
        else if (_align == Qt::AlignCenter)
        {
            lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
            lay->addWidget(_iconLabel);
            lay->addWidget(textLabel);
            lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        }
        else if (_align == Qt::AlignRight)
        {
            lay->addWidget(_iconLabel);
            lay->addWidget(textLabel);
            lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        }

        _palette = palette();
        _palette.setColor(QPalette::Window, _normalColor);
        setPalette(_palette);
        setAutoFillBackground(true);
    }

    void PressButton::switchState()
    {
        _pressed = !_pressed;
        if (_pressed)
            _iconLabel->setPixmap(_iconPressed.pixmap(_iconSize));
        else
            _iconLabel->setPixmap(_iconNormal.pixmap(_iconSize));
    }
}