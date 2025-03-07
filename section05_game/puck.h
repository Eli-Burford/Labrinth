#ifndef PUCK_H
#define PUCK_H

#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QtDebug>
#include "defs.h"

//
// The QGraphicsObject type inherits from QObject and QGraphicsItem
// so objects of this type can utilize signal-slot connections
//

class Puck : public QGraphicsObject
{
    Q_OBJECT

public:
    Puck(QGraphicsItem *parent = nullptr);
    ~Puck() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;

    void placePuck(QPointF);

signals:
    void hit();         // Signal emitted upon collision between Puck and ANY object
};

#endif // PUCK_H
