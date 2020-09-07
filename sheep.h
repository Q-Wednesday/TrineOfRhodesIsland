#ifndef SHEEP_H
#define SHEEP_H
#include"character.h"
//移动速度较慢，攻击力中等，进行抛物线的群攻，可以过墙打。技能是向前后各发四枚火球
class Sheep:public Character{
public:
    Sheep(QObject* parent=nullptr);
    ~Sheep();
    void attack() override;
    void advance(int phase) override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void reset();
    void skill() override;

public slots:
    void shoot();
    void skillshot();

};

#endif // SHEEP_H
