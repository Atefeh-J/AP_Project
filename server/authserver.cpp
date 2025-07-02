#include "authserver.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

AuthServer::AuthServer(QObject *parent) : QTcpServer(parent)
{
    loadUserHistory();
}

AuthServer::~AuthServer()
{
    qDeleteAll(users);
    for (QTcpSocket *socket : activeSockets) {
        socket->close();
        socket->deleteLater();
    }
}

bool AuthServer::registerUser(const QString &username, const QString &hashedPassword,
                              const QString &name, const QString &lastname,
                              const QString &phone, const QString &email)
{
    if (users.contains(username)) {
        return false;
    }

    User *newUser = new User(username, hashedPassword, name, lastname, phone, email);
    users.insert(username, newUser);
    saveUserHistory();
    return true;
}

bool AuthServer::authenticate(const QString &username, const QString &hashedPassword)
{
    if (!users.contains(username)) {
        qDebug() << "User not found:" << username;
        return false;
    }
    return users[username]->getHashPassword() == hashedPassword;
}

void AuthServer::notifyPlayersConnected()
{
    QMutexLocker locker(&socketsMutex);

    if (activeSockets.size() < 2) {
        return;
    }

    QJsonObject response = {
        {"status", "info"},
        {"message", "Another player has connected"}
    };

    for (QTcpSocket *socket : activeSockets) {
        if (socket && socket->state() == QTcpSocket::ConnectedState) {
            sendResponse(socket, response);
        }
    }
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
    }
}

void AuthServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket = new QTcpSocket(this);
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        qDebug() << "Failed to set socket descriptor:" << socket->errorString();
        delete socket;
        return;
    }

    {
        QMutexLocker locker(&socketsMutex);
        activeSockets.insert(socket);
    }

    connect(socket, &QTcpSocket::readyRead, this, &AuthServer::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &AuthServer::onDisconnected);

    qDebug() << "New connection received:" << socketDescriptor;
}

void AuthServer::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    while (socket->bytesAvailable() > 0) {
        QByteArray data = socket->readAll();
        qDebug() << "Raw data received:" << data;
        processRequest(socket, data);
    }
}

void AuthServer::onDisconnected()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) return;

    {
        QMutexLocker locker(&socketsMutex);
        activeSockets.remove(socket);
    }

    socket->deleteLater();
    qDebug() << "Client disconnected";
}

void AuthServer::processRequest(QTcpSocket *socket, const QByteArray &data)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        sendResponse(socket, {
                                 {"status", "error"},
                                 {"message", "Invalid JSON format"}
                             });
        return;
    }

    QJsonObject json = doc.object();
    QString action = json["action"].toString();
    QJsonObject response;

    if (action == "register") {
        bool success = registerUser(
            json["username"].toString(),
            json["password"].toString(),
            json["name"].toString(),
            json["lastname"].toString(),
            json["phone"].toString(),
            json["email"].toString()
            );

        response = {
            {"status", success ? "success" : "failed"},
            {"message", success ? "Registration successful" : "Username already exists"}
        };
    }
    else if (action == "login") {
        bool success = authenticate(
            json["username"].toString(),
            json["password"].toString()
            );

        response = {
            {"status", success ? "success" : "failed"},
            {"message", success ? "Login successful" : "Invalid credentials"}
        };
    }
    else if (action == "resetpassword") {
        response = {
            {"status", "success"},
            {"message", "Password reset initiated"}
        };
    }
    else {
        response = {
            {"status", "error"},
            {"message", "Invalid action"}
        };
    }

    sendResponse(socket, response);
}

// void AuthServer::sendResponse(QTcpSocket *socket, const QJsonObject &response)
// {
//     if (socket && socket->state() == QTcpSocket::ConnectedState) {
//         socket->write(QJsonDocument(response).toJson());
//         socket->waitForBytesWritten();
//     }
// }
void AuthServer::sendResponse(QTcpSocket *socket, const QJsonObject &response)
{
    if (socket && socket->state() == QTcpSocket::ConnectedState) {
        QByteArray data = QJsonDocument(response).toJson();
        qint64 bytesWritten = socket->write(data);
        if (bytesWritten == -1) {
            qDebug() << "Write error:" << socket->errorString();
        } else if (bytesWritten < data.size()) {
            qDebug() << "Partial write occurred";
        }
        if (!socket->waitForBytesWritten(3000)) {
            qDebug() << "Failed to write all data:" << socket->errorString();
        }
        qDebug() << "Response sent successfully";
    } else {
        qDebug() << "Socket not connected, state:" << (socket ? socket->state() : -1);
    }
}
