#include "speedpowerup.h"

SpeedPowerUp::SpeedPowerUp(QGraphicsItem *parent) : Puck (parent)
{

}

SpeedPowerUp::~SpeedPowerUp()
{

}

QRectF SpeedPowerUp::boundingRect() const
{
    return QRectF(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}

QPainterPath SpeedPowerUp::shape() const
{
    QPainterPath path;
    path.addRect(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
    return path;
}

void SpeedPowerUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::blue));
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}

void SpeedPowerUp::advance(int phase)
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
        // qDebug() << "Powerup detects collision";

        // notify program of collision
        //emit hit();

        //  puck experiences collision, remove
        //this->scene()->removeItem(this);

        // schedule for deallocatoin of associated memory
        //this->deleteLater();

    }
}
