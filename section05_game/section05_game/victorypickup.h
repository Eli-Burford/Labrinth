#ifndef VICTORYPICKUP_H
#define VICTORYPICKUP_H
#include "puck.h"

class victoryPickup : public Puck
{
    Q_OBJECT
public:
    explicit victoryPickup(QGraphicsItem *parent = nullptr);
    ~victoryPickup() override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    void advance(int phase) override;

signals:
    void hit();
public slots:
};

#endif // VICTORYPICKUP_H
