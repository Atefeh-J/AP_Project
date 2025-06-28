#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    updateBackground();
    // view=new QGraphicsView(this);
    // view->setGeometry(this->rect());
    // scene=new CardScene(this);
    // view->setScene(scene);
    // view->setSceneRect(0,0,width(),height());
    // view->setRenderHint(QPainter::Antialiasing);
    // view->setStyleSheet("background:transparent");
    // view->setFrameStyle(QFrame::NoFrame);
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->raise();
    // connect(scene, &CardScene::goToMainWindow, this, &MainWindow::showMainContent);
    // scene->startRandomSelection();

    // CardScene* scene13 = new CardScene(this);
    // setupCardScene(scene13);
    // scene13->startRandomSelection();

    CardScene* scene = new CardScene(this);
    setupCardScene(scene);

    connect(scene, &CardScene::firstPhaseFinished, this, [this]() {
    });

    connect(scene, &CardScene::allPhasesFinished, this, [this]() {
        QTimer::singleShot(3000, this, &MainWindow::showMainContent);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateBackground();
    QMainWindow::resizeEvent(event);
}

void MainWindow::updateBackground()
{
    QPixmap bg(":/images/background.jpeg");
    QPixmap scaledBg=bg.scaled(this->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPalette p=this->palette();
    p.setBrush(QPalette::Window,scaledBg);
    this->setPalette(p);
}

void MainWindow::showMainContent() {
    view->hide();


    // QLabel* label = new QLabel("🎉 کارت انتخاب شد!", this);
    // label->setAlignment(Qt::AlignCenter);
    // label->setStyleSheet("font-size: 24px; color: white;");
    // label->setGeometry(this->rect());
    // label->raise();
}

void MainWindow::setupCardScene(CardScene* sceneObject)
{
    // if (view)
    //     view->deleteLater();
    // view = new QGraphicsView(this);
    // view->setGeometry(this->rect());
    // scene1 = sceneObject;
    // view->setScene(scene1);
    // view->setSceneRect(0, 0, width(), height());
    // view->setRenderHint(QPainter::Antialiasing);
    // view->setStyleSheet("background: transparent;");
    // view->setFrameStyle(QFrame::NoFrame);
    // view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // view->raise();
    // connect(scene1, &CardScene::goToMainWindow, this, &MainWindow::showMainContent);

    if (view) {
        view->deleteLater();
        view = nullptr;
    }
    view = new QGraphicsView(this);
    view->setGeometry(this->rect());
    view->setScene(sceneObject);
    view->setSceneRect(0, 0, width(), height());
    view->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    view->setStyleSheet("background: transparent; border: none;");
    view->setFrameShape(QFrame::NoFrame);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);

    view->raise();
    connect(sceneObject, &CardScene::goToMainWindow, this, &MainWindow::showMainContent);
}

