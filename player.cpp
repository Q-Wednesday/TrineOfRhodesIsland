#include"player.h"
#include<QPainter>
Player::Player(QObject* parent):Character(parent),
    m_skillpoint(3)
{
    setData(entityType,characterType);
}

Player::~Player(){

}

void Player::move(moveDirection d){
    if(!m_jumping){
        //qDebug()<<"moveanime";


        m_animemanager->changeMode(moveMode);
    }
    int max_speed=2*m_ax;
    switch (d) {
    case moveRight:
    {
         m_speedx=(m_speedx>max_speed)?max_speed:(m_speedx+m_ax);
        break;
    }
    case moveLeft:
    {
        m_speedx=(m_speedx<-max_speed)?-max_speed:(m_speedx-m_ax);
        break;
    }
    case cancelRight:
    {
        if(m_speedx>0)
            m_speedx=0;
        break;
    }
    case cancelLeft:
    {
        if(m_speedx<0)
            m_speedx=0;
        break;
    }

    }
}


void Player::add_skill_point(int p){
    m_skillpoint+=p;
    if(m_skillpoint>10)
        m_skillpoint=10;
}

void Player::jump(){
    if(m_doublejump)
        return;
    m_jump_sound.play();
    m_speedy=-5;
    m_ay=-5;
    setY(y()-20);
    if(!m_jumping)
        m_jumping=true;
    else
        m_doublejump=true;


    m_animemanager->changeMode(jumpMode);
}

void Player::advance(int phase){
    if(!phase)
        return;
    if(!m_enabled)
        return;
    m_animemanager->advance();
    fall();
    Character::move();
    if(!check_alive()){
        setEnabled(false);
        setAdvanceEnanbled(false);

        emit deathSignal(this);
    }
    update(boundingRect());
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
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

QRectF Player::boundingRect() const{
    return QRectF(-186,-184,372,368);
}

QPainterPath Player::shape() const{
    QPainterPath path;
    path.addRect(-36,-34,80,150);


    return  path;
}


void Player::attack(){
    if(m_attacking)
        return;
    m_attacking=true;
    m_animemanager->changeMode(attackMode);
    m_attack_sound.play();
}
