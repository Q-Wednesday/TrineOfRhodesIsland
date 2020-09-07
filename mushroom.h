#ifndef MUSHROOM_H
#define MUSHROOM_H
#include"prop.h"
class Mushroom:public Prop{
public:
    Mushroom(int x,int y,QObject* parent=nullptr);
    ~Mushroom();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
};

#endif // MUSHROOM_H
