#include"fragileland.h"
#include"constant.h"
#include<QPainter>
FragileLand::FragileLand(int width,int height,int x,int y,QObject*parent):
    Land(width,height,x,y,parent){
    setData(detailType,fragileLand);
    m_maxhp=10;
    m_hp=8;
    m_texture=QPixmap(":/texture/unbroken");
    m_broken_texture=QPixmap(":/texture/broken");
}

FragileLand::~FragileLand(){

}




void FragileLand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    if(m_hp>=5)
        painter->setBrush(m_texture);
    else
        painter->setBrush(QBrush(m_broken_texture));
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
