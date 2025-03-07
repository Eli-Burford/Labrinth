//
// Custom Obstacle Class
//

#include "obstacle.h"


Obstacle::Obstacle(QGraphicsItem* parent, int width, int height) : QGraphicsItem(parent)
{
    brush = oBrush;


    // Default values of width and height are 10 pixels each
    w = width;
    h = height;
}


Obstacle::~Obstacle()
{

}

QRectF Obstacle::boundingRect() const
{
    return QRectF(-w/2, -h/2, w, h);
}

QPainterPath Obstacle::shape() const
{
    QPainterPath path;
    path.addRect(-w/2, -h/2, w, h);
    return path;
}

void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::yellow));
    painter->setBrush(*brush);
    painter->drawRect(-w/2, -h/2, w, h);
}

void Obstacle::advance(int phase)
{
    if (phase == 0)
    {
        return;
    }

    // If ANYTHING collides with the target, change the target brush to red
    // Otherwise, set target brush to blue
    QList<QGraphicsItem*> list = collidingItems();
    if (!list.isEmpty())
    {       
        // Collison has occurred
        //brush = redBrush;
        //qDebug() << "Obstacle detects collision";

    }
    else
    {
        // No collision
        brush = oBrush;

    }

    // Force redraw of entire Obstacle object
    this->update();
}





