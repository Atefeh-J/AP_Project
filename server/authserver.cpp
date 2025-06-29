#include "authserver.h"


Authserver::Authserver()
{

}

bool Authserver::registerUser(QString username, QString hashedPassword, QString name, QString lastname, QString phone, QString email)
{
    // بررسی وجود کاربر
    if (Users.contains(username)) {
        return false; // کاربر از قبل وجود دارد
    }

    User *u = new User(username, hashedPassword, name, lastname, phone, email);
    Users.insert(username, u);
    return true;
}

bool Authserver::authenticate(QString username, QString hashpassword)
{
    for(const auto &x:Users)
    {
        if(x->getUsername()==username && x->getHashpasword()==hashpassword)
            return 1;
    }
    return 0;
}

bool Authserver::resetPassword(QString phone)
{
    for(const auto &x:Users)
    {
        if(x->getPhone()==phone)
            return 1;
    }
    return 0;
}

void Authserver::saveUserHistory()
{

}

void Authserver::loadUserHistory()
{

}
