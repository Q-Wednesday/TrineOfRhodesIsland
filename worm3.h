#ifndef WORM3_H
#define WORM3_H
#include"enemy.h"
//自爆虫，有察觉范围，平常静止，角色进到察觉范围内虫出动，并进行普通攻击，速度慢攻击低
//但是被杀死后会自爆，对察觉范围内敌人造成五倍攻击力伤害
class Worm3:public Enemy{
public:
    Worm3(QObject*parent=nullptr);
    Worm3(int x,int y,QObject*parent=nullptr);
    ~Worm3();
    void auto_move() override;
    void attack() override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase) override;
public slots:
    void causeDamage() ;
    void boom();
private:
    bool m_boomed;
};

#endif // WORM3_H
