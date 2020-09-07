#include"deadzone.h"
#include"constant.h"
#include<QPainter>
DeadZone::DeadZone(int width,int height,int x,int y,QObject*parent):
    Land(width,height,x,y,parent){
    setData(entityType,deadZone);
}

DeadZone::~DeadZone(){}

QRectF DeadZone::boundingRect() const{
    return  QRectF(-m_width/2,-m_height/2,m_width,m_height);
}


QPainterPath DeadZone::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void DeadZone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(boundingRect());
}
