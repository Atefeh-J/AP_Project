#ifndef User_H
#define User_H

#include <QString>
#include <QDateTime>

struct GameHistory {
    QString Date;
    QString Opponent;
    QString Level1;
    QString Level2;
    QString Level3;
    QString Result;
};

class User
{
    QString Username;
    QString HashedPassword;
    QString Name;
    QString Lastname;
    QString Phone;
    QString Email;
    QVector<GameHistory> history;
public:
    User(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email);
    void updateProfile(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email);
    void addGameToHistory(QString date,QString opponent,QString level1,QString level2,QString level3, QString result);
    QString getUsername();
    QString getHashPassword();
    QString getPhone();
    QString getName();
    QString getLastname();
    QString getEmail();
    QVector<GameHistory> getGamehistory();
    // QString getDate(int index);
    // QString getOpponent();
    // QString getLevel1();
    // QString getLevel2();
    // QString getLevel3();
    // QString getResult();
};

#endif // User_H
