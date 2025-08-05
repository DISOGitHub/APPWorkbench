#include <QApplication>
#include "EmptyComponent.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    EmptyComponent empty;

    for (int iarg = 0; iarg < argc; ++iarg)
    {
        QString arg = argv[iarg];
        if (arg == "-FITKWB" && iarg != argc - 1)
        {
            QString input = argv[iarg + 1];
            empty.setInput(input);
            break;
        }
    }
    empty.show();

    return app.exec();
}

