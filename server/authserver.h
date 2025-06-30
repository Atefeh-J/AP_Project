#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QTcpServer>
#include <QMap>
#include "user.h"
#include "databasemanage.h"

class MyThread;

class AuthServer : public QTcpServer
{
    Q_OBJECT

public:
    AuthServer(QObject *parent = nullptr);
    bool registerUser(const QString &username, const QString &hashedPassword,
                      const QString &name, const QString &lastname,
                      const QString &phone, const QString &email);
    bool authenticate(const QString &username, const QString &hashedPassword);
    bool resetPassword(const QString &phone, const QString &newPassword);
    void saveUserHistory();
    void loadUserHistory();

    void startServer();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QMap<QString, User*> users;
    Databasemanage dbManager;
};

#endif // AUTHSERVER_H
