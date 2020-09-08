#include"normalland.h"
#include<QPainter>
#include"constant.h"
NormalLand::NormalLand(QObject*parent):Land(parent){
    setData(detailType,normalLand);
    m_texture=QPixmap(":/texture/normal");
}

NormalLand::~NormalLand(){

}

NormalLand::NormalLand(int width,int height,int x,int y,QObject* parent):Land(width,height,x,y,parent){
    setData(detailType,normalLand);
    m_texture=QPixmap(":/texture/normal");
}



QRectF NormalLand::boundingRect() const{
    return  QRectF(-m_width/2,-m_height/2,m_width,m_height);
}


QPainterPath NormalLand::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void NormalLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->setBrush(m_texture);
    //painter->drawTiledPixmap(boundingRect(),m_texture);
    painter->drawRect(boundingRect());
    painter->restore();
}
