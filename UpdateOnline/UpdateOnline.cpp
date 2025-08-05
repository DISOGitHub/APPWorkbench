#include "UpdateOnline.h"
#include "OperatorsInterface/UpdateOnlineEventOperator.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "NotityDialog.h"

namespace UpdateOnline
{
    QString UpdateTool::_defaultOperName = "SimpleUpdateOnline";

    void UpdateTool::setUpdateOperator(const QString & name)
    {
        _defaultOperName = name;
    }

    void UpdateTool::updateOperation()
    {
        /// prepares
        EventOper::UpdateOnlineEventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::UpdateOnlineEventOperator>(_defaultOperName);
        if (!oper)
            return;

        /// step 1. check updates
        QString desc;
        bool check = oper->checkForUpdates(desc);
        if (!check) { return; }

        /// step 2. user decide whether to update
        NotifyDialog dlg;
        if (QDialog::Rejected == dlg.exec()) { return; }

        /// step 3. download updates
        if (!oper->downLoadUpdates()) { return; }

        /// step 4. operate downloads
        if (!oper->operateDownloads()) { return; }

        /// step 5. update components
        oper->backupComponents();
        if (!oper->updateComponents()) {
            oper->restoreComponents();
        }
        return;
    }

}