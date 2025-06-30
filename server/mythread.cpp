#include "mythread.h"
#include "authserver.h"

MyThread::MyThread(qintptr socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{
    server = qobject_cast<AuthServer*>(parent);
    // if (server) {
    //     // استفاده از متدهای سرور
    // }
    //server=parent;
}

void MyThread::run()
{
    socket = new QTcpSocket();
    if (!socket->setSocketDescriptor(socketDescriptor)) {
        emit error(socket->error());
        return;
    }

    connect(socket, &QTcpSocket::readyRead, this, &MyThread::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyThread::disconnected);

    qDebug() << "Client connected:" << socketDescriptor;
    qDebug() <<"run\n";
    exec(); // شروع event loop
}

// void MyThread::readyRead()
// {
//     qDebug() << "Data from client:";
//     QByteArray data = socket->readAll();
//     qDebug() << "Data from client:" << data;
//     processRequest(data);
// }

// void MyThread::processRequest(const QByteArray &data)
// {
//     QJsonDocument doc = QJsonDocument::fromJson(data);
//     if (doc.isNull()) {
//         socket->write("Invalid JSON format");
//         return;
//     }
//     qDebug()<<data;
//     QJsonObject json = doc.object();
//     QString action = json["action"].toString();

//     if (action == "register") {
//         // پردازش ثبت‌نام
//     } else if (action == "login") {
//         // پردازش ورود
//     } else if (action == "reset_password") {
//         // پردازش بازیابی رمز عبور
//     } else {
//         socket->write("Invalid action");
//     }
// }
void MyThread::readyRead() {
    while (socket->bytesAvailable() > 0) { // ✅ حلقه while اضافه شود
        QByteArray data = socket->readAll();
        qDebug() << "Raw data received:";// << data;
        processRequest(data);
    }
}

void MyThread::processRequest(const QByteArray &data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        socket->write("{\"error\":\"Invalid JSON\"}");
        return;
    }

    QJsonObject json = doc.object();
    QString action = json["action"].toString();

    if (action == "register") {
        // پردازش ثبت‌نام
        QJsonObject response;
        if(server->registerUser(json["username"].toString(),json["password"].toString(),json["name"].toString(),json["lastname"].toString(),json["phone"].toString(),json["email"].toString()))
        {
            response["status"] = "success";
            response["message"] = "Registration successful";
        }
        else
        {
            response["status"] = "faild";
            response["message"] = "Registration faild";
        }
        socket->write(QJsonDocument(response).toJson());
    }

    else if (action == "login") {
        QJsonObject response;
        // پردازش ورود

        if(server->authenticate(json["username"].toString(),json["password"].toString()))
        {

            response["status"] = "success";
            response["message"] = "Registration successful";
        }
        else
        {
            response["status"] = "faild";
            response["message"] = "Registration faild";
        }
        socket->write(QJsonDocument(response).toJson());
    }
    else if (action == "resetpassword") {
        QJsonObject response;
        response["status"] = "success";
        response["message"] = "Registration successful";
        socket->write(QJsonDocument(response).toJson());
    }
    /////////////////////////////////
    else if (action == "updateinformation") {
        // پردازش ثبت‌نام
        QJsonObject response;
        if(server->updateinformationUser(json["username"].toString(),json["password"].toString(),json["name"].toString(),json["lastname"].toString(),json["phone"].toString(),json["email"].toString()))
        {
            response["status"] = "success";
            response["message"] = "Registration successful";
        }
        else
        {
            response["status"] = "faild";
            response["message"] = "Registration faild";
        }
        socket->write(QJsonDocument(response).toJson());
    }
    else
    {
        socket->write("Invalid action");
    }
}
void MyThread::disconnected()
{
    qDebug() << "Client disconnected:" << socketDescriptor;
    socket->deleteLater();
    quit(); // توقف event loop
}
