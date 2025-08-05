/**
 *  error,warning :  progress bar : scale, full screen
 *  error_icon, error_msg_num. warning_icon, warning_msg_num. last error msg:
 *  progress_bar_desc, progress_bar : scale_label, scale_bar,  full_screen_icon
 */

#include "StatusBarWidget.h"
#include "GUIWidget/IconButton.h"
#include "GUIWidget/ComboBox.h"
#include <QHBoxLayout>
#include <QFile>
#include "GUIWidget/StyleMenu.h"

#define _DEFAULT_SCALES_ \
    QStringList { "75%", "100%", "150", "200%" }

namespace GUI
{
    StatusBarWidget::StatusBarWidget(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        initUI();
    }

    StatusBarWidget::~StatusBarWidget()
    {
    }

    void StatusBarWidget::setWarningMsgNum(int msgNum)
    {
    }

    void StatusBarWidget::setErrorMsgNum(int msgNum)
    {
    }

    void StatusBarWidget::setLastErrorMsg(const QString &msg)
    {
    }

    void StatusBarWidget::showProgress(int per, const QString &msg)
    {
    }

    void StatusBarWidget::hideProgress()
    {
    }

    void StatusBarWidget::initUI()
    {
        setFixedHeight(20);
        auto lay = new QHBoxLayout();
        setLayout(lay);
        lay->setSpacing(5);
        lay->setContentsMargins(5, 0, 5, 0);

        IconButton *errorBtn = new IconButton(QIcon(":/frames/error.png"), QIcon(":/frames/error.png"), tr("Error Message Number"), this, QSize(16, 16));
        _errorLabel = new QLabel("0", this);
        IconButton *warningBtn = new IconButton(QIcon(":/frames/warning.png"), QIcon(":/frames/warning.png"), tr("Warn Message Number"), this, QSize(16, 16));
        _warningLabel = new QLabel("0", this);

        _centerWidget = new QWidget(this);
        auto centerLay = new QHBoxLayout();
        _centerWidget->setLayout(centerLay);
        centerLay->setContentsMargins(5, 0, 5, 0);

        _progressMsg = new QLabel(_centerWidget);
        _progressBar = new QProgressBar(_centerWidget);
        centerLay->addWidget(_progressMsg);
        centerLay->addWidget(_progressBar);
        _centerWidget->setVisible(false);

        _dropScale = new ComboBox(this);
        StyleMenu * menu = new StyleMenu();
        _dropScale->registerMenu(menu);
        _dropScale->addItems(_DEFAULT_SCALES_);

        _decScale = new IconButton(QIcon(":/frames/dec.png"), QIcon(":/frames/dec.png"), tr("Reduce Canvas By 10%"), this, QSize(16, 16));
        _slider = new QSlider(Qt::Orientation::Horizontal, this);
        _slider->setMaximumWidth(150);
        _slider->setRange(50, 200);
        _slider->setTickInterval(10);
        _slider->setValue(100);
        QFile file(":/frames/Slider.qss");
        if (file.open(QIODevice::ReadOnly))
        {
            QString style = file.readAll();
            file.close();
            _slider->setStyleSheet(style);
        }

        _incScale = new IconButton(QIcon(":/frames/inc.png"), QIcon(":/frames/inc.png"), tr("Increase Canvas By 10%"), this, QSize(16, 16));

        _fullScreen = new IconButton(QIcon(":/frames/full.png"), QIcon(":/frames/full.png"), tr("Canvas Full Screen"), this, QSize(16, 16));

        lay->addWidget(errorBtn);
        lay->addWidget(_errorLabel);
        lay->addWidget(warningBtn);
        lay->addWidget(_warningLabel);

        lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
        lay->addWidget(_centerWidget);
        lay->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

        lay->addWidget(_dropScale);
        lay->addWidget(_decScale);
        lay->addWidget(_slider);
        lay->addWidget(_incScale);
        lay->addWidget(_fullScreen);
    }
}