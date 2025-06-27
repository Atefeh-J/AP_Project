///
#include "forgotpswwindow.h"
Forgotpswwindow::Forgotpswwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
Forgotpswwindow::~Forgotpswwindow()
{}

void Forgotpswwindow::setObjects()
{
        Lpagename = new QLabel("forgot password", this);
        Lphone = new QLabel("enter your phonenumber", this);
        txtphone = new QTextEdit(this);
        pbnsign = new QPushButton("signin", this);
        Lerror = new QLabel("h",this);
        // تنظیم موقعیت و اندازه مناسب
        int y=200;
        Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
        Lphone->setGeometry(600, y, 300, 25);y=y+25+5;
        txtphone->setGeometry(600, y, 300, 40);y=y+30+30;
        pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;
        Lerror->setGeometry(600, y, 300, 25);
        pbnsign->setStyleSheet("color: white; background: red;");
        Lerror->setStyleSheet("color: red;");

    connect(pbnsign, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
}
void Forgotpswwindow::readInfo()
{
    QString phone= txtphone->toPlainText();
}

void Forgotpswwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        Menuwindow *n = new Menuwindow();
        n->show();
        this->close();
        break;
    }

    }

}
