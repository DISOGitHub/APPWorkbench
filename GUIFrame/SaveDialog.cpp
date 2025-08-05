#include "SaveDialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDir>
#include "DataCenter/LogData.h"

namespace GUI
{

    SaveDialog::SaveDialog(SaveDialogType save /*= Save_App_Template_Dialog*/, QWidget *parent /*= nullptr*/, Qt::WindowFlags f /*= Qt::WindowFlags()*/)
        : Dialog(parent, f)
        , _type(save)
    {
        initUi();
    }

    SaveDialog::~SaveDialog()
    {

    }

    void SaveDialog::accept()
    {
        QString name = _line->text();
        if (_type == Save_App_Template_Dialog)
        {
            QString templatePath = QDir::cleanPath(qApp->applicationDirPath() + "/../AppTemplate");
            for (QFileInfo info : QDir(templatePath).entryInfoList(QStringList{ "*.json" }, QDir::Files))
            {
                if (name == info.baseName())
                {
                    LOGW(tr("Already Exist App Template Named %1.").arg(name));
                    return;
                }
            }
        }

        QDialog::accept();
    }

    QString SaveDialog::text() const
    {
        return _line->text();
    }

    void SaveDialog::initUi()
    {
        /// item num and layout . multi type same
        if (_type == Save_App_Template_Dialog)
        {
            QHBoxLayout * lay = new QHBoxLayout(this);
            QGroupBox * group = new QGroupBox();
            lay->addWidget(group);

            QVBoxLayout * groupLay = new QVBoxLayout(group);
            QHBoxLayout * lay1 = new QHBoxLayout();
            QLabel * name = new QLabel(group);
            _line = new QLineEdit(group);
            lay1->addWidget(name);
            lay1->addWidget(_line);
            lay1->setStretch(0, 1);
            lay1->setStretch(1, 4);

            QHBoxLayout * lay2 = new QHBoxLayout();
            QPushButton * btnOk = new QPushButton(tr("Ok"), group);
            QPushButton * btnCancel = new QPushButton(tr("Cancel"), group);
            connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));
            connect(btnCancel, SIGNAL(clicked()), this, SLOT(reject()));

            lay2->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
            lay2->addWidget(btnOk);
            lay2->addWidget(btnCancel);

            groupLay->addLayout(lay1);
            groupLay->addLayout(lay2);

            if (Save_App_Template_Dialog == _type)
            {
                setWindowTitle(tr("Save App Template"));
                group->setTitle(tr("App Template"));
                name->setText(tr("App Template Name:"));
            }
        }
    }

}