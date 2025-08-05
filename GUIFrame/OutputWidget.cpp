#include "OutputWidget.h"
#include <QPainter>
#include <QHBoxLayout>

namespace GUI
{
    OutputWidget::OutputWidget(QWidget* parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QWidget(parent, f)
    {
        initUi();
    }

    OutputWidget::~OutputWidget()
    {

    }

    void OutputWidget::paintEvent(QPaintEvent *e)
    {
        QWidget::paintEvent(e);

        QPainter painter(this);
        painter.setPen(_borderPen);
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void OutputWidget::addLog(const QString & log)
    {
        _textEdit->appendPlainText(log);
    }

    void OutputWidget::addLog(Data::LogData log)
    {
        _textEdit->appendPlainText(log.log2String());
    }

    void OutputWidget::initUi()
    {
        QPalette palette;
        palette.setColor(QPalette::Base, QColor(240, 240, 240));
        setPalette(palette);

        _textEdit = new QPlainTextEdit(this);
        _textEdit->setFrameShape(QFrame::NoFrame);
        _textEdit->setReadOnly(true);

        QFile file(":/frames/TextEdit.qss");
        if (file.open(QIODevice::ReadOnly))
        {
            QString style = file.readAll();
            _textEdit->setStyleSheet(style);
        }

        _highLighter = new HighLighter(_textEdit->document());

        QFont font("Consolas", 12);
        _textEdit->setFont(font);

        QHBoxLayout * lay = new QHBoxLayout();
        setLayout(lay);
        lay->addWidget(_textEdit);
    }

}