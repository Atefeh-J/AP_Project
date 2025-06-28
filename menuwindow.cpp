#include "Menuwindow.h"
Menuwindow::Menuwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
Menuwindow::~Menuwindow()
{}

void Menuwindow::setObjects()
{
    QTransform transform;
    transform.rotate(90);
    background = background.transformed(transform, Qt::SmoothTransformation);

    Lpagename = new QLabel("menu", this);
    pbnstartgame = new QPushButton("start game" ,this);
    pbneditinformation = new QPushButton("edit information" ,this);
    pbnhistory = new QPushButton("history" ,this);
    pbnsignout = new QPushButton("signout" ,this);

    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(730, y, 200, 25);y=y+30+20;
    pbnstartgame->setGeometry(650, y, 200, 25);y=y+30+20;
    pbneditinformation->setGeometry(650, y, 200, 25);y=y+30+20;
    pbnhistory->setGeometry(650, y, 200, 25);y=y+30+20;
    pbnsignout->setGeometry(650, y, 200, 25);y=y+30+20;
    
    pbnstartgame->setStyleSheet("color: white; background: red;");
    pbneditinformation->setStyleSheet("color: white; background: red;");
    pbnhistory->setStyleSheet("color: white; background: red;");
    pbnsignout->setStyleSheet("color: white; background: red;");

    connect(pbnstartgame, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
    connect(pbneditinformation, &QPushButton::clicked, this, [this]() {
        gotowindow(2);
    });
    connect(pbnhistory, &QPushButton::clicked, this, [this]() {
        gotowindow(3);
    });
    connect(pbnsignout, &QPushButton::clicked, this, [this]() {
        gotowindow(4);
    });
}
void Menuwindow::readInfo()
{}

void Menuwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:

        break;
    case 2:
    {
        Editwindow *n = new Editwindow();
        n->show();
        this->close();
    }
        break;
    case 3:
        break;
    case 4:
        Beginwindow *n=new Beginwindow();
        n->show();
        this->close();
        break;
    }

}
