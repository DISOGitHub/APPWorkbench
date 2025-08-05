#include "GraphicsObjectEventOperator.h"

namespace EventOper
{

    GraphicsObjectEventOperator::GraphicsObjectEventOperator()
        : EventOperator()
    {

    }

    GraphicsObjectEventOperator::~GraphicsObjectEventOperator()
    {

    }

    void GraphicsObjectEventOperator::setGraphicsObject(QList<QGraphicsObject *> items)
    {
        _items = items;
    }

}