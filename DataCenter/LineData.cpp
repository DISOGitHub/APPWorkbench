#include "LineData.h"

namespace Data
{

    LineData::LineData(QGraphicsObject * obj, QGraphicsObject * from, QGraphicsObject * to)
        : _obj(obj)
        , _from(from)
        , _to(to)
    {

    }

    bool LineData::copy(FITKAbstractDataObject * obj)
    {
        LineData * data = dynamic_cast<LineData*>(obj);
        if (!data) { return false; }
        FITKAbstractDataObject::copy(data);

        /// copy graphics item
        _obj = data->graphicsObject();
        _from = data->fromGraphicsObject();
        _to = data->toGraphicsObject();

        return true;
    }

    void LineData::clearDegeneratedChannels()
    {
        while (!_degeneratedChannels.isEmpty())
        {
            Channel * channel = _degeneratedChannels.takeFirst();
            delete channel;
            channel = nullptr;
        }
    }

    Data::LineData * LineDataManger::getLineDataByGraphicsItem(QGraphicsItem * item)
    {
        int num = getDataCount();
        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::LineData * data = getDataByIndex(iCnt);
            if (data->graphicsObject() == item)
            {
                return data;
            }
        }
        return nullptr;
    }

    Data::LineData * LineDataManger::getLineDataByFromToGraphicsItem(QGraphicsItem * from, QGraphicsItem * to)
    {
        int num = getDataCount();
        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::LineData * data = getDataByIndex(iCnt);
            if (data->fromGraphicsObject() == from &&
                data->toGraphicsObject() == to)
            {
                return data;
            }
        }
        return nullptr;
    }

    bool LineDataManger::removeLineDataByGraphicsItem(QGraphicsItem * item)
    {
        int num = getDataCount();
        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::LineData * data = getDataByIndex(iCnt);
            if (data->graphicsObject() == item)
            {
                removeDataObj(data);
                return true;
            }
        }
        return false;
    }

    void LineDataManger::removeInvalidData(QList<QGraphicsItem *> items)
    {
        int num = getDataCount();
        QList<Data::LineData *> needRemoves;
        for (int iCnt = 0; iCnt < num; ++iCnt)
        {
            Data::LineData * data = getDataByIndex(iCnt);
            QGraphicsItem * from = data->fromGraphicsObject();
            QGraphicsItem * to = data->toGraphicsObject();

            if (items.contains(from) && items.contains(to)) { continue; }
            needRemoves.append(data);
        }

        for (Data::LineData * line : needRemoves)
        {
            removeDataObj(line);
        }
    }

}