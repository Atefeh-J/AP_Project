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
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "SigninWindow.h"
#include "forgotpswwindow.h"
#include"menuwindow.h"
#include"signupwindow.h"
#include"editwindow.h"
#include"mainwindow.h"
class Forgotpswwindow : public MainWindow
{
    Q_OBJECT

    QLabel *Lpagename;
    QLabel *Lphone;
    QTextEdit *txtphone;
    QPushButton *pbnsign;
    QLabel *Lerror;
public:
    Forgotpswwindow(QString imagename=":/images/sign.jpg" ,MainWindow *parent = nullptr);
    ~Forgotpswwindow();
    void setObjects()override;
public slots:
    void readInfo() override;
    void gotowindow(int choice) override;
};
#endif // FORGOTPSWWINDOW_H
