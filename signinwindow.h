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
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include"mainwindow.h"
class SigninWindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lpassword;
    QTextEdit *txtusername;
    QTextEdit *txtpassword;
    QPushButton *pbnforgotpass;
    QPushButton *pbnsign;
    QLabel *Lerror;

public:
    SigninWindow(QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~SigninWindow();
    virtual void setObjects()override;
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice) override;
};
#endif // SIGNINWINDOW_H
