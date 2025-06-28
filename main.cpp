#include "mainwindow.h"

#include <QApplication>
#include <welcomescreen.h>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // WelcomeScreen welcome;
    // welcome.exec();
    MainWindow w;
    w.show();
    return a.exec();
}
