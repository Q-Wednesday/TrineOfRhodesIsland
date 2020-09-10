#include"hidentrap.h"
#include"constant.h"
#include<QPainter>
#include"missile.h"
HidenTrap::HidenTrap(int x,int y,int T,QObject*parent):
    Trap(100,100,x,y,T,parent),m_launched(0){
    setData(detailType,hidenTrap);
    m_range=new AirWall(this);
    QPainterPath shape;
    shape.addRect(-100,-100,200,200);
    m_range->setShape(shape);

    m_hp=5;
    m_texture=QPixmap(":/texture/normal");
}


HidenTrap::~HidenTrap(){

}

QRectF HidenTrap::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}


QPainterPath HidenTrap::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void HidenTrap::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawPixmap(boundingRect(),m_texture,QRect(0,0,100,100));
}


void HidenTrap::launch(){
    if(m_launched>=3)
        return;

    Missile* missile1=new Missile(5,10,this);
    Missile* missile2=new Missile(5,-10,this);
    missile1->setPos(x(),y()-60);
    missile2->setPos(x(),y()-60);
    emit addEntity(missile1);
    emit addEntity(missile2);
}

void HidenTrap::advance(int phase){
    if(!phase)
        return;

    m_tick=(m_tick+1)%m_T;
    if(m_tick!=0)
        return;
    if(m_hp<=0){
        emit deathSignal(this);
    }
    for(auto collision:m_range->collidingItems()){
        if(collision->data(entityType)==characterType){
            launch();
            //qDebug()<<"launch";
        }
    }
}


