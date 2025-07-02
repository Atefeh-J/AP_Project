
#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QCryptographicHash>
#include<QJsonDocument>
#include <QJsonObject>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    bool connectToServer(const QString &host, quint16 port);
    void sendRequest(const QJsonObject &request);
    QString hashPassword(const QString &password);

    QString getUsername();
    void setUsername(QString username);

signals:
    void connected();
    void responseReceived(const QJsonObject &response);
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    QString Username;
};

#endif // CLIENT_H
