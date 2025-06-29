#ifndef CARD_H
#define CARD_H

#include <QString>
#include <vector>
#include <algorithm>

class Card {
    int Value;
    int Type;
public:
    Card(int value, int type);
    int getValue() const;
    int getType() const;


};

#endif // CARD_H
