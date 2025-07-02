#ifndef CARD_H
#define CARD_H

#include <QString>
#include <vector>
#include <algorithm>

class Card {
    int Value;
    int Type;
public:
    Card(int value=0, int type=0);
    int getValue() const;
    int getType() const;
    Card& operator=(const Card & v);

};

#endif // CARD_H
