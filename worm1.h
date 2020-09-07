#ifndef WORM1_H
#define WORM1_H
#include"enemy.h"
class Worm1:public Enemy{
public:
    Worm1(QObject*parent=nullptr);
    Worm1(int x,int y,QObject*parent=nullptr);
    ~Worm1();
    void auto_move() override;
    void attack() override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase) override;
public slots:
    void causeDamage() ;
};

#endif // WORM1_H
