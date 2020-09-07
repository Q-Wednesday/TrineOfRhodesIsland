#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include"entity.h"
#include"constant.h"
class CheckPoint:public Entity{
    Q_OBJECT
public:
    CheckPoint(int x,int y,QObject* parent =nullptr);
    ~CheckPoint();
    QRectF boundingRect() const override;
    QPainterPath shape()const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
signals:
    void achieve(CheckPoint*);

};

#endif // CHECKPOINT_H
