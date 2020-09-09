#include"checkpoint.h"
#include<QPainter>
#include<QtDebug>
CheckPoint::CheckPoint(int x,int y,bool is_destination,QObject* parent):Entity(parent)
  ,m_destination(is_destination)
,m_checked(false){
    setPos(x,y);
    setData(entityType,checkPoint);
    m_checked_texture=QImage(":/texture/check");
    m_unchecked_texture=QImage(":/texture/uncheck");
   // qDebug()<<"create checkpoint";
}


CheckPoint::~CheckPoint(){

}

QRectF CheckPoint::boundingRect() const{
    return QRectF(-100,-100,200,200);


}


QPainterPath CheckPoint::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return  path;
}

void CheckPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(m_checked)
        painter->drawImage(boundingRect(),m_checked_texture);
    else
        painter->drawImage(boundingRect(),m_unchecked_texture);

}

void CheckPoint::advance(int phase){
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            //m_checked=true;
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

bool CheckPoint::is_checked(){
    return m_checked;
}

void  CheckPoint::set_checked(bool on){
    m_checked=true;
}
