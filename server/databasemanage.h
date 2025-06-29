#ifndef DATABASEMANAGE_H
#define DATABASEMANAGE_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QIODevice>  // اصلاح شده از QJsonDevice به QIODevice
#include <QDebug>
#include <QMap>

#include "user.h"
#include "exceptions.h"

class Databasemanage
{
    QFile *filename;
    QByteArray bytes;
    QJsonDocument document;
    QJsonObject jsonObject;
    User * user;
    QString username;

    QMap<QString, User*> *users;

public:
    Databasemanage(QMap<QString, User*> *u);
    ~Databasemanage();  // افزودن destructor برای مدیریت حافظه

    bool saveUserData();  // const و reference اضافه شد
    bool loadUserData();  // reference اضافه شد
    bool updateHistory();  // const و reference اضافه شد
};

#endif // DATABASEMANAGE_H
