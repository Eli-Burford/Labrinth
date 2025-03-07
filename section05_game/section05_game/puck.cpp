#include "puck.h"

Puck::Puck(QGraphicsItem *parent) : QGraphicsObject (parent)
{

}

Puck::~Puck()
{

}

QRectF Puck::boundingRect() const
{
    return QRectF(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}

QPainterPath Puck::shape() const
{
    QPainterPath path;
    path.addRect(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
    return path;
}

void Puck::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::white));
    painter->setBrush(QBrush(Qt::green));
    painter->drawEllipse(-PUCK_WIDTH/2, -PUCK_HEIGHT/2, PUCK_WIDTH, PUCK_HEIGHT);
}

void Puck::advance(int phase)
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
         qDebug() << "Puck detects collision";

//        // notify program of collision
//        emit hit();


//         // puck experiences collision, remove
//        this->scene()->removeItem(this);

//        // schedule for deallocation of associated memory
//        this->deleteLater();

    }
}

void Puck::placePuck(QPointF position) // Currently unused
{
    this->setPos(position);
}
