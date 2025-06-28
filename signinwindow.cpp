#include "signinwindow.h"
SigninWindow::SigninWindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
SigninWindow::~SigninWindow()
{}

void SigninWindow::setObjects()
{
    Lpagename = new QLabel("sign in", this);
    Lusername = new QLabel("enter your username", this);
    Lpassword = new QLabel("enter your password", this);
    txtusername = new QTextEdit(this);
    txtpassword = new QTextEdit(this);
    pbnforgotpass = new QPushButton("forgot password", this);
    pbnsign = new QPushButton("signin", this);

    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
    Lusername->setGeometry(600, y, 300, 25);y=y+25+5;
    txtusername->setGeometry(600, y, 300, 40);y=y+40+10;
    Lpassword->setGeometry(600, y, 300, 25);y=y+25+5;
    txtpassword->setGeometry(600, y, 300, 40);y=y+40+10;
    pbnforgotpass->setGeometry(670, y, 150, 30);y=y+30+30;
    pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;

    pbnsign->setStyleSheet("color: white; background: red;");

    connect(pbnsign, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
    connect(pbnforgotpass, &QPushButton::clicked, this, [this]() {
        gotowindow(2);
    });

}
void SigninWindow::readInfo()
{
    QString username= txtusername->toPlainText();
    QString password= txtpassword->toPlainText();

    if (isEmptytxt(username)||isEmptytxt(password))
    {
        throw EmptyFieldException();
    }
    if (ContainInvalidCh(username)||ContainInvalidCh(password))
    {
        throw CharactersException();
    }
    if (username.contains(" ")||password.contains(" "))
    {
        throw CharactersException();
    }
}

void SigninWindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        try{
            readInfo();
            Menuwindow *n = new Menuwindow();
            n->show();
            this->close();
        }
        catch (const MyException& e)
        {
            Lerror->setText(e.getMessage());
            Lerror->show();

        }
        break;

    }
    case 2:
    {
        try{
            Forgotpswwindow *n = new Forgotpswwindow();
            n->show();
            this->close();
        }
        catch (const MyException& e)
        {
            Lerror->setText(e.getMessage());
            Lerror->show();

        }
        break;
    }
    }
}
