#include "MainWindowGenerator.h"
#include "GUIFrame/MainWindow.h"

MainWindowGenerator::MainWindowGenerator()
{

}

QWidget * MainWindowGenerator::genMainWindow()
{
    return new GUI::MainWindow;
}
