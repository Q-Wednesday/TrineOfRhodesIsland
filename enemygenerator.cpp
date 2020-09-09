#include"enemygenerator.h"
#include"worm1.h"
#include"worm2.h"
#include<QPainter>
#include<QDebug>
EnemyGenerator::EnemyGenerator(int x,int y,EnemyType type,int T,QObject* parent):
   Trap(100,40,x,y,T,parent),m_type(type),m_generated(0){
    setData(detailType,enemyGenerator);
    m_range=new AirWall(this);
    QPainterPath shape;
    shape.addRect(-200,-200,400,400);
    m_range->setShape(shape);

    m_hp=10;
    m_texture=QPixmap(":/texture/generator");
}


EnemyGenerator::~EnemyGenerator(){

}

QRectF EnemyGenerator::boundingRect() const{
    return QRectF(-m_width/2,-m_height/2,m_width,m_height);
}

QPainterPath EnemyGenerator::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}


void EnemyGenerator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->drawPixmap(boundingRect(),m_texture,QRect(0,0,100,40));


    painter->restore();
}


void EnemyGenerator::launch(){
    if(m_generated>=3)
        return;
    switch (m_type) {
    case worm1:{
        Worm1* worm1=new Worm1(x(),y()-80);
        emit addEntity(worm1);
        break;
    }
    case worm2:{
        Worm2* worm2=new Worm2(x(),y()-80);
        emit addEntity(worm2);
        break;
    }

    }
    m_generated++;
}

void EnemyGenerator::advance(int phase){
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
EnemyType  EnemyGenerator::get_type(){
    return m_type;
}
