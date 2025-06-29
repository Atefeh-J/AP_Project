#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

// #include <QCoreApplication>
// #include <QDebug>
// #include "gamelogic.h"
// #include "card.h"

// void printCards(const QVector<Card>& cards, const QString& playerName) {
//     qDebug() << playerName << "cards:";
//     for (const Card& card : cards) {
//         qDebug() << card.toString();
//     }
//     qDebug() << "Pattern:" << GameLogic::detectPattern(cards);
//     qDebug() << "----------------------------------";
// }

// int main(int argc, char *argv[]) {
//     QCoreApplication a(argc, argv);

//     // مثال 1: Golden Hand vs Order Hand
//     QVector<Card> player1 = {
//         Card(Card::Diamond, Card::Seven),
//         Card(Card::Gold, Card::Seven),
//         Card(Card::Coin, Card::Nine),
//         Card(Card::Dollar, Card::Nine),
//         Card(Card::Diamond, Card::Ten)
//     };

//     QVector<Card> player2 = {
//         Card(Card::Gold, Card::Nine),
//         Card(Card::Gold, Card::Nine),
//         Card(Card::Coin, Card::Seven),
//         Card(Card::Gold, Card::Seven),
//         Card(Card::Coin, Card::Five)
//     };

//     printCards(player1, "Player 1");
//     printCards(player2, "Player 2");

//     int winner = GameLogic::determineWinner(player1, player2);
//     qDebug() << "Winner is:" << (winner == 1 ? "Player 1" : "Player 2");
//     qDebug() << "==================================";

//     // مثال 2: FourPlusOne vs Penthouse
//     QVector<Card> player3 = {
//         Card(Card::Diamond, Card::King),
//         Card(Card::Gold, Card::King),
//         Card(Card::Dollar, Card::King),
//         Card(Card::Coin, Card::King),
//         Card(Card::Diamond, Card::Three)
//     };

//     QVector<Card> player4 = {
//         Card(Card::Diamond, Card::Ten),
//         Card(Card::Gold, Card::Ten),
//         Card(Card::Dollar, Card::Ten),
//         Card(Card::Coin, Card::Five),
//         Card(Card::Diamond, Card::Five)
//     };

//     printCards(player3, "Player 3");
//     printCards(player4, "Player 4");

//     winner = GameLogic::determineWinner(player3, player4);
//     qDebug() << "Winner is:" << (winner == 1 ? "Player 3" : "Player 4");

//     return a.exec();
// }
