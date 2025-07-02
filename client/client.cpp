#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onError);
}

bool Client::connectToServer(const QString &host, quint16 port)
{

    socket->connectToHost(host, port);
    if (socket->waitForConnected(3000)) {
        qDebug()<<"connected";
        return true;
        //emit connected();
    } else {
        qDebug()<<"connected failed";
        return false;
        //emit errorOccurred("Connection failed: " + socket->errorString());
    }
}

void Client::sendRequest(const QJsonObject &request)
{
    qDebug()<<"wr";
    if (socket->state() == QTcpSocket::ConnectedState) {
        QByteArray data = QJsonDocument(request).toJson();
        socket->write(data);
        qDebug()<<"wrote\n"<<request;
    } else {
        qDebug()<< "Not connected to server";
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
QString Client::getUsername()
{
    return Username;
}

void Client::setUsername(QString username)
{
    Username=username;
}
