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
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

#include "exceptions.h"
#include "signinwindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include "mainwindow.h"
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

    QTextEdit *txtusername;
    QTextEdit *txtname;
    QTextEdit *txtlastname;
    QTextEdit *txtemail;
    QTextEdit *txtphone;
    QTextEdit *txtpassword;

    QPushButton *pbnsignup;


public:
    Signupwindow(QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Signupwindow();
    virtual void setObjects()override;
    // bool ContainInvalidCh(QString str);
    // bool isEmptytxt(QString str);
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice) override;

};
#endif // Signupwindow_H
