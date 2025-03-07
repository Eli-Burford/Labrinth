#ifndef SPEEDPOWERUP_H
#define SPEEDPOWERUP_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QtDebug>
#include <QTimer>
#include "puck.h"
#include "defs.h"

class SpeedPowerUp : public Puck
{
    Q_OBJECT

public:
    SpeedPowerUp(QGraphicsItem *parent = nullptr);
    ~SpeedPowerUp() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;


signals:
    void Speedhit();         // Signal emitted upon collision between Puck and ANY object
};

#endif // SPEEDPOWERUP_H
