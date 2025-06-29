#include "gamelogic.h"
#include <QMap>
#include <QSet>

QVector<Card> GameLogic::sortCards(QVector<Card> cards) {
    std::sort(cards.begin(), cards.end(), Card::compareCards);
    return cards;
}

QMap<Card::Rank, int> GameLogic::countRanks(const QVector<Card>& cards) {
    QMap<Card::Rank, int> count;
    for (const Card& card : cards) {
        count[card.rank()]++;
    }
    return count;
}

QMap<Card::Suit, int> GameLogic::countSuits(const QVector<Card>& cards) {
    QMap<Card::Suit, int> count;
    for (const Card& card : cards) {
        count[card.suit()]++;
    }
    return count;
}

bool GameLogic::hasNOfAKind(const QVector<Card>& cards, int n) {
    QMap<Card::Rank, int> rankCount = countRanks(cards);
    for (auto it = rankCount.begin(); it != rankCount.end(); ++it) {
        if (it.value() >= n) return true;
    }
    return false;
}

bool GameLogic::hasStraight(const QVector<Card>& cards) {
    QVector<Card> sorted = sortCards(cards);
    for (int i = 1; i < sorted.size(); ++i) {
        if (sorted[i].rank() != sorted[i-1].rank() - 1)
            return false;
    }
    return true;
}

// Pattern Detection Functions
bool GameLogic::isGoldenHand(const QVector<Card>& cards) {
    if (cards.size() != 5) return false;
    Card::Suit suit = cards[0].suit();
    QVector<Card::Rank> requiredRanks = { Card::Bitcoin, Card::King, Card::Queen, Card::Soldier, Card::Ten };

    for (int i = 0; i < 5; ++i) {
        if (cards[i].suit() != suit || cards[i].rank() != requiredRanks[i])
            return false;
    }
    return true;
}

bool GameLogic::isOrderHand(const QVector<Card>& cards) {
    if (cards.size() != 5) return false;
    Card::Suit suit = cards[0].suit();
    for (const Card& card : cards) {
        if (card.suit() != suit) return false;
    }
    return hasStraight(cards);
}

bool GameLogic::isFourPlusOne(const QVector<Card>& cards) {
    QMap<Card::Rank, int> rankCount = countRanks(cards);
    return rankCount.size() == 2 && (rankCount.values().contains(4));
}

bool GameLogic::isPenthouse(const QVector<Card>& cards) {
    QMap<Card::Rank, int> rankCount = countRanks(cards);
    return rankCount.size() == 2 && (rankCount.values().contains(3));
}

bool GameLogic::isMSC(const QVector<Card>& cards) {
    QMap<Card::Suit, int> suitCount = countSuits(cards);
    return suitCount.size() == 1;
}

bool GameLogic::isSeries(const QVector<Card>& cards) {
    if (cards.size() != 5) return false;
    QSet<Card::Suit> suits;
    for (const Card& card : cards) {
        suits.insert(card.suit());
    }
    return suits.size() == cards.size() && hasStraight(cards);
}

bool GameLogic::isThreePlusTwo(const QVector<Card>& cards) {
    QMap<Card::Rank, int> rankCount = countRanks(cards);
    return rankCount.size() == 2 && (rankCount.values().contains(3));
}

bool GameLogic::isDoublePair(const QVector<Card>& cards) {
    QMap<Card::Rank, int> rankCount = countRanks(cards);
    int pairCount = 0;
    for (int count : rankCount.values()) {
        if (count == 2) pairCount++;
    }
    return pairCount == 2;
}

bool GameLogic::isSinglePair(const QVector<Card>& cards) {
    return hasNOfAKind(cards, 2) && !isDoublePair(cards) && !isThreePlusTwo(cards);
}

// Pattern Comparison Functions
int GameLogic::comparePatterns(Pattern p1, Pattern p2) {
    if (p1 < p2) return 1;
    if (p1 > p2) return -1;
    return 0;
}

int GameLogic::compareSamePattern(Pattern pattern, const QVector<Card>& p1, const QVector<Card>& p2) {
    QVector<Card> sorted1 = sortCards(p1);
    QVector<Card> sorted2 = sortCards(p2);

    switch (pattern) {
    case GoldenHand:
        return sorted1[0].suit() > sorted2[0].suit() ? 1 : -1;

    case OrderHand:
    case Series:
        for (int i = 0; i < 5; ++i) {
            if (sorted1[i].rank() != sorted2[i].rank())
                return sorted1[i].rank() > sorted2[i].rank() ? 1 : -1;
        }
        return 0;

    case FourPlusOne: {
        QMap<Card::Rank, int> ranks1 = countRanks(p1);
        QMap<Card::Rank, int> ranks2 = countRanks(p2);
        Card::Rank quad1, quad2;
        for (auto it = ranks1.begin(); it != ranks1.end(); ++it) {
            if (it.value() == 4) quad1 = it.key();
        }
        for (auto it = ranks2.begin(); it != ranks2.end(); ++it) {
            if (it.value() == 4) quad2 = it.key();
        }
        return quad1 > quad2 ? 1 : -1;
    }

    case Penthouse:
    case ThreePlusTwo: {
        QMap<Card::Rank, int> ranks1 = countRanks(p1);
        QMap<Card::Rank, int> ranks2 = countRanks(p2);
        Card::Rank triple1, triple2;
        for (auto it = ranks1.begin(); it != ranks1.end(); ++it) {
            if (it.value() == 3) triple1 = it.key();
        }
        for (auto it = ranks2.begin(); it != ranks2.end(); ++it) {
            if (it.value() == 3) triple2 = it.key();
        }
        return triple1 > triple2 ? 1 : -1;
    }

    case DoublePair: {
        QVector<Card::Rank> pairs1, pairs2;
        QMap<Card::Rank, int> ranks1 = countRanks(p1);
        QMap<Card::Rank, int> ranks2 = countRanks(p2);

        for (auto it = ranks1.begin(); it != ranks1.end(); ++it) {
            if (it.value() == 2) pairs1.append(it.key());
        }
        for (auto it = ranks2.begin(); it != ranks2.end(); ++it) {
            if (it.value() == 2) pairs2.append(it.key());
        }

        std::sort(pairs1.begin(), pairs1.end(), std::greater<Card::Rank>());
        std::sort(pairs2.begin(), pairs2.end(), std::greater<Card::Rank>());

        for (int i = 0; i < pairs1.size(); ++i) {
            if (pairs1[i] != pairs2[i])
                return pairs1[i] > pairs2[i] ? 1 : -1;
        }
        return compareHighCards(p1, p2);
    }

    case SinglePair: {
        Card::Rank pair1, pair2;
        QMap<Card::Rank, int> ranks1 = countRanks(p1);
        QMap<Card::Rank, int> ranks2 = countRanks(p2);

        for (auto it = ranks1.begin(); it != ranks1.end(); ++it) {
            if (it.value() == 2) pair1 = it.key();
        }
        for (auto it = ranks2.begin(); it != ranks2.end(); ++it) {
            if (it.value() == 2) pair2 = it.key();
        }

        if (pair1 != pair2) return pair1 > pair2 ? 1 : -1;
        return compareHighCards(p1, p2);
    }

    case MSC:
        return compareHighCards(p1, p2);

    default: // MessyHand
        return compareHighCards(p1, p2);
    }
}

int GameLogic::compareHighCards(const QVector<Card>& p1, const QVector<Card>& p2) {
    QVector<Card> sorted1 = sortCards(p1);
    QVector<Card> sorted2 = sortCards(p2);

    for (int i = 0; i < sorted1.size(); ++i) {
        if (sorted1[i].rank() != sorted2[i].rank())
            return sorted1[i].rank() > sorted2[i].rank() ? 1 : -1;
        if (sorted1[i].suit() != sorted2[i].suit())
            return sorted1[i].suit() > sorted2[i].suit() ? 1 : -1;
    }
    return 0;
}

int GameLogic::determineWinner(const QVector<Card>& player1, const QVector<Card>& player2) {
    Pattern p1 = detectPattern(player1);
    Pattern p2 = detectPattern(player2);

    int patternComparison = comparePatterns(p1, p2);
    if (patternComparison != 0) return patternComparison;

    return compareSamePattern(p1, player1, player2);
}
GameLogic::Pattern GameLogic::detectPattern(const QVector<Card>& cards) {
    if (isGoldenHand(cards)) return GoldenHand;
    if (isOrderHand(cards)) return OrderHand;
    if (isFourPlusOne(cards)) return FourPlusOne;
    if (isPenthouse(cards)) return Penthouse;
    if (isMSC(cards)) return MSC;
    if (isSeries(cards)) return Series;
    if (isThreePlusTwo(cards)) return ThreePlusTwo;
    if (isDoublePair(cards)) return DoublePair;
    if (isSinglePair(cards)) return SinglePair;
    return MessyHand;
}
