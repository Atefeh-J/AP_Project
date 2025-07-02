#include "connectwindow.h"

// Connectwindow::Connectwindow()
// {
//     Client *client = new Client(this);

//     client->connectToServer("127.0.0.1", 1029);
// }
Connectwindow::Connectwindow(QString imagename ,MainWindow *parent) : MainWindow(imagename,parent)
{
    Client *client;
    client = new Client(this);
    setObjects(client);

}
Connectwindow::~Connectwindow()
{}

void Connectwindow::setObjects(Client *client)
{
    LIP=new QLabel("IP", this);
    LPort=new QLabel("Port", this);
    txtIP=new QLineEdit(this);
    txtPort=new QLineEdit(this);
    pbnconnect=new QPushButton("connect", this);

    int y=200;
    //Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
    LIP->setGeometry(600, y, 300, 25);y=y+25+5;
    txtIP->setGeometry(600, y, 300, 40);y=y+40+10;
    LPort->setGeometry(600, y, 300, 25);y=y+25+5;
    txtPort->setGeometry(600, y, 300, 40);y=y+40+10;
    pbnconnect->setGeometry(670, y, 150, 30);y=y+30+30;
    //pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;

    pbnconnect->setStyleSheet("color: white; background: red;");

    connect(pbnconnect, &QPushButton::clicked, this, [this,client]() {
        gotowindow(1,client);
    });
    // connect(pbnforgotpass, &QPushButton::clicked, this, [this]() {
    //     gotowindow(2);
    // });

    //QLineEdit* txtpassword = new QLineEdit(this);
    //txtpassword->setEchoMode(QLineEdit::Password);
    //txtpassword->setStyleSheet("QLineEdit { font: 20pt; }");


}
void Connectwindow::gotowindow(int choice,Client *client)
{
    switch(choice)
    {
    case 1:
    {
        try{
            //readInfo();
            // if(onSigninButtonClicked())
            // {
            //     qDebug()<<"goto";
            //     Menuwindow *n = new Menuwindow();
            //     n->show();
            //     this->close();
            // }
            onSigninButtonClicked(client);
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

bool Connectwindow::onSigninButtonClicked(Client *client) {
    // Client *client = new Client(this);

    if(client->connectToServer(txtIP->text(), static_cast<quint16>(txtPort->text().toInt())))
    {
        Beginwindow *n = new Beginwindow(client);
        n->show();
        this->close();
        return true;
    }

    return false; // مقدار موقت
}
