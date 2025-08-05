/**
 *
 * @file      StatusBarWidget.h
 * @brief     A Look Like Status Bar . Inherit From Widget
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-24 19:24
 *
 */
#pragma once
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QComboBox>

namespace GUI
{
    class IconButton;
    class ComboBox;
    /**
     * @brief     A Look Like Status Bar Class
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-24 19:25
     */
    class StatusBarWidget : public QWidget
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     parent[i]. parent widget
         * @param     f[i]. widget flags
         * @return    StatusBarWidget object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:25
         */
        explicit StatusBarWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

        /**
         * @brief     destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:27
         */
        ~StatusBarWidget();

        /**
         * @brief     set number of warning message
         * @param     msgNum[i] . warning message number
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:27
         */
        void setWarningMsgNum(int msgNum);

        /**
         * @brief     set number of error message
         * @param     msgNum[i]. error message number
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:27
         */
        void setErrorMsgNum(int msgNum);

        /**
         * @brief     set last error message
         * @param     msg[i]. last error message
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:28
         */
        void setLastErrorMsg(const QString &msg);

        /**
         * @brief     show process progress
         * @param     per[i]. current percentage
         * @param     msg[i]. show message
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:29
         */
        void showProgress(int per, const QString &msg);

        /**
         * @brief     hide progress
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:30
         */
        void hideProgress();

    private:
        /**
         * @brief     initialize user interface
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-24 19:30
         */
        void initUI();

        /**
         * @brief     number of error message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:31
         */
        int _errorMsgNum{ 0 };

        /**
         * @brief     number of warning message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:45
         */
        int _warningMsgNum{ 0 };

        /**
         * @brief     last error message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:45
         */
        QString _lastErrorMsg;

        /**
         * @brief     process run percent
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:46
         */
        double _percent{ .0 };

        /**
         * @brief     error label. show error number
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:46
         */
        QLabel *_errorLabel{};

        /**
         * @brief     warning label . show warning number
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:46
         */
        QLabel *_warningLabel{};

        /**
         * @brief     center widget for show process status
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:46
         */
        QWidget *_centerWidget{};

        /**
         * @brief     show process progress message
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:47
         */
        QLabel *_progressMsg{};

        /**
         * @brief     show process progress percent
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:47
         */
        QProgressBar *_progressBar{};

        /**
         * @brief     canvas view ratio
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:48
         */
        ComboBox *_dropScale{};

        /**
         * @brief     reduce canvas view ratio
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:48
         */
        IconButton *_decScale{};

        /**
         * @brief     canvas view ratio slider
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:49
         */
        QSlider *_slider{};

        /**
         * @brief     increase canvas view ratio
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:49
         */
        IconButton *_incScale{};

        /**
         * @brief     fit screen
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-24 19:49
         */
        IconButton *_fullScreen{};
    };
}