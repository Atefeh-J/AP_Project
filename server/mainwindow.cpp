#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //qDebug()<<"hi";
    QMap<QString, User*> u;
    Databasemanage d(&u);
    d.loadUserData();
    if(u.contains("rri")) {
        qDebug() << u["rri"]->getUsername();
        qDebug() << u["rri"]->getHashpasword();
        qDebug() << u["rri"]->getName();
        qDebug() << u["rri"]->getLastname();
        qDebug() << u["rri"]->getEmail();
        qDebug() << u["rri"]->getPhone();
        qDebug() << u["rri"]->getGamehistory()[0].Opponent;
    } else {
        qDebug() << "User Ali not found!";
    }
    qDebug()<<"hi";
    //d.saveUserData();
}

MainWindow::~MainWindow()
{
    delete ui;
}
