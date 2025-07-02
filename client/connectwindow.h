#ifndef CONNECTWINDOW_H
#define CONNECTWINDOW_H
#include "beginwindow.h"
#include "client.h"

class Connectwindow :public MainWindow
{
    Q_OBJECT

    QLabel *LIP;
    QLineEdit *txtIP;
    QLabel *LPort;
    QLineEdit *txtPort;
    QPushButton *pbnconnect;
public:
    //Connectwindow();
    Connectwindow(QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Connectwindow();
    void setObjects(Client *client);
    void gotowindow(int choice,Client *client);
    bool onSigninButtonClicked(Client *client);
};

#endif // CONNECTWINDOW_H
