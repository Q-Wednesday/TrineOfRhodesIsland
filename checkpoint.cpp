#include"checkpoint.h"
#include<QPainter>
#include<QtDebug>
CheckPoint::CheckPoint(int x,int y,bool is_destination,QObject* parent):Entity(parent),m_destination(is_destination){
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
            if(m_destination)
                emit achievefinal();
            else
                emit achieve(this);
        }
    }
}

bool CheckPoint::is_destination(){
    return  m_destination;
}
