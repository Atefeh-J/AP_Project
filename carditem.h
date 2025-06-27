#ifndef CARDITEM_H
#define CARDITEM_H

#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include <QTimer>

class CardItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ boundingRect)

public:
    CardItem(const QPixmap& pixmap);

    void animateEnlarge();

signals:
    void animationFinished();
};

#endif // CARDITEM_H
