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
Card& Card::operator=(const Card & v)
{
    Value=v.getValue();
    Type=v.getType();
    return *this;
}
