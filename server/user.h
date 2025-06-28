#ifndef User_H
#define User_H

#include <QString>
#include <QDateTime>

struct GameHistory {
    QDateTime date;
    QString opponent;
    bool level1;
    bool level2;
    bool level3;
    bool isWinner;
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
    void addGameToHistory(GameHistory h);
    QString getUsername();
    QString getHashpasword();
    QString getPhone();
};

#endif // User_H
