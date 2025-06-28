#include "carditem.h"

CardItem::CardItem(const QPixmap& pixmap,QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(pixmap,parent) {
    setTransformationMode(Qt::SmoothTransformation);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setTransformOriginPoint(boundingRect().center());
}

void CardItem::animateEnlarge()
{
    if (currentAnimation) {
        currentAnimation->stop();
        currentAnimation->deleteLater();
    }

    currentAnimation = new QVariantAnimation(this);
    currentAnimation->setDuration(2000);
    currentAnimation->setStartValue(1.0);
    currentAnimation->setEndValue(2.0);
    currentAnimation->setEasingCurve(QEasingCurve::OutBack);

    connect(currentAnimation, &QVariantAnimation::valueChanged, this, [=](const QVariant &value) {
        setScale(value.toReal());
    });

    connect(currentAnimation, &QVariantAnimation::finished, this, [=]() {
        emit animationFinished();
        currentAnimation->deleteLater();
        currentAnimation = nullptr;
    });

    currentAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CardItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
    QGraphicsPixmapItem::mousePressEvent(event); // فراخوانی نسخه‌ی پایه
}