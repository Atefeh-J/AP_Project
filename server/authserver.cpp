#include "authserver.h"
#include "mythread.h"

AuthServer::AuthServer(QObject *parent) : QTcpServer(parent)//, dbManager(&users)
{

    loadUserHistory(); // بارگذاری داده‌های کاربران از فایل

}

bool AuthServer::registerUser(const QString &username, const QString &hashedPassword,
                              const QString &name, const QString &lastname,
                              const QString &phone, const QString &email)
{
    if (users.contains(username)) {
        return false; // کاربر از قبل وجود دارد
    }

    User *newUser = new User(username, hashedPassword, name, lastname, phone, email);
    users.insert(username, newUser);
    saveUserHistory(); // ذخیره تغییرات در فایل
    return true;
}

bool AuthServer::authenticate(const QString &username, const QString &hashedPassword)
{

    if (!users.contains(username)) {
        qDebug()<<"myt2"<<username;
        return false;
    }

    return users[username]->getHashPassword() == hashedPassword;
}

bool AuthServer::resetPassword(const QString &phone, const QString &newPassword)
{
    for (User *user : users) {
        if (user->getPhone() == phone) {
            //user->setPassword(newPassword);
            //saveUserHistory();
            return true;
        }
    }
    return false;
}

void AuthServer::saveUserHistory()
{
    dbManager.saveUserData(users);
}

void AuthServer::loadUserHistory()
{
    dbManager.loadUserData(users);

}

void AuthServer::startServer()
{
    if (!listen(QHostAddress::Any, 1029)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port 1029";
        qDebug() <<"hi";

    }
}

void AuthServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "New connection received:" << socketDescriptor;
    qDebug() <<"hiincom\n";
    MyThread *thread = new MyThread(socketDescriptor, this);
    connect(thread, &MyThread::finished, thread, &MyThread::deleteLater);
    thread->start();
}
