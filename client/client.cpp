
#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onError);
}

void Client::connectToServer(const QString &host, quint16 port)
{

    socket->connectToHost(host, port);
    if (socket->waitForConnected(3000)) {
        qDebug()<<"connected";
        //emit connected();
    } else {
        qDebug()<<"connected failed";
        //emit errorOccurred("Connection failed: " + socket->errorString());
    }
}

void Client::sendRequest(const QJsonObject &request)
{
    if (socket->state() == QTcpSocket::ConnectedState) {
        QByteArray data = QJsonDocument(request).toJson();
        socket->write(data);
        qDebug()<<"wrote\n"<<request;
    } else {
        emit errorOccurred("Not connected to server");
    }
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isNull()) {
        emit responseReceived(doc.object());
    }
}

void Client::onError(QAbstractSocket::SocketError socketError)
{
    emit errorOccurred("Socket error: " + socket->errorString());
}

QString Client::hashPassword(const QString &password)
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}
