#ifndef CARDSCENE_H
#define CARDSCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>
#include <algorithm>
#include <QSet>
#include <QVector>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include "carditem.h"

// class CardScene : public QGraphicsScene {
//     Q_OBJECT

// public:
//     CardScene(QObject* parent = nullptr);
//     void startRandomSelection();

// signals:
//     void goToMainWindow();

// private slots:
//     void handleAnimationFinished();

// private:
//     QList<CardItem*> cards;
//     CardItem* selectedCard = nullptr;
// };
class CardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CardScene(QObject *parent = nullptr);
    void startFirstPhase();
    void startSecondPhase();

signals:
    void firstPhaseFinished();
    void allPhasesFinished();
    void goToMainWindow();

private slots:
    void onShuffleAnimationFinished();

private:
    QList<CardItem*> cards;
    CardItem* selectedCard = nullptr;
    QParallelAnimationGroup *shuffleAnimationGroup;

    void setupDiamondCards();
    void setupAllCards();
    void selectRandomCard();
    void createShuffleAnimations();
    // void initializeAnimations();
};

#endif // CARDSCENE_H
