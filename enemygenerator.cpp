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


EnemyType  EnemyGenerator::get_type(){
    return m_type;
}
