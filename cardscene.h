#ifndef CARDSCENE_H
#define CARDSCENE_H
#include <QGraphicsScene>
#include <QTimer>
#include <QRandomGenerator>
#include "carditem.h"

class CardScene : public QGraphicsScene {
    Q_OBJECT

public:
    CardScene(QObject* parent = nullptr);
    void startRandomSelection();

signals:
    void goToMainWindow();

private slots:
    void handleAnimationFinished();

private:
    QList<CardItem*> cards;
    CardItem* selectedCard = nullptr;
};

#endif // CARDSCENE_H
