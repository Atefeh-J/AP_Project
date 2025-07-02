#include "HistoryWindow.h"
HistoryWindow::HistoryWindow(Client *client,QString imagename ,QWidget *parent ) : QWidget(parent)
{
    setFixedSize(1500, 750);

    // چرخش تصویر
    background = QPixmap(imagename);
    QTransform transform;
    transform.rotate(90);
    background = background.transformed(transform, Qt::SmoothTransformation);

    //نام بازی
    // QLabel *gamenameL= new QLabel(this);
    // QPixmap  gamenameP(":/new/gamename.jpg");
    // gamenameP = gamenameP.scaledToWidth(400, Qt::SmoothTransformation);
    // gamenameL->setGeometry(550, 100, gamenameP.width(), gamenameP.height());
    // gamenameL->setPixmap(gamenameP);
    //جدول
    QLabel *tableL = new QLabel(this);
    QPixmap tableP(":/images/table.png");
    tableP = tableP.scaledToWidth(1000, Qt::SmoothTransformation);
    tableL->setGeometry(260, 150, 1000, 500);
    tableL->setPixmap(tableP);

    // تنظیم شفافیت 40% (60% opacity)
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    opacityEffect->setOpacity(0.6); // مقدار بین 0 (کاملاً شفاف) تا 1 (کاملاً مات)
    tableL->setGraphicsEffect(opacityEffect);

    // برای پس‌زمینه شفاف
    tableL->setAttribute(Qt::WA_TranslucentBackground);
    tableL->setStyleSheet("background: transparent;");
    setObjects();

    onSigninButtonClicked(client);
}
HistoryWindow::~HistoryWindow()
{}
void HistoryWindow:: paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), background);
    QWidget::paintEvent(event);
}
void HistoryWindow::setObjects()
{
    LOpponent=new QLabel("Opponent", this);
    LDate=new QLabel("Date", this);
    LLevel1=new QLabel("Level1", this);
    LLevel2=new QLabel("Level2", this);
    LLevel3=new QLabel("Level3", this);
    LResult=new QLabel("Result", this);
    // txtIP=new QLineEdit(this);
    // txtPort=new QLineEdit(this);
    //pbnconnect=new QPushButton("connect", this);

    int y=160;
    LOpponent->setGeometry(300, y, 300, 150);//y=y+25+5;
    LDate->setGeometry(465, y, 300, 150);//y=y+25+5;
    LLevel1->setGeometry(630, y, 300, 150);//y=y+25+5;
    LLevel2->setGeometry(795, y, 300, 150);//y=y+25+5;
    LLevel3->setGeometry(960, y, 300, 150);//y=y+25+5;
    LResult->setGeometry(1125, y, 300, 150);//y=y+25+5;

    LOpponent->setStyleSheet("font-size: 25pt;");
    LDate->setStyleSheet("font-size: 25pt;");
    LLevel1->setStyleSheet("font-size: 25pt;");
    LLevel2->setStyleSheet("font-size: 25pt;");
    LLevel3->setStyleSheet("font-size: 25pt;");
    LResult->setStyleSheet("font-size: 25pt;");

}
bool HistoryWindow::onSigninButtonClicked(Client *client) {
    bool loginSuccess = false;

    // قطع تمام اتصالات قبلی
    disconnect(client, &Client::responseReceived, nullptr, nullptr);

    // ایجاد اتصال جدید
    connect(client, &Client::responseReceived,
            [this, &loginSuccess, client](const QJsonObject &response) {
                // if (response["status"] == "success") {
                    loginSuccess = true;
                    qDebug()<<"history receved";
                    displayHistory(response);
            });

    QJsonObject loginRequest;
    loginRequest["action"] = "history";
    loginRequest["reccentusername"]=client->getUsername();
    client->sendRequest(loginRequest);

    return false;
}
void HistoryWindow::displayHistory(const QJsonObject &his)
{
    // پاکسازی محتوای قبلی
    clearHistoryDisplay();

    // بررسی وجود کلید History
    if (!his.contains("History")) {
        qDebug() << "No history data found";
        return;
    }

    QJsonArray historyArray = his["History"].toArray();

    // بررسی خالی بودن آرایه
    if (historyArray.isEmpty()) {
        LOpponent->setText("No game history available");
        return;
    }

    // ساخت متن برای نمایش
    QString opponentText="Opponent\n", dateText="Date\n", level1Text="Lavel1\n", level2Text="Level2\n", level3Text="Level3\n", resultText="Result\n";

    foreach (const QJsonValue &historyValue, historyArray) {
        if (!historyValue.isObject()) continue;

        QJsonObject historyObj = historyValue.toObject();

        // اضافه کردن اطلاعات هر بازی به متن مربوطه
        dateText += historyObj.value("Date").toString() + "\n";
        opponentText += historyObj.value("Opponent").toString() + "\n";
        level1Text += historyObj.value("Level1").toString() + "\n";
        level2Text += historyObj.value("Level2").toString() + "\n";
        level3Text += historyObj.value("Level3").toString() + "\n";
        resultText += historyObj.value("Result").toString() + "\n";
    }

    // تنظیم متن نهایی برای هر QLabel
    LOpponent->setText(opponentText);
    LDate->setText(dateText);
    LLevel1->setText(level1Text);
    LLevel2->setText(level2Text);
    LLevel3->setText(level3Text);
    LResult->setText(resultText);
}

void HistoryWindow::clearHistoryDisplay()
{
    LOpponent->clear();
    LDate->clear();
    LLevel1->clear();
    LLevel2->clear();
    LLevel3->clear();
    LResult->clear();
}
