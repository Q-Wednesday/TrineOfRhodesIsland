#include"fireball.h"
#include<QPainter>
#include"constant.h"
#include<QDebug>
Fireball::Fireball(int attack,int speed,QObject* parent):Entity(parent),
    m_attack(attack),m_range(new AirWall(this)),m_tick(0){
    m_speedx=speed;
    m_speedy=-10.0;
    QPainterPath path;
    path.addEllipse(-50,-50,100,100);
    m_range->setShape(path);
    m_range->setVisible(false);
}

Fireball::~Fireball(){
    qDebug()<<"fireball delete";
}

QRectF Fireball::boundingRect() const{
    return QRectF(-20,-20,40,40);

}

QPainterPath Fireball::shape() const{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


void Fireball::advance(int phase){
    if(!phase)
        return;
    if(!m_enabled)
        return;
    m_tick++;
    //qDebug()<<m_tick;
    if(m_tick>=165)
        emit deathSignal(this);
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==enemyType||collision->data(entityType)==landType){
            //qDebug()<<"attack";
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack);
            boom();
        }

    }
    m_speedy+=0.5;

    //qDebug()<<m_speedy;
    setY(y()+m_speedy);
    setX(x()+m_speedx);
}

void Fireball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(boundingRect(),QImage(":/texture/fireball"));
}

void Fireball::boom(){
    for(auto collision:m_range->collidingItems()){
        if(collision->data(entityType)==characterType||collision->data(entityType)==landType){
            //qDebug()<<"attack";
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack);


        }
    }
    m_enabled=false;
    setVisible(false);
    emit deathSignal(this);
}

