#include"exusiai.h"
#include<QPainter>
#include"bullet.h"
#include<QDebug>
Exusiai::Exusiai(QObject* parent):Character(parent)
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


QRectF Exusiai::boundingRect() const{
    return QRectF(-186,-184,372,368);
}


QPainterPath Exusiai::shape() const{
    QPainterPath path;
    path.addRect(-36,-34,80,150);


    return  path;
}


void Exusiai::attack(){
    if(m_attacking)
        return;
    m_attacking=true;
    m_animemanager->changeMode(attackMode);
    m_attack_sound.play();
}
void Exusiai::skill(){
    if(m_attacking||m_skillpoint<1)
        return;
    m_attacking=true;
    m_skillpoint-=1;
    m_animemanager->changeMode(skillMode);
    m_skill_sound.play();
}
void Exusiai::advance(int phase){
    if(!phase)
        return;
    if(!m_enabled)
        return;
    m_animemanager->advance();
    fall();
    move();
    //qDebug()<<m_hp;
    if(!check_alive()){
        setEnabled(false);
        setAdvanceEnanbled(false);

        emit deathSignal(this);
    }



    update(boundingRect());
}

void Exusiai::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    painter->drawImage(boundingRect(),m_animemanager->get_currentframe());

    //painter->drawPath(shape());

    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-136,-124,272*m_hp/m_maxhp,10);
    for(int i=0;i<m_skillpoint;i++){
        painter->setBrush(QBrush(Qt::blue));
        painter->drawEllipse(-136+20*i,-104,10,10);
    }
    painter->restore();
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
