#include"exusiai.h"
#include<QPainter>
#include"bullet.h"
#include<QDebug>
Exusiai::Exusiai(QObject* parent):Player(parent)
{
    setPos(100,100);
    setData(detailType,exusiai);
    m_animemanager=new AnimationManager({":/images/exusiai/relax/frame%1.png",
                                        ":/images/exusiai/move/frame%1.png",
                                        ":/images/exusiai/jump/frame%1.png",
                                        ":/images/exusiai/attack/frame%1.png","",
                                        ":/images/exusiai/attack/frame%1.png"},
    {17,18,1,16,0,16},this );
    m_ax=8;
    m_hp=10;
    m_maxhp=10;
    m_attack=2;
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Exusiai::shoot);
    connect(m_animemanager,&AnimationManager::skillFinish,this,&Exusiai::skillshot);
    m_attack_sound.setSource(QUrl("qrc:/sound/exusiai/attack"));
    m_jump_sound.setSource(QUrl("qrc:/sound/jump"));
    m_skill_sound.setSource(QUrl("qrc:/sound/exusiai/skill"));
}


Exusiai::~Exusiai(){
    qDebug()<<"delete exusiai";
}

void Exusiai::skill(){
    if(m_attacking||m_skillpoint<1)
        return;
    m_attacking=true;
    m_skillpoint-=1;
    m_animemanager->changeMode(skillMode);
    m_skill_sound.play();
}

void Exusiai::shoot(){
       m_attacking=false;
       Bullet* bullet;
       if(m_orientation){
           bullet=new Bullet(m_attack,15,this);
           bullet->setPos(x()+40,y()+40);

       }
       else{
           bullet=new Bullet(m_attack,-15,this);
           bullet->setPos(x()-40,y()+40);
       }
       emit addEntity(bullet);
}

void Exusiai::skillshot(){
    m_attacking=false;
    for(int i=0;i<3;i++){
        Bullet* bullet;
        if(m_orientation){
            bullet=new Bullet(m_attack*2,20,this);
            bullet->setPos(x()+40,y()+20+20*i);

        }
        else{
            bullet=new Bullet(m_attack*2,-20,this);
            bullet->setPos(x()-40,y()+20+20*i);
        }
        emit addEntity(bullet);
    }
}
