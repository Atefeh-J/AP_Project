#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "card.h"
#include <QVector>

class GameLogic {
public:
    enum Pattern {
        GoldenHand,     // 1
        OrderHand,      // 2
        FourPlusOne,    // 3
        Penthouse,      // 4
        MSC,            // 5
        Series,         // 6
        ThreePlusTwo,   // 7
        DoublePair,     // 8
        SinglePair,     // 9
        MessyHand       // 10
    };

    static Pattern detectPattern(const QVector<Card>& cards);
    static int comparePatterns(Pattern p1, Pattern p2);
    static int compareSamePattern(Pattern pattern, const QVector<Card>& p1, const QVector<Card>& p2);
    static int determineWinner(const QVector<Card>& player1, const QVector<Card>& player2);

private:
    static bool isGoldenHand(const QVector<Card>& cards);
    static bool isOrderHand(const QVector<Card>& cards);
    static bool isFourPlusOne(const QVector<Card>& cards);
    static bool isPenthouse(const QVector<Card>& cards);
    static bool isMSC(const QVector<Card>& cards);
    static bool isSeries(const QVector<Card>& cards);
    static bool isThreePlusTwo(const QVector<Card>& cards);
    static bool isDoublePair(const QVector<Card>& cards);
    static bool isSinglePair(const QVector<Card>& cards);

    static QVector<Card> sortCards(QVector<Card> cards);
    static int compareHighCards(const QVector<Card>& p1, const QVector<Card>& p2);

    // Helper functions
    static QMap<Card::Rank, int> countRanks(const QVector<Card>& cards);
    static QMap<Card::Suit, int> countSuits(const QVector<Card>& cards);
    static bool hasNOfAKind(const QVector<Card>& cards, int n);
    static bool hasStraight(const QVector<Card>& cards);
};

#endif // GAMELOGIC_H
