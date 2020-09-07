#ifndef EXUSIAI_H
#define EXUSIAI_H
#include"character.h"
class Exusiai:public Character{
public:
    Exusiai(QObject*parent=nullptr);
    ~Exusiai();
    void attack() override;
    void advance(int phase)override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void skill() override;
public slots:
    void shoot();
    void skillshot();
};

#endif // EXUSIAI_H
