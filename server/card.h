#ifndef CARD_H
#define CARD_H

#include <QString>
#include <vector>
#include <algorithm>

class Card {
public:
    enum Suit { Diamond, Gold, Dollar, Coin };
    enum Rank {
        Bitcoin = 14, King = 13, Queen = 12, Soldier = 11,
        Ten = 10, Nine = 9, Eight = 8, Seven = 7,
        Six = 6, Five = 5, Four = 4, Three = 3, Two = 2
    };

    Card(Suit suit, Rank rank) : m_suit(suit), m_rank(rank) {}

    Suit suit() const { return m_suit; }
    Rank rank() const { return m_rank; }

    QString toString() const {
        QString suitStr;
        switch (m_suit) {
        case Diamond: suitStr = "Diamond"; break;
        case Gold:    suitStr = "Gold";    break;
        case Dollar:  suitStr = "Dollar";  break;
        case Coin:    suitStr = "Coin";    break;
        }

        QString rankStr;
        switch (m_rank) {
        case Bitcoin: rankStr = "Bitcoin"; break;
        case King:   rankStr = "King";   break;
        case Queen:  rankStr = "Queen";  break;
        case Soldier: rankStr = "Soldier"; break;
        default:     rankStr = QString::number(m_rank); break;
        }

        return rankStr + " of " + suitStr;
    }

    static bool compareCards(const Card& a, const Card& b) {
        if (a.rank() != b.rank())
            return a.rank() > b.rank();
        return a.suit() > b.suit();
    }

private:
    Suit m_suit;
    Rank m_rank;
};

#endif // CARD_H
