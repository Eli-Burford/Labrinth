#include "ghostplayer.h"


ghostPlayer::ghostPlayer(Player *parent)  //: QGraphicsItem(parent)
{
    /*for(int k = 0; k < NUM_IMAGES; k++)
    {
        QString s = ":/images/tile" + QString::number(k) + QString(".png");
        images[k] = QPixmap(s);
        images[k] = images[k].scaled(PLAYER_WIDTH, PLAYER_HEIGHT);
    }

    // Start at first image of walking towards viewer pixmaps
    index = 0;
    offset = 18;*/
    speed = 3;

}

ghostPlayer::~ghostPlayer()
{

}

void ghostPlayer::setPosition(int new_x, int new_y){
    this->setPos(new_x,new_y);
}

QRectF ghostPlayer::boundingRect() const
{
    return QRectF(-PLAYER_WIDTH/2, -PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT);
}

QPainterPath ghostPlayer::shape() const
{
    QPainterPath path;
    path.addRect(-PLAYER_WIDTH/2, -PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT);

    // path.addRect(-PLAYER_WIDTH/8, -PLAYER_HEIGHT/8, PLAYER_WIDTH/4, PLAYER_HEIGHT/4);
    return path;
}

void ghostPlayer::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
{
    //index = (index + 1) % NUM_FRAMES;
    //painter->drawPixmap(-PLAYER_WIDTH/2, -Player_HEIGHT/2, images[offset + index]);

    painter->setPen(QPen(Qt::yellow));
    painter->drawRect(this->boundingRect());

    painter->setPen(QPen(Qt::red));
    painter->drawRect(QRect(-PLAYER_WIDTH/8, -PLAYER_HEIGHT/8, PLAYER_WIDTH/4, PLAYER_HEIGHT/4));
}

void ghostPlayer::setSpeed(qreal n)
{
    speed = n * speed;
}

void ghostPlayer::advance(int phase)
{
    if (phase == 0) return;

    // Detect any collisions
    QList<QGraphicsItem*> list = collidingItems();
    if (!list.isEmpty())
    {
        //qDebug() << "Player detects collision";



        QGraphicsItem* test = list[0];                          // Get first item in list of colliding objects
        //qDebug() << test;                                       // Display first item in list of colliding objects


        foreach(QGraphicsItem * i, list)                        // For each item in colliding list
        {
            Puck * testPuck = dynamic_cast<Puck *>(i);              // Try to cast list items into being pucks
            SpeedPowerUp * testSPU = dynamic_cast<SpeedPowerUp *>(i);

            if (testPuck || testSPU)                                           // If you can, then they're pucks, and you should delete them
            {
                //this->pScore++;
                //emit hit(this->pScore);
                //test->scene()->removeItem(test);                // Remove the puck from the scene
                //test->deleteLater();                           // Schedule for deallocation of associated memory

            }

            else                                                // This executes if player hits wall/boundary
            {
                this->setPos((x - (2*dx)), (y - (2*dy)));   // Revert their position
                //ghostPlayer::stop();                                 // Call stop here for constant movement after press
            }
        }


    }

    //ghostPlayer::stop();                                           // Call stop here if we want hold-to-move
}


