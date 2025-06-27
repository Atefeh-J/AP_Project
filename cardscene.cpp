#include "cardscene.h"

CardScene::CardScene(QObject* parent) : QGraphicsScene(parent) {
    int cardWidth = 200;
    int overlap = 30;
    int totalWidth = (cards.count() - 1) * overlap + cardWidth;

    int sceneWidth = 1000;
    int offsetX = (sceneWidth - totalWidth) / 2;

    for (int i = 0; i < 13; ++i) {
        QString path = QString(":/cards/Dimond-%1.JPG").arg(i + 2);
        QPixmap pix = QPixmap(path).scaled(cardWidth, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        CardItem* card = new CardItem(pix);
        card->setPos(offsetX + i * overlap, 250);
        addItem(card);
        cards.append(card);
    }
}

void CardScene::startRandomSelection() {
    int index = QRandomGenerator::global()->bounded(13);
    selectedCard = cards[index];

    selectedCard->setZValue(1);
    connect(selectedCard, &CardItem::animationFinished, this, &CardScene::handleAnimationFinished);
    selectedCard->animateEnlarge();
}

void CardScene::handleAnimationFinished() {
    QTimer::singleShot(3000, this, [=]() {
        emit goToMainWindow();
    });
}
