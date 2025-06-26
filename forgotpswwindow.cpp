#include"forgotpswwindow.h"
Forgotpswwindow::Forgotpswwindow(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1500, 750);
    // background = QPixmap(":/images/signin.jpg");
    // QTransform transform;
    // transform.rotate(90); // چرخش 90 درجه ساعتگرد
    // background = background.transformed(transform, Qt::SmoothTransformation);

    // چرخش تصویر
    background = QPixmap(":/images/sign.jpg");
    // QTransform transform;
    // transform.rotate(90);
    // background = background.transformed(transform, Qt::SmoothTransformation);

    // کاهش شفافیت
    // QPixmap semiTransparentBg(background.size());
    // semiTransparentBg.fill(Qt::transparent);
    // QPainter p(&semiTransparentBg);
    // p.setOpacity(0.85); // 85% مات
    // p.drawPixmap(0, 0, background);
    // p.end();
    // background = semiTransparentBg;
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


    Lpagename = new QLabel("forgot password", this);
    Lphone = new QLabel("enter your phonenumber", this);
    txtphone = new QTextEdit(this);
    pbnsign = new QPushButton("signin", this);
    Lerror = new QLabel("h",this);
    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(720, y, 200, 25);y=y+25+10;
    Lphone->setGeometry(600, y, 300, 25);y=y+25+5;
    txtphone->setGeometry(600, y, 300, 40);y=y+30+30;
    pbnsign->setGeometry(670, y, 150, 30);y=y+30+20;
    Lerror->setGeometry(600, y, 300, 25);
    pbnsign->setStyleSheet("color: white; background: red;");
    Lerror->setStyleSheet("color: red;");

}
Forgotpswwindow::~Forgotpswwindow()
{}
void Forgotpswwindow:: paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);

    //map.displaymap(this);

    QWidget::paintEvent(event);
}
