#pragma once
#include <QDialog>

namespace Ui
{
    class NotifyDialog;
}

namespace UpdateOnline
{
    class NotifyDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit NotifyDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
        ~NotifyDialog();

        /**
         * @brief:
         * @param:    const QString & desc
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-29 11:22
         */
        void setDescription(const QString & desc);

    private:

        /**
         * @brief     user defined notify dialog user interface object
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 11:22
         */
        Ui::NotifyDialog * _ui{};

        /**
         * @brief     the description of updates from net
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-29 11:20
         */
        QString _description{};
    };
}