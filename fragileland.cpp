#include"fragileland.h"
#include"constant.h"
#include<QPainter>
FragileLand::FragileLand(int width,int height,int x,int y,QObject*parent):
    Land(width,height,x,y,parent){
    setData(detailType,fragileLand);
    m_maxhp=10;
    m_hp=10;
}

FragileLand::~FragileLand(){

}


QRectF FragileLand::boundingRect() const{
    return  QRectF(-m_width/2,-m_height/2,m_width,m_height);
}


QPainterPath FragileLand::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void FragileLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    if(m_hp>=5)
        painter->setBrush(QBrush(Qt::red));
    else
        painter->setBrush(QBrush(QColor("#FFC0CB")));
    painter->drawRect(boundingRect());
    painter->restore();
}

void FragileLand::advance(int phase){
    if(!phase)
        return;
    if(m_hp<=0)
        emit deathSignal(this);
    update(boundingRect());
}
