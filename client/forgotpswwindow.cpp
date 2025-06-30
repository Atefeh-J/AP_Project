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
        txtphone = new QLineEdit(this);
        pbnsign = new QPushButton("signin", this);

        // تنظیم موقعیت و اندازه مناسب
        int y=200;
        Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
        Lphone->setGeometry(600, y, 300, 25);y=y+25+5;
        txtphone->setGeometry(600, y, 300, 40);y=y+30+30;
        pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;

        pbnsign->setStyleSheet("color: white; background: red;");


    connect(pbnsign, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });
}
void Forgotpswwindow::readInfo()
{
    QString phone= txtphone->text();

    if (isEmptytxt(phone))
    {
        throw EmptyFieldException();
    }
    if (ContainInvalidCh(phone))
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

void Forgotpswwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        try{
            readInfo();
            // if(onSigninButtonClicked()){
            //     Menuwindow *n = new Menuwindow();
            //     n->show();
            //     this->close();
            // }
            onSigninButtonClicked();
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
bool Forgotpswwindow::onSigninButtonClicked() {
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
    loginRequest["action"] = "resetpassword";
    loginRequest["phone"] = txtphone->text();

    client->sendRequest(loginRequest);

    // در اینجا نمی‌توانیم مقدار را برگردانیم چون پاسخ هنوز دریافت نشده
    // باید منتظر بمانیم تا سیگنال responseReceived فراخوانی شود
    return false; // مقدار موقت
}

// bool Forgotpswwindow::onSigninButtonClicked()
// {
//     Client *client = new Client(this); // ✅ استفاده از اشیاء روی heap

//     // connect(client, &Client::responseReceived, [this](const QJsonObject &response) {
//     //     qDebug() << "Server response:" << response;
//     // });

//     client->connectToServer("127.0.0.1", 1029);

//     QJsonObject registerRequest;
//     registerRequest["action"] = "resetpassword";
//     registerRequest["phone"] = txtphone->text();

//     client->sendRequest(registerRequest);

//     connect(client, &Client::responseReceived, [this](const QJsonObject &response) {
//         if (response["status"] == "success") {
//             return true;
//         } else {
//             return false;
//         }
//     });
// }

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
