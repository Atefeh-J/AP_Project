#ifndef HistoryWindow_H
#define HistoryWindow_H

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
#include <QJsonArray>
#include <QJsonObject>
#include"client.h"
class HistoryWindow : public QWidget
{
    Q_OBJECT

    QLabel* LOpponent;
    QLabel* LDate;
    QLabel* LLevel1;
    QLabel* LLevel2;
    QLabel* LLevel3;
    QLabel* LResult;

public:
    HistoryWindow(Client *client,QString imagename=":/images/history.jpg" ,QWidget *parent = nullptr);
    ~HistoryWindow();
    void setBackground(QString imagename);
    virtual void setObjects();
    bool onSigninButtonClicked(Client *client);
    void displayHistory(const QJsonObject &his);
    void clearHistoryDisplay();

public slots:
              //virtual void readInfo();
              //virtual void gotowindow(int choice,Client *client);

protected:
    QPixmap background;
    QLabel *Lerror;
    void paintEvent(QPaintEvent* event) override;
};
#endif // HistoryWindow_H
