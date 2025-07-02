
#include <QApplication>
#include "beginwindow.h"
#include "connectwindow.h"
#include "client.h"
//Client *client;
//Client *client;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connectwindow w;
    w.show();
    return a.exec();
}
