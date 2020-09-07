#include"checkpoint.h"
#include<QPainter>
#include<QtDebug>
CheckPoint::CheckPoint(int x,int y,QObject* parent):Entity(parent){
    setPos(x,y);
    setData(entityType,checkPoint);
   // qDebug()<<"create checkpoint";
}


CheckPoint::~CheckPoint(){

}

QRectF CheckPoint::boundingRect() const{
    return QRectF(-50,-50,100,100);


}


QPainterPath CheckPoint::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return  path;
}

void CheckPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPath(shape());
}

void CheckPoint::advance(int phase){
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            emit achieve(this);
        }
    }
}
