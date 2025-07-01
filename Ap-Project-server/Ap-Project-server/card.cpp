
#include "card.h"

Card::Card(int s,int v):suit(s),value(v) {}

int Card::getSuit() const
{
    return suit;
}

int Card::getValue() const
{
    return value;
}
