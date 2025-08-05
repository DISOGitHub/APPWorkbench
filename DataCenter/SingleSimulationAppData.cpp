#include "SingleSimulationAppData.h"
#include <QDir>

namespace Data
{

    bool SingleSimulationAppDataManger::removeByGraphicsItem(QGraphicsItem * item)
    {
        int num = getDataCount();

        for (int index = 0; index < num; ++index)
        {
            SingleSimulationAppData * single = getDataByIndex(index);
            if (single->graphicsObject() == item)
            {
                removeDataByIndex(index);
                return true;
            }
        }
        return false;
    }

    Data::SingleSimulationAppData * SingleSimulationAppDataManger::getSingleAppDataByGraphicsObject(QGraphicsItem * obj)
    {
        int num = getDataCount();
        for (int index = 0; index < num; ++index)
        {
            auto single = getDataByIndex(index);
            if (single->graphicsObject() == obj)
            {
                return single;
            }
        }
        return nullptr;
    }

    void SingleSimulationAppDataManger::dataUpdateByRemoveItems(QList<QGraphicsItem *> removes)
    {
        int num = getDataCount();
        QList<Data::SingleSimulationAppData *> needRemoves;
        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::SingleSimulationAppData * data = getDataByIndex(iCnt);
            QGraphicsItem * item = data->graphicsObject();

            if (removes.contains(item))
                needRemoves.append(data);
        }

        for (Data::SingleSimulationAppData * item : needRemoves)
        {
            removeDataObj(item);
        }
    }

}