/**
 *
 * @file      SaveDialog.h
 * @brief     Save Item Dialog.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 13:26
 *
 */

#pragma once
#include <QLineEdit>
#include "GUIFrameAPI.h"
#include "Dialog.h"

namespace GUI
{
    enum SaveDialogType
    {
        /**
         * @brief     Save Application Template Dialog
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 13:59
         */
        Save_App_Template_Dialog,
    };

    /**
     * @brief     Save Item Dialog. option as SaveDialogType
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 13:30
     */
    class GUI_FRAME_API SaveDialog : public Dialog
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     save[i] . save dialog type
         * @param     parent[i] . parent widget
         * @param     f[i] . widget flag
         * @return    SaveDialog object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 13:31
         */
        explicit SaveDialog(SaveDialogType save = Save_App_Template_Dialog, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 13:32
         */
        ~SaveDialog();

        /**
         * @brief     is accept
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 14:01
         */
        virtual void accept() override;

        /**
         * @brief     recommend size
         * @return    QSize . recommend size
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 14:06
         */
        virtual QSize sizeHint() const override { return QSize(600, 180); }

        /**
         * @brief     return line edit item text
         * @return    QString line edit item text
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 14:33
         */
        QString text() const;

    protected:

        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 13:33
         */
        void initUi();

        /**
         * @brief     save dialog type
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 13:33
         */
        SaveDialogType _type{ Save_App_Template_Dialog };

        /**
         * @brief     line item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 14:26
         */
        QLineEdit * _line{};
    };
}