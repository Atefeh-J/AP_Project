#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
public:
    Card(int value, int type);
    int getSuit() const;
    int getValue() const;

private:
    int suit;
    int value;

};

#endif // CARD_H
