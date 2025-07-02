#ifndef BEGINWINDOW_H
#define BEGINWINDOW_H


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
class Beginwindow : public MainWindow
{
    Q_OBJECT

    QPushButton *pbnsignin;
    QPushButton *pbnsignup;

public:
    Beginwindow(Client *client,QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Beginwindow();
    virtual void setObjects(Client *client)override;
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice,Client *client) override;

};
#endif // Beginwindow_H
