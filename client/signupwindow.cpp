#include "signupwindow.h"
Signupwindow::Signupwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{

    setObjects();

}
Signupwindow::~Signupwindow()
{

}

void Signupwindow::setObjects()
{
    Lpagename = new QLabel("sign up", this);
    Lusername = new QLabel("enter your username", this);
    Lpassword = new QLabel("enter your password", this);
    Lname = new QLabel("enter your name" ,this);
    Llastname = new QLabel("enter your lastname" ,this);
    Lemail = new QLabel("enter your email" ,this);
    Lphone = new QLabel("enter your phone" ,this);

    txtusername = new QLineEdit(this);
    txtpassword = new QLineEdit(this);
    txtname = new QLineEdit(this);
    txtlastname = new QLineEdit(this);
    txtemail = new QLineEdit(this);
    txtphone = new QLineEdit(this);

    pbnsignup = new QPushButton("signup", this);

    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(730, y, 200, 25);y=y+25+10;
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

    pbnsignup->setStyleSheet("color: white; background: red;");

    connect(pbnsignup, &QPushButton::clicked, this, [this]() {
        gotowindow(1);
    });

    txtpassword->setEchoMode(QLineEdit::Password);

}
void Signupwindow::readInfo()
{
    QString username= txtusername->text();
    QString password= txtpassword->text();
    QString name= txtname->text();
    QString lastname= txtlastname->text();
    QString email= txtemail->text();
    QString phone= txtphone->text();

    if (isEmptytxt(username)||isEmptytxt(name)||isEmptytxt(lastname)||isEmptytxt(password)||isEmptytxt(email)||isEmptytxt(phone))
    {
        throw EmptyFieldException();
    }
    if (ContainInvalidCh(username)||ContainInvalidCh(name)||ContainInvalidCh(lastname)||ContainInvalidCh(password)||ContainInvalidCh(email)||ContainInvalidCh(phone))
    {
        throw CharactersException();
    }
    if (username.contains(" ")||password.contains(" ")||email.contains(" ")||phone.contains(" "))
    {
        throw CharactersException();
    }
    if (!email.contains("@") || !email.contains("."))
    {
        throw EmailException();
    }
    if (phone.size() != 11||  !phone.startsWith("09"))
    {
        throw PhoneException();
    }
    // if (database->usernameExists(username)) {
    //     throw DuplicateUsernameException(username);
    // }
}

void Signupwindow::gotowindow(int choice)
{
    switch(choice)
    {
    case 1:
    {
        try{
            readInfo();
            // if(onSignupButtonClicked()){
            //     SigninWindow *n = new SigninWindow();
            //     n->show();
            //     this->close();
            // }
            onSignupButtonClicked();
        }
        catch (const MyException& e)
        {
            Lerror->setText(e.getMessage()); // بدون کوتیشن
            Lerror->show();

        }
        break;
    }
    case 2:
    {
        // Signupwindow *n = new Signupwindow();
        // n->show();
        // this->close();
        // break;
    }
    }

}

// bool Signupwindow::onSignupButtonClicked()
// {
//     Client *client = new Client(this); // ✅ استفاده از اشیاء روی heap

//     // connect(client, &Client::responseReceived, [this](const QJsonObject &response) {
//     //     qDebug() << "Server response:" << response;
//     // });

//     client->connectToServer("127.0.0.1", 1029);

//     QJsonObject registerRequest;
//     registerRequest["action"] = "register";
//     registerRequest["username"] = txtusername->text();
//     registerRequest["password"] = client->hashPassword(txtpassword->text());
//     registerRequest["name"] = txtname->text();
//     registerRequest["lastname"] = txtlastname->text();
//     registerRequest["phone"] = txtphone->text();
//     registerRequest["email"] = txtemail->text();

//     client->sendRequest(registerRequest);


//     connect(client, &Client::responseReceived, [this](const QJsonObject &response) {
//         if (response["status"] == "success") {
//                 return true;
//         } else {
//             return false;
//         }
//     });
// }
bool Signupwindow::onSignupButtonClicked() {
    Client *client = new Client(this);
    bool loginSuccess = false; // حالت اولیه

    // اتصال سیگنال قبل از ارسال درخواست
    connect(client, &Client::responseReceived,
            [this, &loginSuccess, client](const QJsonObject &response) {
                if (response["status"] == "success") {
                    loginSuccess = true;
                    SigninWindow *n = new SigninWindow();
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
    loginRequest["action"] = "register";
    loginRequest["username"] = txtusername->text();
    loginRequest["password"] = client->hashPassword(txtpassword->text());
    loginRequest["name"] = txtname->text();
    loginRequest["lastname"] = txtlastname->text();
    loginRequest["phone"] = txtphone->text();
    loginRequest["email"] = txtemail->text();

    client->sendRequest(loginRequest);

    // در اینجا نمی‌توانیم مقدار را برگردانیم چون پاسخ هنوز دریافت نشده
    // باید منتظر بمانیم تا سیگنال responseReceived فراخوانی شود
    return false; // مقدار موقت
}
