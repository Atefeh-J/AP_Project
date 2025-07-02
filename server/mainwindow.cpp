#include "mainwindow.h"
MainWindow::MainWindow(QString imagename ,QWidget *parent ) : QWidget(parent)
{
    setFixedSize(1500, 750);

    // چرخش تصویر
    background = QPixmap(imagename);
    // QTransform transform;
    // transform.rotate(90);
    // background = background.transformed(transform, Qt::SmoothTransformation);

    //نام بازی
    QLabel *gamenameL= new QLabel(this);
    QPixmap  gamenameP(":/new/gamename.jpg");
    gamenameP = gamenameP.scaledToWidth(400, Qt::SmoothTransformation);
    gamenameL->setGeometry(550, 100, gamenameP.width(), gamenameP.height());
    gamenameL->setPixmap(gamenameP);
    //جدول
    QLabel *tableL = new QLabel(this);
    QPixmap tableP(":/new/table.png");
    tableP = tableP.scaledToWidth(400, Qt::SmoothTransformation);
    tableL->setGeometry(550, 180, 400, 450);
    tableL->setPixmap(tableP);

    // تنظیم شفافیت 40% (60% opacity)
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(0.4); // مقدار بین 0 (کاملاً شفاف) تا 1 (کاملاً مات)
    tableL->setGraphicsEffect(opacityEffect);

    // برای پس‌زمینه شفاف
    tableL->setAttribute(Qt::WA_TranslucentBackground);
    tableL->setStyleSheet("background: transparent;");
    setObjects();

}
MainWindow::~MainWindow()
{}
void MainWindow:: paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
    QWidget::paintEvent(event);
}
void MainWindow::setObjects()
{
    QLabel* LIP=new QLabel("IP Is '127.0.0.1'", this);
    QLabel* LPort=new QLabel("Port Is '1029'", this);
    // txtIP=new QLineEdit(this);
    // txtPort=new QLineEdit(this);
    //pbnconnect=new QPushButton("connect", this);

    int y=200;
    LIP->setGeometry(600, y, 300, 25);y=y+25+5;
    LPort->setGeometry(600, y, 300, 25);y=y+25+5;

    LIP->setStyleSheet("color: black; background: white;");
    LPort->setStyleSheet("color: black; background: white;");
}
