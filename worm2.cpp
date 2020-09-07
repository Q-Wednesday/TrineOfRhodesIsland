#include"worm2.h"
#include<QPainter>
#include"airwall.h"
#include"missile.h"
#include<QDebug>
Worm2::Worm2(QObject*parent):Enemy(parent){
    m_hp=6;
    setPos(100,100);
    setData(detailType,worm2);
    m_attack=2;
    m_height=30;
    m_speedx=-1;
    m_speedy=0;
    m_animemanager=new AnimationManager({":/images/worm2/idle/frame%1.png",":/images/worm2/idle/frame%1.png"
                                         ,":/images/worm2/idle/frame%1.png",":/images/worm2/attack/frame%1.png"},
    {11,11,11,40},this);
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Worm2::launch);
    m_orientation=1;
    AirWall* wall=new AirWall(this);

    QPainterPath shape;
    shape.addEllipse(-300,-300,600,600);

    wall->setShape(shape);
}

Worm2::Worm2(int x,int y,QObject*parent):Worm2(parent){
    setPos(x,y);
}

Worm2::~Worm2(){}

QRectF Worm2::boundingRect() const{
    return  QRectF(-185,-270,370,370);
}

QPainterPath Worm2::shape() const{
    QPainterPath path;
    path.addRect(-55,-40,130,65);
    return path;
}

void Worm2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(boundingRect(),m_animemanager->get_currentframe());
    painter->drawPath(shape());
 }

void Worm2::attack(){
    if(m_attacking)
        return;
    m_animemanager->changeMode(attackMode);
    m_attacking=true;
}

void Worm2::auto_move(){
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
       m_orientation=1;
    }
    else if(m_speedx<0){
        setTransform(QTransform().rotate(180,Qt::YAxis));
        m_orientation=0;
    }
}

void Worm2::advance(int phase){
    if(!phase)
        return;
    for(auto collision:childItems()[0]->collidingItems())
    {
        if(collision->data(entityType)==characterType){
            Entity* entity=static_cast<Entity*>(collision);
            m_target=entity;
            if(m_target->x()>x()){
                m_orientation=1;
                setTransform(QTransform().rotate(0,Qt::YAxis));
                m_speedx=abs(m_speedx);
            }
            else{
                m_orientation=0;
                setTransform(QTransform().rotate(180,Qt::YAxis));
                m_speedx=-abs(m_speedx);
            }
            attack();
            //qDebug()<<"attack";
        }
    }
    Enemy::advance(phase);
}
void Worm2::launch(){
    m_attacking=false;
    Missile* missile;
    if(m_orientation)
    {
        missile=new Missile(m_attack,10,this);
        missile->setPos(x()+40,y()-40);
    }
    else{
        missile=new Missile(m_attack,-10,this);
        missile->setPos(x()-40,y()-40);
    }
    emit addEntity(missile);

}
