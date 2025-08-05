#include "ProjectNavi.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "OperatorsInterface/TreeEventOperator.h"
#include <QPainter>
#include <QHBoxLayout>

namespace GUI
{
    ProjectNavi::ProjectNavi(QWidget *parent, Qt::WindowFlags f)
        : QWidget(parent, f)
    {
        init();
    }

    ProjectNavi::~ProjectNavi()
    {

    }

    void ProjectNavi::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setPen(QPen(QColor(229, 229, 229), 1));
        painter.drawRect(rect().adjusted(0, 0, -1, -1));
    }

    void ProjectNavi::init()
    {
        _tree = new QTreeWidget(this);
        auto lay = new QHBoxLayout();
        setLayout(lay);
        lay->addWidget(_tree);

        _tree->setHeaderHidden(true);
        _tree->setFrameShape(QFrame::NoFrame);
        _tree->setLineWidth(1);

        QPalette palette;
        palette.setColor(QPalette::Base, QColor(248, 248, 248));
        palette.setColor(QPalette::Window, QColor(248, 248, 248));
        setPalette(palette);
        setAutoFillBackground(true);

        _tree->setPalette(palette);

        EventOper::TreeEventOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::TreeEventOperator>("ProjectTreeEvent");
        if (!oper)
            return;

        oper->setTreeWidget(_tree);
        oper->updateTree();
    }
}