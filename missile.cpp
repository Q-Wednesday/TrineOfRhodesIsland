#include"missile.h"
#include<QPainter>
#include"constant.h"
#include<QDebug>
Missile::Missile(int attack,int speed,QObject* parent):Entity(parent),
m_attack(attack),m_tick(0){
    m_speedx=speed;
    m_speedy=-10.0;
}

Missile::~Missile(){

    qDebug()<<"missile delete";
}

QRectF Missile::boundingRect() const{
    return QRectF(-10,-10,20,20);
}


QPainterPath Missile::shape() const{
    QPainterPath path;
    path.addRect(QRectF(-10,-10,20,20));
    return path;
}


void Missile::advance(int phase){
    if(!phase)
        return;
    if(!m_enabled)
        return;
    m_tick++;
    if(m_tick>=165)
        emit deathSignal(this);
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType||collision->data(entityType)==landType){
            //qDebug()<<"attack";
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack);

            m_enabled=false;
            setVisible(false);
            emit deathSignal(this);

        }

    }
    m_speedy+=0.5;
    //setTransform(QTransform().rotate(qAtan2(m_speedy,m_speedx),Qt::ZAxis));
    //qDebug()<<m_speedy;
    setY(y()+m_speedy);
    setX(x()+m_speedx);
}



void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();


     painter->setBrush(QBrush(Qt::black));
     painter->drawEllipse(QRectF(-10,-10,20,20));


    painter->restore();
}
