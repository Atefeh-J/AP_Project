#ifndef AUTHSERVER_H
#define AUTHSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QSet>
#include <QMutex>
#include "user.h"
#include "databasemanage.h"
#include "user.h"
class AuthServer : public QTcpServer
{
    Q_OBJECT

public:
    AuthServer(QObject *parent = nullptr);
    ~AuthServer();

    bool registerUser(const QString &username, const QString &hashedPassword,
                      const QString &name, const QString &lastname,
                      const QString &phone, const QString &email);
    bool authenticate(const QString &username, const QString &hashedPassword);
    bool editInfo(const QString &recentusername,const QString &username, const QString &hashedPassword,
                              const QString &name, const QString &lastname,
                              const QString &phone, const QString &email);
    bool resetPassword(const QString &username , const QString &phone);
    void saveUserHistory();
    void loadUserHistory();
    void notifyPlayersConnected();
    void startServer();

signals:
    void playersConnected();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    void processRequest(QTcpSocket *socket, const QByteArray &data);
    void sendResponse(QTcpSocket *socket, const QJsonObject &response);

    QMap<QString, User*> users;
    QSet<QTcpSocket*> activeSockets;
    QMutex socketsMutex;
    Databasemanage dbManager;
};

#endif // AUTHSERVER_H
