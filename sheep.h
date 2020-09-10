#ifndef SHEEP_H
#define SHEEP_H
#include"player.h"
//移动速度较慢，攻击力中等，进行抛物线的群攻，可以过墙打。技能是向前后各发四枚火球
class Sheep:public Player{
public:
    Sheep(QObject* parent=nullptr);
    ~Sheep();
    void skill() override;
public slots:
    void shoot();
    void skillshot();

};

#endif // SHEEP_H
