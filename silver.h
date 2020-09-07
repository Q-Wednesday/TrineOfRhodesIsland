#ifndef SILVER_H
#define SILVER_H
#include"character.h"
class Silver:public Character{
public:
    Silver(QObject* parent=nullptr);
    ~Silver();
    void attack() override;
    void advance(int phase) override;
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void reset();
public slots:
    void causeDamage();
public:
    Entity* m_target;
};

#endif // SILVER_H
