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
class Forgotpswwindow : public QWidget
{
    //QLabel* playerp;
    //Player player;
    QPixmap background;
    //QMovie* playerGif;
    QLabel *Lpagename;
    QLabel *Lphone;
    QTextEdit *txtphone;
    QPushButton *pbnsign;
    QLabel *Lerror;
    //QVBoxLayout *mainLayout;

public:
    Forgotpswwindow(QWidget *parent = nullptr);
    ~Forgotpswwindow();

protected:
    void paintEvent(QPaintEvent* event) override;
};
#endif // FORGOTPSWWINDOW_H
