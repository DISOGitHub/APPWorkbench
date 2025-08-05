/**
 *
 * @file      ComponentCoreDriver.h
 * @brief     Component Core Application Driver. Binding Graphics Instance Item.
 * @author    maguiwa(maguiwa520@163.com)
 * @date      2024-8-30 14:37
 *
 */

#pragma once
#include <QString>
#include <QProcess>
#include <QGraphicsObject>
#include <QFileSystemWatcher>

namespace Graphics
{
    class GraphicsItem;
}

namespace Data
{
    class ComponentAppData;
}

namespace EventHelper
{
    /**
     * @brief     Component Core Application Driver.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-30 14:44
     */
    class ComponentCoreDriver : public QObject
    {
        Q_OBJECT
    public:
        /**
         * @brief     constructor
         * @param     item[i]. graphics item
         * @param     withGUI[i]. component app with gui attribute
         * @return    component core driver instance
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 8:37
         */
        explicit ComponentCoreDriver(QGraphicsItem * item);

        /**
         * @brief:    destructor
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 14:45
         */
        ~ComponentCoreDriver();

        /**
         * @brief:    set core app path
         * @param:    const QString & _coreAppPath : core app path
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 14:50
         */
        void setCoreAppPath(const QString & coreAppPath);

        /**
         * @brief:    set ini file path
         * @param:    const QString & _iniFilePath : ini file path
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 14:51
         */
        void setIniFilePath(const QString & iniFilePath);

        /**
         * @brief:    whether core application is running
         * @return:   bool : running or not
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:48
         */
        bool isRunning();

        /**
         * @brief:    add core start arg
         * @param:    const QString & arg : arg
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 14:51
         */
        void addArg(const QString & arg);

        /**
         * @brief     clear core start arg
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-8-31 16:11
         */
        void clearArgs();

        /**
         * @brief:    start
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 14:52
         */
        void start();

        /**
         * @brief:    run with Graphical User Interface or Console
         * @param:    bool with : with Graphical User Interface or not
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:22
         */
        void setWithGUI(bool with);

        /**
         * @brief     terminate current process . while process is running
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 14:43
         */
        void terminate();

    protected slots:

        /**
         * @brief:    ready to read standard output. read it
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:18
         */
        void readStandardOutput();

        /**
         * @brief:    ready to read standard error. read it
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:18
         */
        void readStandardError();

        /**
         * @brief     component app 's core run finished
         * @param     exitCode[i]. component app 's core run finished exit code
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-9 20:56
         */
        void componentFinished(int exitCode);

        /**
         * @brief     initialize
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-10 9:50
         */
        void initialize(QGraphicsItem * item);

    protected:
        /**
         * @brief     while under linux / ubuntu system . load bash rc env
         * @param     env[i]. process environment
         * @return    void
         * @author    maguiwa (maguiwa520@163.com)
         * @data      2024-9-25 13:25
         */
        void loadBashRCEnvironmentVariables(QProcessEnvironment & env);

        /**
         * @brief     core app path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 14:52
         */
        QString _corePath{};

        /**
         * @brief     ini file path
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 14:53
         */
        QString _iniFilePath{};

        /**
         * @brief     extra args;
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 14:54
         */
        QString _args;

        /**
         * @brief     process to start component core
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 14:56
         */
        QProcess * _process{};

        /**
         * @brief     component core app run with Graphical User Interface or Console
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 15:21
         */
        bool _withGUI{ true };

        /**
         * @brief     real use graphics item
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-10 9:17
         */
        Graphics::GraphicsItem * _item{};

        /**
         * @brief     component app data
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-9-10 9:53
         */
        Data::ComponentAppData * _cptAppData{};
    };

    /**
     * @brief     Component Core Application Driver. binding with graphics object.
     * @author    maguiwa(maguiwa520@163.com)
     * @date      2024-8-30 15:30
     */
    class ComponentCoreDriverManger
    {
    public:
        /**
         * @brief:    get singleton instance
         * @return:   EventHelper::ComponentCoreDriverManger * : instance
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:34
         */
        static ComponentCoreDriverManger * instance();

        /**
         * @brief:    get driver by binding graphics object
         * @param:    QGraphicsObject * obj : graphics object
         * @return:   EventHelper::ComponentCoreDriver *
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:37
         */
        ComponentCoreDriver * getDriver(QGraphicsItem * obj);

        /**
         * @brief:    remove driver by binding graphics object
         * @param:    QGraphicsObject * obj : graphics object
         * @return:   void
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:38
         */
        void removeDriver(QGraphicsItem * obj);

    private:
        /**
         * @brief:    constructor
         * @return:   component core driver manger instance
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:34
         */
        ComponentCoreDriverManger() = default;

        /**
         * @brief:    destructor
         * @author:   maguiwa (maguiwa520@163.com)
         * @data      2024-8-30 15:35
         */
        ~ComponentCoreDriverManger();

        /**
         * @brief     graphics object component core driver pair
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 15:31
         */
        QMap<QGraphicsItem *, ComponentCoreDriver *> _drivers;

        /**
         * @brief     singleton instance
         * @author    maguiwa(maguiwa520@163.com)
         * @date      2024-8-30 15:32
         */
        static ComponentCoreDriverManger * _instance;
    };
}
