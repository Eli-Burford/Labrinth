#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include "defs.h"
#include "puck.h"
#include "speedpowerup.h"

class Player : public QGraphicsItem
{
public:
    Player(QGraphicsItem *parent = nullptr);
    ~Player() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void advance(int phase) override;

    void goRight();
    void goLeft();
    void goUp();
    void goDown();
    void stop();
    void setPosition(int, int);     // making setPos public
    void setSpeed(qreal n);

    unsigned int pScore = 0;
    bool ghost = true;          // Flag we can use to track whether a player object is a ghost or not
                                // Starts as true, and is changed to false when spawning client player
    unsigned int speedTime;

    QTimer* displaySpeed = nullptr;


private:

    //QPixmap images[NUM_IMAGES];
    //int index;
    //int offset;

    qreal x, y, dx, dy, speed;  // Declare movement variables
    char direction; // s for stop, u for up, l for left, r for right, d for down

//signals:
//    unsigned int hit(unsigned int score);
};

#endif // PLAYER_H
