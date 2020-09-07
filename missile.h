#ifndef MISSILE_H
#define MISSILE_H
#include"entity.h"
#include"airwall.h"
//导弹类，可以以抛物线形式飞行的物体
class Missile:public Entity{
public:
    Missile(int attack,int speed,QObject* parent=nullptr);
    ~Missile();
    void advance(int phase)override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;


private:
    int m_attack;
    int m_tick;

};
//可以接收贴图改变，目标类型改变
#endif // MISSILE_H
