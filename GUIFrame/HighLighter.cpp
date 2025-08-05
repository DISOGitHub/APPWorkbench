#include "HighLighter.h"

namespace GUI
{

    HighLighter::HighLighter(QObject *parent /*= nullptr*/)
        : QSyntaxHighlighter(parent)
    {
        init();
    }

    HighLighter::HighLighter(QTextDocument *parent)
        : QSyntaxHighlighter(parent)
    {
        init();
    }

    void HighLighter::highlightBlock(const QString &text)
    {
        QRegularExpression time("\\d{4}-\\d{2}-\\d{2} \\d{2}:\\d{2}:\\d{2}.\\d{3}");
        auto timeMatches = time.globalMatch(text);
        while (timeMatches.hasNext())
        {
            QRegularExpressionMatch match = timeMatches.next();
            setFormat(match.capturedStart(), match.capturedLength(), _timeFormat);
        }

        QRegularExpression bracket("\\[(.*?)\\]");
        auto bracketMatches = bracket.globalMatch(text);
        while (bracketMatches.hasNext()) {
            auto match = bracketMatches.next();
            if (match.capturedTexts().contains("[info]"))
                setFormat(match.capturedStart(), match.capturedLength(), _normalFormat);
            else if (match.capturedTexts().contains("[warning]"))
                setFormat(match.capturedStart(), match.capturedLength(), _warningFormat);
            else if (match.capturedTexts().contains("[error]"))
                setFormat(match.capturedStart(), match.capturedLength(), _errorFormat);
        }
    }

    void HighLighter::init()
    {
        _timeFormat.setForeground(QColor(55, 126, 33));
        _normalFormat.setForeground(QColor(60, 132, 92));
        _warningFormat.setForeground(QColor(150, 38, 30));
        _errorFormat.setForeground(Qt::red);
    }

}