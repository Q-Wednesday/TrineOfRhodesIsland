#ifndef WORM2_H
#define WORM2_H
#include"enemy.h"
class Worm2:public Enemy{
public:
    Worm2(QObject*parent=nullptr);
    Worm2(int x,int y,QObject*parent=nullptr);
    ~Worm2();
    void auto_move() override;
    void attack() override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void advance(int phase) override;
public slots:
    void launch() ;
private:
    Entity* m_target;
};
#endif // WORM2_H
