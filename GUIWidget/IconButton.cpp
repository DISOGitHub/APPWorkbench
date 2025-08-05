#include "IconButton.h"

namespace GUI
{
    IconButton::IconButton(const QIcon &icon0, const QIcon &icon1, const QString &tip, QWidget *parent, QSize size)
        : QPushButton(icon0, "", parent)
    {
        _icon0 = icon0;
        _icon1 = icon1;
        _tip = tip;
        _size = size;

        setToolTip(tip);
        setFlat(true);
        setIconSize(_size);
        setFixedSize(_size);
        setStyleSheet("QPushButton:pressed { background-color: rgb(216,216,216);color: white;border: none;} QPushButton:hover { background-color: rgb(230,230,230);color: white;border: none;} ");
        toNormal();
    }

    IconButton::~IconButton()
    {

    }

    void IconButton::toNormal()
    {
        setEnabled(true);
        if (!_icon0.isNull())
        {
            setIcon(_icon0);
        }
        else
        {
            setFixedSize(QSize(1, _size.height()));
            setStyleSheet("QPushButton { background-color: rgb(199,199,199);border: none;} ");
        }
    }

    void IconButton::toSelected()
    {
        setEnabled(true);
        if (!_icon1.isNull())
        {
            setIcon(_icon1);
        }
        else
        {
            setFixedSize(QSize(1, _size.height()));
            setStyleSheet("QPushButton { background-color: rgb(199,199,199);border: none;} ");
        }
    }

    void IconButton::toDisabled()
    {
        setEnabled(false);
    }

    void IconButton::enterEvent(QEvent *event)
    {
        toSelected();
        QPushButton::enterEvent(event);
    }

    void IconButton::leaveEvent(QEvent *event)
    {
        if (!_selected)
            toNormal();
        QPushButton::leaveEvent(event);
    }

}