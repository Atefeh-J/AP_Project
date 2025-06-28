#ifndef Editwindow_H
#define Editwindow_H

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

#include "exceptions.h"
#include "signinwindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include "mainwindow.h"
class Editwindow : public MainWindow
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
    //QLabel *Lerror;

public:
    Editwindow(QString imagename=":/images/edit.jpg" ,MainWindow *parent = nullptr);
    ~Editwindow();
    virtual void setObjects()override;
    // bool ContainInvalidCh(QString str);
//bool isEmptytxt(QString str);

public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice) override;

};
#endif // Editwindow_H
