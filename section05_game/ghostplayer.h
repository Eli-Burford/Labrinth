#ifndef GHOSTPLAYER_H
#define GHOSTPLAYER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "defs.h"
#include "puck.h"
#include "player.h"
#include "speedpowerup.h"

class ghostPlayer : public Player
{
public:
    ghostPlayer(Player *parent = nullptr);
    ~ghostPlayer() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void advance(int phase) override;

    void setPosition(int, int);     // making setPos public
    void setSpeed(qreal n);

//    unsigned int pScore;

//    unsigned int speedTime;

//    QTimer* displaySpeed = nullptr;


private:

    //QPixmap images[NUM_IMAGES];
    //int index;
    //int offset;

    qreal x, y, dx, dy, speed;

//signals:
//    unsigned int hit(unsigned int score);
};

#endif // GHOSTPLAYER_H
