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
    void setId(int id) { m_id = id; }
    int cardId() const { return m_id; }
    void animateEnlarge();
    void showFront();
    void showBack();
    void setFrontPixmap(const QPixmap& pixmap);
    void enableDrag();
    void disableDrag();

signals:
    void animationFinished();
    void clicked();
    void cardClicked(CardItem *item);
    void draggedDown(CardItem* self);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int m_id=-1;
    QPointF originalPos;
    QVariantAnimation* currentAnimation = nullptr;
    QPixmap m_frontPixmap;
    QPixmap m_backPixmap;
    bool isFrontShown = false;
    QPointF dragStartPos;
};


#endif // CARDITEM_H
