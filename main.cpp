#include <QApplication>
#include "maingui.h"
#include <QtPlugin>
#include <QPluginLoader>
#include <QCoreApplication>
#include <QLibraryInfo>
#include <iostream>
#include <QImageIOPlugin>
#include "ndviprocessor.h"
#include "outputimagegui.h"
#include "inputimagegui.h"

int main(int argc, char *argv[])
{ 
    QApplication app(argc, argv);

    mainGui gui; //(_refToProcessor);

    gui.show();

    return app.exec();
}
