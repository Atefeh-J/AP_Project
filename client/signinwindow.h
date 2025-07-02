#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

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
#include<QLineEdit>

#include "exceptions.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include"mainwindow.h"
#include"connectwindow.h"
//extern Client *client;

class SigninWindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lpassword;
    QLineEdit *txtusername;
    //QLineEdit *txtpassword;
    QPushButton *pbnforgotpass;
    QPushButton *pbnsign;
    //QLabel *Lerror;

    QString username;
    QString password;
    QLineEdit *txtpassword;

public:
    SigninWindow(Client *client,QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~SigninWindow();
    virtual void setObjects(Client *client)override;
    //*bool ContainInvalidCh(QString str);
    //bool isEmptytxt(QString str);
    bool onSigninButtonClicked(Client *client);
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice,Client *client) override;
};
#endif // SIGNINWINDOW_H
