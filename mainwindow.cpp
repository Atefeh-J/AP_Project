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
    QPixmap  gamenameP(":/images/gamename.jpg");
    gamenameP = gamenameP.scaledToWidth(400, Qt::SmoothTransformation);
    gamenameL->setGeometry(550, 100, gamenameP.width(), gamenameP.height());
    gamenameL->setPixmap(gamenameP);
    //جدول
    QLabel *tableL = new QLabel(this);
    QPixmap tableP(":/images/table.png");
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


}
MainWindow::~MainWindow()
{}
void MainWindow:: paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);

    //map.displaymap(this);

    QWidget::paintEvent(event);
}
// void MainWindow::setBackground(QString imagename)
// {
//     setFixedSize(1500, 750);

//     // چرخش تصویر
//     background = QPixmap(imagename);
//     // QTransform transform;
//     // transform.rotate(90);
//     // background = background.transformed(transform, Qt::SmoothTransformation);

//     //نام بازی
//     QLabel *gamenameL= new QLabel(this);
//     QPixmap  gamenameP(":/images/gamename.jpg");
//     gamenameP = gamenameP.scaledToWidth(400, Qt::SmoothTransformation);
//     gamenameL->setGeometry(550, 100, gamenameP.width(), gamenameP.height());
//     gamenameL->setPixmap(gamenameP);
//     //جدول
//     QLabel *tableL = new QLabel(this);
//     QPixmap tableP(":/images/table.png");
//     tableP = tableP.scaledToWidth(400, Qt::SmoothTransformation);
//     tableL->setGeometry(550, 180, 400, 450);
//     tableL->setPixmap(tableP);

//     // تنظیم شفافیت 40% (60% opacity)
//     QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
//     opacityEffect->setOpacity(0.4); // مقدار بین 0 (کاملاً شفاف) تا 1 (کاملاً مات)
//     tableL->setGraphicsEffect(opacityEffect);

//     // برای پس‌زمینه شفاف
//     tableL->setAttribute(Qt::WA_TranslucentBackground);
//     tableL->setStyleSheet("background: transparent;");
// }
void MainWindow::setObjects()
{

}

void MainWindow::readInfo()
{

}

void MainWindow::gotowindow(int choice)
{

}
