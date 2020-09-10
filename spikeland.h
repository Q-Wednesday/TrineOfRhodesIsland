#ifndef SPIKELAND_H
#define SPIKELAND_H
#include"Land.h"
//地刺
class SpikeLand:public Land{
public:
    SpikeLand(QObject* parent=nullptr);
    SpikeLand(int width,int height,int x,int y,int attack,QObject*parent=nullptr);
    ~SpikeLand();
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase)override;
    int get_attack();
private:
    int m_tick;//计数器，周期性造成伤害
    int m_attack;
};

#endif // SPIKELAND_H
