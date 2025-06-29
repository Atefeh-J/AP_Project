#include "carditem.h"

CardItem::CardItem(const QPixmap& pixmap,QGraphicsItem* parent)
    : QObject(), QGraphicsPixmapItem(pixmap,parent), m_backPixmap(pixmap)
{
    setTransformationMode(Qt::SmoothTransformation);
    // setFlag(QGraphicsItem::ItemIsSelectable);
    // setFlag(QGraphicsItem::ItemIsMovable);
    // setTransformOriginPoint(boundingRect().center());
    setAcceptHoverEvents(true);
    isFrontShown = false;
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
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
    // dragStartPos = event->scenePos();
    // QGraphicsPixmapItem::mousePressEvent(event);
    dragStartPos = event->scenePos();
    originalPos = pos();
    QGraphicsPixmapItem::mousePressEvent(event);
}

void CardItem::setFrontPixmap(const QPixmap& pixmap)
{
    m_frontPixmap = pixmap;
    if(!m_frontPixmap.isNull())
    {
        m_frontPixmap = m_frontPixmap.scaled(m_backPixmap.size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    }
}

void CardItem::showFront()
{
    if (!isFrontShown && !m_frontPixmap.isNull()) {
        setPixmap(m_frontPixmap);
        setTransformOriginPoint(boundingRect().center());
        isFrontShown = true;
    }
}

void CardItem::showBack()
{
    if (isFrontShown) {
        QPixmap scaledBack = m_backPixmap.scaled(boundingRect().size().toSize(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation);
        setPixmap(scaledBack);
        isFrontShown = false;
    }
}

void CardItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF delta = event->scenePos() - dragStartPos;
    setPos(pos() + delta);
    dragStartPos = event->scenePos();

    QGraphicsPixmapItem::mouseMoveEvent(event);
}

void CardItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // if (pos().y() > scene()->height() * 0.75) {
    //     emit draggedDown(this);
    // }

    // QGraphicsPixmapItem::mouseReleaseEvent(event);

    QGraphicsPixmapItem::mouseReleaseEvent(event);

    if ((pos() - originalPos).manhattanLength() > 20) {
        emit draggedDown(this);
    }
}




