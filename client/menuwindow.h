#ifndef Menuwindow_H
#define Menuwindow_H

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
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "signinwindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include "mainwindow.h"
#include "beginwindow.h"
class Menuwindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QPushButton *pbnstartgame;
    QPushButton *pbneditinformation;
    QPushButton *pbnhistory;
    QPushButton *pbnsignout;
    //QLabel *Lerror;

public:
    Menuwindow(Client *client,QString imagename=":/images/menu.jpg" ,MainWindow *parent = nullptr);
    ~Menuwindow();
    virtual void setObjects(Client *client)override;
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice,Client *client) override;

};
#endif // Menuwindow_H
