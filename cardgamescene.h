#ifndef CARDGAMESCENE_H
#define CARDGAMESCENE_H

#include <QGraphicsScene>
#include <QVector>
#include <QSet>
#include <QPointF>
#include <QPainter>
#include <QTimer>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsDropShadowEffect>
#include "carditem.h"

class CardGameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CardGameScene(QObject *parent = nullptr);
    void startGame();

private:
    QVector<CardItem*> deck;
    QList<CardItem*> currentCards;
    QList<CardItem*> selectedCards;
    QList<CardItem*> cardsThisRound;
    QPointF stackPosition;
    QPointF centerPosition;
    QTimer* selectionTimer = nullptr;
    QTimer* countdownTimer = nullptr;
    QGraphicsEllipseItem* countdownCircle = nullptr;
    QGraphicsEllipseItem* progressArc = nullptr;
    QGraphicsTextItem* countdownText = nullptr;
    QTimer* pulseTimer = nullptr;
    int pulseState = 0;
    int autoSelectWarnings = 0;
    int countdownRemaining = 10;
    int roundCount = 0;
    const int maxRounds = 5;
    bool cardChosenInCurrentRound = false;
    void initializeDeck();
    void showNextSevenCards();
    void clearPreviousCards();
    void startCountdownWarning();
    void countdownTick();
    void autoSelectRandomCard();
    void cleanupCountdownDisplay();
    bool isAnimating;
    bool isCountdownActive = false;
signals:
    void gameFinished();
    void cardClicked(CardItem*);

private slots:
    void onCardSelected(CardItem* item);
};

#endif // CARDGAMESCENE_H
