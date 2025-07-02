#ifndef FORGOTPSWWINDOW_H
#define FORGOTPSWWINDOW_H
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

#include "exceptions.h"
#include "SigninWindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include"mainwindow.h"
#include"connectwindow.h"
//extern Client *client;

class Forgotpswwindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lphone;
    QLineEdit *txtusername;
    QLineEdit *txtphone;
    QPushButton *pbnsign;
    //QLabel *Lerror;
public:
    Forgotpswwindow(Client *client,QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Forgotpswwindow();
    void setObjects(Client *client)override;
    // bool ContainInvalidCh(QString str);
    // bool isEmptytxt(QString str);
    bool onSigninButtonClicked(Client *client);


public slots:
    void readInfo() override;
    void gotowindow(int choice,Client *client) override;
};
#endif // FORGOTPSWWINDOW_H
