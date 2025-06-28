#include "beginwindow.h"

Beginwindow::Beginwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
Beginwindow::~Beginwindow()
{}

void Beginwindow::setObjects()
{
    pbnsignin = new QPushButton("sign in",this);
    pbnsignup = new QPushButton("sign up",this);

    // تنظیم موقعیت و اندازه مناسب
    int y=300;
    pbnsignin->setGeometry(670,y,150,40);y=y+30+30;
    pbnsignup->setGeometry(670,y,150,40);
    pbnsignin->setStyleSheet("color: white; background: red;");
    pbnsignup->setStyleSheet("color: white; background: red;");

    connect(pbnsignin, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
    connect(pbnsignup, &QPushButton::clicked, this, [this]() {
        gotowindow(2);
    });
}
void Beginwindow::readInfo()
{}

void Beginwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        SigninWindow *n = new SigninWindow();
        n->show();
        this->close();
        break;
    }
    case 2:
    {
        Signupwindow *n = new Signupwindow();
        n->show();
        this->close();
        break;
    }
    }

}
