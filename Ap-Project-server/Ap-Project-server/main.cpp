#include "mainwindow.h"

#include <QApplication>
#include <server.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Server server;
    server.start(1025);
    return a.exec();
}
