#ifndef Menuwindow_H
#define Menuwindow_H

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
class Menuwindow : public QWidget
{
    //QLabel* playerp;
    //Player player;
    QPixmap background;
    //QMovie* playerGif;
    QLabel *Lpagename;
    QPushButton *pbnstartgame;
    QPushButton *pbneditinformation;
    QPushButton *pbnhistory;
    QPushButton *pbnsignout;
    QLabel *Lerror;
    //QVBoxLayout *mainLayout;

public:
    Menuwindow(QWidget *parent = nullptr);
    ~Menuwindow();

protected:
    void paintEvent(QPaintEvent* event) override;
};
#endif // Menuwindow_H
