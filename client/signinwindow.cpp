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
    txtusername = new QLineEdit(this);
    txtpassword = new QLineEdit(this);
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

    //QLineEdit* txtpassword = new QLineEdit(this);
    txtpassword->setEchoMode(QLineEdit::Password);
    //txtpassword->setStyleSheet("QLineEdit { font: 20pt; }");



}
void SigninWindow::readInfo()
{
    username= txtusername->text();
    // password= txtpassword->text();
    password=txtpassword->text();

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
            // if(onSigninButtonClicked())
            // {
            //     qDebug()<<"goto";
            //     Menuwindow *n = new Menuwindow();
            //     n->show();
            //     this->close();
            // }
            onSigninButtonClicked();
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
// bool SigninWindow::onSigninButtonClicked()
// {
//     Client *client = new Client(this); // ✅ استفاده از اشیاء روی heap

//     // connect(client, &Client::responseReceived, [this](const QJsonObject &response) {
//     //     qDebug() << "Server response:" << response;
//     // });

//     client->connectToServer("127.0.0.1", 1029);

//     QJsonObject registerRequest;
//     registerRequest["action"] = "login";
//     registerRequest["username"] = txtusername->text();
//     registerRequest["password"] = client->hashPassword(txtpassword->text());

//     client->sendRequest(registerRequest);

//     connect(client, &Client::responseReceived, [this](const QJsonObject &response) {

//         if (response["status"] == "success") {

//             return true;
//         } else {
//                 qDebug()<<"onb";
//             return false;

//         }
//     });
// }
bool SigninWindow::onSigninButtonClicked() {
    Client *client = new Client(this);
    bool loginSuccess = false; // حالت اولیه

    // اتصال سیگنال قبل از ارسال درخواست
    connect(client, &Client::responseReceived,
            [this, &loginSuccess, client](const QJsonObject &response) {
                if (response["status"] == "success") {
                    loginSuccess = true;
                    Menuwindow *n = new Menuwindow();
                    n->show();
                    this->close();
                } else {
                    Lerror->setText("Login failed");
                    Lerror->show();
                }
                client->deleteLater(); // آزاد کردن حافظه
            });

    client->connectToServer("127.0.0.1", 1029);

    QJsonObject loginRequest;
    loginRequest["action"] = "login";
    loginRequest["username"] = txtusername->text();
    loginRequest["password"] = client->hashPassword(txtpassword->text());

    client->sendRequest(loginRequest);

    // در اینجا نمی‌توانیم مقدار را برگردانیم چون پاسخ هنوز دریافت نشده
    // باید منتظر بمانیم تا سیگنال responseReceived فراخوانی شود
    return false; // مقدار موقت
}
