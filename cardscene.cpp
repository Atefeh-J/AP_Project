#include "cardscene.h"

// CardScene::CardScene(QObject* parent) : QGraphicsScene(parent) {
//     int cardWidth = 200;
//     int overlap = 30;
//     int totalWidth = (cards.count() - 1) * overlap + cardWidth;

//     int sceneWidth = 1000;
//     int offsetX = (sceneWidth - totalWidth) / 2;

//     for (int i = 0; i < 13; ++i) {
//         QString path = QString(":/cards/Dimond-%1.JPG").arg(i + 2);
//         QPixmap pix = QPixmap(path).scaled(cardWidth, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);

//         CardItem* card = new CardItem(pix);
//         card->setPos(offsetX + i * overlap, 250);
//         addItem(card);
//         cards.append(card);
//     }
// }

// void CardScene::startRandomSelection() {
//     int index = QRandomGenerator::global()->bounded(13);
//     selectedCard = cards[index];

//     selectedCard->setZValue(1);
//     connect(selectedCard, &CardItem::animationFinished, this, &CardScene::handleAnimationFinished);
//     selectedCard->animateEnlarge();
// }

// void CardScene::handleAnimationFinished() {
//     QTimer::singleShot(3000, this, [=]() {
//         emit goToMainWindow();
//     });
// }
CardScene::CardScene(QObject *parent) : QGraphicsScene(parent),
    shuffleAnimationGroup(new QParallelAnimationGroup(this))
{
    // connect(shuffleAnimationGroup, &QParallelAnimationGroup::finished,
    //         this, &CardScene::onShuffleAnimationFinished);

    // startFirstPhase();
    shuffleAnimationGroup = new QParallelAnimationGroup(this);
    connect(shuffleAnimationGroup, &QParallelAnimationGroup::finished,
            this, &CardScene::onShuffleAnimationFinished);

    startFirstPhase();
}

void CardScene::startFirstPhase()
{
    clear();
    cards.clear();
    setupDiamondCards();
    selectRandomCard();
}

void CardScene::startSecondPhase()
{
    clear();
    cards.clear();
    setupAllCards();
    createShuffleAnimations();
    shuffleAnimationGroup->start();
}

void CardScene::setupDiamondCards()
{
    int cardWidth = 120;
    int overlap = 30;
    int totalWidth = 12 * overlap + cardWidth;
    int sceneWidth = 1000;
    int offsetX = (sceneWidth - totalWidth) / 2;

    for (int i = 0; i < 13; ++i) {
        QString path = QString(":/cards/Dimond-%1.JPG").arg(i + 2);
        QPixmap pix(path);

        if(pix.isNull()) {
            pix = QPixmap(cardWidth, 180);
            pix.fill(QColor(QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256)));
            //qDebug() << "Failed to load:" << path;
        } else {
            pix = pix.scaled(cardWidth, 180, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

        CardItem* card = new CardItem(pix);
        card->setPos(offsetX + i * overlap, 250);
        addItem(card);
        cards.append(card);
    }
}

void CardScene::setupAllCards()
{
    int cardWidth = 80;
    int cardHeight = 120;
    int cardsPerRow = 13;
    int spacing = 15;
    int startX = 50;
    int startY = 50;

    QString suits[4] = {"Dimond", "Dollar", "Coin", "Gold"};

    for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
        for (int value = 2; value <= 14; value++) {
            QString path = QString(":/cards/%1-%2.JPG").arg(suits[suitIndex]).arg(value);
            QPixmap pix(path);

            if(pix.isNull()) {
                pix = QPixmap(cardWidth, cardHeight);
                pix.fill(QColor(QRandomGenerator::global()->bounded(256),
                         QRandomGenerator::global()->bounded(256),
                         QRandomGenerator::global()->bounded(256)));
            } else {
                pix = pix.scaled(cardWidth, cardHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            }

            CardItem* card = new CardItem(pix);
            int index = suitIndex * 13 + (value - 2);
            int row = index / cardsPerRow;
            int col = index % cardsPerRow;
            card->setPos(startX + col * (cardWidth + spacing),
                        startY + row * (cardHeight + spacing));
            addItem(card);
            cards.append(card);
        }
    }

}

void CardScene::createShuffleAnimations()
{
    shuffleAnimationGroup->clear();
    qreal sceneWidth = sceneRect().width();
    qreal sceneHeight = sceneRect().height();
    qreal cardWidth = 80;
    qreal cardHeight = 120;

    for (CardItem* card : cards) {
        QPointF newPos(
            QRandomGenerator::global()->bounded(sceneWidth - cardWidth),
            QRandomGenerator::global()->bounded(sceneHeight - cardHeight)
            );
        QPropertyAnimation* moveAnim = new QPropertyAnimation(card, "pos");
        moveAnim->setDuration(800 + QRandomGenerator::global()->bounded(400));
        moveAnim->setStartValue(card->pos());
        moveAnim->setEndValue(newPos);
        moveAnim->setEasingCurve(QEasingCurve::InOutBack);
        QPropertyAnimation* rotateAnim = new QPropertyAnimation(card, "rotation");
        rotateAnim->setDuration(1000);
        rotateAnim->setStartValue(card->rotation());
        rotateAnim->setEndValue(QRandomGenerator::global()->bounded(360));
        rotateAnim->setEasingCurve(QEasingCurve::InOutQuad);

        shuffleAnimationGroup->addAnimation(moveAnim);
        shuffleAnimationGroup->addAnimation(rotateAnim);
    }
}

void CardScene::selectRandomCard()
{
    if (cards.isEmpty()) return;

    int index = QRandomGenerator::global()->bounded(cards.size());
    selectedCard = cards[index];
    selectedCard->setZValue(1);

    connect(selectedCard, &CardItem::animationFinished, this, [this]() {
        QTimer::singleShot(2000, this, [this]() {
            clear();
            emit firstPhaseFinished();
            QTimer::singleShot(1000, this, &CardScene::startSecondPhase);
        });
    });

    selectedCard->animateEnlarge();
}

void CardScene::onShuffleAnimationFinished()
{
    qDebug() << "انیمیشن شافل کامل شد!";
    emit allPhasesFinished();
}
