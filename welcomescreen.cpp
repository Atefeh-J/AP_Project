// #include "welcomescreen.h"
// #include "ui_welcomescreen.h"

// WelcomeScreen::WelcomeScreen(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::WelcomeScreen)
// {
//     setFixedSize(800,600);
//     setWindowFlags(Qt::FramelessWindowHint);

//     QLabel* bg=new QLabel(this);
//     bg->setPixmap(QPixmap(":/images/background2.jpg").scaled(size()));
//     QMediaPlayer* player=new QMediaPlayer(this);
//     QAudioOutput* audioOutput=new QAudioOutput(this);
//     player->setAudioOutput(audioOutput);
//     player->setSource(QUrl::fromLocalFile(":/sounds/welcome.wav"));
//     player->play();
//     QTimer::singleShot(3000,this,&QDialog::accept);
//     ui->setupUi(this);
// }

// WelcomeScreen::~WelcomeScreen()
// {
//     delete ui;
// }
