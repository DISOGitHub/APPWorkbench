#include "MultiSimulationAppData.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QApplication>
#include "LogData.h"
#include "OperatorsInterface/FileIOOperator.h"

namespace Data
{

    bool MultiSimulationAppData::isValidSimulationAppData()
    {
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            if (!cpt->isValidComponentAppData())
                return false;
        }

        return true;
    }

    bool MultiSimulationAppData::writeOutAppDescribeFile(const QString & appName)
    {
        EventOper::FileIOOperator * oper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::FileIOOperator>("FileIO");
        if (!oper) { return false; }
        QString filePath = QDir::cleanPath(qApp->applicationDirPath() + QString("/../AppTemplate/%1").arg(appName));
        return oper->writeAppDescription(this, filePath);
    }

    bool MultiSimulationAppData::addComponentAppData(ComponentAppData * data)
    {
        _componentAppDatas.append(data);
        return true;
    }

    bool MultiSimulationAppData::removeComponentAppData(QGraphicsItem * item)
    {
        ComponentAppData * data = nullptr;
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            if (cpt->graphicsObject() == item)
            {
                data = cpt;
                break;
            }
        }
        if (data)
        {
            _componentAppDatas.removeOne(data);
            return true;
        }
        return false;
    }

    bool MultiSimulationAppData::addLineData(LineData * data)
    {
        _lineDatas.append(data);
        return true;
    }

    bool MultiSimulationAppData::removeLineData(QGraphicsItem * item)
    {
        LineData * data = nullptr;
        for (LineData * line : _lineDatas)
        {
            if (line->graphicsObject() == item)
            {
                data = line;
                break;
            }
        }
        if (data)
        {
            _lineDatas.removeOne(data);
            return true;
        }
        return false;
    }

    bool MultiSimulationAppData::combine(MultiSimulationAppData * app)
    {
        /// combine data
        _componentAppDatas.append(app->_componentAppDatas);
        _lineDatas.append(app->_lineDatas);
        return true;
    }

    void MultiSimulationAppData::setProjectPath(const QString & projectPath)
    {
        _projectPath = projectPath;
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            cpt->setProjectPath(projectPath);
        }
    }

    Data::ComponentAppData * MultiSimulationAppData::getFirstComponentAppData()
    {
        QList<ComponentAppData *> mays;
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            bool first = true;
            for (auto line : _lineDatas)
            {
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    first = false;
                    break;
                }
            }
            if (first)
            {
                _currentAppData = cpt;
                return _currentAppData;
            }
        }
        return nullptr;
    }

    Data::ComponentAppData * MultiSimulationAppData::getCurrentComponentAppData()
    {
        if (_currentAppData)
            return _currentAppData;
        return getFirstComponentAppData();
    }

    bool MultiSimulationAppData::setCurrentComponentAppData(ComponentAppData * data)
    {
        _currentAppData = data;
        return true;
    }

    Data::ComponentAppData * MultiSimulationAppData::getNextSolveComponentApp()
    {
        /// first check next linked component app as next solve component app. No Need Next Component Not Solved.
        if (!_currentAppData)
            getCurrentComponentAppData();

        QList<ComponentAppData *> nextApps = getNextLinkedComponentApps(_currentAppData);
        for (ComponentAppData * nextApp : nextApps)
        {
            int inDegree = getComponentAppInDegree(nextApp);
            if (inDegree == 0)
                return nextApp;
        }

        /// if next linked component app not meet the in degree need. find in this multiple component app. Need Next Component Not Solved
        for (ComponentAppData * app : _componentAppDatas)
        {
            int inDegree = getComponentAppInDegree(app);
            if (inDegree == 0 && !app->existProject())
                return app;
        }
        return nullptr;
    }

    int MultiSimulationAppData::getComponentAppInDegree(ComponentAppData * cpt)
    {
        int inDegree = 0;
        for (LineData * line : _lineDatas)
        {
            if (line->toGraphicsObject() == cpt->graphicsObject())
            {
                ComponentAppData * from = getComponentAppDataByGraphicsObject(line->fromGraphicsObject());
                if (from->existProject())
                    continue;
                else
                    inDegree += 1;
            }
        }
        return inDegree;
    }

    QList<ComponentAppData *> MultiSimulationAppData::getPreviousLinkedComponentApps(ComponentAppData * cpt)
    {
        QList<ComponentAppData *> previousApps;
        for (LineData * line : _lineDatas)
        {
            if (line->toGraphicsObject() == cpt->graphicsObject())
            {
                previousApps.append(getComponentAppDataByGraphicsObject(line->fromGraphicsObject()));
            }
        }
        return previousApps;
    }

    QList<ComponentAppData *> MultiSimulationAppData::getNextLinkedComponentApps(ComponentAppData * cpt)
    {
        QList<ComponentAppData *> nextApps;
        for (LineData * line : _lineDatas)
        {
            if (line->fromGraphicsObject() == cpt->graphicsObject())
            {
                nextApps.append(getComponentAppDataByGraphicsObject(line->toGraphicsObject()));
            }
        }
        return nextApps;
    }

    Data::ComponentAppData * MultiSimulationAppData::getComponentAppDataByGraphicsObject(QGraphicsItem * item)
    {
        for (auto cpt : _componentAppDatas)
        {
            if (cpt->graphicsObject() == item)
            {
                return cpt;
            }
        }
        return nullptr;
    }

    bool MultiSimulationAppData::isReferenceGraphicItem(QGraphicsItem * item)
    {
        for (Data::ComponentAppData * cpt : _componentAppDatas)
        {
            QGraphicsItem * part = cpt->graphicsObject();
            if (part == item)
            {
                return true;
            }
        }
        for (Data::LineData * line : _lineDatas)
        {
            QGraphicsItem * part = line->graphicsObject();
            if (part == item)
            {
                return true;
            }
        }
        return false;
    }

    QList<Data::ComponentAppData *> MultiSimulationAppData::referenceComponentAppData(QList<QGraphicsItem *> items)
    {
        QList<Data::ComponentAppData *> references;
        for (QGraphicsItem * item : items)
        {
            for (Data::ComponentAppData * cpt : _componentAppDatas)
            {
                if (cpt->graphicsObject() == item)
                {
                    references.append(cpt);
                    break;
                }
            }
        }
        return references;
    }

    QList<Data::LineData *> MultiSimulationAppData::referenceLineData(QList<QGraphicsItem *> items)
    {
        QList<Data::LineData *> references;
        for (QGraphicsItem * item : items)
        {
            for (Data::LineData * line : _lineDatas)
            {
                if (line->graphicsObject() == item)
                {
                    references.append(line);
                    break;
                }
            }
        }
        return references;
    }

    QList<Data::ComponentAppData *> MultiSimulationAppData::endComponentAppData()
    {
        ///with line to. not with line from
        QList<Data::ComponentAppData *> ends;
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            bool lineTo = false;
            bool lineFrom = false;

            for (LineData * line : _lineDatas)
            {
                if (line->fromGraphicsObject() == cpt->graphicsObject())
                {
                    lineFrom = true;
                    break;
                }
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    lineTo = true;
                }
            }

            if (!lineFrom && lineTo)
            {
                ends.append(cpt);
            }
        }
        return ends;
    }

    QList<Data::ComponentAppData *> MultiSimulationAppData::beginComponentAppData()
    {
        /// with line from. not with line to
        QList<Data::ComponentAppData *> begs;
        for (ComponentAppData * cpt : _componentAppDatas)
        {
            bool lineTo = true;
            bool lineFrom = false;

            for (LineData * line : _lineDatas)
            {
                if (line->fromGraphicsObject() == cpt->graphicsObject())
                {
                    lineFrom = true;
                }
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    lineTo = true;
                    break;
                }
            }

            if (lineFrom && !lineTo)
            {
                begs.append(cpt);
            }
        }
        return begs;
    }

    Data::MultiSimulationAppData * MultiSimulationAppDataManger::getMultiAppDataByGraphicsObject(QGraphicsItem * item)
    {
        int num = getDataCount();
        for (int index = 0; index < num; ++index)
        {
            auto multi = getDataByIndex(index);
            for (auto cpt : multi->_componentAppDatas)
            {
                if (cpt->graphicsObject() == item)
                {
                    return multi;
                }
            }
        }
        return nullptr;
    }

    Data::ComponentAppData * MultiSimulationAppDataManger::getComponentAppDataByGraphicsObject(QGraphicsItem * item)
    {
        int num = getDataCount();
        for (int index = 0; index < num; ++index)
        {
            auto multi = getDataByIndex(index);
            for (auto cpt : multi->_componentAppDatas)
            {
                if (cpt->graphicsObject() == item)
                {
                    return cpt;
                }
            }
        }
        return nullptr;
    }

    QList<ComponentAppData *> MultiSimulationAppDataManger::dataUpdateByRemoveItems(QList<QGraphicsItem *> removes)
    {
        if (removes.isEmpty()) { return QList<ComponentAppData *>(); }

        /// get reference multi simulation app data
        QList<Data::MultiSimulationAppData *> references;
        int num = getDataCount();

        for (int index = 0; index < num; ++index)
        {
            Data::MultiSimulationAppData * data = getDataByIndex(index);
            for (QGraphicsItem * remove : removes)
            {
                if (data->isReferenceGraphicItem(remove))
                {
                    references.append(data);
                    break;
                }
            }
        }

        /// remove reference multi simulation app data and get rest component app data and line data
        QList<Data::ComponentAppData * > restCpts;
        QList<Data::LineData *> restLines;
        for (Data::MultiSimulationAppData * data : references)
        {
            restCpts.append(data->componentAppDatas());
            restLines.append(data->lineDatas());
            QList<Data::ComponentAppData *> deletedCpts = data->referenceComponentAppData(removes);
            QList<Data::LineData *> deletedLines = data->referenceLineData(removes);
            for (Data::ComponentAppData * deleteCpt : deletedCpts)
                restCpts.removeOne(deleteCpt);
            for (Data::LineData * deleteLine : deletedLines)
                restLines.removeOne(deleteLine);

            removeDataObj(data);
        }

        /// remove line with invalid from or to item
        QList<Data::LineData *> invalidLines;
        for (Data::LineData * line : restLines)
        {
            QGraphicsItem * from = line->fromGraphicsObject();
            QGraphicsItem * to = line->toGraphicsObject();

            if (removes.contains(from) || removes.contains(to))
            {
                invalidLines.append(line);
            }
        }

        for (Data::LineData * line : invalidLines)
        {
            restLines.removeOne(line);
        }

        /// recombine multi simulation app data .
        /// first get all multi simulation app 's begin component app data
        /// component has line from but do not has line to is a multi simulation app 's begin component app data
        QList<Data::ComponentAppData *> begs;
        for (Data::ComponentAppData * cpt : restCpts)
        {
            /// get has line from component app data
            bool noTo = true;
            bool yesFrom = false;
            for (Data::LineData * line : restLines)
            {
                if (line->fromGraphicsObject() == cpt->graphicsObject())
                {
                    yesFrom = true;
                }
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    noTo = false;
                    break;
                }
            }
            if (yesFrom && noTo)
            {
                begs.append(cpt);
            }
        }

        while (!begs.isEmpty())
        {
            recombineMultiSimulationAppData(begs.first(), begs, restCpts, restLines);
        }
        Q_ASSERT(restLines.isEmpty());
        return restCpts;
    }

    bool MultiSimulationAppDataManger::isPortLinked(QGraphicsItem * item, bool inputPort)
    {
        MultiSimulationAppData * data = getMultiAppDataByGraphicsObject(item);
        if (!data) { return false; }

        for (Data::LineData * line : data->lineDatas())
        {
            if (!inputPort &&
                line->fromGraphicsObject() == item)
            {
                return true;
            }
            else if (inputPort &&
                line->toGraphicsObject() == item)
            {
                return true;
            }
        }
        return false;
    }

    void MultiSimulationAppDataManger::recombineMultiSimulationAppData(Data::ComponentAppData * beg, QList<Data::ComponentAppData *> & begs, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines)
    {
        /// forward spread 
        MultiSimulationAppData * data = new MultiSimulationAppData();
        data->addComponentAppData(beg);
        begs.removeOne(beg);
        cpts.removeOne(beg);

        QList<Data::ComponentAppData *> currents = { beg };
        while (!currents.isEmpty())
        {
            currents = forwardSpread(data, currents, cpts, lines);
        }

        if (!lines.isEmpty())
        {
            /// get current multi simulation app 's end item.
            currents = data->endComponentAppData();
            while (!currents.isEmpty())
            {
                currents = reverseSpread(data, begs, currents, cpts, lines);
            }
        }
        appendDataObj(data);
    }



    QList<Data::ComponentAppData *> MultiSimulationAppDataManger::forwardSpread(MultiSimulationAppData * data, QList<Data::ComponentAppData *> currents, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines)
    {
        /// forward find lines
        QList<Data::LineData *> forwardLines;
        for (Data::ComponentAppData * cpt : currents)
        {
            for (Data::LineData * line : lines)
            {
                if (line->fromGraphicsObject() == cpt->graphicsObject())
                {
                    forwardLines.append(line);
                }
            }
        }
        currents.clear();

        for (Data::LineData * line : forwardLines)
        {
            data->addLineData(line);
            lines.removeOne(line);
        }

        /// forward find items
        for (Data::LineData * line : forwardLines)
        {
            for (Data::ComponentAppData * cpt : cpts)
            {
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    /// line only has one to item. so find can break
                    /// while multi line to item. just record once
                    if (!currents.contains(cpt))
                        currents.append(cpt);
                    break;
                }
            }
        }

        for (Data::ComponentAppData * current : currents)
        {
            data->addComponentAppData(current);
            cpts.removeOne(current);
        }

        return currents;
    }

    QList<Data::ComponentAppData *> MultiSimulationAppDataManger::reverseSpread(MultiSimulationAppData * data, QList<Data::ComponentAppData *> & begs, QList<Data::ComponentAppData *> currents, QList<ComponentAppData *> & cpts, QList<Data::LineData *> & lines)
    {
        /// reverse find lines
        QList<Data::LineData *> reverseLines;
        for (Data::ComponentAppData * cpt : currents)
        {
            for (Data::LineData * line : lines)
            {
                if (line->toGraphicsObject() == cpt->graphicsObject())
                {
                    reverseLines.append(line);
                }
            }
        }
        currents.clear();

        for (Data::LineData * line : reverseLines)
        {
            data->addLineData(line);
            lines.removeOne(line);
        }

        /// reverse find items
        for (Data::LineData * line : reverseLines)
        {
            for (Data::ComponentAppData * cpt : cpts)
            {
                if (line->fromGraphicsObject() == cpt->graphicsObject())
                {
                    /// line only has one from item. so find can break
                    /// while multi line from item. just record once
                    if (!currents.contains(cpt))
                        currents.append(cpt);
                    break;
                }
            }
        }

        for (Data::ComponentAppData * current : currents)
        {
            data->addComponentAppData(current);
            cpts.removeOne(current);

            if (begs.contains(current))
            {
                begs.removeOne(current);
            }
        }

        return currents;
    }

}
