#include "carditem.h"

CardItem::CardItem(const QPixmap& pixmap)
    : QGraphicsPixmapItem(pixmap) {
    setTransformationMode(Qt::SmoothTransformation);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void CardItem::animateEnlarge() {
    auto* animation = new QVariantAnimation(this);
    animation->setDuration(2000);
    animation->setStartValue(1.0);
    animation->setEndValue(2.0);
    animation->setEasingCurve(QEasingCurve::OutBack);

    connect(animation, &QVariantAnimation::valueChanged, this, [=](const QVariant &value) {
        qreal scale = value.toReal();
        setScale(scale);
    });

    connect(animation, &QVariantAnimation::finished, this, [=]() {
        emit animationFinished();
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
