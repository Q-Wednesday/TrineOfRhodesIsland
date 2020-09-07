#ifndef SPRINGLAND_H
#define SPRINGLAND_H
#include"constant.h"
#include"land.h"
class SpringLand:public Land{
public:
    SpringLand(int x,int y,QObject* parent=nullptr);
    ~SpringLand();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
};

#endif // SPRINGLAND_H
