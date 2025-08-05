#include "DescriptionItem.h"
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include <QSvgRenderer>

namespace GUI
{

    DescriptionItem::DescriptionItem(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QWidget(parent, f)
    {
        initUi();

    }

    DescriptionItem::~DescriptionItem()
    {

    }

    void DescriptionItem::setSvg(const QString & svg)
    {
        _svg = svg;
    }

    void DescriptionItem::setDescription(const QString & name, const QString & type, const QString & author, const QString & company, const QString & majors)
    {
        _name = name;
        _type = type;
        _author = author;
        _company = company;
        _majors = majors;
        updateUi();
    }

    void DescriptionItem::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);

        QSvgRenderer render;
        render.load(_svg);
        render.render(&painter, QRect(QPoint(20, 20), QPoint(60, 60)));
        painter.setPen(_iconBorderPen);
        painter.drawRoundRect(QRect(QPoint(10, 10), QPoint(70, 70)));
        painter.setPen(_framePen);
        painter.drawLine(QPoint(2, height() - 1), QPoint(width() - 2, height() - 1));
    }

    void DescriptionItem::mousePressEvent(QMouseEvent* event)
    {

    }

    void DescriptionItem::updateUi()
    {
        /// update
        _nameLabel->setText("Name:" + _name);
        _typeLabel->setText("Type:" + _type);
        _authorLabel->setText("Author:" + _author);
        _companyLabel->setText("Company:" + _company);
        _disciplinesLabel->setText("Major:" + _majors);
    }

    void DescriptionItem::initUi()
    {
        setFixedHeight(80);

        /// layout 
        QHBoxLayout * lay = new QHBoxLayout();
        lay->setContentsMargins(0, 0, 0, 0);
        setLayout(lay);

        QWidget * icon = new QWidget(this);
        icon->setFixedSize(80, 80);

        QVBoxLayout * descLay = new QVBoxLayout();
        descLay->setSpacing(0);
        _nameLabel = new QLabel();
        _typeLabel = new QLabel();
        _authorLabel = new QLabel();
        _companyLabel = new QLabel();
        _disciplinesLabel = new QLabel();
        QHBoxLayout * line1 = new QHBoxLayout();
        line1->setContentsMargins(0, 0, 0, 0);
        line1->addWidget(_nameLabel);
        line1->addWidget(_typeLabel);

        descLay->addLayout(line1);
        descLay->addWidget(_authorLabel);
        //descLay->addWidget(_companyLabel);
        descLay->addWidget(_disciplinesLabel);

        lay->addWidget(icon);
        lay->addLayout(descLay);
    }
}