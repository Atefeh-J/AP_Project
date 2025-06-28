// #include "client.h"

// client::client(QObject *parent) :
//     QObject(parent),
//     socket(new QTcpSocket(this))
// {
//     connect(socket, &QTcpSocket::connected, this, &client::onConnected);
//     connect(socket, &QTcpSocket::readyRead, this, &client::onReadyRead);
//     connect(socket, &QTcpSocket::disconnected, this, &client::onDisconnected);
// }

// client::~client()
// {
//     socket->deleteLater();  // destructor را پیاده‌سازی کنید
// }

// void client::startConnection(const QString &host, quint16 port)
// {
//     qDebug() << "Connecting to" << host << "on port" << port;
//     socket->connectToHost(host, port);
// }

// void client::sendMessage(const QString &message)
// {
//     if(socket->state() == QTcpSocket::ConnectedState) {
//         socket->write(message.toUtf8());
//     }
// }

// void client::onConnected()
// {
//     qDebug() << "Connected!";
//     emit connected();
// }

// void client::onReadyRead()
// {
//     QByteArray data = socket->readAll();
//     qDebug() << "Received:" << data;
//     emit messageReceived(data);
// }

// void client::onDisconnected()
// {
//     qDebug() << "Disconnected";
//     emit disconnected();
// }

// QString client::hashPassword(const QString &password) {
//     // تبدیل پسورد به بایت‌آرایه و ایجاد هش
//     QByteArray hash = QCryptographicHash::hash(
//         password.toUtf8(),
//         QCryptographicHash::Sha256
//         );

//     // تبدیل هش به فرمت hexadecimal
//     return hash.toHex();
// }
