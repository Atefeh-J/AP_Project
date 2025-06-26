#include"signupwindow.h"
Signupwindow::Signupwindow(QWidget *parent) : QWidget(parent)
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

    QLabel *Lpagename;
    QLabel *Lusername;
    QLabel *Lname;
    QLabel *Llastname;
    QLabel *Lemail;
    QLabel *Lphone;
    QLabel *Lpassword;

    QTextEdit *txtusername;
    QTextEdit *txtname;
    QTextEdit *txtlastname;
    QTextEdit *txtemail;
    QTextEdit *txtphone;
    QTextEdit *txtpassword;

    QPushButton *pbnsignup;

    Lpagename = new QLabel("sign in", this);
    Lusername = new QLabel("enter your username", this);
    Lpassword = new QLabel("enter your password", this);
    Lname = new QLabel("enter your name" ,this);
    Llastname = new QLabel("enter your lastname" ,this);
    Lemail = new QLabel("enter your email" ,this);
    Lphone = new QLabel("enter your phone" ,this);

    txtusername = new QTextEdit(this);
    txtpassword = new QTextEdit(this);
    txtname = new QTextEdit(this);
    txtlastname = new QTextEdit(this);
    txtemail = new QTextEdit(this);
    txtphone = new QTextEdit(this);

    pbnsignup = new QPushButton("signin", this);
    Lerror = new QLabel("h",this);
    // تنظیم موقعیت و اندازه مناسب
    int y=200;
    Lpagename->setGeometry(730, y, 200, 25);y=y+25+10;  // عرض بیشتر برای متن
    Lname->setGeometry(600, y, 130, 25);y=y+25+5;
    txtname->setGeometry(600, y, 120, 40);y=y+40+10;
    Llastname->setGeometry(600, y, 130, 25);y=y+25+5;
    txtlastname->setGeometry(600, y, 120, 40);y=y+40+10;
    Lphone->setGeometry(600, y, 130, 25);y=y+25+5;
    txtphone->setGeometry(600, y, 120, 40);y=y+40+10;
    y=235;
    Lemail->setGeometry(785, y, 130, 25);y=y+25+5;
    txtemail->setGeometry(785, y, 120, 40);y=y+40+10;
    Lusername->setGeometry(785, y, 130, 25);y=y+25+5;
    txtusername->setGeometry(785, y, 120, 40);y=y+40+10;
    Lpassword->setGeometry(785, y, 130, 25);y=y+25+5;
    txtpassword->setGeometry(785, y, 120, 40);y=y+40+30;

    pbnsignup->setGeometry(670, y, 150, 30);y=y+30+20;
    Lerror->setGeometry(600, y, 300, 25);
    pbnsignup->setStyleSheet("color: white; background: red;");
    Lerror->setStyleSheet("color: red;");

}
Signupwindow::~Signupwindow()
{}
void Signupwindow:: paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);

    //map.displaymap(this);

    QWidget::paintEvent(event);
}
