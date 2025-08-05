/**
 *
 * @file      Dialog.h
 * @brief     Dialog Base . Auto Use MainWindow ' Icon
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 14:49
 *
 */
#include <QDialog>

namespace GUI
{
    /**
     * @brief     Dialog Base
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 14:51
     */
    class Dialog : public QDialog
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i] . parent widget
         * @param     f[i] . dialog flags
         * @return    Dialog object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 14:51
         */
        explicit Dialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 14:52
         */
        ~Dialog();
    };
}