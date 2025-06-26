#ifndef EDITWINDOW_H
#define EDITWINDOW_H

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
class Editwindow : public QWidget
{
    //QLabel* playerp;
    //Player player;
    QPixmap background;
    //QMovie* playerGif;
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
    //QVBoxLayout *mainLayout;

public:
    Editwindow(QWidget *parent = nullptr);
    ~Editwindow();

protected:
    void paintEvent(QPaintEvent* event) override;
};
#endif // EDITWINDOW_H
