#include"character.h"
#include<QDebug>
Character::Character(QObject*parent):Entity(parent)


,m_jumping(true)
,m_doublejump(false)
,m_leftblocked(false)
,m_rightblocked(false)
,m_height(120)
,m_attacking(false)
,m_indeadzone(false)
,m_orientation(true)
,m_skillpoint(3){
    setData(entityType,characterType);
}

Character::~Character(){

}

void Character::fall(){
    //先标记为false,碰到了再标记true
    m_leftblocked=false;
    m_rightblocked=false;
    m_jumping=true;
    m_indeadzone=false;
    //然后检测是否左右被阻挡，是否站在地上
    for(auto collision:collidingItems()){

        if(collision->data(entityType)==landType){

            int height=collision->boundingRect().height();

            if(y()<collision->y()-height/2-m_height*1/2){
                //粗略的代码，需要调整。

                m_speedy=0;

                setY(collision->y()-height/2-m_height);

                m_jumping=false;
                m_doublejump=false;
                if( m_speedx==0){


                    m_animemanager->changeMode(relaxMode);
                }
                else if(m_speedx!=0){

                    m_animemanager->changeMode(moveMode);
                }
                continue;
            }
            else if(x()<collision->x()){
                m_rightblocked=true;

            }
            else if(x()>collision->x()){
                m_leftblocked=true;
            }
        }
        else if(collision->data(entityType)==deadZone){
            m_indeadzone=true;
        }
    }
    //跳跃中则播放跳跃动画
    if(m_jumping){


        m_animemanager->changeMode(jumpMode);
    }//对y轴的速度进行计算，最高为10
    if(m_ay<g)
        m_ay+=1;
    m_speedy+=m_ay;

    if(m_speedy>=10)
        m_speedy=10;


    setY(y()+m_speedy);

}

bool Character::can_move(){
    //需要重新填充


    if(m_speedx>0&& m_rightblocked)
        return false;
    else if(m_speedx<0&&m_leftblocked)
        return false;

    return true;

}

void Character::move(moveDirection d){


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

void Character::move(){
    if(!can_move())
        return;
    if(m_speedx>0){
        m_orientation=true;
       setTransform(QTransform().rotate(0,Qt::YAxis));
    }
    else if(m_speedx<0){
        m_orientation=false;
        setTransform(QTransform().rotate(180,Qt::YAxis));
    }
    else{
            if(!m_jumping)

                m_animemanager->changeMode(relaxMode);

    }
    setX(x()+m_speedx);
}

void Character::jump(){
    if(m_doublejump)
        return;

    m_speedy=-5;
    m_ay=-5;
    setY(y()-20);
    if(!m_jumping)
        m_jumping=true;
    else
        m_doublejump=true;


    m_animemanager->changeMode(jumpMode);
}

bool Character::check_alive(){
    if(m_indeadzone)
    {
        m_hp=0;
        m_indeadzone=false;
    }
    if(m_hp<=0)
        return false;
    return true;
}

AnimationManager* Character::get_animemanager(){
    return m_animemanager;
}

bool Character::get_orientation(){
    return m_orientation;
}

int Character::get_height(){
    return m_height;
}

void Character::skill(){

}

void Character::add_skill_point(){
    if(m_skillpoint>=5)
        return;
    m_skillpoint+=1;

}
