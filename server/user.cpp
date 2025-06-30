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

void User::addGameToHistory(QString date,QString opponent,QString level1,QString level2,QString level3, QString result)
{
    GameHistory h;
    h.Date=date;
    h.Opponent=opponent;
    h.Level1=level1;
    h.Level2=level2;
    h.Level3=level3;
    h.Result=result;
    if(history.size() < 3) {
        history.push_back(h);
    } else {
        // حذف قدیمی‌ترین مورد و اضافه کردن جدید
        history.removeFirst();
        history.push_back(h);
    }
    // qDebug()<<history[0].Level1;
}
QString User::getUsername()
{
    return Username;
}

QString User::getHashPassword()
{
    return HashedPassword;
}
QString User::getPhone()
{
    return Phone;
}
QString User::getName()
{
    return Name;
}

QString User::getLastname()
{
    return Lastname;
}

QString User::getEmail()
{
    return Email;
}

QVector<GameHistory> User::getGamehistory()
{
    return history;
}
// QString User::getDate()
// {
//     return history[0].Date;
// }

// QString User::getOpponent()
// {
//     return history[0].Opponent;
// }

// QString User::getLevel1()
// {
//     return history[0].Level1;
// }

// QString User::getLevel2()
// {
//     return history[0].Level2;
// }

// QString User::getLevel3()
// {
//     return history[0].Level3;
// }

// QString User::getResult()
// {
//     return history[0].Result;
// }
