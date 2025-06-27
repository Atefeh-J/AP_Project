#include "Editwindow.h"
Editwindow::Editwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
Editwindow::~Editwindow()
{}

void Editwindow::setObjects()
{
    QTransform transform;
    transform.rotate(90);
    background = background.transformed(transform, Qt::SmoothTransformation);

    // تنظیم موقعیت و اندازه مناسب
    Lpagename = new QLabel("edit information", this);
    Lusername = new QLabel("enter your new username", this);
    Lpassword = new QLabel("enter your new password", this);
    Lname = new QLabel("enter your new name" ,this);
    Llastname = new QLabel("enter your new lastname" ,this);
    Lemail = new QLabel("enter your new email" ,this);
    Lphone = new QLabel("enter your new phone" ,this);

    txtusername = new QTextEdit(this);
    txtpassword = new QTextEdit(this);
    txtname = new QTextEdit(this);
    txtlastname = new QTextEdit(this);
    txtemail = new QTextEdit(this);
    txtphone = new QTextEdit(this);

    pbnsignup = new QPushButton("edit", this);
    Lerror = new QLabel("h",this);
    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(730, y, 200, 25);y=y+25+10;  // عرض بیشتر برای متن
    Lname->setGeometry(600, y, 130, 25);y=y+25+5;
    txtname->setGeometry(600, y, 120, 40);y=y+40+10;
    Llastname->setGeometry(600, y, 130, 25);y=y+25+5;
    txtlastname->setGeometry(600, y, 120, 40);y=y+40+10;
    Lphone->setGeometry(600, y, 130, 25);y=y+25+5;
    txtphone->setGeometry(600, y, 120, 40);y=y+40+10;
    y=235;
    Lemail->setGeometry(785, y, 130, 25);y=y+25+5;
    txtemail->setGeometry(785, y, 120, 40);y=y+40+10;
    Lusername->setGeometry(785, y, 130, 25);y=y+25+5;
    txtusername->setGeometry(785, y, 120, 40);y=y+40+10;
    Lpassword->setGeometry(785, y, 130, 25);y=y+25+5;
    txtpassword->setGeometry(785, y, 120, 40);y=y+40+30;

    pbnsignup->setGeometry(670, y, 150, 30);y=y+30+20;
    Lerror->setGeometry(600, y, 300, 25);
    pbnsignup->setStyleSheet("color: white; background: red;");
    Lerror->setStyleSheet("color: red;");

    //     connect(pbnsignup,SIGNAL(clicked()),this,SLOT(readInfo()));
    connect(pbnsignup, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
}
void Editwindow::readInfo()
{
    QString username= txtusername->toPlainText();
    QString password= txtpassword->toPlainText();
    QString name= txtname->toPlainText();
    QString lastname= txtlastname->toPlainText();
    QString email= txtemail->toPlainText();
    QString phone= txtpassword->toPlainText();
}

void Editwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        {
            Menuwindow *n = new Menuwindow();
            n->show();
            this->close();
        }
    }
    }

}
