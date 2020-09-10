#include"land.h"
#include"constant.h"

#include<QDebug>
#include<QPainter>

Land::Land(QObject* parent):Entity(parent),
m_height(100),m_width(100){
    setData(entityType,landType);

}

Land::~Land(){

}

Land::Land(int width,int height,int x,int y,QObject* parent):Entity(parent),
m_height(height),
m_width(width){
    setPos(x,y);
    setData(entityType,landType);
    setAcceptDrops(true);
}

int Land::get_height(){
    return m_height;
}



int Land::get_width(){
    return m_width;
}

void Land::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setBrush(m_texture);

    painter->drawRect(boundingRect());
    painter->restore();
}


QPainterPath Land::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


QRectF Land::boundingRect() const{
    return  QRectF(-m_width/2,-m_height/2,m_width,m_height);
}
