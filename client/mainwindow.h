#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include<QMessageBox>

#include "client.h"
class MainWindow : public QWidget
{
    Q_OBJECT

// protected:
//     QPixmap background;
//     //QLabel *Lerror;

public:
    MainWindow(QString imagename ,QWidget *parent = nullptr);
    ~MainWindow();
    void setBackground(QString imagename);
    virtual void setObjects();
    bool ContainInvalidCh(QString str);
    bool isEmptytxt(QString str);

public slots:
    virtual void readInfo();
    virtual void gotowindow(int choice);

protected:
    QPixmap background;
        QLabel *Lerror;
    void paintEvent(QPaintEvent* event) override;
};
#endif // MAINWINDOW_H
