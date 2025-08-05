#include "MultiEventOperator.h"
#include "QApplication"
#include "GUIFrame/MainWindow.h"

namespace EventOper
{

    MultiEventOperator::MultiEventOperator()
    {

    }

    MultiEventOperator::~MultiEventOperator()
    {

    }

    QString MultiEventOperator::getEventSign() const
    {
        return _eventSign;
    }

    void MultiEventOperator::setEventSign(const QString & sign)
    {
        _eventSign = sign;
    }

    bool MultiEventOperator::triggered()
    {
        if (!prepareArgs()) { return false; }
        QString name = getEventSign();
        if (_signEventHandler.contains(name))
            return _signEventHandler[name]();
        return false;
    }

    bool MultiEventOperator::prepareArgs()
    {
        return true;
    }

}