#include "NotityDialog.h"

namespace UpdateOnline
{

    NotifyDialog::NotifyDialog(QWidget *parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : QDialog(parent, f)
    {

    }

    NotifyDialog::~NotifyDialog()
    {

    }

    void NotifyDialog::setDescription(const QString & desc)
    {
        _description = desc;
    }

}
