#include "card.h"

Card::Card(int value, int type):Value(value),Type(type)
{

}

int Card::getValue() const
{
    return Value;
}

int Card::getType() const
{
    return Type;
}
