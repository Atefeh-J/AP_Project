#include "detectwinner.h"

DetectWinner::DetectWinner(QVector<Card> &player1,QVector<Card> &player2):Player1(player1),Player2(player2)
{
    Player1 = sortCards(Player1);
    Player2 = sortCards(Player2);
}

int DetectWinner::whoIsWinner()
{
    {
        Pattern p1 = detectPattern(Player1);
        Pattern p2 = detectPattern(Player2);
        qDebug()<<p1;
        qDebug()<<p2;
        int patternComparison = comparePatterns(p1, p2);
        if (patternComparison != 0) return patternComparison;

        return compareSamePattern(p1);
    }
}
int DetectWinner::comparePatterns(Pattern p1, Pattern p2) {
    if (p1 < p2) return 1;
    if (p1 > p2) return 2;
    return 0;
}
DetectWinner::Pattern DetectWinner::detectPattern(QVector<Card> &cards)
{
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

QVector<Card> DetectWinner::sortCards(QVector<Card> cards) {
    std::sort(cards.begin(),cards.end(),[=](const Card& a, const Card& b){
        if(a.getValue()!=b.getValue())
            return a.getValue()> b.getValue();
        return a.getType()>b.getType();
    });
    return cards;
}
bool DetectWinner::isGoldenHand(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    int type=cards[0].getType();
    //sortCards(cards);
    for (int i = 0; i < 5; ++i) {
        if (cards[i].getType() != type || cards[i].getValue() != 14-i)
            return false;
    }
    return true;
}

bool DetectWinner::isOrderHand(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    int type=cards[0].getType();
    //sortCards(cards);
        for (int i = 1; i < 5; ++i) {
        if (cards[i].getType() != type || cards[i].getValue()-cards[i-1].getValue()!=-1)
            return false;
    }
    return true;
}

bool DetectWinner::isFourPlusOne(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    QMap<int,int> equalv;
    for (int i = 0; i < 5; ++i)
    {
        equalv[cards[i].getValue()]++;
    }
    for(auto x:equalv)
    {
        if(x==4)
            return true;
    }
    return false;
}

bool DetectWinner::isPenthouse(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    QMap<int,int> equalv;
    for (int i = 0; i < 5; ++i)
    {
        equalv[cards[i].getValue()]++;
    }
    for(auto x:equalv)
    {
        if(x==3)
        {
            for(auto y:equalv)
            {
                if(y==2)
                    return true;
            }
        }
    }
    return false;
}

bool DetectWinner::isMSC(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    int type=cards[0].getType();
    for (int i = 1; i < 5; ++i) {
        if (cards[i].getType() != type)
            return false;
    }
    return true;
}

bool DetectWinner::isSeries(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    //sortCards(cards);
    for (int i = 1; i < 5; ++i) {
        if (cards[i].getValue()-cards[i-1].getValue()!=-1)
            return false;
    }
    return true;
}

bool DetectWinner::isThreePlusTwo(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    QMap<int,int> equalv;
    for (int i = 0; i < 5; ++i)
    {
        equalv[cards[i].getValue()]++;
    }
    for(auto x:equalv)
    {
        if(x==3)
        {
            return true;
        }
    }
    return false;
}

bool DetectWinner::isDoublePair(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    QMap<int,int> equalv;
    for (int i = 0; i < 5; ++i)
    {
        equalv[cards[i].getValue()]++;
    }
    for(auto x:equalv)
    {
        if(x==2)
        {
            for(auto y:equalv)
            {
                if(y==2 && x!=y)
                    return true;
            }
        }
    }
    return false;
}

bool DetectWinner::isSinglePair(const QVector<Card>& cards)
{
    if (cards.size() != 5)
        return false;
    QMap<int,int> equalv;
    for (int i = 0; i < 5; ++i)
    {
        equalv[cards[i].getValue()]++;
    }
    for(auto x:equalv)
    {
        if(x==2)
        {
            return true;
        }
    }
    return false;
}

bool DetectWinner::compareCards(const Card& a, const Card& b) {
    if(a.getValue()!=b.getValue())
        return a.getValue()> b.getValue();
    return a.getType()>b.getType();
}
int DetectWinner::compareSamePattern(Pattern pattern)
{
    switch (pattern)
    {
        case GoldenHand:
            if(compareCards(Player1[0],Player2[0]))
                    return 1;
            return 2;
        break;
        case OrderHand:
            if(compareCards(Player1[0],Player2[0]))
                return 1;
            return 2;
            break;

        case FourPlusOne:{
            QMap<int,int> e1,e2;
            int c1,c2;
            for (int i = 0; i < 5; ++i)
            {
                if(++e1[Player1[i].getValue()] >1)
                    c1=Player1[i].getValue();
                if(++e2[Player2[i].getValue()] >1)
                    c2=Player2[i].getValue();
            }
            if(c1>c2)
                return 1;
            return 2;
        break;}
        case Penthouse:{
            QMap<int,int> e1,e2;
            int c1,c2;
            for (int i = 0; i < 5; ++i)
            {
                if(++e1[Player1[i].getValue()]==3)
                    c1=Player1[i].getValue();
                if(++e2[Player2[i].getValue()]==3)
                    c2=Player2[i].getValue();
            }
            if(c1>c2)
                return 1;
            return 2;
            break;}

        case MSC:
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getValue()> Player2[i].getValue())
                    return 1;
                if(Player1[i].getValue()< Player2[i].getValue())
                    return 2;
            }
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getType()> Player2[i].getType())
                    return 1;
                if(Player1[i].getType()< Player2[i].getType())
                    return 2;
            }
            break;
        case Series:
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getValue()> Player2[i].getValue())
                    return 1;
                if(Player1[i].getValue()< Player2[i].getValue())
                    return 2;
            }
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getType()> Player2[i].getType())
                    return 1;
                if(Player1[i].getType()< Player2[i].getType())
                    return 2;
            }
            break;
        case ThreePlusTwo:{
            QMap<int,int> e1,e2;
            int c1,c2;
            for (int i = 0; i < 5; ++i)
            {
                if(++e1[Player1[i].getValue()]==3)
                    c1=Player1[i].getValue();
                if(++e2[Player2[i].getValue()]==3)
                    c2=Player2[i].getValue();
            }
            if(c1>c2)
                return 1;
            if(c1<c2)
                return 2;
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getValue()> Player2[i].getValue())
                    return 1;
                if(Player1[i].getValue()< Player2[i].getValue())
                    return 2;
            }
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getType()> Player2[i].getType())
                    return 1;
                if(Player1[i].getType()< Player2[i].getType())
                    return 2;
            }
            break;}

        case DoublePair:
            ////////////////////////////////////////
            break;
        case SinglePair:{
            QMap<int,int> e1,e2;
            int c1,c2;
            for (int i = 0; i < 5; ++i)
            {
                if(++e1[Player1[i].getValue()]==2)
                    c1=Player1[i].getValue();
                if(++e2[Player2[i].getValue()]==2)
                    c2=Player2[i].getValue();
            }
            qDebug()<<c1<<' '<<c2<<' ';
            if(c1>c2)
                return 1;
            if(c1<c2)
                return 2;
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getValue()> Player2[i].getValue())
                    return 1;
                if(Player1[i].getValue()< Player2[i].getValue())
                    return 2;
            }
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getType()> Player2[i].getType())
                    return 1;
                if(Player1[i].getType()< Player2[i].getType())
                    return 2;
            }
            break;
        }

        case MessyHand:
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getValue()> Player2[i].getValue())
                    return 1;
                if(Player1[i].getValue()< Player2[i].getValue())
                    return 2;
            }
            for(int i=0;i<5;i++)
            {
                if(Player1[i].getType()> Player2[i].getType())
                    return 1;
                if(Player1[i].getType()< Player2[i].getType())
                    return 2;
            }
            break;
    }
}
