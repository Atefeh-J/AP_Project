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
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

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

    QTextEdit *txtusername;
    QTextEdit *txtname;
    QTextEdit *txtlastname;
    QTextEdit *txtemail;
    QTextEdit *txtphone;
    QTextEdit *txtpassword;

    QPushButton *pbnsignup;
    QLabel *Lerror;

public:
    Editwindow(QString imagename=":/images/edit.jpg" ,MainWindow *parent = nullptr);
    ~Editwindow();
    virtual void setObjects()override;
public slots:
    virtual void readInfo()override;
    virtual void gotowindow(int choice) override;

};
#endif // Editwindow_H
