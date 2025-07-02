#include "beginwindow.h"

Beginwindow::Beginwindow(Client *client,QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects( client);

}
Beginwindow::~Beginwindow()
{}

void Beginwindow::setObjects(Client *client)
{
    pbnsignin = new QPushButton("sign in",this);
    pbnsignup = new QPushButton("sign up",this);

    // تنظیم موقعیت و اندازه مناسب
    int y=300;
    pbnsignin->setGeometry(670,y,150,40);y=y+30+30;
    pbnsignup->setGeometry(670,y,150,40);
    pbnsignin->setStyleSheet("color: white; background: red;");
    pbnsignup->setStyleSheet("color: white; background: red;");

    connect(pbnsignin, &QPushButton::clicked, this, [this,client]() {
        gotowindow(1,client);
    });
    connect(pbnsignup, &QPushButton::clicked, this, [this,client]() {
        gotowindow(2,client);
    });
}
void Beginwindow::readInfo()
{}

void Beginwindow::gotowindow(int choice,Client *client)
{
    switch(choice)
    {
    case 1:
    {
        SigninWindow *n = new SigninWindow( client);
        n->show();
        this->close();
        break;
    }
    case 2:
    {
        Signupwindow *n = new Signupwindow(client);
        n->show();
        this->close();
        break;
    }
    }

}
