#ifndef DETECTWINNER_H
#define DETECTWINNER_H

#include "card.h"
#include <QVector>
#include <QMap>
#include <QString>
#include <QDebug>
class DetectWinner{
    QVector<Card> Player1;
    QVector<Card> Player2;
public:
    enum Pattern {
        GoldenHand,     // 0
        OrderHand,      // 1
        FourPlusOne,    // 2
        Penthouse,      // 3
        MSC,            // 4
        Series,         // 5
        ThreePlusTwo,   // 6
        DoublePair,     // 7
        SinglePair,     // 8
        MessyHand       // 9
    };
    DetectWinner(QVector<Card> &player1,QVector<Card> &player2);
    int whoIsWinner();
    int comparePatterns(Pattern p1, Pattern p2);
    Pattern detectPattern(QVector<Card> &cards);
    QVector<Card> sortCards(QVector<Card> cards);

    bool isGoldenHand(const QVector<Card>& cards);
    bool isOrderHand(const QVector<Card>& cards);
    bool isFourPlusOne(const QVector<Card>& cards);
    bool isPenthouse(const QVector<Card>& cards);
    bool isMSC(const QVector<Card>& cards);
    bool isSeries(const QVector<Card>& cards);
    bool isThreePlusTwo(const QVector<Card>& cards);
    bool isDoublePair(const QVector<Card>& cards);
    bool isSinglePair(const QVector<Card>& cards);

    int compareSamePattern(Pattern pattern);
    bool compareCards(const Card& a, const Card& b);
};

#endif // DETECTWINNER_H
