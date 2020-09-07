#include"worm1.h"
#include<QPainter>
#include<QDebug>
Worm1::Worm1(QObject*parent):Enemy(parent){
    m_hp=3;
    setPos(100,100);
    setData(detailType,worm1);
    m_attack=1;
    m_height=30;
    m_speedx=-2;
    m_speedy=0;
    m_animemanager=new AnimationManager({":/images/worm1/idle/frame%1.png",":/images/worm1/idle/frame%1.png"
                                         ,":/images/worm1/idle/frame%1.png",":/images/worm1/attack/frame%1.png"},
    {11,11,11,12},this);
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Worm1::causeDamage);
}
Worm1::Worm1(int x,int y,QObject*parent):Worm1(parent){
    setPos(x,y);

}

Worm1::~Worm1(){

}

QRectF Worm1::boundingRect() const{
    return  QRectF(-185,-270,370,370);
}

QPainterPath Worm1::shape() const{
    QPainterPath path;
    path.addRect(-55,-40,110,65);
    return path;
}

void Worm1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
   painter->drawImage(boundingRect(),m_animemanager->get_currentframe());
   painter->drawPath(shape());
}

void Worm1::attack(){
    if(m_attacking)
        return;
    m_animemanager->changeMode(attackMode);

    m_attacking=true;
}

void Worm1::auto_move(){
    if(m_animemanager->get_mode()!=attackMode &&m_animemanager->get_mode()!=jumpMode){
        if(can_move()){
            setX(x()+m_speedx);
        }
        else{
            m_speedx=-m_speedx;
        }
    }
    if(m_speedx>0){
       setTransform(QTransform().rotate(0,Qt::YAxis));
    }
    else if(m_speedx<0){
        setTransform(QTransform().rotate(180,Qt::YAxis));
    }
}

void Worm1::advance(int phase){
    if(!phase)
        return;
    for(auto collision:collidingItems()){
        if(collision->data(entityType)==characterType){
            //qDebug()<<"attack";
            m_target=static_cast<Entity*>(collision);
            attack();
        }
    }
    //qDebug()<<m_hp;
    Enemy::advance(phase);


}

void Worm1::causeDamage(){
    if(collidesWithItem(m_target))
        m_target->set_hp(m_target->get_hp()-m_attack);
    m_attacking=false;

}
