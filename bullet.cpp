#include"bullet.h"
#include"constant.h"
#include<QPainter>
#include<QDebug>
Bullet::Bullet(int attack,int speed,QObject* parent):Entity(parent)
  ,m_attack(attack)
,m_tick(0)
{

    m_speedx=speed;
};

Bullet::~Bullet(){

}
QRectF Bullet::boundingRect() const{
    return QRectF(-10,5,20,10);
}

QPainterPath Bullet::shape() const{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
void Bullet::advance(int phase){
    if(!phase)
        return;
    if(!m_enabled)
        return;
    m_tick+=1;
    //qDebug()<<m_tick;
    if(m_tick>=165)
        emit deathSignal(this);
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==enemyType||collision->data(entityType)==landType
                ||collision->data(entityType)==trapType){
            //qDebug()<<"attack";
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack);
            m_enabled=false;
            setVisible(false);
            emit deathSignal(this);

        }


    }
    setX(x()+m_speedx);
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    painter->save();

    painter->drawImage(boundingRect(),QImage(":/texture/bullet"));
    painter->restore();
}
