#include "server.h"

Server::Server(QObject* parent):QTcpServer(parent)
{
    disconnectTimer = new QTimer(this);
    disconnectTimer->setSingleShot(true);
    connect(disconnectTimer, &QTimer::timeout, this, [this](){
        QJsonObject msg;
        msg["type"] = "game_terminated";
        msg["winner"] = "nobody";
        if(disconnectedPlayerIndex==0)
        {
            msg["loser"]="player1";
            sendJson(players[1],msg);
        }
        else if(disconnectedPlayerIndex==1)
        {
            msg["loser"]="player2";
            sendJson(players[0],msg);
        }

        for (int i = 0; i < MAX_PLAYERS; ++i)
        {
            if(players[i])
            {
                players[i]->disconnectFromHost();
                players[i] = nullptr;
            }
        }
        playerCount = 0;
        roundCount = 0;
        turnCount = 0;
        player1winsCount = 0;
        player2winsCount = 0;
        player1Card = -1;
        player2Card = -1;
        starterPlayer = nullptr;
        swapingPlayer = nullptr;
        chosenCards1.clear();
        chosenCards2.clear();
        IsCardPicked1 = false;
        IsCardPicked2 = false;
        disconnectedPlayerIndex = -1;
        disconnectTimer->stop();
    });
}

bool Server::start(quint16 port)
{
    if (!listen(QHostAddress::Any, port))
    {
        qCritical() << "Server could not start:" << errorString();
        return false;
    }
    qDebug() << "Server listening on port" << port;
    return true;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    if (disconnectedPlayerIndex == -1 || playerCount >= 2) {
        QTcpSocket *temp = new QTcpSocket(this);
        temp->setSocketDescriptor(socketDescriptor);
        temp->write("Server full\n");
        temp->disconnectFromHost();
        temp->deleteLater();
        return;
    }
    if(disconnectedPlayerIndex != -1)
    {
        if (players[disconnectedPlayerIndex] != nullptr)
        {
            QTcpSocket* temp = new QTcpSocket(this);
            temp->setSocketDescriptor(socketDescriptor);
            temp->write("Player already connected\n");
            temp->disconnectFromHost();
            temp->deleteLater();
            return;
        }

        players[disconnectedPlayerIndex] = new QTcpSocket(this);
        players[disconnectedPlayerIndex]->setSocketDescriptor(socketDescriptor);

        connect(players[disconnectedPlayerIndex], &QTcpSocket::readyRead, this, &Server::onReadyRead);
        connect(players[disconnectedPlayerIndex], &QTcpSocket::disconnected, this, &Server::onDisconnected);

        playerCount++;

        disconnectTimer->stop();
        QJsonObject msg,message;
        msg["type"] = "player_reconnected";
        message["type"]="reconnection";
        if(disconnectedPlayerIndex==0)
        {
            sendJson(players[1],msg);
            sendJson(players[0],message);
        }
        else if(disconnectedPlayerIndex==1)
        {
            sendJson(players[0],msg);
            sendJson(players[1],message);
        }
        disconnectedPlayerIndex = -1;
        return;
    }

    int idx = (players[0] == nullptr) ? 0 : 1;
    players[idx] = new QTcpSocket(this);
    players[idx]->setSocketDescriptor(socketDescriptor);
    qDebug()<<"connected\n";

    connect(players[idx], &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(players[idx], &QTcpSocket::disconnected, this, &Server::onDisconnected);
    playerCount++;

    if(playerCount == 1)
    {
        QJsonObject message;
        message["type"] = "waiting";
        message["message"] = "Waiting for another player to join for starting the poffer game...";
        sendJson(players[idx],message);
    }

    if(playerCount == 2)
    {
        QJsonObject message;
        message["type"] = "start";
        message["message"] = "Game is staring now!";
        for(int i=0;i<MAX_PLAYERS;++i)
        {
            sendJson(players[i],message);
        }
    }

}

void Server::handleStarterCard(int val1,int val2)
{
    QJsonObject startMsg;
    startMsg["type"] = "starter_decision";
    if (val1 > val2)
    {
        startMsg["starter"] = "player1";
        starterPlayer = players[0];
    }
    else if (val2 > val1)
    {
        startMsg["starter"] = "player2";
        starterPlayer = players[1];
    }
    else
    {
        int r = QRandomGenerator::global()->bounded(2);
        if (r == 0)
        {
            startMsg["starter"] = "player1";
            starterPlayer = players[0];
        }
        else
        {
            startMsg["starter"] = "player2";
            starterPlayer = players[1];
        }
    }
    sendJson(players[0], startMsg);
    sendJson(players[1], startMsg);
    player1Card = -1;
    player2Card = -1;
}

void Server::handleSelectedCards(const QJsonObject &object,const QTcpSocket* socket)
{
    QJsonArray cardArray=object.value("cards").toArray();
    if(cardArray.size()!=6)
    {
        qWarning()<<"Wrong number of cards in selected_cards part!";//Ask AI what to add after it
        return;
    }

    QJsonObject chosenCard=object["chosen_card"].toObject();
    Card card(chosenCard["suit"].toInt(),chosenCard["value"].toInt());
    if(socket==players[0])
    {
        chosenCards1.append(card);
        QJsonObject msg;
        msg["type"]="selected_cards";
        msg["cards"]=cardArray;
        sendJson(players[1],msg);
        starterPlayer=players[1];
    }
    else if(socket==players[1])
    {
        chosenCards2.append(card);
        QJsonObject msg;
        msg["type"]="selected_cards";
        msg["cards"]=cardArray;
        sendJson(players[0],msg);
        starterPlayer=players[0];
    }
    // else
    // {
    //     qWarning() << "Sender is not a valid QTcpSocket!";
    //     return;
    // }
}

void Server::sendJson(QTcpSocket *socket, const QJsonObject &obj)
{
    if (!socket)
    {
        qWarning() << "sendJson called, but sender is not a valid QTcpSocket!";
        return;
    }
    QJsonDocument doc(obj);
    socket->write(doc.toJson(QJsonDocument::Compact));
    socket->write("\n");
}

void Server::onReadyRead()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket != players[0] && socket != players[1]) {
        qWarning() << "Unknown socket tried to send a messgae!";
        return;
    }
    if (!socket)
    {
        qWarning() << "onReadyRead called, but sender is not a valid QTcpSocket!";
        return;
    }

    QByteArray data = socket->readAll();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "JSON is not an object!";
        return;
    }

    QJsonObject obj = doc.object();
    if(!obj.contains("type"))
    {
        qWarning() << "Wrong Json message!";
        return;
    }

    QString type = obj.value("type").toString();
    if(/*type.compare("show_initial_card",Qt::CaseInsensitive)*/type == "show_initial_card")
    {
        if (!obj.contains("card") || !obj["card"].isObject()) {
            qWarning() << "Wrong Json message in show_initial_card part!";
            return;
        }
        QJsonObject cardObj;
        cardObj=obj.value("card").toObject();
        int cardValue = cardObj.value("value").toInt();
        if (socket == players[0]) {
            player1Card = cardValue;
        } else if (socket == players[1]) {
            player2Card = cardValue;
        }

        if (player1Card != -1 && player2Card != -1) {
            handleStarterCard(player1Card, player2Card);
        }
    }
    if(type == "selected_cards")
    {
        if(turnCount>5)
        {
            qWarning()<<"Can't hand anymore cards to select!";//Ask AI what to add after it
            return;
        }
        if(starterPlayer!=nullptr && socket!=starterPlayer)
        {
            qWarning()<<"Wrong player is starting the game!";//Ask AI what to add after it
            return;
        }
        if (!obj.contains("cards") || !obj["cards"].isArray() || !obj.contains("chosen_card"))
        {
            qWarning()<<"Wrong Json message in selected_cards part!";//Ask AI what to add after it
            return;
        }
        if(!obj["chosen_card"].isObject())
        {
            qWarning()<<"Wrong Json format of the chosen card in selected_cards part!";//Ask AI what to add after it
            return;
        }

        handleSelectedCards(obj,socket);
        ++turnCount;
    }
    if(type == "decide_round_winner")
    {
        if(roundCount>3)
        {
            qWarning()<<"More rounds can't happen!";//Ask AI what to add after it
            return;
        }
        DetectWinner detecting(chosenCards1,chosenCards2);
        int winner=detecting.whoIsWinner();
        turnCount=0;
        starterPlayer=nullptr;
        chosenCards1.clear();
        chosenCards2.clear();
        if(winner == 1)
        {
            ++player1winsCount;
        }
        if(winner == 2)
        {
            ++player2winsCount;
        }
        if(player1winsCount>=2)
        {
            QJsonObject msg;
            msg["type"]="decide_round_winner";
            msg["winner"]="player1";
            msg["loser"]="player2";
            sendJson(players[0],msg);
            sendJson(players[1],msg);
            roundCount=0;
            player1winsCount=0;
            player2winsCount=0;
        }
        else if(player2winsCount>=2)
        {
            QJsonObject msg;
            msg["type"]="decide_round_winner";
            msg["winner"]="player2";
            msg["loser"]="player1";
            sendJson(players[1],msg);
            sendJson(players[0],msg);
            roundCount=0;
            player1winsCount=0;
            player2winsCount=0;
        }
    }
    if(type=="swap_cards_between_two_players")
    {
        if(turnCount==5)
        {
            qWarning()<<"Can't swap cards in the fifth turn!";//Ask AI what to add after it
            return;
        }
        if(socket==players[0])
        {
            QJsonObject msg;
            msg["type"]="request_for_swaping_cards_between_two_players";
            sendJson(players[1],msg);
            swapingPlayer=players[0];
        }
        else if(socket==players[1])
        {
            QJsonObject msg;
            msg["type"]="request_for_swaping_cards_between_two_players";
            sendJson(players[0],msg);
            swapingPlayer=players[1];
        }
    }
    if(type=="answer_to_swap_cards_between_two_players")
    {
        if(turnCount==5)
        {
            qWarning()<<"Can't swap cards in the fifth turn!";//Ask AI what to add after it
            return;
        }
        if(socket==swapingPlayer)
        {
            qWarning()<<"The other player must answer the request for swaping cards!";//Ask AI what to add after it
            return;
        }
        if(!obj.contains("answer"))
        {
            qWarning()<<"Wrong Json message in answer_to_swap_cards_between_two_players part!";//Ask AI what to add after it
            return;
        }

        QString answer = obj["answer"].toString().toLower();
        if(answer=="no")
        {
            QJsonObject msg;
            msg["type"]="answer_to_swap_cards_between_two_players";
            msg["answer"]="no";
            sendJson(swapingPlayer,msg);
            swapingPlayer=nullptr;
        }
        else if(answer=="yes")
        {
            QJsonObject msg;
            msg["type"]="answer_to_swap_cards_between_two_players";
            msg["answer"]="yes";
            sendJson(swapingPlayer,msg);
            swapingPlayer=nullptr;
        }
        else
        {
            qWarning()<<"Invalid answer to swap cards between two players!";//Ask AI what to add after it
            return;
        }
    }
    if(type=="card_picked_to_swap")
    {
        if(turnCount==5)
        {
            qWarning()<<"Can't swap cards in the fifth turn!";//Ask AI what to add after it
            return;
        }
        if(!obj.contains("card_picked"))
        {
            qWarning()<<"Wrong Json message in card_picked_to_swap part!";//Ask AI what to add after it
            return;
        }

        QJsonObject msg1;
        msg1["type"]="card_picked_to_swap";
        QJsonObject msg2;
        msg2["type"]="card_picked_to_swap";
        QJsonObject card1,card2;
        if(socket==players[0])
        {
            IsCardPicked1=true;
            card1["card_picked"]=obj["card_picked"];
            // msg1["card_picked"]=obj["card_picked"];

        }
        else if(socket==players[1])
        {
            IsCardPicked2=true;
            // msg2["card_picked"]=obj["card_picked"];
            card2["card_picked"]=obj["card_picked"];
        }

        msg1["card_picked"]=card1;
        msg2["card_picked"]=card2;
        if(IsCardPicked1 != false && IsCardPicked2 != false)
        {
            IsCardPicked1=false;
            IsCardPicked2=false;
            sendJson(players[1],msg1);
            sendJson(players[0],msg2);
        }
    }
    if(type=="stop_game")
    {
        if(socket==players[0])
        {
            QJsonObject msg;
            msg["type"]="stop_game";
            sendJson(players[1],msg);
        }
        else if(socket==players[1])
        {
            QJsonObject msg;
            msg["type"]="stop_game";
            sendJson(players[0],msg);
        }
    }
    if(type=="decide_loser_because_of_fault")
    {
        chosenCards1.clear();
        chosenCards2.clear();
        roundCount=0;
        turnCount=0;
        player1winsCount=0;
        player2winsCount=0;
        starterPlayer=nullptr;
        swapingPlayer=nullptr;
        IsCardPicked1=false;
        IsCardPicked2=false;
        QString loser;
        if(socket==players[0])
        {
            loser="player1";
        }
        else if(socket==players[1])
        {
            loser="player2";
        }
        QJsonObject msg;
        msg["type"] = "decide_loser_because_of_fault";
        msg["winner"] = "nobody";
        msg["loser"] = loser;
        sendJson(players[0],msg);
        sendJson(players[1],msg);
    }
}

void Server::onDisconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
    {
        qWarning() << "sendJson called, but sender is not a valid QTcpSocket!";
        return;
    }

    if(players[0] == socket)
    {
        disconnectedPlayerIndex = 0;
        QJsonObject msg;
        msg["type"] = "component_disconnected";
        // msg["message"] = "Player disconnected, waiting 60 seconds for reconnection...";
        sendJson(players[1],msg);
        disconnectTimer->start(60000);
    }
    else if(players[1] == socket)
    {
        disconnectedPlayerIndex = 1;
        QJsonObject msg;
        msg["type"] = "component_disconnected";
        // msg["message"] = "Player disconnected, waiting 60 seconds for reconnection...";
        sendJson(players[0],msg);
        disconnectTimer->start(60000);
    }

}
