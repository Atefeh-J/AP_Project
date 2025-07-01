#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QRandomGenerator>
#include <card.h>
#include <detectwinner.h>
#include <QJsonArray>
#include <QTimer>

class Server:public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);
    bool start(quint16 port);
    void sendJson(QTcpSocket *socket, const QJsonObject &obj);

private slots:
    void onReadyRead();
    void onDisconnected();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private:
    static const int MAX_PLAYERS=2;
    QTcpSocket* players[MAX_PLAYERS]={nullptr,nullptr};
    int playerCount=0;
    int player1Card = -1;
    int player2Card = -1;
    void handleStarterCard(int val1,int val2);
    void handleSelectedCards(const QJsonObject& object,const QTcpSocket* socket);
    QVector<Card>chosenCards1;
    QVector<Card>chosenCards2;
    int roundCount=0;
    int turnCount=0;
    int player1winsCount=0;
    int player2winsCount=0;
    QTcpSocket* starterPlayer=nullptr;
    QTcpSocket* swapingPlayer=nullptr;
    bool IsCardPicked1=false;
    bool IsCardPicked2=false;
    int disconnectedPlayerIndex = -1;
    QTimer* disconnectTimer = nullptr;

};

#endif // SERVER_H
