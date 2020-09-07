#ifndef AIRWALL_H
#define AIRWALL_H
#include<QGraphicsItem>
class AirWall:public QGraphicsItem{
public:
    AirWall(QGraphicsItem*parent=nullptr);
    ~AirWall();
    QRectF boundingRect()const override;
    QPainterPath shape() const override;
    void paint(QPainter*painter,const QStyleOptionGraphicsItem*option,QWidget*widget) override;
    void setShape(QPainterPath shape);

protected:

    QPainterPath m_shape;


};

#endif // AIRWALL_H
