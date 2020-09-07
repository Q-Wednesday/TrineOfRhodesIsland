#ifndef BULLET_H
#define BULLET_H
#include"entity.h"
class Bullet:public Entity{
public:
    Bullet(int attack,int speed,QObject* parent=nullptr);
    ~Bullet();
    void advance(int phase)override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;

private:
    int m_attack;
    int m_tick;//删除倒计时，只允许存在五秒


};

#endif // BULLET_H
