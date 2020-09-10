#include"sheep.h"
#include<QPainter>
#include"fireball.h"
#include"constant.h"
#include<QDebug>
Sheep::Sheep(QObject*parent):Player(parent){
    setPos(100,100);
    setData(detailType,sheep);
    m_animemanager=new AnimationManager({":/images/sheep/relax/frame%1.png",":/images/sheep/move/frame%1.png"
                                         ,":/images/sheep/jump/frame%1.png",":/images/sheep/attack/frame%1.png","",
                                        ":/images/sheep/skill/frame%1.png"},
    {27,16,1,20,0,24},this);
    m_ax=4;
    m_hp=10;
    m_maxhp=10;
    m_attack=3;
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Sheep::shoot);
    connect(m_animemanager,&AnimationManager::skillFinish,this,&Sheep::skillshot);
    m_attack_sound.setSource(QUrl("qrc:/sound/sheep/attack"));
    m_jump_sound.setSource(QUrl("qrc:/sound/jump"));
    m_skill_sound.setSource(QUrl("qrc:/sound/sheep/skill"));
}

Sheep::~Sheep(){
    qDebug()<<"delete sheep";
}

void Sheep::skill(){
    if(m_attacking||m_skillpoint<3)
        return;
    m_attacking=true;
    m_skillpoint-=3;
    m_animemanager->changeMode(skillMode);
    m_skill_sound.play();
}

void Sheep::shoot(){
    m_attacking=false;
    Fireball* fireball;
    if(m_orientation){
       fireball=new Fireball(m_attack,10,this);
       fireball->setPos(x()+40,y()+40);

    }
    else{

        fireball=new Fireball(m_attack,-10,this);
        fireball->setPos(x()-40,y()+40);

    }
    emit addEntity(fireball);
}

void Sheep::skillshot(){
    m_attacking=false;
    Fireball* fireball1=new Fireball(m_attack*2,10,this);
    fireball1->setPos(x()+40,y()+40);

    Fireball* fireball2=new Fireball(m_attack*2,8,this);
    fireball2->setPos(x()+40,y());

    Fireball* fireball3=new Fireball(m_attack*2,-10,this);
    fireball3->setPos(x()-40,y()+40);

    Fireball* fireball4=new Fireball(m_attack*2,-8,this);
    fireball4->setPos(x()-40,y());

    emit addEntity(fireball1);
    emit addEntity(fireball2);
    emit addEntity(fireball3);
    emit addEntity(fireball4);
}
