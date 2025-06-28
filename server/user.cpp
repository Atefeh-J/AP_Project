#include "User.h"

User::User(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email)
{
    Username=username;
    HashedPassword=hashedPassword;
    Name=name;
    Lastname=lastname;
    Phone=phone;
    Email=email;
}
void User::updateProfile(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email)
{
    Username=username;
    HashedPassword=hashedPassword;
    Name=name;
    Lastname=lastname;
    Phone=phone;
    Email=email;
}

void User::addGameToHistory(GameHistory h)
{
    history.push_back(h);
}
QString User::getUsername()
{
    return Username;
}

QString User::getHashpasword()
{
    return HashedPassword;
}
QString User::getPhone()
{
    return HashedPassword;
}
