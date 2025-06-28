#ifndef Authserver_H
#define Authserver_H

#include "User.h"
#include <QMap>

class Authserver
{
    QMap<QString, User*> Users;

public:
    Authserver();
    bool registerUser(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email);
    bool authenticate(QString username, QString hashpassword);
    bool resetPassword(QString phone);
    void saveUserHistory();
    void loadUserHistory();
};

#endif // Authserver_H
