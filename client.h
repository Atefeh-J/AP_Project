// #ifndef CLIENT_H
// #define CLIENT_H

// #include <QObject>
// #include <QTcpSocket>
// #include <QDebug>

// class client : public QObject
// {
//     Q_OBJECT

// public:
//     explicit client(QObject *parent = nullptr);
//     ~client();  // destructor را اضافه کنید

//     void startConnection(const QString &host, quint16 port);
//     void sendMessage(const QString &message);

// signals:  // بخش signals را اضافه کنید
//     void connected();
//     void messageReceived(const QByteArray &data);
//     void disconnected();

// private slots:
//     void onConnected();
//     void onReadyRead();
//     void onDisconnected();

// private:
//     QTcpSocket *socket;
// };

// #endif // CLIENT_H
//////////////////////////////////////////////////
