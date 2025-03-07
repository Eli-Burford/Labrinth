//
// Custom Obstacle Class
//
// Dimensions derived from Constructor invocation only
// Does not assume that OBSTACLE_WIDTH and OBSTACLE_HEIGHT are defined anywhere
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QtDebug>
#include <QGraphicsScene>
#include "defs.h"

class Obstacle : public QGraphicsItem
{
public:
    Obstacle(QGraphicsItem* parent = nullptr, int width = 10, int height = 10);
    ~Obstacle() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;

private:
    QBrush* redBrush = new QBrush(Qt::red);         // Collision brush color
    QBrush* blueBrush = new QBrush(Qt::blue);       // Default brush color
    QBrush* oBrush = new QBrush(Qt::yellow);
    QBrush* brush;                                  // Current brush in use

    int w, h;       // Obstacle dimensions set within constructor
};

#endif // OBSTACLE_H

