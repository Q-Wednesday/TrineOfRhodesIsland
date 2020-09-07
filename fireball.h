#ifndef FIREBALL_H
#define FIREBALL_H
#include"entity.h"
#include"airwall.h"
class Fireball:public Entity{
public:
    Fireball(int attack,int speed,QObject* parent=nullptr);
    ~Fireball();
    void advance(int phase)override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void boom();
private:
    int m_attack;
    AirWall* m_range;//爆炸范围
    QImage* m_texture;
    int m_tick;
};

#endif // FIREBALL_H
