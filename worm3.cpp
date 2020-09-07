#include"worm3.h"
#include"airwall.h"
#include<QPainter>
#include<QDebug>
Worm3::Worm3(QObject*parent):Enemy(parent),m_boomed(false){
    m_hp=6;
    setPos(100,100);
    setData(detailType,worm3);
    m_attack=1;
    m_height=30;
    m_speedx=0;
    m_speedy=0;
    m_animemanager=new AnimationManager({":/images/worm3/idle/frame%1.png",":/images/worm3/move/frame%1.png"
                                         ,":/images/worm3/idle/frame%1.png",":/images/worm3/attack/frame%1.png",
                                        ":/images/worm3/die/frame%1.png"},
    {15,33,15,30,18},this);
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Worm3::attack);
    connect(m_animemanager,&AnimationManager::dieFinish,this,&Worm3::boom);
    m_orientation=1;
    AirWall* wall=new AirWall(this);

    QPainterPath shape;
    shape.addEllipse(-200,-200,400,400);//察觉范围

    wall->setShape(shape);
}


Worm3::Worm3(int x,int y,QObject*parent):Worm3(parent){
    setPos(x,y);
}


Worm3::~Worm3(){

}

QRectF Worm3::boundingRect() const{
    return  QRectF(-185,-270,370,370);
}


QPainterPath Worm3::shape() const{
    QPainterPath path;
    path.addRect(-55,-40,130,65);
    return path;
}

void Worm3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->drawImage(boundingRect(),m_animemanager->get_currentframe());
    painter->drawPath(shape());
}

void Worm3::attack(){
    if(m_attacking)
        return;
    m_animemanager->changeMode(attackMode);
    m_attacking=true;
}

void Worm3::auto_move(){
    m_speedx=0;
    for(auto collison:childItems()[0]->collidingItems()){
        if(collison->data(entityType)==characterType){
            if(collison->x()>x())
                m_speedx=1;
            else
                m_speedx=-1;
        }
    }
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

void Worm3::advance(int phase){
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
    m_animemanager->advance();
    fall();
    auto_move();

    update(boundingRect());
    qDebug()<<m_hp;
    if(m_boomed){
         emit deathSignal(this);
    }
    if(!check_alive()){
        m_animemanager->changeMode(dieMode);
    }

}

void Worm3::causeDamage(){
    if(collidesWithItem(m_target))
        m_target->set_hp(m_target->get_hp()-m_attack);
    m_attacking=false;
}

void Worm3::boom(){

       for(auto collison:childItems()[0]->collidingItems()){
           if(collison->data(entityType)==characterType||
                   collison->data(entityType)==landType||collison->data(entityType)==trapType){
           Entity* entity=static_cast<Entity*>(collison);
           entity->set_hp(entity->get_hp()-m_attack*5);
           }
       }
       qDebug()<<"boom";
       m_boomed=true;

}
