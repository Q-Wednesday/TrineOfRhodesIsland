#include"airwall.h"
#include<QPainter>

#include<QDebug>
AirWall::~AirWall(){

}

AirWall:: AirWall(QGraphicsItem*parent):QGraphicsItem(parent){
   // qDebug()<<"create";
};

QRectF AirWall::boundingRect() const{
    return m_shape.boundingRect();
}

QPainterPath AirWall::shape() const{
    return m_shape;
}

void AirWall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
   // qDebug()<<"paint air";
    painter->save();
    //painter->setBrush(QBrush(Qt::red));
    painter->drawPath(m_shape);
    painter->restore();
}

void AirWall::setShape(QPainterPath shape){
    m_shape=shape;
}





