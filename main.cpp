#include "mainwindow.h"

#include <QStyleFactory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle (QStyleFactory::create("fusion"));
    a.setOrganizationName ("Smena LTD.");
    a.setApplicationName ("2048 The Game");
    MainWindow w;
    w.show();
    return a.exec();
}
