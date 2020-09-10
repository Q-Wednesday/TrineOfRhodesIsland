#include"deadzone.h"
#include"constant.h"
#include<QPainter>
DeadZone::DeadZone(int width,int height,int x,int y,QObject*parent):
    AirWall(){
    setData(entityType,deadZone);
    QPainterPath shape;
    shape.addRect(x,y,width,height);
    setShape(shape);
}

DeadZone::~DeadZone(){}


void DeadZone::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawRect(boundingRect());
}
