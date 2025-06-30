
#include <QApplication>
#include "beginwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Beginwindow w;
    w.show();
    return a.exec();
}
