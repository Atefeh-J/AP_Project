#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QTimer>
#include <QVariantAnimation>
#include <QDebug>

class CardItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos) // برای انیمیشن pos
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit CardItem(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    void animateEnlarge();

signals:
    void animationFinished();
    void clicked();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    QPointF dragStartPos;
    QVariantAnimation* currentAnimation = nullptr;
};


#endif // CARDITEM_H