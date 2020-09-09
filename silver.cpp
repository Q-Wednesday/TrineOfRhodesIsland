#include"silver.h"
#include<QPainter>
#include<QDebug>
#include"airwall.h"
Silver::Silver(QObject* parent):Character(parent)
,m_target(nullptr){
    setPos(100,100);
    setData(detailType,silver);
    m_animemanager=new AnimationManager({":/images/silver/relax/frame%1.png",":/images/silver/move/frame%1.png"
                                         ,":/images/silver/jump/frame%1.png",":/images/silver/attack/frame%1.png","",
                                        ":/images/silver/skill/frame%1.png"},
    {17,36,1,19,0,40},this);
    m_ax=5;
    m_hp=10;
    m_maxhp=10;
    m_attack=5;
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Silver::causeDamage);
    connect(m_animemanager,&AnimationManager::skillFinish,this,&Silver::skillDamage);
    AirWall* wall=new AirWall(this);
    wall->setVisible(false);
    QPainterPath shape;
    shape.addRect(-36,-34,80,150);
    shape.addRect(44,0,110,110);
    wall->setShape(shape);
    m_attack_sound.setSource(QUrl("qrc:/sound/silver/attack"));
    m_jump_sound.setSource(QUrl("qrc:/sound/jump"));
    m_skill_sound.setSource(QUrl("qrc:/sound/silver/skill"));
}

Silver::~Silver(){
    qDebug()<<"delete silver";
}


QRectF Silver::boundingRect() const{
    return QRectF(-186,-184,372,368);

}
QPainterPath Silver::shape() const{
    QPainterPath path;
    path.addRect(-36,-34,80,150);


    return  path;
}


void Silver::attack(){
    if(m_attacking)
        return;
    m_attack_sound.play();
    m_attacking=true;
    m_animemanager->changeMode(attackMode);
}
void Silver::skill(){
    if(m_attacking||m_skillpoint<2)
        return;

    m_attacking=true;
    m_skillpoint-=2;
    m_animemanager->changeMode(skillMode);
    m_skill_sound.play();
}
void Silver::advance(int phase){
    if(!phase)
        return;

    if(!m_enabled)
        return;

    m_animemanager->advance();
    fall();
    move();
    //qDebug()<<m_hp;
    //qDebug()<<"update"<<m_animationframe;
    if(!check_alive()){
        setEnabled(false);
        setAdvanceEnanbled(false);


        emit deathSignal(this);
    }
    update(boundingRect());
}

void Silver::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
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

void Silver::causeDamage(){

    for(auto collision:childItems()[0]->collidingItems()){
        if(collision->data(entityType)==enemyType||collision->data(entityType)==trapType){
            m_target=static_cast<Entity*>(collision);
        }
        else if(collision->data(entityType)==landType&&collision->data(detailType)==fragileLand){
            m_target=static_cast<Entity*>(collision);
        }
    }

    if(m_target){
        m_target->set_hp(m_target->get_hp()-m_attack);
    }
    m_target=nullptr;
    m_attacking=false;
}
void Silver::skillDamage(){
    for(auto collision:childItems()[0]->collidingItems()){
        if(collision->data(entityType)==enemyType||collision->data(entityType)==trapType){
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack*2);
        }
        else if(collision->data(entityType)==landType&&collision->data(detailType)==fragileLand){
            Entity* entity=static_cast<Entity*>(collision);
            entity->set_hp(entity->get_hp()-m_attack*2);
        }
    }


    m_attacking=false;
}
