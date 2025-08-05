#include "TerminalWidget.h"

namespace GUI
{
    TerminalWidget::TerminalWidget(QWidget *parent)
        : QTextEdit(parent)
    {
    }

    TerminalWidget::TerminalWidget(const QString &text, QWidget *parent)
        : QTextEdit(text, parent)
    {
    }

    TerminalWidget::~TerminalWidget()
    {
    }
}