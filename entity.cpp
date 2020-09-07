#include"entity.h"
#include"constant.h"
#include<QCursor>
#include<QEvent>
#include<QApplication>
#include<QGraphicsSceneMouseEvent>
Entity::Entity(QObject* parent):QObject(parent),
m_hp(0),m_weight(0)
,m_speedx(0),m_speedy(0),m_ay(g),m_ax(0),m_candrag(false)
,m_enabled(true),m_maxhp(0)
{

}


Entity::~Entity(){


}

void Entity::set_hp(int hp){
    m_hp=hp;
}


void Entity::set_weight(int weight){
    m_weight=weight;
}

int Entity::get_hp(){
    return m_hp;
}


int Entity::get_weight(){
    return m_weight;
}


void Entity::set_can_drag(bool on){
    m_candrag=on;
}

void Entity::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;

    setCursor(Qt::ClosedHandCursor);
}

void Entity::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton))
        .length() < QApplication::startDragDistance()) {
        return;
    }


    setPos(event->scenePos());
}

void Entity::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if(!m_candrag)
        return;
    setCursor(Qt::OpenHandCursor);
}

void Entity::setAdvanceEnanbled(bool on){
    m_enabled=on;
}

void Entity::set_speed(int speed){
    m_speedx=speed;
}

int Entity::get_maxhp(){
    return m_maxhp;
}
