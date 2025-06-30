#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

#include"authserver.h"
class MyThread : public QThread
{
    Q_OBJECT

public:
    explicit MyThread(qintptr socketDescriptor, QObject *parent = nullptr);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

public slots:
    void readyRead();
    void disconnected();

private:
    AuthServer *server;
    QTcpSocket *socket;
    qintptr socketDescriptor;
    void processRequest(const QByteArray &data);
};

#endif // MYTHREAD_H
