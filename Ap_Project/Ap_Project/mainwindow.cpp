#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    updateBackground();

    QString localIP = getLocalIP();
    ui->ipLabel->setText("Local IP: " + localIP);
    if (localIP == "IP not found!") {
        QMessageBox::critical(this, "Error", "No local network connection detected!");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateBackground();
    QMainWindow::resizeEvent(event);
    int x=(this->width()-ui->ipLabel->width())/2;
    int y=(this->height()-ui->ipLabel->height())/2;
    ui->ipLabel->move(x,y);
}

void MainWindow::updateBackground()
{
    QPixmap bg(":/images/image-2.jpg");
    QPixmap scaledBg=bg.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPalette p=this->palette();
    p.setBrush(QPalette::Window,scaledBg);
    this->setPalette(p);
}

QString MainWindow::getLocalIP()
{
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol &&
            address != QHostAddress(QHostAddress::LocalHost)) {
            return address.toString();
        }
    }
    return "IP not found!";
}
