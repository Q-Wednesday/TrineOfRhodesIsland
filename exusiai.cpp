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
                                        ":/images/exusiai/attack/frame%1.png"},
    {17,18,1,16},this );
    m_ax=8;
    m_hp=10;
    m_maxhp=10;
    m_attack=2;
    connect(m_animemanager,&AnimationManager::attackFinish,this,&Exusiai::shoot);
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

    painter->drawPath(shape());

    painter->setBrush(QBrush(Qt::red));
    painter->drawRect(-186,-184,372*m_hp/m_maxhp,10);
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
