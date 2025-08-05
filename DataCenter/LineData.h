/**
 *
 * @file      LineData.h
 * @brief     Line Item Carry Data.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-9-3 17:55
 *
 */
#pragma once
#include "DataCenterAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"

#include "ComponentData.h"

#include <QGraphicsItem>

namespace Data
{
    /**
     * @brief     Line Carry Data
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-3 18:00
     */
    class DATA_CENTER_API LineData : public Core::FITKAbstractDataObject
    {
    public:
        /**
         * @brief     constructor
         * @param     obj[i]. Line Item
         * @return    LineData object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:00
         */
        explicit LineData(QGraphicsObject * obj, QGraphicsObject * from, QGraphicsObject * to);

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:01
         */
        ~LineData() = default;

        /**
         * @brief     get from graphics object
         * @return    QGraphicsObject * . from graphics object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 9:54
         */
        QGraphicsObject * fromGraphicsObject() const { return _from; }

        /**
         * @brief     get to graphics object
         * @return    QGraphicsObject * . to graphics object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-6 9:55
         */
        QGraphicsObject * toGraphicsObject() const { return _to; }

        /**
         * @brief     Get Line Item
         * @return    QGraphicsObject * . Line Item
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:01
         */
        QGraphicsObject * graphicsObject() const { return _obj; }

        /**
         * @brief     copy LineData
         * @param     data[i]. LineData object pointer
         * @return    bool . copy success
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-3 18:02
         */
        bool copy(FITKAbstractDataObject * obj) override;

        /**
         * @brief     add degenerated channel
         * @param     channel[i].degenerated channel add in
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 11:08
         */
        void addDegeneratedChannel(Channel * channel) { _degeneratedChannels.append(channel); }

        /**
         * @brief     get degenerated channels
         * @return    QList<Channel *> .degenerated channels
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 11:08
         */
        QList<Data::Channel *> degeneratedChannels() { return _degeneratedChannels; }

        /**
         * @brief     clear degenerated channels . free memory
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 11:08
         */
        void clearDegeneratedChannels();

    protected:
        /**
         * @brief     Line Item . From Item . To Item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-3 18:02
         */
        QGraphicsObject * _obj{}, *_from{}, *_to{};

        /**
         * @brief     degenerated channels. while line between two component app
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-12 11:04
         */
        QList<Data::Channel *> _degeneratedChannels;
    };

    /**
     * @brief     line data manger
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-9-5 11:14
     */
    class DATA_CENTER_API LineDataManger : public Core::FITKAbstractDataManager<LineData>
    {
    public:
        /**
         * @brief     default constructor
         * @return    LineDataManger object
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 11:14
         */
        explicit LineDataManger() = default;

        /**
         * @brief     default destructor
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 11:15
         */
        virtual ~LineDataManger() = default;

        /**
         * @brief     get line data by graphics item
         * @param     item[i]. line graphics item
         * @return    Data::LineData * . line data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-5 11:16
         */
        LineData * getLineDataByGraphicsItem(QGraphicsItem * item);

        /**
         * @brief     get line data by line 's from graphics item and to graphics item
         * @param     from[i]. line 's from graphics item
         * @param     to[i]. line 's to graphics item
         * @return    Data::LineData * . line data
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-12 13:22
         */
        LineData * getLineDataByFromToGraphicsItem(QGraphicsItem * from, QGraphicsItem * to);

        /**
         * @brief     remove line data by graphics item
         * @param     item[i]. line graphics item
         * @return    bool . remove result
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 12:47
         */
        bool removeLineDataByGraphicsItem(QGraphicsItem * item);

        /**
         * @brief     remove invalid line data
         * @param     items[i] . graphics items in view. used to get line data is valid
         * @return    bool .
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-19 10:12
         */
        void removeInvalidData(QList<QGraphicsItem *> items);
    };
}