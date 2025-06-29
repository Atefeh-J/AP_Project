#include "Databasemanage.h"


Databasemanage::Databasemanage(QMap<QString, User*> *u) : filename(nullptr), users(u)
{
    filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    if(!filename->open(QIODevice::ReadOnly)) {  // اصلاح به QIODevice
        qWarning() << "Couldn't open file for reading!";
        //return false;
    }
}

Databasemanage::~Databasemanage() {
    if(filename) {
        if(filename->isOpen()) {
            filename->close();
        }
        delete filename;
    }
}

bool Databasemanage::saveUserData()
{
    filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    if(!filename->open(QIODevice::WriteOnly)) {  // اصلاح به QIODevice
        qWarning() << "Couldn't open file for reading!";
        //return false;
    }

    QJsonArray usersArray;
    for(auto it = users->constBegin(); it != users->constEnd(); ++it) {
        QJsonObject userObject;
        userObject["Username"] = it.key();
        userObject["Password"] = it.value()->getHashpasword();
        userObject["Name"] = it.value()->getName();
        userObject["Lastname"] = it.value()->getLastname();
        userObject["Phone"] = it.value()->getPhone();
        userObject["Email"] = it.value()->getEmail();

        QJsonArray historyArray;
        QVector<GameHistory> gamehistory = it.value()->getGamehistory();

        for(const auto &historyItem : gamehistory) {
            QJsonObject historyObj;
            historyObj["Date"] = historyItem.Date;
            historyObj["Opponent"] = historyItem.Opponent;
            historyObj["Level1"] = historyItem.Level1;
            historyObj["Level2"] = historyItem.Level2;
            historyObj["Level3"] = historyItem.Level3;
            historyObj["Result"] = historyItem.Result;
            historyArray.append(historyObj);
        }

        userObject["History"] = historyArray;
        usersArray.append(userObject);
    }
    // QJsonArray usersArray;
    // for(auto it = users->constBegin(); it != users->constEnd(); ++it)
    // {
    //     QJsonObject userObject;
    //     userObject["Username"] = it.key();
    //     userObject["Password"] = it.value()->getHashpasword();
    //     userObject["Name"] = it.value()->getName();
    //     userObject["Lastname"] = it.value()->getLastname();
    //     userObject["Phone"] = it.value()->getPhone();
    //     userObject["Email"] = it.value()->getEmail();
    //     QJsonArray historyArray;
    //     QVector<GameHistory> gamehistory(it.value()->getGamehistory());
    //     for(int i=0;i<gamehistory.size();i++)
    //     {
    //         QJsonObject historyObj;
    //         historyObj["Date"] =gamehistory[i].Date;
    //         historyObj["Opponent"] =gamehistory[i].Opponent;
    //         historyObj["Level1"] =gamehistory[i].Level1;
    //         historyObj["Level2"] =gamehistory[i].Level2;
    //         historyObj["Level3"] =gamehistory[i].Level3;
    //         historyObj["Result"] =gamehistory[i].Result;
    //         historyArray.append(historyObj);

    //     }
    //     userObject["History"] =historyArray;
    //     // historyObj["Date"] =it.value()->getDate();
    //     // historyObj["Opponent"] =it.value()->getOpponent();
    //     // historyObj["Level1"] =it.value()->getLevel1();
    //     // historyObj["Level2"] =it.value()->getLevel2();
    //     // historyObj["Level3"] =it.value()->getLevel3();
    //     // historyObj["Result"] =it.value()->getResult();
    //     // userObject["History"] =historyObj;
    //     // تبدیل هر User به QJsonObject و اضافه به آرایه
    //     // این بخش بستگی به ساختار کلاس User شما دارد
    //     usersArray.append(userObject);
    // }

    QJsonObject mainObject;
    mainObject["Users"] = usersArray;

    QJsonDocument document(mainObject);
    filename->write(document.toJson());
    filename->close();

    return true;
    // QJsonArray usersArray;
    // for(auto it = users.constBegin(); it != users.constEnd(); ++it) {
    //     QJsonObject userObject;
    //     // تبدیل هر User به QJsonObject و اضافه به آرایه
    //     // این بخش بستگی به ساختار کلاس User شما دارد
    //     usersArray.append(userObject);
    // }

    // QJsonObject mainObject;
    // mainObject["Users"] = usersArray;

    // QJsonDocument doc(mainObject);
    // filename->write(doc.toJson());
    // filename->close();

    // return true;
}

bool Databasemanage::loadUserData()
{
    filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    if(!filename->open(QIODevice::ReadOnly)) {  // اصلاح به QIODevice
        qWarning() << "Couldn't open file for reading!";
        //return false;
    }
    bytes = filename->readAll();
    document = QJsonDocument::fromJson(bytes);
    if(document.isNull()) {
        qWarning() << "Failed to create JSON doc.";
        return false;
    }

    jsonObject = document.object();
    QJsonArray usersArray = jsonObject["Users"].toArray();

    foreach(const QJsonValue &value, usersArray) {
        QJsonObject userObj = value.toObject();
        QJsonArray historyArray = userObj["History"].toArray(); // تغییر به toArray()

        QString username = userObj["Username"].toString();
        User* user = new User(username, userObj["Password"].toString(),
                              userObj["Name"].toString(), userObj["Lastname"].toString(),
                              userObj["Phone"].toString(), userObj["Email"].toString());

        // پردازش تمام تاریخچه‌های کاربر
        foreach(const QJsonValue &historyValue, historyArray) {
            QJsonObject historyObj = historyValue.toObject();
            user->addGameToHistory(historyObj["Date"].toString(),
                                   historyObj["Opponent"].toString(),
                                   historyObj["Level1"].toString(),
                                   historyObj["Level2"].toString(),
                                   historyObj["Level3"].toString(),
                                   historyObj["Result"].toString());
        }

        users->insert(username, user);
    }

    filename->close();
    return true;
}

bool Databasemanage::updateHistory()
{
    // پیاده‌سازی بر اساس نیاز شما
    return true;
}
