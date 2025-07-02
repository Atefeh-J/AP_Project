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
    qDebug()<<hashedPassword;
    return users[username]->getHashPassword() == hashedPassword;
}

bool AuthServer::editInfo(const QString &recentusername, const QString &username,
                          const QString &hashedPassword, const QString &name,
                          const QString &lastname, const QString &phone,
                          const QString &email)
{
    qDebug() << "authEdit" << username << ' ' << recentusername;

    // 1. بررسی وجود کاربر با نام قدیمی
    if (!users.contains(recentusername)) {
        qDebug() << "User not found:" << recentusername;
        return false;
    }

    // 2. اگر نام کاربری تغییر کرده و نام جدید تکراری است
    if (!username.isEmpty() && username != recentusername && users.contains(username)) {
        qDebug() << "Username already exists:" << username;
        return false;
    }

    User* user = users.value(recentusername);

    // 3. اعمال تغییرات
    if (!hashedPassword.isEmpty())
        user->setHashPassword(hashedPassword);
    if (!name.isEmpty())
        user->setName(name);
    if (!lastname.isEmpty())
        user->setLastname(lastname);
    if (!phone.isEmpty())
        user->setPhone(phone);
    if (!email.isEmpty())
        user->setEmail(email);

    // 4. اگر نام کاربری تغییر کرده
    if (!username.isEmpty() && username != recentusername) {
        // حذف از مپ با کلید قدیمی و اضافه با کلید جدید
        users.remove(recentusername);
        user->setUsername(username);
        users.insert(username, user);
    }

    qDebug() << "saving changes...";
    saveUserHistory();
    qDebug() << "changes saved";

    return true;
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

bool AuthServer::resetPassword(const QString &username , const QString &phone)
{
    // for (User *user : users) {
    //     if (user->getPhone() == phone) {
    //         //user->setPassword(newPassword);
    //         //saveUserHistory();
    //         return true;
    //     }
    // }
    for(auto x:users)
    {
        if(x->getUsername()==username)
        {
            if(x->getPhone()==phone)
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
        bool success = resetPassword(
            json["username"].toString(),
            json["phone"].toString()
            );
        response = {
            {"status", success ? "success" : "failed"},
            {"message", success ? "Password reset initiated": "Invalid credentials"}
        };
    }
    else if (action == "editInfo") {

        bool success = editInfo(
            json["recentusername"].toString(),
            json["username"].toString(),
            json["password"].toString(),
            json["name"].toString(),
            json["lastname"].toString(),
            json["phone"].toString(),
            json["email"].toString()
            );
        qDebug()<<success;
        // QString recentusername;
        // if(success&&!json["username"].toString().isEmpty())
        //     recentusername=json["username"].toString();
        // else
        //     recentusername= json["recentusername"].toString();
        response = {
            {"status", success ? "success" : "failed"},
            {"message", success ? "editInformation successful": "Edit failed"},
            //{"recentusername",recentusername}
        };
    }
    else if (action == "history") {
        QJsonObject userObject;
        QJsonArray historyArray;
        QVector<GameHistory> gamehistory = users[json["reccentusername"].toString()]->getGamehistory();

        for(const auto &historyItem : gamehistory) {
            QJsonObject historyObj;
            historyObj["Date"] = historyItem.Date;
            historyObj["Opponent"] = historyItem.Opponent;
            historyObj["Level1"] = historyItem.Level1;
            historyObj["Level2"] = historyItem.Level2;
            historyObj["Level3"] = historyItem.Level3;
            historyObj["Result"] = historyItem.Result;
            historyArray.append(historyObj);
        }
        userObject["History"] = historyArray;
        response=userObject;
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
