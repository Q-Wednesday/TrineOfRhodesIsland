#ifndef FLOWER_H
#define FLOWER_H
#include"prop.h"
//吃到以后恢复少量生命，获得三点技力，并立马释放一次技能
class Flower:public Prop{
public:
    Flower(int x,int y,QObject*parent=nullptr);
    ~Flower();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
};

#endif // FLOWER_H
