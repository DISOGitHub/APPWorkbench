#include "ActionEventHandler.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/MultiEventOperator.h"
#include "GUIWidget/IconButton.h"

namespace GUI
{

    ActionEventsHandler * ActionEventsHandler::_instance = nullptr;
    QMutex ActionEventsHandler::m_mutex;

    void ActionEventsHandler::handleIconButtons(QList<IconButton *> buttons)
    {
        for (auto button : buttons)
        {
            if (!button->triggeredName().isEmpty())
            {
                connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));
            }
        }
    }

    void ActionEventsHandler::handleIconButton(IconButton * action)
    {
        connect(action, SIGNAL(triggered()), this, SLOT(buttonClicked()));
    }

    void ActionEventsHandler::buttonClicked()
    {
        IconButton * obj = qobject_cast<IconButton *>(sender());
        if (!obj || obj->triggeredName().isEmpty()) { return; }
        EventOper::MultiEventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::MultiEventOperator>(obj->triggeredName());
        if (!oper) { return; }
        oper->setEventSign(obj->triggeredName());
        oper->triggered();
    }

}