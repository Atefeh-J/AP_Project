#include "forgotpswwindow.h"
Forgotpswwindow::Forgotpswwindow(Client *client,QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects(client);

}
Forgotpswwindow::~Forgotpswwindow()
{}

void Forgotpswwindow::setObjects(Client *client)
{
        Lpagename = new QLabel("forgot password", this);
        Lusername = new QLabel("enter your username", this);
        txtusername = new QLineEdit(this);
        Lphone = new QLabel("enter your phonenumber", this);
        txtphone = new QLineEdit(this);
        pbnsign = new QPushButton("signin", this);

        // تنظیم موقعیت و اندازه مناسب
        // int y=200;
        // Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;

        int y=200;
        Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
        Lusername->setGeometry(600, y, 300, 25);y=y+25+5;
        txtusername->setGeometry(600, y, 300, 40);y=y+40+10;
        Lphone->setGeometry(600, y, 300, 25);y=y+25+5;
        txtphone->setGeometry(600, y, 300, 40);y=y+40+10;
        pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;

        pbnsign->setStyleSheet("color: white; background: red;");


    connect(pbnsign, &QPushButton::clicked, this, [this,client]() {
        gotowindow(1,client);
    });
}
void Forgotpswwindow::readInfo()
{
    QString phone= txtphone->text();
    QString username=txtusername->text();
    if (isEmptytxt(phone)||isEmptytxt(username))
    {
        throw EmptyFieldException();
    }
    if (ContainInvalidCh(phone)||ContainInvalidCh(username))
    {
        throw CharactersException();
    }
    if (phone.contains(" "))
    {
        throw CharactersException();
    }
    if (phone.size() != 11||  !phone.startsWith("09"))
    {
        throw PhoneException();
    }
}

void Forgotpswwindow::gotowindow(int choice,Client *client)
{
    switch(choice)
    {
    case 1:
    {
        try{
            readInfo();
            // if(onSigninButtonClicked(client)){
            //     Menuwindow *n = new Menuwindow(client);
            //     n->show();
            //     this->close();
            // }
            onSigninButtonClicked(client);
        }

        catch (const MyException& e)
        {
            Lerror->setText(e.getMessage()); // بدون کوتیشن
            Lerror->show();

        }
        break;
    }

    }

}
// bool Forgotpswwindow::onSigninButtonClicked(Client *client) {
//     //Client *client = new Client(this);
//     bool loginSuccess = false; // حالت اولیه

//     // اتصال سیگنال قبل از ارسال درخواست
//     connect(client, &Client::responseReceived,
//             [this, &loginSuccess, client](const QJsonObject &response) {
//                 if (response["status"] == "success") {
//                     loginSuccess = true;
//                     Menuwindow *n = new Menuwindow(client);
//                     n->show();
//                     this->close();
//                 } else {
//                     Lerror->setText("Login failed");
//                     Lerror->show();
//                 }
//                 client->deleteLater(); // آزاد کردن حافظه
//             });

//     //client->connectToServer("127.0.0.1", 1029);

//     QJsonObject loginRequest;
//     loginRequest["action"] = "resetpassword";
//     loginRequest["phone"] = txtphone->text();

//     client->sendRequest(loginRequest);

//     // در اینجا نمی‌توانیم مقدار را برگردانیم چون پاسخ هنوز دریافت نشده
//     // باید منتظر بمانیم تا سیگنال responseReceived فراخوانی شود
//     return false; // مقدار موقت
// }

bool Forgotpswwindow::onSigninButtonClicked(Client *client) {
    bool loginSuccess = false;

    // قطع تمام اتصالات قبلی
    disconnect(client, &Client::responseReceived, nullptr, nullptr);

    // ایجاد اتصال جدید
    connect(client, &Client::responseReceived,
            [this, &loginSuccess, client](const QJsonObject &response) {
                if (response["status"] == "success") {
                    loginSuccess = true;
                    client->setUsername(txtusername->text());
                    Menuwindow *n = new Menuwindow(client);
                    n->show();
                    this->close();
                } else {
                    Lerror->setText("Login failed");
                    Lerror->show();
                }
            });

    QJsonObject loginRequest;
    loginRequest["action"] = "resetpassword";
    loginRequest["phone"] = txtphone->text();
    loginRequest["username"] = txtusername->text();
    client->sendRequest(loginRequest);

    return false;
}

// bool Forgotpswwindow::ContainInvalidCh(QString str)
// {
//     if (str.contains("#")||str.contains("!")||str.contains("^")||str.contains("&")||str.contains("*")||str.contains("\n")/*||str.contains("")*/)
//         return true;


//     return false;
// }
// bool Forgotpswwindow::isEmptytxt(QString str)
// {
//     if(str.isEmpty())
//         return true;
//     return false;
// }
