#include "Databasemanage.h"


Databasemanage::Databasemanage(/*QMap<QString, User*> *u*/) : filename(nullptr)/*, users(u)*/
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

bool Databasemanage::saveUserData(QMap<QString, User*> &users)
{
    // filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    // if(!filename->open(QIODevice::WriteOnly)) {  // اصلاح به QIODevice
    //     qWarning() << "Couldn't open file for reading!";
    //     //return false;
    // }
    filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    try{

        if(!filename->open(QIODevice::WriteOnly))
            throw openForWriteException();
    }
    catch (const MyException& e)
    {
        //qWarning() <<e.getMessage();
        return false;
    }

    QJsonArray usersArray;
    for(auto it = users.constBegin(); it != users.constEnd(); ++it) {
        QJsonObject userObject;
        userObject["Username"] = it.key();
        userObject["Password"] = it.value()->getHashPassword();
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

    QJsonObject mainObject;
    mainObject["Users"] = usersArray;

    QJsonDocument document(mainObject);
    filename->write(document.toJson());
    filename->close();

    return true;

}

bool Databasemanage::loadUserData(QMap<QString, User*> &users)
{
    qDebug()<<"hi2";
    // filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    // if(!filename->open(QIODevice::ReadOnly)) {  // اصلاح به QIODevice
    //     qWarning() << "Couldn't open file for reading!";
    //     //return false;
    // }
    filename = new QFile("D:\\projects\\AP\\ApProject\\server\\Usersinformation.json");
    try{

        if(!filename->open(QIODevice::ReadOnly))
            throw openForReadException();
    }
    catch (const MyException& e)
    {
        //qWarning() <<e.getMessage();
        return false;
    }

    bytes = filename->readAll();
    // document = QJsonDocument::fromJson(bytes);
    // if(document.isNull()) {
    //     qWarning() << "Failed to create JSON doc.";
    //     return false;
    // }
    try{
        document = QJsonDocument::fromJson(bytes);
        if(document.isNull())
            throw createJSONdocException();
    }
    catch (const MyException& e)
    {
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

        users.insert(username, user);
    }

    // if(users.contains("rri")) {
    //     qDebug() << users["rri"]->getUsername();
    //     qDebug() << users["rri"]->getHashPassword();
    //     qDebug() << users["rri"]->getName();
    //     qDebug() << users["rri"]->getLastname();
    //     qDebug() << users["rri"]->getEmail();
    //     qDebug() << users["rri"]->getPhone();
    //     qDebug() << users["rri"]->getGamehistory()[0].Opponent;
    // } else {
    //     qDebug() << "User Ali not found!";
    // }

    filename->close();
    return true;
}

bool Databasemanage::updateHistory(QMap<QString, User*> &users)
{
    // پیاده‌سازی بر اساس نیاز شما
    return true;
}
