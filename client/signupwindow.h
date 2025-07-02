#ifndef Signupwindow_H
#define Signupwindow_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QPainter>
#include <QMovie>
#include <QTransform>
#include <QTimer>
#include<QVector>
#include <QGraphicsOpacityEffect>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include"client.h"
#include "exceptions.h"
#include "signinwindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include "mainwindow.h"
#include"connectwindow.h"

//extern Client *client;
class Signupwindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lname;
    QLabel *Llastname;
    QLabel *Lemail;
    QLabel *Lphone;
    QLabel *Lpassword;

    QLineEdit *txtusername;
    QLineEdit *txtname;
    QLineEdit *txtlastname;
    QLineEdit *txtemail;
    QLineEdit *txtphone;
    QLineEdit *txtpassword;

    QPushButton *pbnsignup;


public:
    Signupwindow(Client *client,QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Signupwindow();
    virtual void setObjects(Client *client)override;
    // bool ContainInvalidCh(QString str);
    // bool isEmptytxt(QString str);
    bool onSignupButtonClicked(Client *client);

public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice,Client *client) override;

};
#endif // Signupwindow_H
