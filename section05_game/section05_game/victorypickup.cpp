#include "victorypickup.h"
#include "puck.h"
victoryPickup::victoryPickup(QGraphicsItem *parent) : Puck (parent)
{

}

victoryPickup::~victoryPickup()
{

}

QRectF victoryPickup::boundingRect() const
{
    return QRectF(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}

QPainterPath victoryPickup::shape() const
{
    QPainterPath path;
    path.addRect(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
    return path;
}


void victoryPickup::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::blue));
    painter->drawEllipse(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}


void victoryPickup::advance(int phase)
{
    // Puck does not move
    if (phase == 0)
    {
        return;
    }

    // If this puck experiences a collision with ANY other object,
    // emit the hit( ) signal and remove this instance of Puck
    // from current scene object
    QList<QGraphicsItem*> list = collidingItems();
    if (!list.isEmpty())
    {
         qDebug() << "Victory Pickup collected!";
         emit hit();
    }
}
