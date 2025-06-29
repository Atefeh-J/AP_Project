#include "cardgamescene.h"

CardGameScene::CardGameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 800, 600);
    setBackgroundBrush(Qt::transparent);
}

void CardGameScene::startGame()
{
    stackPosition = QPointF(50, height() / 2 - 50);
    centerPosition = QPointF(width() / 2, height() / 2);

    initializeDeck();
    showNextSevenCards();
}

void CardGameScene::initializeDeck()
{
    int cardWidth = 80;
    int cardHeight = 120;

    QPixmap back(":/images/back.jpg");
    back = back.scaled(cardWidth, cardHeight, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);


    QString suits[4] = {"Dimond", "Dollar", "Coin", "Gold"};

    int i=0;
    // QPointF stackStart(30, height() / 2 - 60);
    QPointF stackStart(30, height() - cardHeight - 30);
    qreal offsetX = 3;
    qreal offsetY = 0;
    for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
        for (int value = 2; value <= 14; value++) {
            CardItem *card = new CardItem(back);
            // card->setPos(stackStart + QPointF(0, i * 0.7));
            card->setId(i);

            QString frontPath = QString(":/cards/%1-%2.JPG").arg(suits[suitIndex]).arg(value);
            QPixmap front(frontPath);
            if (!front.isNull())
                front = front.scaled(cardWidth, cardHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            card->setFrontPixmap(front);

            qreal x = stackStart.x() + (i * offsetX);
            qreal y = stackStart.y() + (i * offsetY);
            card->setPos(QPointF(x, y));

            // card->setPos(stackPosition);
            card->showBack();
            connect(card, &CardItem::draggedDown, this, &CardGameScene::onCardSelected);
            deck.append(card);
            addItem(card);
            ++i;
        }
    }

}

void CardGameScene::showNextSevenCards()
{
    if (roundCount >= maxRounds) {
        emit gameFinished();
        return;
    }

    clearPreviousCards();
    currentCards.clear();
    cardsThisRound.clear();
    cardChosenInCurrentRound = false;

    int cardWidth = 80;
    int cardHeight = 120;
    int spacing = 20;
    int totalWidth = 7 * cardWidth + 6 * spacing;
    int cardAreaWidth = 7 * cardWidth + 6 * spacing;
    int startX = (width() - totalWidth) / 2;
    // int startX = centerPosition.x() - totalWidth / 2;
    // int yPos = centerPosition.y();
    // int yPos = height() / 2 - (cardHeight / 2);
    int yPos = height() - cardHeight - 180;

    QSet<int> used;
    int count = 0;

    for (int i = 0; i < 7;++i) {
        int index = QRandomGenerator::global()->bounded(deck.size());
        if (used.contains(index))
        {
            i--;
            continue;
        }
        used.insert(index);

        CardItem* card = deck[index];

        int xPos = startX + i * (cardWidth + spacing);
        QPointF targetPos(xPos, yPos);

        QPropertyAnimation* anim = new QPropertyAnimation(card, "pos");
        anim->setDuration(500);
        anim->setEndValue(targetPos);
        anim->start(QAbstractAnimation::DeleteWhenStopped);

        card->setZValue(1);
        card->showFront();
        card->setFlag(QGraphicsItem::ItemIsMovable, true);

        currentCards.append(card);
        cardsThisRound.append(card);
        ++count;
    }
    for (CardItem* card : cardsThisRound) {
        deck.removeOne(card);
    }
    ++roundCount;
    if (!selectionTimer) {
        selectionTimer = new QTimer(this);
        connect(selectionTimer, &QTimer::timeout, this, &CardGameScene::startCountdownWarning);
    }
    selectionTimer->start(20000);
}

void CardGameScene::clearPreviousCards()
{
    // for (CardItem* card : currentCards) {
    //     card->setZValue(0);
    //     card->setPos(stackPosition);
    //     card->showBack();
    // }
    // currentCards.clear();

    for (CardItem* card : currentCards) {
        if (!selectedCards.contains(card)) {
            card->setZValue(0);
            card->setPos(stackPosition);
            card->showBack();
        }
    }
    currentCards.clear();
}

void CardGameScene::onCardSelected(CardItem* item)
{
    if (isCountdownActive) {
        cleanupCountdownDisplay();
    }

    // if (selectionTimer) selectionTimer->stop();
    // if (countdownTimer) countdownTimer->stop();
    if (countdownText) {
        removeItem(countdownText);
        delete countdownText;
        countdownText = nullptr;
    }

    if (cardChosenInCurrentRound || !cardsThisRound.contains(item))
        return;

    cardChosenInCurrentRound = true;
    selectedCards.append(item);

    item->setZValue(1);
    item->setScale(1.3);

    for (CardItem* card : currentCards) {
        if (card != item) {
            removeItem(card);  // یا card->hide();
        }
    }

    int cardWidth = item->boundingRect().width() * 1.3;
    int spacing = 20;
    int totalWidth = selectedCards.size() * cardWidth + (selectedCards.size() - 1) * spacing;
    int startX = (width() - totalWidth) / 2;
    // int y = height() / 2 - cardWidth / 2;
    int y = height() / 2 - cardWidth - 80;

    for (int i = 0; i < selectedCards.size(); ++i) {
        CardItem* selected = selectedCards[i];
        QPointF targetPos(startX + i * (cardWidth + spacing), y);

        QPropertyAnimation* anim = new QPropertyAnimation(selected, "pos");
        anim->setDuration(500);
        anim->setEndValue(targetPos);
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }

    QTimer::singleShot(700, this, [this]() {
        showNextSevenCards();
    });

}

void CardGameScene::startCountdownWarning()
{
    // selectionTimer->stop();

    // if (autoSelectWarnings >= 2)
    //     return;

    // qDebug() << "⚠️ No card selected. Starting 10s countdown!";

    // countdownRemaining = 10;

    // // حذف متن قبلی اگر وجود دارد
    // if (countdownText) {
    //     removeItem(countdownText);
    //     delete countdownText;
    //     countdownText = nullptr;
    // }

    // // ایجاد متن جدید
    // countdownText = new QGraphicsTextItem(QString::number(countdownRemaining));
    // QFont font("Arial", 32, QFont::Bold);
    // countdownText->setFont(font);
    // countdownText->setDefaultTextColor(Qt::red);

    // // محاسبه موقعیت مرکزی صحنه
    // QRectF sceneRect = this->sceneRect();
    // qreal xPos = (sceneRect.width() - countdownText->boundingRect().width()) / 2;
    // qreal yPos = 50;

    // countdownText->setPos(xPos, yPos);
    // countdownText->setZValue(1000);
    // addItem(countdownText);

    // if (!countdownTimer) {
    //     countdownTimer = new QTimer(this);
    //     connect(countdownTimer, &QTimer::timeout, this, &CardGameScene::countdownTick);
    // }

    // countdownTimer->start(1000);
    // ++autoSelectWarnings;

    selectionTimer->stop();
    if (autoSelectWarnings >= 2) return;

    cleanupCountdownDisplay();

    countdownRemaining = 10;


    countdownCircle = new QGraphicsEllipseItem();
    countdownCircle->setRect(0, 0, 160, 160);
    countdownCircle->setBrush(QBrush(QColor(40, 40, 50)));
    countdownCircle->setPen(QPen(QColor(100, 100, 120), 3));
    // countdownCircle->setPos(width()/2 - 60, 50);
    int marginRight = -10;
    int marginTop = 20;
    countdownCircle->setPos(width() - countdownCircle->rect().width() - marginRight, marginTop);
    addItem(countdownCircle);


    progressArc = new QGraphicsEllipseItem(countdownCircle);
    progressArc->setRect(15, 15, 130, 130);
    progressArc->setStartAngle(90 * 16);
    progressArc->setSpanAngle(360 * 16);
    progressArc->setBrush(Qt::NoBrush);
    progressArc->setPen(QPen(QColor(65, 200, 255), 8));
    progressArc->setZValue(1);


    countdownText = new QGraphicsTextItem(QString::number(countdownRemaining), countdownCircle);
    QFont font("Arial", 48, QFont::Bold);
    countdownText->setFont(font);
    countdownText->setDefaultTextColor(Qt::white);


    QRectF textRect = countdownText->boundingRect();
    countdownText->setPos(80 - textRect.width()/2, 80 - textRect.height()/2);


    QGraphicsDropShadowEffect* glowEffect = new QGraphicsDropShadowEffect();
    glowEffect->setBlurRadius(15);
    glowEffect->setColor(QColor(100, 200, 255));
    glowEffect->setOffset(0);
    countdownText->setGraphicsEffect(glowEffect);


    pulseTimer = new QTimer(this);
    connect(pulseTimer, &QTimer::timeout, this, [this]() {
        pulseState = (pulseState + 1) % 10;
        qreal scale = 1.0 + 0.05 * (pulseState < 5 ? pulseState : 10 - pulseState);
        countdownCircle->setScale(scale);
    });
    pulseTimer->start(50);

    countdownRemaining = 10;
    isCountdownActive = true;

    if (!countdownTimer) {
        countdownTimer = new QTimer(this);
        connect(countdownTimer, &QTimer::timeout, this, &CardGameScene::countdownTick);
    }
    countdownTimer->start(1000);
    ++autoSelectWarnings;

}

void CardGameScene::countdownTick()
{

    if (!isCountdownActive || !countdownCircle || !countdownText || !progressArc) {
        qWarning() << "Countdown items not initialized!";
        return;
    }

    countdownRemaining--;
    countdownText->setPlainText(QString::number(countdownRemaining));

    if (countdownRemaining > 0) {
        qreal progress = countdownRemaining / 10.0;
        progressArc->setSpanAngle(360 * 16 * progress);
    }


    if (countdownRemaining <= 3) {
        int greenValue = 80 + 50 * countdownRemaining;
        QColor alertColor(255, qMin(greenValue, 255), 80);
        progressArc->setPen(QPen(alertColor, 8));
        countdownText->setDefaultTextColor(alertColor);


        if (countdownRemaining == 1 && !isAnimating) {
            isAnimating = true;
            QTimeLine *timer = new QTimeLine(400, this);
            timer->setFrameRange(0, 10);

            connect(timer, &QTimeLine::frameChanged, [this](int frame) {
                qreal offset = 5 * sin(frame * 0.1 * M_PI * 2);
                if (countdownCircle) {
                    countdownCircle->setX(width()/2 - 60 + offset);
                }
            });

            connect(timer, &QTimeLine::finished, [this, timer]() {
                if (countdownCircle) {
                    countdownCircle->setX(width()/2 - 60);
                }
                timer->deleteLater();
                isAnimating = false;
            });

            timer->start();
        }
    }

    if (countdownRemaining <= 0) {
        cleanupCountdownDisplay();
        QTimer::singleShot(500, this, &CardGameScene::autoSelectRandomCard);
    }
}

void CardGameScene::autoSelectRandomCard()
{
    if (cardChosenInCurrentRound || cardsThisRound.isEmpty())
        return;

    int index = QRandomGenerator::global()->bounded(cardsThisRound.size());
    CardItem* randomCard = cardsThisRound[index];

    onCardSelected(randomCard);
}

void CardGameScene::cleanupCountdownDisplay() {

    isCountdownActive = false;
    if (countdownTimer) countdownTimer->stop();
    if (pulseTimer) pulseTimer->stop();

    if (!countdownCircle) return;

    QGraphicsOpacityEffect* fadeEffect = new QGraphicsOpacityEffect();
    countdownCircle->setGraphicsEffect(fadeEffect);

    QPropertyAnimation* fadeAnim = new QPropertyAnimation(fadeEffect, "opacity");
    fadeAnim->setDuration(500);
    fadeAnim->setStartValue(1);
    fadeAnim->setEndValue(0);
    connect(fadeAnim, &QPropertyAnimation::finished, [this]() {
        if (countdownCircle) {
            removeItem(countdownCircle);
            delete countdownCircle;
        }
        countdownCircle = nullptr;
        countdownText = nullptr;
        progressArc = nullptr;
    });
    fadeAnim->start(QAbstractAnimation::DeleteWhenStopped);
}

