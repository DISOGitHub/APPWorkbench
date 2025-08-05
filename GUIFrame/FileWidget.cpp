#include "FileWidget.h"
#include <QPainter>
#include <QTextEdit>
#include <QHBoxLayout>
#include "QHeaderView"

namespace GUI
{
    FileWidget::FileWidget(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QWidget(parent, f)
    {
        initUi();
    }

    FileWidget::~FileWidget()
    {
    }

    void FileWidget::paintEvent(QPaintEvent *e)
    {
        QWidget::paintEvent(e);

        QPainter painter(this);
        painter.setPen(_borderPen);
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void FileWidget::initUi()
    {
        /// layout
        QHBoxLayout * lay = new QHBoxLayout();
        setLayout(lay);
        _table = new QTableWidget(this);
        lay->addWidget(_table);

        /// set style
        _table->setFrameShape(QFrame::NoFrame);

        _table->setColumnCount(5);
        QStringList headers = { tr("FROM"), tr("FILE TYPE"), tr("FILE"), tr("TO"), tr("TOOL") };
        _table->setHorizontalHeaderLabels(headers);
        _table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        _table->horizontalHeader()->setStretchLastSection(true);
        _table->setAlternatingRowColors(true);

        QFile file(":/frames/Table.qss");
        if (file.open(QIODevice::ReadOnly))
        {
            QString style = file.readAll();
            _table->setStyleSheet(style);
        }


    }

}