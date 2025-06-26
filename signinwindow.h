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
class SigninWindow : public QWidget
{
    //QLabel* playerp;
    //Player player;
    QPixmap background;
    //QMovie* playerGif;
    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lpassword;
    QTextEdit *txtusername;
    QTextEdit *txtpassword;
    QPushButton *pbnforgotpass;
    QPushButton *pbnsign;
    QLabel *Lerror;
    //QVBoxLayout *mainLayout;

public:
    SigninWindow(QWidget *parent = nullptr);
    ~SigninWindow();

protected:
    void paintEvent(QPaintEvent* event) override;
};
#endif // SIGNINWINDOW_H
